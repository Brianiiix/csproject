#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
// declare both fstream and ostream is necessary before C++11
#include <ostream>
#include <map>
#include <set>
#include <list>
#include <math.h>
#include <chrono>
#include "board.h"
#include "IO_interface.hpp"
#include "output_gds.hpp"
#include "initVar.hpp"
#include "gridUnit.hpp"
#include "TileStructure.hpp"
#include "phase.hpp"

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
// map[i][j][k] implies map[a][b][c].netid = map[x][y][z].netid
void lsfunc(list<string> &ls, vector<vector<vector<Node>>> &map, int i, int j, int k, int a, int b, int c, int x, int y, int z)
{
    for(int l = 0; l < 5; l++){
        ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(-map[a][b][c].net_id[l])+' '+to_string(map[x][y][z].net_id[l])+" 0");
        ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[a][b][c].net_id[l])+' '+to_string(-map[x][y][z].net_id[l])+" 0");
    }
}

bool notInVector(vector<int> &a, int j)
{
    for(int i=0; i<a.size(); i++)
        if(j==a[i]) return false;
    return true;
}

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
    chrono::steady_clock::time_point tStart = chrono::steady_clock::now();
    chrono::duration<double> Stime, Ttime;
    config cfig;
    // ***
    cfig.load_config("config/config_1_1.txt");
    // *
    //string obs_name = "case/2.brd";
    //cfig.load_config(obs_name+".obs");

    vector<vector<vector<int> > > netBox;
    vector<vector<pin> > pinBox;
    int groupSize = cfig.group_name.size() + 1; // include CPU
    
    vector<Line_Box> outputedge;
    vector<OutputRect> outputpin;
    vector< vector<int> > crossing_line_total;
    crossing_line_total.resize(100);
    cout << "Size of Group: " << static_cast<int>(cfig.group_name.size()) << endl;

    // main finc start
    for (int group_count = 0; group_count < static_cast<int>(cfig.group_name.size()); group_count++) {
    std::vector< std::vector<int> > net;
    vector<int> x,y;//,newx,newy,box_x,box_y,psudoVertex;
    vector<pin> pin;
    //vector<edge> all_edge;
    int net_count = 0;
    int vertex_count = 1;
    //int edge_count = 0;

    //printf("Loading Config completed\n");
    ifstream fin;
    string line;
    // ***
    fin.open("case/1.brd_input.netlist", ios::in);

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
                                //@cout << "Find net: "<< pin[pin_name_temp[0]].name << " " << pin[pin_name_temp[1]].name << endl;
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
                                //@cout << "Find net: "<< pin[pin_name_temp[foundA]].name << " " << pin[pin_name_temp[foundB]].name << endl;
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

    printf("Loading Input End. #Nets : %d\n", static_cast<int>(net.size()));
    if (net.size() == 0)
        continue;
        netBox.push_back(net);
        pinBox.push_back(pin);
    }
    // *** Grid Unit, 1.default : 800
    int GU = findType("./case/1.brd_input.pCSet" , "DEFAULT", "./case/1.brd_input.sCSet", "DEFAULT");
    // Pin info
    vector<vector<pair<int, int>>> P(groupSize);
    // Pin info for map coor, first:j of map[i][j][k] second:k of map[i][j][k]
    vector<vector<pair<int, int>>> P_map(groupSize);
    // boundary info
    vector<boundary> set(groupSize);
    // many m x n 2D vector of vector
    vector<vector <vector<Node> > > map;
    int var_id_counter = 1;
    // length between boundary and nearest pin #even only#
    int bsize = 4;
    // +1 is for CPU name and node[0] is CPU
    map.resize(groupSize);
    //first vector imply which (slot[0] = DDR1)
    vector<vector<slot>> CPUslot(groupSize-1),DDRslot(groupSize-1);
    // whether slots are reverse to their iteration (rev[0] = DDR1)
    vector<bool> CPUslotRev(groupSize-1), DDRslotRev(groupSize-1);
    // how many pin in the group (accumulated)
    vector<int> groupnum(groupSize-1);
    // grid map size info
    vector<pair<int,int>> mapsize(groupSize);

    // set grid maps
    for(int z = 0; z < groupSize; z++){
        
        if(z == 0){ // CPU
            int sum = 0;
            for(int i = 0; i < netBox.size(); i++)
                sum += netBox[i].size();
            P[z].reserve(sum);
            P_map[z].resize(sum);
            for(int i = 0; i < netBox.size(); i++){
                for(int j = 0; j < netBox[i].size(); j++){
                    P[z].push_back(make_pair(exactgrid(pinBox[i].at(netBox[i].at(j).at(0)).x, GU),exactgrid(pinBox[i].at(netBox[i].at(j).at(0)).y, GU)));
                }
                groupnum[i] = netBox[i].size();
                if(i != 0)
                    groupnum[i] += groupnum[i-1];
            }
        }else{
            P[z].reserve(netBox[z-1].size());
            P_map[z].resize(netBox[z-1].size());
            for(int i = 0; i < netBox[z-1].size(); i++){
                P[z].push_back(make_pair(exactgrid(pinBox[z-1].at(netBox[z-1].at(i).at(1)).x, GU),exactgrid(pinBox[z-1].at(netBox[z-1].at(i).at(1)).y, GU)));
            }
        }
        set.at(z) = findBoundary(P[z]);
        set.at(z).setUp(set.at(z).top + GU, set.at(z).down - GU, set.at(z).left - GU, set.at(z).right + GU);
        //@cout << set[z].top << " " << set[z].down << " " << set[z].left << " " << set[z].right << endl;
        // row and column here contains only pins, so - 2 slots/fanout_nodes
        int row = (set.at(z).top/GU)-(set.at(z).down/GU)+1-2;
        int column = (set.at(z).right/GU)-(set.at(z).left/GU)+1-2;
        // pin + edge(pin * 2 - 1) + slot/fanout_node(2) = pin * 2 + 1
        map.at(z).resize(row * 2 + 1 + bsize*2, vector<Node>(column * 2 + 1 + bsize*2));
        mapsize[z] = make_pair(row * 2 + 1 + bsize*2, column * 2 + 1 + bsize*2);
        for(int j = 0; j < map.at(z).size(); j++){
            for(int k = 0; k < map.at(z).at(0).size(); k++){
                // set x and y coor (origin is at top-left)
                map.at(z).at(j).at(k).SetUp(set.at(z).left / 100 + k * GU / 100, set.at(z).top / 100 - j * GU / 100);
                // default : 4 vertexes of grip map and (x,y)=(even,even) have nothing
                //if((j == 0 || j == map.at(i).size() - 1) && (k == 0 || k == map.at(i).at(0).size() - 1)){
                // Slot (boundary except the vertexes)
                if(j == 0 || k == 0 || j == map.at(z).size() - 1 || k == map.at(z).at(0).size() - 1){
                    map.at(z).at(j).at(k).type = 'B';
                // Grid (x,y)=(odd,odd)
                }else if((j % 2 != 0) && (k % 2 != 0)){
                    map.at(z).at(j).at(k).type = 'G';
                // Edge (x,y)=(odd,even)vertical or (even,odd)horizontal
                }else if(((j % 2 != 0) && (k % 2 == 0)) || ((j % 2 == 0) && (k % 2 != 0))){
                    map.at(z).at(j).at(k).type = 'E';
                }
                map.at(z).at(j).at(k).var_id = var_id_counter++;
            }
        }
        // Pin
        int groupnumvar = 1;
        for(int j = 0; j < P[z].size(); j++){
            //@cout << "coor of the pin is (" << (P[z][j].first/GU - (set.at(z).left/GU+1)) * 2 + 1+bsize
            //@    << "," << ((set.at(z).top/GU-1) - P[z][j].second/GU) * 2 + 1+bsize << ")" << endl;
            // top/GU-1 and left/GU+1 to elim slots
            P_map[z][j] = {((set.at(z).top/GU-1) - P[z][j].second/GU) * 2 + 1+bsize,(P[z][j].first/GU - (set.at(z).left/GU+1)) * 2 + 1+bsize};
            map.at(z).at(((set.at(z).top/GU-1) - P[z][j].second/GU) * 2 + 1+bsize).at((P[z][j].first/GU - (set.at(z).left/GU+1)) * 2 + 1+bsize).type = 'P';
            map.at(z).at(((set.at(z).top/GU-1) - P[z][j].second/GU) * 2 + 1+bsize).at((P[z][j].first/GU - (set.at(z).left/GU+1)) * 2 + 1+bsize).pin_id = j;
            if(z == 0){
                if(groupnum[groupnumvar-1] == j){
                    groupnumvar++;
                }
                map.at(z).at(((set.at(z).top/GU-1) - P[z][j].second/GU) * 2 + 1+bsize).at((P[z][j].first/GU - (set.at(z).left/GU+1)) * 2 + 1+bsize).group = groupnumvar;
            }
            int cnt = 0;
            int dec = j;
            //set dec = 0 every different group
            /*for(int x = groupnum.size() - 1; x >= 0; x--){
                if(dec >= groupnum[x]){
                    dec -= groupnum[x];
                    break;
                }
            }*/
            // add dec for >=2rd DDR group
            if(z >= 2){
                dec += groupnum[z-2];
            }

            while(dec != 0)
            {
                map.at(z).at(((set.at(z).top/GU-1) - P[z][j].second/GU) * 2 + 1+bsize).at((P[z][j].first/GU - (set.at(z).left/GU+1)) * 2 + 1+bsize).net_id[cnt] = (dec % 2);
                dec /= 2;
                cnt++;
            }
        }
    }

    // set the slots **
    // find relative location between CPU & DDRs, not slot location!
    for(int i = 1; i < groupSize; i++){
        CPUslot[i-1].resize(netBox[i-1].size());
        DDRslot[i-1].resize(netBox[i-1].size());
        // whether slots are reverse to their iterations
        CPUslotRev[i-1] = false;
        DDRslotRev[i-1] = false;
        if(set[i].top <= set[0].down){ // bottom
            if(set[i].left >= set[0].left+(set[0].right-set[0].left)/2){
                set[i].loc = 'b'; // bottom right
                CPUslotRev[i-1] = true;
                if(set[0].loc == 'b' || set[0].loc == 'B') // CPU's slot is at top and bot
                    set[0].loc = 'C';
                else if(set[0].loc != 'C')
                    set[0].loc = 'T'; // DDR:bottom right <-> CPU:top left
            }else{
                set[i].loc = 'B'; // bottom left
                DDRslotRev[i-1] = true;
                if(set[0].loc == 'b' || set[0].loc == 'B')
                    set[0].loc = 'C';
                else if(set[0].loc != 'C')
                    set[0].loc = 't';
            }
        }else if(set[i].down >= set[0].top){ // top
            if(set[i].left >= set[0].left+(set[0].right-set[0].left)/2){
                set[i].loc = 't'; // top right
                CPUslotRev[i-1] = true;
                if(set[0].loc == 't' || set[0].loc == 'T')
                    set[0].loc = 'C';
                else if(set[0].loc != 'C')
                    set[0].loc = 'B';
            }else{
                set[i].loc = 'T'; // top left
                DDRslotRev[i-1] = true;
                if(set[0].loc == 't' || set[0].loc == 'T')
                    set[0].loc = 'C';
                else if(set[0].loc != 'C')
                    set[0].loc = 'b';
            }
        }else{
            cout << "Slot allocation failed at group " << i << endl;
        }
        int z = 1, bd = 0, Z = 1, BD = 0; // Z, BD for CPU
        z = (set[i].loc == 'T' || set[i].loc == 'B') ? map[i][0].size()-2 : 1;
        bd = (set[i].loc == 'B' || set[i].loc == 'b') ? 0 : map[i].size()-1;
        Z = (set[i].loc == 't' || set[i].loc == 'b') ? map[0][0].size()-2 : 1;
        BD = (set[i].loc == 'T' || set[i].loc == 't') ? 0 : map[0].size()-1;
        for(int j = 0; j < netBox[i-1].size(); j++){
            map[i][bd][z].type = 'S';
            map[0][BD][Z].type = 'S';
            CPUslot[i-1][j].setup(0, BD, Z);
            DDRslot[i-1][j].setup(i, bd, z);
            if(set[i].loc == 't' || set[i].loc == 'b'){
                z += 4;
                Z -= 4;
            }else{
                z -= 4;
                Z += 4;
            }
        }
    }
    drawMap0(map, groupSize, mapsize);
    // constraint
    // ls is to store the constraint in dimacs format, will write into the file later
    list<string> ls;
    list<string> lshard1, lshard2;
    list<string> lssoft1, lssoft2;
    // net_id[i] = 0 -> false, 1 ->true
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map.at(i).size(); j++){
            for(int k = 0; k < map.at(i).at(0).size(); k++){
                if(map[i][j][k].type == 'P'){
                    for(int l = 0; l < 5; l++){
                        if(map[i][j][k].net_id[l] == 1){
                            map[i][j][k].net_id[l] = var_id_counter++;
                            ls.push_back(to_string(map[i][j][k].net_id[l])+" 0");
                            if(!i)
                                lshard1.push_back(to_string(map[i][j][k].net_id[l])+" 0");
                            else
                                lshard2.push_back(to_string(map[i][j][k].net_id[l])+" 0");
                        }
                        else{
                            map[i][j][k].net_id[l] = var_id_counter++;
                            ls.push_back(to_string(-map[i][j][k].net_id[l])+" 0");
                            if(!i)
                                lshard1.push_back(to_string(-map[i][j][k].net_id[l])+" 0");
                            else
                                lshard2.push_back(to_string(-map[i][j][k].net_id[l])+" 0");
                        }
                    }
                }
                else{
                    for(int l = 0; l < 5; l++){
                        map[i][j][k].net_id[l] = var_id_counter++;
                    }
                }
            }
        }
    }

    for(int i = 0; i < map.size(); i++){
        int CPUslotC;
        int DDRslotC;
        if(i != 0){
            CPUslotC = (CPUslotRev[i-1])?CPUslot[i-1].size() - 1:0;
            DDRslotC = (DDRslotRev[i-1])?DDRslot[i-1].size() - 1:0;   
        }
        for(int j = 0; j < map.at(i).size(); j++){
            for(int k = 0; k < map.at(i).at(0).size(); k++){
                // each pin choose a way out
                if(map[i][j][k].type == 'P'){
                    //(¬a ∨ ¬b) ∧ (¬a ∨ ¬c) ∧ (¬a ∨ ¬d) ∧ (a ∨ b ∨ c ∨ d) ∧ (¬b ∨ ¬c) ∧ (¬b ∨ ¬d) ∧ (¬c ∨ ¬d)
                    ls.push_back(to_string(map[i][j-1][k].var_id)+' '+to_string(map[i][j+1][k].var_id)+' '+
                                 to_string(map[i][j][k-1].var_id)+' '+to_string(map[i][j][k+1].var_id)+" 0");
                    ls.push_back(to_string(-map[i][j-1][k].var_id)+' '+to_string(-map[i][j][k+1].var_id)+" 0");
                    ls.push_back(to_string(-map[i][j-1][k].var_id)+' '+to_string(-map[i][j][k-1].var_id)+" 0");
                    ls.push_back(to_string(-map[i][j-1][k].var_id)+' '+to_string(-map[i][j+1][k].var_id)+" 0");
                    ls.push_back(to_string(-map[i][j][k+1].var_id)+' '+to_string(-map[i][j][k-1].var_id)+" 0");
                    ls.push_back(to_string(-map[i][j][k+1].var_id)+' '+to_string(-map[i][j+1][k].var_id)+" 0");
                    ls.push_back(to_string(-map[i][j+1][k].var_id)+' '+to_string(-map[i][j][k-1].var_id)+" 0");
                    if(!i){
                        lshard1.push_back(to_string(map[i][j-1][k].var_id)+' '+to_string(map[i][j+1][k].var_id)+' '+
                                     to_string(map[i][j][k-1].var_id)+' '+to_string(map[i][j][k+1].var_id)+" 0");
                        lshard1.push_back(to_string(-map[i][j-1][k].var_id)+' '+to_string(-map[i][j][k+1].var_id)+" 0");
                        lshard1.push_back(to_string(-map[i][j-1][k].var_id)+' '+to_string(-map[i][j][k-1].var_id)+" 0");
                        lshard1.push_back(to_string(-map[i][j-1][k].var_id)+' '+to_string(-map[i][j+1][k].var_id)+" 0");
                        lshard1.push_back(to_string(-map[i][j][k+1].var_id)+' '+to_string(-map[i][j][k-1].var_id)+" 0");
                        lshard1.push_back(to_string(-map[i][j][k+1].var_id)+' '+to_string(-map[i][j+1][k].var_id)+" 0");
                        lshard1.push_back(to_string(-map[i][j+1][k].var_id)+' '+to_string(-map[i][j][k-1].var_id)+" 0");
                    }
                    else{
                        lshard2.push_back(to_string(map[i][j-1][k].var_id)+' '+to_string(map[i][j+1][k].var_id)+' '+
                                     to_string(map[i][j][k-1].var_id)+' '+to_string(map[i][j][k+1].var_id)+" 0");
                        lshard2.push_back(to_string(-map[i][j-1][k].var_id)+' '+to_string(-map[i][j][k+1].var_id)+" 0");
                        lshard2.push_back(to_string(-map[i][j-1][k].var_id)+' '+to_string(-map[i][j][k-1].var_id)+" 0");
                        lshard2.push_back(to_string(-map[i][j-1][k].var_id)+' '+to_string(-map[i][j+1][k].var_id)+" 0");
                        lshard2.push_back(to_string(-map[i][j][k+1].var_id)+' '+to_string(-map[i][j][k-1].var_id)+" 0");
                        lshard2.push_back(to_string(-map[i][j][k+1].var_id)+' '+to_string(-map[i][j+1][k].var_id)+" 0");
                        lshard2.push_back(to_string(-map[i][j+1][k].var_id)+' '+to_string(-map[i][j][k-1].var_id)+" 0");
                    }
                }
                else if(map[i][j][k].type == 'E'){
                    //-
                    if(k % 2 == 0){
                        ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j][k+1].var_id)+" 0");
                        ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j][k-1].var_id)+" 0");
                        
                        lsfunc(ls, map, i, j, k, i, j, k-1, i, j, k+1);
                        lsfunc(ls, map, i, j, k, i, j, k-1, i, j, k);
                        
                        if(!i){
                            lshard1.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j][k+1].var_id)+" 0");
                            lshard1.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j][k-1].var_id)+" 0");
                            
                            lsfunc(lshard1, map, i, j, k, i, j, k-1, i, j, k+1);
                            lsfunc(lshard1, map, i, j, k, i, j, k-1, i, j, k);
                        }
                        else{
                            lshard2.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j][k+1].var_id)+" 0");
                            lshard2.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j][k-1].var_id)+" 0");
                            
                            lsfunc(lshard2, map, i, j, k, i, j, k-1, i, j, k+1);
                            lsfunc(lshard2, map, i, j, k, i, j, k-1, i, j, k);
                        }
                    }
                    //|
                    else{
                        ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j+1][k].var_id)+" 0");
                        ls.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j-1][k].var_id)+" 0");
                        
                        lsfunc(ls, map, i, j, k, i, j-1, k, i, j+1, k);
                        lsfunc(ls, map, i, j, k, i, j-1, k, i, j, k);

                        if(!i){
                            lshard1.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j+1][k].var_id)+" 0");
                            lshard1.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j-1][k].var_id)+" 0");
                            
                            lsfunc(lshard1, map, i, j, k, i, j-1, k, i, j+1, k);
                            lsfunc(lshard1, map, i, j, k, i, j-1, k, i, j, k);
        
                            //lssoft1.push_back(to_string(-map[i][j][k].var_id)+" 0");
                        }
                        else{
                            lshard2.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j+1][k].var_id)+" 0");
                            lshard2.push_back(to_string(-map[i][j][k].var_id)+' '+to_string(map[i][j-1][k].var_id)+" 0");
                            
                            lsfunc(lshard2, map, i, j, k, i, j-1, k, i, j+1, k);
                            lsfunc(lshard2, map, i, j, k, i, j-1, k, i, j, k);
        
                            //lssoft2.push_back(to_string(-map[i][j][k].var_id)+" 0");
                        }
                    }
                }
                else if(map[i][j][k].type == 'G'){
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
                    
                    if(!i){
                        lshard1.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c)+' '+to_string(-d)+" 0");
                        lshard1.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c)+' '+to_string(-e)+" 0");
                        lshard1.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-d)+' '+to_string(-e)+" 0");
                        lshard1.push_back(to_string(-a)+' '+to_string(b)+' '+to_string(c)+' '+to_string(d)+" 0");
                        lshard1.push_back(to_string(-a)+' '+to_string(b)+' '+to_string(c)+' '+to_string(e)+" 0");
                        lshard1.push_back(to_string(-a)+' '+to_string(b)+' '+to_string(d)+' '+to_string(e)+" 0");
                        lshard1.push_back(to_string(-a)+' '+to_string(-c)+' '+to_string(-d)+' '+to_string(-e)+" 0");
                        lshard1.push_back(to_string(-a)+' '+to_string(c)+' '+to_string(d)+' '+to_string(e)+" 0");
                        lssoft1.push_back(to_string(-a)+" 0");
                    }
                    else{
                        lshard2.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c)+' '+to_string(-d)+" 0");
                        lshard2.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c)+' '+to_string(-e)+" 0");
                        lshard2.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-d)+' '+to_string(-e)+" 0");
                        lshard2.push_back(to_string(-a)+' '+to_string(b)+' '+to_string(c)+' '+to_string(d)+" 0");
                        lshard2.push_back(to_string(-a)+' '+to_string(b)+' '+to_string(c)+' '+to_string(e)+" 0");
                        lshard2.push_back(to_string(-a)+' '+to_string(b)+' '+to_string(d)+' '+to_string(e)+" 0");
                        lshard2.push_back(to_string(-a)+' '+to_string(-c)+' '+to_string(-d)+' '+to_string(-e)+" 0");
                        lshard2.push_back(to_string(-a)+' '+to_string(c)+' '+to_string(d)+' '+to_string(e)+" 0");
                        lssoft2.push_back(to_string(-map[i][j][k].var_id)+" 0");
                    }
                }
                else if(map[i][j][k].type == 'S'){
                    //ls.push_back(to_string(map[i][j][k].var_id)+" 0");
                    if(j == 0){
                        ls.push_back(to_string(map[i][j+1][k].var_id)+" 0");
                        if(!i){
                            lshard1.push_back(to_string(map[i][j+1][k].var_id)+" 0");
                        }
                        else{
                            lshard2.push_back(to_string(map[i][j+1][k].var_id)+" 0");
                        }
                    }
                    else{
                        ls.push_back(to_string(map[i][j-1][k].var_id)+" 0");
                        if(!i){
                            lshard1.push_back(to_string(map[i][j-1][k].var_id)+" 0");
                        }
                        else{
                            lshard2.push_back(to_string(map[i][j-1][k].var_id)+" 0");
                        }
                    }
                    /*
                        if(j == 0){
                            lsfunc(ls, map, i, j, k, i, j, k, i, j+1, k);
                        }else{
                            lsfunc(ls, map, i, j, k, i, j, k, i, j-1, k);
                        }
                    */
                    
                    if(i != 0){
                        if(j == 0){ // now
                            for(int l = 0; l < 5; l++){
                                ls.push_back(to_string(map[CPUslot[i-1][CPUslotC].i][CPUslot[i-1][CPUslotC].j-1][CPUslot[i-1][CPUslotC].k].net_id[l])+" "+to_string(-map[DDRslot[i-1][DDRslotC].i][DDRslot[i-1][DDRslotC].j+1][DDRslot[i-1][DDRslotC].k].net_id[l])+" 0");
                                ls.push_back(to_string(-map[CPUslot[i-1][CPUslotC].i][CPUslot[i-1][CPUslotC].j-1][CPUslot[i-1][CPUslotC].k].net_id[l])+" "+to_string(map[DDRslot[i-1][DDRslotC].i][DDRslot[i-1][DDRslotC].j+1][DDRslot[i-1][DDRslotC].k].net_id[l])+" 0");
                                if(!i){
                                    lshard1.push_back(to_string(map[CPUslot[i-1][CPUslotC].i][CPUslot[i-1][CPUslotC].j-1][CPUslot[i-1][CPUslotC].k].net_id[l])+" "+to_string(-map[DDRslot[i-1][DDRslotC].i][DDRslot[i-1][DDRslotC].j+1][DDRslot[i-1][DDRslotC].k].net_id[l])+" 0");
                                    lshard1.push_back(to_string(-map[CPUslot[i-1][CPUslotC].i][CPUslot[i-1][CPUslotC].j-1][CPUslot[i-1][CPUslotC].k].net_id[l])+" "+to_string(map[DDRslot[i-1][DDRslotC].i][DDRslot[i-1][DDRslotC].j+1][DDRslot[i-1][DDRslotC].k].net_id[l])+" 0");
                                }
                                else{
                                    lshard2.push_back(to_string(map[CPUslot[i-1][CPUslotC].i][CPUslot[i-1][CPUslotC].j-1][CPUslot[i-1][CPUslotC].k].net_id[l])+" "+to_string(-map[DDRslot[i-1][DDRslotC].i][DDRslot[i-1][DDRslotC].j+1][DDRslot[i-1][DDRslotC].k].net_id[l])+" 0");
                                    lshard2.push_back(to_string(-map[CPUslot[i-1][CPUslotC].i][CPUslot[i-1][CPUslotC].j-1][CPUslot[i-1][CPUslotC].k].net_id[l])+" "+to_string(map[DDRslot[i-1][DDRslotC].i][DDRslot[i-1][DDRslotC].j+1][DDRslot[i-1][DDRslotC].k].net_id[l])+" 0");
                                }
                            }
                        }else{
                            for(int l = 0; l < 5; l++){
                                ls.push_back(to_string(map[CPUslot[i-1][CPUslotC].i][CPUslot[i-1][CPUslotC].j+1][CPUslot[i-1][CPUslotC].k].net_id[l])+" "+to_string(-map[DDRslot[i-1][DDRslotC].i][DDRslot[i-1][DDRslotC].j-1][DDRslot[i-1][DDRslotC].k].net_id[l])+" 0");
                                ls.push_back(to_string(-map[CPUslot[i-1][CPUslotC].i][CPUslot[i-1][CPUslotC].j+1][CPUslot[i-1][CPUslotC].k].net_id[l])+" "+to_string(map[DDRslot[i-1][DDRslotC].i][DDRslot[i-1][DDRslotC].j-1][DDRslot[i-1][DDRslotC].k].net_id[l])+" 0");
                                if(!i){
                                    lshard1.push_back(to_string(map[CPUslot[i-1][CPUslotC].i][CPUslot[i-1][CPUslotC].j+1][CPUslot[i-1][CPUslotC].k].net_id[l])+" "+to_string(-map[DDRslot[i-1][DDRslotC].i][DDRslot[i-1][DDRslotC].j-1][DDRslot[i-1][DDRslotC].k].net_id[l])+" 0");
                                    lshard1.push_back(to_string(-map[CPUslot[i-1][CPUslotC].i][CPUslot[i-1][CPUslotC].j+1][CPUslot[i-1][CPUslotC].k].net_id[l])+" "+to_string(map[DDRslot[i-1][DDRslotC].i][DDRslot[i-1][DDRslotC].j-1][DDRslot[i-1][DDRslotC].k].net_id[l])+" 0");
                                }
                                else{
                                    lshard2.push_back(to_string(map[CPUslot[i-1][CPUslotC].i][CPUslot[i-1][CPUslotC].j+1][CPUslot[i-1][CPUslotC].k].net_id[l])+" "+to_string(-map[DDRslot[i-1][DDRslotC].i][DDRslot[i-1][DDRslotC].j-1][DDRslot[i-1][DDRslotC].k].net_id[l])+" 0");
                                    lshard2.push_back(to_string(-map[CPUslot[i-1][CPUslotC].i][CPUslot[i-1][CPUslotC].j+1][CPUslot[i-1][CPUslotC].k].net_id[l])+" "+to_string(map[DDRslot[i-1][DDRslotC].i][DDRslot[i-1][DDRslotC].j-1][DDRslot[i-1][DDRslotC].k].net_id[l])+" 0");
                                }
                            }
                        }
                        CPUslotC = (CPUslotRev[i-1])?CPUslotC - 1:CPUslotC + 1;
                        DDRslotC = (DDRslotRev[i-1])?DDRslotC - 1:DDRslotC + 1;
                    }
                }
                else if(map[i][j][k].type == 'B'){
                    ls.push_back(to_string(-map[i][j][k].var_id)+" 0");
                    if(!i){
                        lshard1.push_back(to_string(-map[i][j][k].var_id)+" 0");
                    }
                    else{
                        lshard2.push_back(to_string(-map[i][j][k].var_id)+" 0");
                    }
                }
            }
        }
    }

    //* group 1 only
    // for each pair of edge in a row(*fan out node is at top/down),
    // 1 edge is true imply another edge is false
    // meaning only 1 edge is true in a row
    // mono start
    for(int z = 0; z < netBox[0].size(); z++){ // 1 group
    //for(int z = 0; z <= 3; z++){ // 1 group

        int dec = z, temp[5] = {0};
        for(int T = 0; T < 5; T++){
            temp[T] = dec % 2;
            dec /= 2;
        }
        
        for(int i = 0; i < map.size(); i++){
            int jmin = 0, jmax = map[i].size();
            int kmin = 0, kmax = map[i][0].size()-1; // -1
            if(set[i].loc == 'B' || set[i].loc == 'b'){ // slot at top
                jmax = P_map[i][z].first;
            }else if(set[i].loc == 'T' || set[i].loc == 't'){ // slot at bot
                jmin = P_map[i][z].first;
            }
            for(int j = jmin; j < jmax; j++){
                for(int k = kmin; k < kmax; k++){
                    if(map[i][j][k].type == 'E' && k % 2 == 1){ // |
                        for(int K = k + 2; K < map.at(i).at(0).size(); K+=2){
                            string tmps = "";
                            for(int T = 0; T < 5; T++){
                                tmps += (temp[T])?(to_string(-map[i][j][k].net_id[T])):(to_string(map[i][j][k].net_id[T]));
                                tmps += " ";
                            }
                            for(int T = 0; T < 5; T++){
                                tmps += (temp[T])?(to_string(-map[i][j][K].net_id[T])):(to_string(map[i][j][K].net_id[T]));
                                tmps += " ";
                            }
                            tmps += "0";
                            ls.push_back(tmps);
                            if(!i){
                                //lshard1.push_back(tmps);
                            }
                            else{
                                lshard2.push_back(tmps);
                            }
                        }  
                    }
                }
            }
        }
    }
    // mono end

    //tile structure begin

    TSoffset offset1, offset2;
    offset1.SetUp(4,4,4,4); // offset from RowLeft, RowRight, ColLeft, ColRight *even only*
    offset2.SetUp(8,0,0,0);
    int nxn = 5; // n x n tile structure
    TileStruct(ls, lshard1, lshard2, map, nxn, offset1, offset2, netBox);
    //drawMap0(map, groupSize, mapsize);

    //To match two map's slot order
    /*for(int i=0; i < pp.size(); i++)
    {
        int a = (CPUslotRev) ? CPUslot[pp.size()-1-i].i : CPUslot[i].i;
        int b = (CPUslotRev) ? CPUslot[pp.size()-1-i].j : CPUslot[i].j;
        int c = (CPUslotRev) ? CPUslot[pp.size()-1-i].k : CPUslot[i].k;
        int x = (DDRslotRev) ? DDRslot[pp.size()-1-i].i : DDRslot[i].i;
        int y = (DDRslotRev) ? DDRslot[pp.size()-1-i].j : DDRslot[i].j;
        int z = (DDRslotRev) ? DDRslot[pp.size()-1-i].k : DDRslot[i].k;
        for(int j=0; j<5; j++)
        {
            //(¬a ∨ b) ∧ (a ∨ ¬b)
            //map[a][b][c].netid = map[x][y][z].netid
            ls.push_back(to_string(-map[a][b][c].net_id[j])+' '+to_string(map[x][y][z].net_id[j])+" 0");
            ls.push_back(to_string(map[a][b][c].net_id[j])+' '+to_string(-map[x][y][z].net_id[j])+" 0");
        }
    }*/
        cout<<"slotloc\nsize"<<endl;
        vector<int> slotnet;
        cout<<CPUslot[0].size()<<endl;
        for(int i=0;i<CPUslot.size();i++){
            for(int j=0;j<CPUslot[i].size();j++){
                for(int k=0;k<5;k++){
                    if(CPUslot[i][j].j == 0)
                        slotnet.push_back(map[CPUslot[i][j].i][CPUslot[i][j].j+1][CPUslot[i][j].k].net_id[k]);
                    else
                        slotnet.push_back(map[CPUslot[i][j].i][CPUslot[i][j].j-1][CPUslot[i][j].k].net_id[k]);
                }
            }
        }
        cout<<"ls_size\n";
        cout<<ls.size()<<' ' << lshard1.size()<<' '<<lshard2.size()<<endl;
        
    string command, line;
    int numSize;
    vector<int> num;
    /*num = phase1_mac(var_id_counter, numSize, ls);
    num = phase2_mac(var_id_counter, numSize, slotnet, lshard1, lssoft1, num);
    draw(0, map, num, P, set, bsize, GU, (int)cfig.group_name.size()+1, mapsize);
    num = phase2_mac(var_id_counter, numSize, slotnet, lshard2, lssoft2, num);
    draw(1, map, num, P, set, bsize, GU, (int)cfig.group_name.size()+1, mapsize);*/
    
    num = phase1_linux(var_id_counter, numSize, ls);
    num = phase2_linux(var_id_counter, numSize, slotnet, lshard1, lssoft1, num);
    draw(0, map, num, P, set, bsize, GU, (int)cfig.group_name.size()+1, mapsize);
    num = phase2_linux(var_id_counter, numSize, slotnet, lshard2, lssoft2, num);
    draw(1, map, num, P, set, bsize, GU, (int)cfig.group_name.size()+1, mapsize);
    
    /*ofstream file("temp.cnf");
    if(file.is_open()){
        file << "c temp.cnf" << endl;
        file << "p wcnf "<<var_id_counter-1<<' '<<ls.size()<<' '<<1<<endl;
        for(string l: ls)
            file << l << endl;
    }
    file.close();

    chrono::steady_clock::time_point tSStart = chrono::steady_clock::now();
    string command = "./open-wbo temp.cnf > output";
    system(command.c_str());
    chrono::steady_clock::time_point tSEnd = chrono::steady_clock::now();
    Stime = chrono::duration_cast<chrono::duration<double>>(tSEnd - tSStart);
    
    ifstream fil;
    string line;
    int numSize;
    fil.open("output", ios::in);
    for(int i=0;i<27;i++){
        getline(fil, line);
        if(line == "") break;
        if(i == 13){ // fetch num of variables
            stringstream ss(line);
            string temp;
            for(int x = 0; x < 6; x++)
                ss >> temp;
            numSize = stoi(temp);
        }
    }
    vector<int> num;
    num.reserve(numSize);
    char c;
    fil >> c;
    int tem, tem2;
    for(;;){
        tem2 = tem;
        fil>>tem;
        if(tem2 == tem) break;
        num.push_back(tem);
    }
    cout << num.size() << endl;
    for(int i=0;i<5;i++)
        cout << num[map[1][34][29].net_id[i]-1] << " " << num[map[1][34][31].net_id[i]-1]<<endl;
    
     
    for(int i = 0; i < set.size(); i++){
        for(int j = 0; j < map.at(i).size(); j++){
            for(int k = 0; k < map.at(i).at(0).size(); k++){
                map[i][j][k].bit = (num[map[i][j][k].var_id-1] > 0) ? true : false;
            }
        }
    }

    // DFS from pin to find redundant cycles
    for(int i = 0; i < map.size(); i++){
        for(int p = 0; p < P[i].size(); p++){
            int x = (P[i][p].first/GU - (set[i].left/GU+1)) * 2 + 1 + bsize;
            int y = ((set[i].top/GU-1) - P[i][p].second/GU) * 2 + 1 + bsize;
            while(map[i][y][x].type != 'S'){
                if(map[i][y+1][x].bit && !map[i][y+1][x].check){ // D
                    map[i][y++][x].check = true;
                }else if(map[i][y-1][x].bit && !map[i][y-1][x].check){ // T
                    map[i][y--][x].check = true;
                }else if(map[i][y][x+1].bit && !map[i][y][x+1].check){ // L
                    map[i][y][x++].check = true;
                }else if(map[i][y][x-1].bit && !map[i][y][x-1].check){ // R
                    map[i][y][x--].check = true;
                }else{
                    cout << "routing from pin has problem!!!" << endl;
                    break;
                }
            }
        }
    }

    for(int i = 0; i < set.size(); i++){
        for(int j = 1; j < map.at(i).size()-1; j++){
            for(int k = 1; k < map.at(i).at(0).size()-1; k++){
                map[i][j][k].bit = (map[i][j][k].check) ? true : false;
            }
        }
    }

    drawMap(map, (int)cfig.group_name.size()+1, num, mapsize);*/


    for (int i=0; i<static_cast<int>(cfig.Pin_Obs_list.size()); i++) {
        OutputRect temp;

        temp.setup(cfig.Pin_Obs_list[i].LBx,cfig.Pin_Obs_list[i].LBy,
                   cfig.Pin_Obs_list[i].RTx,cfig.Pin_Obs_list[i].RTy,999,cfig.Pin_Obs_list[i].Layer);
        outputpin.push_back(temp);
    }

    // *
    string layout_name = "case/1.brd";
    //outputGDS(layout_name, outputpin, outputedge, crossing_line_total);

    chrono::steady_clock::time_point tEnd = chrono::steady_clock::now();
    Ttime = chrono::duration_cast<chrono::duration<double>>(tEnd - tStart);
    cout << endl << "total run time : " << (int)(Ttime.count()/60) << "m " << Ttime.count() - (int)(Ttime.count()/60)*60 << 's'
         << endl << "set solver run time : " << (int)(Stime.count()/60) << "m " << Stime.count() - (int)(Stime.count()/60)*60 << 's' << endl;
    return 0;
}
