#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ostream>
#include <map>
#include <set>
#include <list>
#include <math.h>
#include <time.h>
#include "board.h"
#include "IO_interface.hpp"
#include "output_gds.hpp"
#include "initVar.hpp"
#include "gridUnit.hpp"

using namespace std;

std::string& trim(std::string &s)
{
    if (s.empty())
    {
        return s;
    }

    s.erase(0,s.find_first_not_of('\r'));
    s.erase(s.find_last_not_of('\r') + 1);

    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

bool Satisfiable(string &sat_out){
    ifstream fin;
    fin.open(sat_out, ios::in);
    string strLine = "";
    while (!fin.eof())
    {
        std::getline(fin, strLine);
        string str = strLine;
        if (str.find("OPTIMUM FOUND") != std::string::npos){
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

struct Obs_Point {
    int x, y;

    bool operator <(const Obs_Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

int cross(const Obs_Point &O, const Obs_Point &A, const Obs_Point &B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

/*push formula like (¬a ∨ ¬b ∨ g) ∧ (¬a ∨ b ∨ ¬g) ∧ (¬a ∨ ¬c ∨ h) ∧ (¬a ∨ c ∨ ¬h) ∧ (¬a ∨ ¬d ∨ i) ∧ (¬a ∨ d ∨ ¬i)
∧ (¬a ∨ ¬e ∨ j) ∧ (¬a ∨ e ∨ ¬j) ∧ (¬a ∨ ¬f ∨ k) ∧ (¬a ∨ f ∨ ¬k)*/
// map[i][j][k] implies map[a][b][c].netid = map[x]y][z].netid
void lsfunc(list<string> &ls, vector<vector<vector<Node>>> &map, int i, int j, int k, int a, int b, int c, int x, int y, int z)
{
    ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(-map[a][b][c].net_id[0])+' '+to_string(map[x][y][z].net_id[0])+" 0");
    ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(-map[a][b][c].net_id[1])+' '+to_string(map[x][y][z].net_id[1])+" 0");
    ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(-map[a][b][c].net_id[2])+' '+to_string(map[x][y][z].net_id[2])+" 0");
    ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(-map[a][b][c].net_id[3])+' '+to_string(map[x][y][z].net_id[3])+" 0");
    ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(-map[a][b][c].net_id[4])+' '+to_string(map[x][y][z].net_id[4])+" 0");
    ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[a][b][c].net_id[0])+' '+to_string(-map[x][y][z].net_id[0])+" 0");
    ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[a][b][c].net_id[1])+' '+to_string(-map[x][y][z].net_id[1])+" 0");
    ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[a][b][c].net_id[2])+' '+to_string(-map[x][y][z].net_id[2])+" 0");
    ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[a][b][c].net_id[3])+' '+to_string(-map[x][y][z].net_id[3])+" 0");
    ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[a][b][c].net_id[4])+' '+to_string(-map[x][y][z].net_id[4])+" 0");
}

struct slot{
    int var_id;
    int i, j, k;
    
    void setup(int var, int _i, int _j, int _k)
    {
        var_id = var;
        i = _i;
        j = _j;
        k = _k;
    }
};

class config{
    public:
        string FileName;
        int Region_Ext_Left;
        int Region_Ext_Right;
        int Region_Ext_Top;
        int Region_Ext_Bot;
        int DivideTech;
        string DivideProcess;
        int HOR_Cutline;
        int Top_Ver_Cutline;
        int Bot_Ver_Cutline;
        set <int> skip_net;
        set <int> complex_routing_net;
        int max_sat_ub = 10;
        int accept_iter;
        bool route_all;
        int MIN_SPACING;
        int WIRE_WIDTH;
        int USED_LAYER;
        bool mulit_pin = true;
        string OutputName;
        string CPUName;
        int MAX_LAYER = 5;
        int tile_width  = 10;
        int tile_height = 10;
        int cut_size    = 30;

        vector <string> group_name;
        vector <string> direction;

        vector < Obstacle > Obs_list;
        vector < Obstacle > Crossing_Line_list;
        vector < Obstacle > Pin_Obs_list;

