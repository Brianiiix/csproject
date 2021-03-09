#ifndef draw_hpp
#define draw_hpp

#include <vector>
#include <iostream>
#include <string>
using namespace std;

void draw_Klayout(vector<vector<vector<vector<Node>>>> &map, int GU){ // map here is map_box in routingBoard.cpp
    
    // single grid
    string str;
    // entire map
    vector<string> str_box;
    // connect slots between CPU and DDR
    vector<int> slot_x, slot_y;
    vector<vector<int>> slot_x_box, slot_y_box;
    // example: b{999 dt0 xy(251.658 265.338 251.722 265.338 251.722 265.402 251.658 265.402)}
    str_box.push_back(string("gds2{600"));
    str_box.push_back(string("m=2020-07-29 16:40:40 a=2020-07-29 16:40:40"));
    str_box.push_back(string("lib 'lib' 0.00025 2.5e-10"));
    str_box.push_back(string("cell{c=2020-07-29 16:40:40 m=2020-07-29 16:40:40 'case/1.brd'"));
    for(int z=0; z<map.size(); z++){
    for(int i=0; i<map[z].size(); i++){
        for(int j=0; j<map[z][0].size(); j++){
            for(int k=0; k<map[z][0][0].size(); k++){
                char type = map[z][i][j][k].type;
                if(type != 'X' && type != 'G' && (type == 'E' && map[z][i][j][k].bit == true)){
                    //cout << map[i][j][k].type << " ";
                    str += string("b{") + to_string(z) + string(" dt1 xy(");
                    //str += string(" : ") + to_string(map[i][j][k].x) + to_string(map[i][j][k].y) + string(" : ");
                    str +=               to_string(map[z][i][j][k].x + GU/200);
                    str += string(" ") + to_string(map[z][i][j][k].y + GU/200);
                    
                    str += string(" ") + to_string(map[z][i][j][k].x - GU/200);
                    str += string(" ") + to_string(map[z][i][j][k].y + GU/200);
                    str += string(" ") + to_string(map[z][i][j][k].x - GU/200);
                    str += string(" ") + to_string(map[z][i][j][k].y - GU/200);
                    str += string(" ") + to_string(map[z][i][j][k].x + GU/200);
                    str += string(" ") + to_string(map[z][i][j][k].y - GU/200);

                    str += string(")}");
                    str_box.push_back(str);
                    str.clear();
                }
                if(type == 'S' && map[z][i][j][k].bit == true){
                    cout << map[z][i][j][k].x << " " << map[z][i][j][k].y << endl;
                    slot_x.push_back(map[z][i][j][k].x);
                    slot_y.push_back(map[z][i][j][k].y);
                }   
            }
        }
        slot_x_box.push_back(slot_x);
        slot_y_box.push_back(slot_y);
        slot_x.clear();
        slot_y.clear();
    }
    for(int i=1; i<slot_x_box.size(); i++){
        for(int j=0; j<slot_x_box[i].size(); j++){
            str += string("b{") + to_string(z) + string(" dt1 xy(");
            //str += string(" : ") + to_string(map[i][j][k].x) + to_string(map[i][j][k].y) + string(" : ");
            str += string(" ") + to_string(slot_x_box[0][j] - GU/200);
            str += string(" ") + to_string(slot_y_box[0][j] - GU/200);
            str += string(" ") + to_string(slot_x_box[0][j] - GU/200);
            str += string(" ") + to_string(slot_y_box[0][j] + GU/200);
            str += string(" ") + to_string(slot_x_box[0][j] + GU/200);
            str += string(" ") + to_string(slot_y_box[0][j] + GU/200);
            str += string(" ") + to_string(slot_x_box[0][j] + GU/200);
            str += string(" ") + to_string(slot_y_box[0][j] - GU/200);
            
            str += string(" ") + to_string(slot_x_box[i][j] + GU/200);
            str += string(" ") + to_string(slot_y_box[i][j] + GU/200);
            str += string(" ") + to_string(slot_x_box[i][j] + GU/200);
            str += string(" ") + to_string(slot_y_box[i][j] - GU/200);
            str += string(" ") + to_string(slot_x_box[i][j] - GU/200);
            str += string(" ") + to_string(slot_y_box[i][j] - GU/200);
            str += string(" ") + to_string(slot_x_box[i][j] - GU/200);
            str += string(" ") + to_string(slot_y_box[i][j] + GU/200);
            

            str += string(")}");
            str_box.push_back(str);
            str.clear();
        }
    }
    slot_x_box.clear();
    slot_y_box.clear();
    }

    str_box.push_back(string("}"));
    str_box.push_back(string("}"));

    
    string name = string("draw");
    ofstream file(name);
    if(file.is_open()){
        for(int i=0; i<str_box.size(); i++){
            file << str_box[i] << endl;
        }
    }
    file.close();

    string command = string("./gdt2gds ") + name + string(".gdt ") + name + string(".gds");
    system(command.c_str());
    
}

#endif