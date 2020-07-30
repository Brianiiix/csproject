#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ostream>
#include <map>
#include <set>
#include <math.h>
#include <time.h>
#include "board.h"
#include "IO_interface.hpp"
#include "output_gds.hpp"

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
                        std::cout<<"file name"<<FileName;
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
                        printf("Min spacing : %d\n",MIN_SPACING);
                    }
                    else if(string_list.at(0) == "WIRE_WIDTH:"){
                        WIRE_WIDTH = atoi(string_list.at(1).c_str());
                        printf("wire width : %d\n",WIRE_WIDTH);
                    }
                    else if(string_list.at(0) == "USED_LAYER:"){
                        USED_LAYER = atoi(string_list.at(1).c_str());
                        printf("#used layer : %d\n",USED_LAYER);
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

int main(int argc, const char * argv[]) {
    int total_net_num = 0;
    clock_t tStart = clock();
    config cfig;
    cfig.load_config("config/config_1_1.txt");

    string obs_name = "case/1.brd";
        //wefewf
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

    for(int i = 0; i < net.size(); i++){
        printf("Net %d : \n",i);
        for(int j = 0; j < net.at(i).size(); j++){
            printf("    %s (%d,%d)\n",pin.at(net.at(i).at(j)).name.c_str(),pin.at(net.at(i).at(j)).x,pin.at(net.at(i).at(j)).y);
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
    outputGDS(layout_name, outputpin, outputedge, crossing_line_total);

    return 0;
}