        void load_config(string config_name){
            ifstream fin;
            fin.open(config_name, ios::in);
            string strLine = "";
            while(!fin.eof())
            {
                std::getline(fin,strLine);
                string str = strLine;
                if(strLine.size() > 0){
                    vector <string> string_list;
                    string sep = " ";
                    SplitString(str,string_list,sep);

                    if(string_list.size() == 0){
                        continue;
                    }

                    if(string_list.at(0) == "FileName:"){
                        FileName = trim(string_list.at(1));
                    }
                    else if(string_list.at(0) == "Region_Ext_Left:"){
                        Region_Ext_Left = atoi(string_list.at(1).c_str());
                    }
                    else if(string_list.at(0) == "Region_Ext_Right:"){
                        Region_Ext_Right = atoi(string_list.at(1).c_str());
                    }
                    else if(string_list.at(0) == "Region_Ext_Top:"){
                        Region_Ext_Top = atoi(string_list.at(1).c_str());
                    }
                    else if(string_list.at(0) == "Region_Ext_Bot:"){
                        Region_Ext_Bot = atoi(string_list.at(1).c_str());
                    }
                    else if(string_list.at(0) == "DivideTech:"){
                        DivideTech = atoi(string_list.at(1).c_str());
                    }
                    else if(string_list.at(0) == "DivideProcess:"){
                        DivideProcess = trim(string_list.at(1));
                    }
                    else if(string_list.at(0) == "HOR_Cutline:"){
                        HOR_Cutline = atoi(string_list.at(1).c_str());
                    }
                    else if(string_list.at(0) == "Top_Ver_Cutline:"){
                        Top_Ver_Cutline = atoi(string_list.at(1).c_str());
                    }
                    else if(string_list.at(0) == "Bot_Ver_Cutline:"){
                        Bot_Ver_Cutline = atoi(string_list.at(1).c_str());
                    }
                    else if(string_list.at(0) == "MIN_SPACING:"){
                        MIN_SPACING = atoi(string_list.at(1).c_str());
                        printf("min spacing : %d\n",MIN_SPACING);
                    }
                    else if(string_list.at(0) == "WIRE_WIDTH:"){
                        WIRE_WIDTH = atoi(string_list.at(1).c_str());
                        printf("wire width : %d\n",WIRE_WIDTH);
                    }
                    else if(string_list.at(0) == "USED_LAYER:"){
                        USED_LAYER = atoi(string_list.at(1).c_str());
                        printf("used layer : %d\n",USED_LAYER);
                    }
                    else if(string_list.at(0) == "Skip_Net:"){
                        for(int i = 1; i < string_list.size();i++){
                            skip_net.insert(atoi(string_list.at(i).c_str()));
                        }
                    }
                    else if(string_list.at(0) == "Complex_Routing_Net:"){
                        for(int i = 1; i < string_list.size();i++){
                            complex_routing_net.insert(atoi(string_list.at(i).c_str()));
                        }
                    }
                    else if(string_list.at(0) == "MaxSAT_ub:"){
                        max_sat_ub = atoi(string_list.at(1).c_str());
                    }
                    else if(string_list.at(0) == "OutputName:"){
                        OutputName = trim(string_list.at(1));
                    }
                    else if(string_list.at(0) == "Group_Name:"){
                        for(int i = 1; i < string_list.size();i++){
                            if (trim(string_list.at(i))!= "") {
                                group_name.push_back(trim(string_list.at(i)));
                            }
                        }
                    }
                    else if(string_list.at(0) == "Direction:"){
                        for(int i = 1; i < string_list.size();i++){
                            direction.push_back(trim(string_list.at(i)));
                        }
                    }
                    else if(string_list.at(0) == "CPU_Name:"){
                        CPUName = trim(string_list.at(1));
                    }
                    else if(string_list.at(0) == "MAX_LAYER:"){
                        MAX_LAYER = atoi(string_list.at(1).c_str());
                        printf("max layer : %d\n",MAX_LAYER);
                    }
                    else if(string_list.at(0) == "TILE_WIDTH:"){
                        tile_width = atoi(string_list.at(1).c_str());
                    }
                    else if(string_list.at(0) == "TILE_HEIGHT:"){
                        tile_height = atoi(string_list.at(1).c_str());
                    }
                    else if(string_list.at(0) == "CUT_SIZE:"){
                        cut_size = atoi(string_list.at(1).c_str());
                    }
                    if(string_list.at(0) == "NO_MULTI_PIN"){
                        mulit_pin = false;
                    }
                    else if(string_list.at(0) == "ObsPad"){
                        int x,y,w,h;
                        int l = -1;
                        vector <string> string_temp;
                        string sep = " ";
                        std::getline(fin,strLine);
                        string layer = strLine;
                        SplitString(layer,string_temp,sep);
                        l = atof(string_temp.at(3).c_str());
                        string_temp.clear();

                        std::getline(fin,strLine);
                        string coor = strLine;
                        vector <string> string_coor_temp;
                        SplitString(coor,string_temp,sep);
                        sep = ",";
                        SplitString(string_temp.at(3),string_coor_temp,sep);
                        x = atof(string_coor_temp.at(0).c_str()) * 100;
                        y = atof(string_coor_temp.at(1).c_str()) * 100;
                        string_temp.clear();

                        std::getline(fin,strLine);
                        std::getline(fin,strLine);
                        string width = strLine;
                        sep = " ";
                        SplitString(width,string_temp,sep);
                        w = atof(string_temp.at(3).c_str()) * 100;
                        string_temp.clear();

                        std::getline(fin,strLine);
                        string height = strLine;
                        SplitString(height,string_temp,sep);
                        h = atof(string_temp.at(3).c_str()) * 100;
                        string_temp.clear();

                        //for (int l = 0; l <= 5; l++) {
                        if (l >= 0) {
                            Obstacle Obs;
                            Obs.setup(x-w, y-h, x+w, y+h, l, 0);
                            Obs_list.push_back(Obs);
                            Pin_Obs_list.push_back(Obs);
                        }
                    }
                }
            }

            fin.close();
        }
};

int main(int argc, const char * argv[])
{
    int total_net_num = 0;
    clock_t tStart = clock();
    config cfig;
    cfig.load_config("config/config_1_1.txt");

    string obs_name = "case/1.brd";
    cfig.load_config(obs_name+".obs");

    vector<Line_Box> outputedge;
    vector<OutputRect> outputpin;
    vector< vector<int> > crossing_line_total;
    crossing_line_total.resize(100);
    cout << "Size of Group: " << static_cast<int>(cfig.group_name.size()) << endl;

    // main finc start
    for (int group_count = 0; group_count < static_cast<int>(cfig.group_name.size()); group_count++) {
    std::vector< std::vector<int> > net;
    std::vector< std::vector<int> > net_box;
    vector<int> x,y,newx,newy,box_x,box_y,psudoVertex;
    vector<pin> pin;
    vector<edge> all_edge;
    int net_count = 0;
    int vertex_count = 1;
    int edge_count = 0;

    //printf("Loading Config completed\n");
    ifstream fin;
    string line;
    ofstream foutput,goutput;
    fin.open("case/1.brd_input.netlist", ios::in);
    foutput.open("board.txt",ios::out);

    int pinx,piny;
    std::string outfilename = "test";

    while (getline(fin, line))
    {
        stringstream ss(line);
        string temp;
        int time = 0;

        while (ss >> temp)
        {
            time++;
        }
        ss.clear();
        ss.str(line);

        std::string str = ss.str();
        if(str == "PIN START"){
            vector<int> temp;
            int vertex_count_temp = vertex_count;

            int net_num = static_cast<int>(net.size()) + 1;

            while (getline(fin, line))
            {
                ss.clear();
                ss.str(line);

                std::string str = ss.str();

                if(str == "PIN END"){
                    if (static_cast<int>(temp.size()) == 2 && group_count < static_cast<int>(cfig.group_name.size()))
                    {
                        vector<int> pin_name_temp;
                        bool foundP = false;
                        bool foundC = false;
                        //size_t found0,found1;

                        //cout << "Pin find" << endl;
                        pin_name_temp.resize(temp.size(),0);
                        for (int i = 0; i < static_cast<int>(temp.size()); i++)
                        {
                            for (int j = 0; j < static_cast<int>(pin.size()); j++)
                            {
                                if (pin[j].pinNo == temp[i])
                                {
                                    //cout << pin[j].name << endl;
                                    pin_name_temp[i] = j;
                                    break;
                                }
                            }
                        }

                        for (int i = 0; i < static_cast<int>(pin_name_temp.size()); i++)
                        {
                            //if (pin[pin_name_temp[i]].name.find(argv[4]) != std::string::npos) {
                            if (pin[pin_name_temp[i]].name.find(cfig.group_name[group_count]) != std::string::npos) {
                                foundP = true;
                                //break;
                            }

                            if (pin[pin_name_temp[i]].name.find(cfig.CPUName) != std::string::npos) {
                                foundC = true;
                            }

                            if (foundC == true && foundP == true)
                            {
                                cout << "Find net: "<< pin[pin_name_temp[0]].name << " " << pin[pin_name_temp[1]].name << endl;
                                net.push_back(temp);
                                net_count++;
                                break;
                            }
                        }
                        //found0=pin[temp[0]].name.find("U3");
                        //found1=pin[temp[1]].name.find("U3");

                        //if (found0 != std::string::npos || found0 != std::string::npos) {
                        /*if (found == true)
                        {
                            cout << "Find net: "<< pin[pin_name_temp[0]].name << " " << pin[pin_name_temp[1]].name << endl;
                            net.push_back(temp);
                            net_count++;
                        }*/
                    } else if (group_count >= static_cast<int>(cfig.group_name.size()) &&
                               static_cast<int>(temp.size()) <= 2*static_cast<int>(cfig.group_name.size())) {
                        vector<int> pin_name_temp;
                        bool found = false;
                        int foundA = -1;
                        int foundB = -1;

                        pin_name_temp.resize(temp.size(),0);
                        for (int i = 0; i < static_cast<int>(temp.size()); i++)
                        {
                            for (int j = 0; j < static_cast<int>(pin.size()); j++)
                            {
                                if (pin[j].pinNo == temp[i])
                                {
                                    //cout << pin[j].name << endl;
                                    pin_name_temp[i] = j;
                                    break;
                                }
                            }
                        }

                        for (int i = 0; i < static_cast<int>(pin_name_temp.size()); i++)
                        {
                            //if (pin[pin_name_temp[i]].name.find(argv[4]) != std::string::npos) {
                            if (pin[pin_name_temp[i]].name.find(cfig.group_name[group_count-static_cast<int>(cfig.group_name.size())]) != std::string::npos) {
                                foundA = i;
                            }

                            if (pin[pin_name_temp[i]].name.find(cfig.group_name[group_count-static_cast<int>(cfig.group_name.size())+1]) != std::string::npos) {
                                foundB = i;
                            }

                            if (foundA >= 0 && foundB >= 0) {
                                vector<int> temp1;
                                cout << "Find net: "<< pin[pin_name_temp[foundA]].name << " " << pin[pin_name_temp[foundB]].name << endl;
                                temp1.push_back(temp[foundA]);
                                temp1.push_back(temp[foundB]);
                                net.push_back(temp1);
                                net_count++;
                                break;
                            }
                        }
                    }
                    else
                    {
                        //vertex_count = vertex_count_temp; //restore
                    }

                    break;
                } else {
                    string name, temp1, type;
                    vector<string> temps;
                    struct pin pintemp;
                    bool repeat = false;

                    ss >> name >> temp1 >> type;
                    //while (getline(ss, temp1, ','))
                    //   temps.push_back(temp1);
                    string sep = ",";
                    SplitString(temp1,temps,sep);
                    if (static_cast<int>(temps.size()) == 2 && isdigit(temps[0][0]) == true)
                    {
                        pinx = stof(temps[0]) * 100;
                        piny = stof(temps[1]) * 100;
                        //temp = type + "." + name;
                        pintemp.name = name;
                        pintemp.x = pinx;
                        pintemp.y = piny;
                        pintemp.pin_x = pinx;
                        pintemp.pin_y = piny;
                        pintemp.pinNo = 0;
                        pintemp.net = 0;
                        pintemp.new_x = pinx;
                        pintemp.new_y = piny;
                        //printf("Pin Name %s , original coor : (%.2f,%.2f) -> coor (%d,%d)\n",pintemp.name.c_str(),stof(temps[0]),stof(temps[1]),pinx,piny);

                        for (int i = 0; i < static_cast<int>(pin.size()); i++)
                        {
                            if (pin[i].name.compare(name) == 0)
                            {
                                repeat = true;
                                break;
                            }
                        }

                        if (repeat != true)
                        {
                            pin.push_back(pintemp);
                            x.push_back(pinx);
                            y.push_back(piny);
                        }
                    }

                    for (int i = 0; i < static_cast<int>(pin.size()); i++)
                    {
                        if (pin[i].name.compare(name) == 0)
                        {
                            if (pin[i].pinNo == 0)
                            {
                                temp.push_back(i);
                                pin[i].pinNo = i;
                                pin[i].net = net_num;
                            } else {
                                temp.push_back(pin[i].pinNo);
                            }
                            //cout << "First: " << pin[i].name << endl;
                            break;
                        }
                    }

                }
            }
        }
    }
    fin.close();

    printf("Loading Input End. #Nets : %lu\n", net.size());
    if (net.size() == 0)
        continue;

    vector<pinpair> pp;
    pp.resize(net.size());
    int GU = findType("./case/1.brd_input.pCSet" , "DEFAULT", "./case/1.brd_input.sCSet", "DEFAULT");// Unit of grid, default : 800
        
    for(int i = 0; i < net.size(); i++){
        printf("Net %d : \n",i);
        for(int j = 0; j < net.at(i).size(); j++){
            printf("    %s (%d,%d)\n",pin.at(net.at(i).at(j)).name.c_str(),pin.at(net.at(i).at(j)).x,pin.at(net.at(i).at(j)).y);
            if(j==0){
                pp[i].first_x = exactgrid(pin.at(net.at(i).at(j)).x, GU);
                pp[i].first_y = exactgrid(pin.at(net.at(i).at(j)).y, GU);
            }
            else{
                pp[i].second_x = exactgrid(pin.at(net.at(i).at(j)).x, GU);
                pp[i].second_y = exactgrid(pin.at(net.at(i).at(j)).y, GU);
            }
        }
    }
    
        
    for(int i=0; i < net.size(); i++)
    {
        std::cout << pp[i].first_x << ' ' << pp[i].first_y << ' ' << pp[i].second_x << ' ' << pp[i].second_y << std::endl;
    }
        
    vector<boundary> set;
    set.resize(2);
    for(int i = 0; i < 2; i++){
        set.at(i) = findboundary(pp, i+1);
        cout<<"boundary "<< i << endl<<set.at(i).top/GU<<' '<<set.at(i).down/GU<<' '<<set.at(i).left/GU<<' '<<set.at(i).right/GU<<endl;
        // extra 1 space for slots
        set.at(i).setUp(set.at(i).top + GU, set.at(i).down - GU, set.at(i).left - GU, set.at(i).right + GU);
    }

    // grid map declared here
    // many m x n 2D vector of vector
    vector<vector <vector<Node> > > map;
    int var_id_counter = 0;
    // +1 is for CPU name and node[0] is CPU
    //map.resize(cfig.group_name.size() + 1);
    map.resize(2);
    for(int i = 0; i < set.size(); i++){
        // row and column here contains only pins, so - 2 slots/fanout_nodes
        int row = (set.at(i).top/GU)-(set.at(i).down/GU)+1-2;
        int column = (set.at(i).right/GU)-(set.at(i).left/GU)+1-2;
        // pin + edge(pin * 2 - 1) + slot/fanout_node(2) = pin * 2 + 1
        map.at(i).resize(row * 2 + 1, vector<Node>(column * 2 + 1));
        cout << "---size of grid map "<< i <<" is " << row * 2 + 1 << " x " << column * 2 + 1 << "---" << endl;
        for(int j = 0; j < map.at(i).size(); j++){
            for(int k = 0; k < map.at(i).at(0).size(); k++){
                // set x and y coor (origin is at top-left)
                map.at(i).at(j).at(k).SetUp(set.at(i).left / 100 + k * GU / 100, set.at(i).top / 100 - j * GU / 100);
                // default : 4 vertexes of grip map and (x,y)=(even,even) have nothing
                if((j == 0 || j == map.at(i).size() - 1) && (k == 0 || k == map.at(i).at(0).size() - 1)){
                // Slot (boundary except the vertexes)
                }else if(j == 0 || k == 0 || j == map.at(i).size() - 1 || k == map.at(i).at(0).size() - 1){
                    map.at(i).at(j).at(k).type = 'S';
                // Grid (x,y)=(odd,odd)
                }else if((j % 2 != 0) && (k % 2 != 0)){
                    map.at(i).at(j).at(k).type = 'G';
                // Edge (x,y)=(odd,even)vertical or (even,odd)horizontal
                }else if(((j % 2 != 0) && (k % 2 == 0)) || ((j % 2 == 0) && (k % 2 != 0))){
                    map.at(i).at(j).at(k).type = 'E';
                }
                map.at(i).at(j).at(k).var_id = var_id_counter++;
            }
        }
        // Pin *2 group only*
        if(i == 0){
            for(int j = 0; j < pp.size(); j++){
                cout << "coor of the pin is (" << (pp[j].first_x/GU - (set.at(i).left/GU+1)) * 2 + 1
                     << "," << ((set.at(i).top/GU-1) - pp[j].first_y/GU) * 2 + 1 << ")" << endl;
                // top/GU-1 and left/GU+1 to elim slots
                map.at(i).at(((set.at(i).top/GU-1) - pp[j].first_y/GU) * 2 + 1).at((pp[j].first_x/GU - (set.at(i).left/GU+1)) * 2 + 1).type = 'P';
                map.at(i).at(((set.at(i).top/GU-1) - pp[j].first_y/GU) * 2 + 1).at((pp[j].first_x/GU - (set.at(i).left/GU+1)) * 2 + 1).pin_id = j;
                int cnt = 0;
                int dec = j;
                while(dec != 0)
                {
                    map.at(i).at(((set.at(i).top/GU-1) - pp[j].first_y/GU) * 2 + 1).at((pp[j].first_x/GU - (set.at(i).left/GU+1)) * 2 + 1).net_id[cnt] = (dec % 2);
                    dec /= 2;
                    cnt++;
                }
            }
        }else if(i == 1){
            for(int j = 0; j < pp.size(); j++){
                cout << "coor of the pin is (" << (pp[j].second_x/GU - (set.at(i).left/GU+1)) * 2 + 1
                     << "," << ((set.at(i).top/GU-1) - pp[j].second_y/GU) * 2 + 1 << ")" << endl;//
                map.at(i).at(((set.at(i).top/GU-1) - pp[j].second_y/GU) * 2 + 1).at((pp[j].second_x/GU - (set.at(i).left/GU+1)) * 2 + 1).type = 'P';
                map.at(i).at(((set.at(i).top/GU-1) - pp[j].second_y/GU) * 2 + 1).at((pp[j].second_x/GU - (set.at(i).left/GU+1)) * 2 + 1).pin_id = j;
                int cnt = 0;
                int dec = j;
                while(dec != 0)
                {
                    map.at(i).at(((set.at(i).top/GU-1) - pp[j].second_y/GU) * 2 + 1).at((pp[j].second_x/GU - (set.at(i).left/GU+1)) * 2 + 1).net_id[cnt] = (dec % 2);
                    dec /= 2;
                    cnt++;
                }
            }
        }
    }
    list<string> ls;
        for(int i = 0; i < set.size(); i++){
            for(int j = 0; j < map.at(i).size(); j++){
                for(int k = 0; k < map.at(i).at(0).size(); k++){
                    if(map[i][j][k].type == 'P'){
                        for(int l = 0; l < 5; l++){
                            if(map[i][j][k].net_id[l] == 1){
                                map[i][j][k].net_id[l] = var_id_counter++;
                                ls.push_back(to_string(map[i][j][k].net_id[l])+" 0");
                            }
                            else{
                                map[i][j][k].net_id[l] = var_id_counter++;
                                ls.push_back(to_string(-map[i][j][k].net_id[l])+" 0");
                            }
                        }
                    }
                    else{
                        for(int l = 0; l < 5; l++)
                            map[i][j][k].net_id[l] = var_id_counter++;
                    }
                }
            }
        }
    int slotcnt1 = 0;
    int slotcnt2 = 0;
    // constraint
    // ls is to store the constraint in dimacs format, will write into the file later
    for(int i = 0; i < set.size(); i++){
        for(int j = 0; j < map.at(i).size(); j++){
            for(int k = 0; k < map.at(i).at(0).size(); k++){
                // each pin choose a way out
                if(map[i][j][k].type == 'P')
                {
                    //(¬a ∨ ¬b) ∧ (¬a ∨ ¬c) ∧ (¬a ∨ ¬d) ∧ (a ∨ b ∨ c ∨ d) ∧ (¬b ∨ ¬c) ∧ (¬b ∨ ¬d) ∧ (¬c ∨ ¬d)
                    ls.push_back(to_string(map[i][j-1][k].var_id)+' '+to_string(map[i][j+1][k].var_id)+' '+to_string(map[i][j][k-1].var_id)+' '+to_string(map[i][j][k+1].var_id)+" 0");
                    ls.push_back(to_string(-map[i][j-1][k].var_id)+' '+to_string(-map[i][j][k+1].var_id)+" 0");
                    ls.push_back(to_string(-map[i][j-1][k].var_id)+' '+to_string(-map[i][j][k-1].var_id)+" 0");
                    ls.push_back(to_string(-map[i][j-1][k].var_id)+' '+to_string(-map[i][j+1][k].var_id)+" 0");
                    ls.push_back(to_string(-map[i][j][k+1].var_id)+' '+to_string(-map[i][j][k-1].var_id)+" 0");
                    ls.push_back(to_string(-map[i][j][k+1].var_id)+' '+to_string(-map[i][j+1][k].var_id)+" 0");
                    ls.push_back(to_string(-map[i][j+1][k].var_id)+' '+to_string(-map[i][j][k-1].var_id)+" 0");
                }
                else if(map[i][j][k].type == 'E')
                {
                    //-
                    if(k % 2 == 0){
                        ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j][k+1].var_id)+" 0");
                        ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j][k-1].var_id)+" 0");
                        
                        lsfunc(ls, map, i, j, k, i, j, k-1, i, j, k+1);
                    }
                    //|
                    else{
                        ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j+1][k].var_id)+" 0");
                        ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j-1][k].var_id)+" 0");
                        
                        lsfunc(ls, map, i, j, k, i, j-1, k, i, j+1, k);
                    }
                }
                else if(map[i][j][k].type == 'G')
                {
                    //(¬a ∨ ¬b ∨ ¬c ∨ ¬d) ∧ (¬a ∨ ¬b ∨ ¬c ∨ ¬e) ∧ (¬a ∨ ¬b ∨ ¬d ∨ ¬e) ∧ (¬a ∨ b ∨ c ∨ d) ∧ (¬a ∨ b ∨ c ∨ e) ∧
                     //(¬a ∨ b ∨ d ∨ e) ∧ (¬a ∨ ¬c ∨ ¬d ∨ ¬e) ∧ (¬a ∨ c ∨ d ∨ e)
                    int a = map[i][j][k].var_id;
                    int b = map[i][j][k-1].var_id;
                    int c = map[i][j+1][k].var_id;
                    int d = map[i][j][k+1].var_id;
                    int e = map[i][j-1][k].var_id;
                    ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c)+' '+to_string(-d)+" 0");
                    ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c)+' '+to_string(-e)+" 0");
                    ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-d)+' '+to_string(-e)+" 0");
                    ls.push_back(to_string(-a)+' '+to_string(b)+' '+to_string(c)+' '+to_string(d)+" 0");
                    ls.push_back(to_string(-a)+' '+to_string(b)+' '+to_string(c)+' '+to_string(e)+" 0");
                    ls.push_back(to_string(-a)+' '+to_string(b)+' '+to_string(d)+' '+to_string(e)+" 0");
                    ls.push_back(to_string(-a)+' '+to_string(-c)+' '+to_string(-d)+' '+to_string(-e)+" 0");
                    ls.push_back(to_string(-a)+' '+to_string(c)+' '+to_string(d)+' '+to_string(e)+" 0");
                }
                else if(map[i][j][k].type == 'S' && i == 0)
                    slotcnt1++;
                else if(map[i][j][k].type == 'S' && i == 1)
                    slotcnt2++;
            }
        }
    }
        
        slot slotorder[slotcnt1 + slotcnt2];
        int i = 0;
            for(int k = 1; k < map[0][0].size()-1; k++, i++)
                slotorder[i].setup(map[0][0][k].var_id, 0, 0, k);
            for(int j = 1; j < map[0].size(); j++, i++)
                slotorder[i].setup(map[0][j][map[0][0].size()-1].var_id, 0, j, (int)map[0][0].size()-1);
            for(int k = (int)map[0][0].size()-3; k >= 0; k--, i++)
                slotorder[i].setup(map[0][map[0].size()-1][k].var_id, 0, (int)map[0].size()-1, k);
            for(int j = (int)map[0].size()-3; j > 0; j--, i++)
                slotorder[i].setup(map[0][j][0].var_id, 0, j, 0);
        
            for(int k = 1; k < map[1][0].size()-1; k++, i++)
                slotorder[i].setup(map[1][0][k].var_id, 0, 0, k);
            for(int j = 1; j < map[1].size(); j++, i++)
                slotorder[i].setup(map[1][j][map[1][0].size()-1].var_id, 0, j, (int)map[1][0].size()-1);
            for(int k = (int)map[1][0].size()-3; k >= 0; k--, i++)
                slotorder[i].setup(map[1][map[0].size()-1][k].var_id, 0, (int)map[1].size()-1, k);
            for(int j = (int)map[1].size()-3; j > 0; j--, i++)
                slotorder[i].setup(map[1][j][0].var_id, 0, j, 0);
        
            for(int i = 0; i < slotcnt1-2; i++){
                for(int j = i+1; j < slotcnt1-1; j++)
                {
                    
                }
            }
        
        ofstream file("temp.cnf");
        if(file.is_open()){
            file << "c temp.cnf" << endl;
            file << "p cnf "<<var_id_counter-1<<' '<<ls.size()<<endl;
            for(string l: ls)
                file << l << endl;
        }
        file.close();
        
        /* for xcode
        string command = "./open-wbo /Users/brian/Library/Developer/Xcode/DerivedData/csproject-ewtkybbytxrmoygdjpvtmhcsgjil/Build/Products/Debug/temp.cnf > output";
        system(command.c_str());
        
         ifstream fil;
    fil.open("/Users/brian/Library/Developer/Xcode/DerivedData/csproject-ewtkybbytxrmoygdjpvtmhcsgjil/Build/Products/Debug/output", ios::in);
        for(int i=0;i<26;i++)
            getline(fil, line);
        int num[64000];
        char c;
        fil >> c;
        for(int i=0;i<62363;i++)
            fil >> num[i];
         */
        
        ifstream fil;
        fil.open("output", ios::in);
        for(int i=0;i<26;i++)
            getline(fil, line);
        int num[64000];
        char c;
        fil >> c;
        for(int i=0;i<62363;i++)
            fil>>num[i];
        
        //draw the grid map
        for(int i = 0; i < set.size(); i++){
            cout << "\n---Grid map " << i << "---" << endl;
            for(int j = 0; j < map.at(i).size(); j++){
                for(int k = 0; k < map.at(i).at(0).size(); k++){
                    switch (map.at(i).at(j).at(k).type){
                        case 'X' : cout << ' '; break;
                        case 'G' :
                            if(num[map[i][j][k].var_id-1]>0)
                                cout << '.';
                            else
                                cout << ' ';
                            break;
                        case 'E' :
                            if(num[map[i][j][k].var_id-1]>0)
                                cout << ((k % 2 == 0)?'-':'|');
                            else
                                cout << ' ';
                            break;
                        case 'P' : cout << 'x'; break;
                        case 'S' : cout << '#'; break;
                    }
                }
                cout << endl;
            }
        }
}

    for (int i=0; i<static_cast<int>(cfig.Pin_Obs_list.size()); i++) {
        OutputRect temp;

        temp.setup(cfig.Pin_Obs_list[i].LBx,cfig.Pin_Obs_list[i].LBy,
                   cfig.Pin_Obs_list[i].RTx,cfig.Pin_Obs_list[i].RTy,999,cfig.Pin_Obs_list[i].Layer);
        outputpin.push_back(temp);
    }

    string layout_name = "case/1.brd";
    //outputGDS(layout_name, outputpin, outputedge, crossing_line_total);

    return 0;
}
