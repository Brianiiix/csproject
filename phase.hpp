#ifndef phase_hpp
#define phase_hpp

#include <stdio.h>
#include <list>
#include <string>
using namespace std;

vector<int> phase1_mac(int var_id_counter, int &numSize, list<string> &ls){
    ofstream file("temp.cnf");
     if(file.is_open()){
         file << "c temp.cnf" << endl;
         file << "p wcnf "<<var_id_counter-1<<' '<<ls.size()<<' '<<1<<endl;
         for(string l: ls)
             file << "1 " << l << endl;
     }
     file.close();
    string command = "./open-wbo  /Users/brian/Library/Developer/Xcode/DerivedData/csproject-ewtkybbytxrmoygdjpvtmhcsgjil/Build/Products/Debug/temp.cnf > output";
    system(command.c_str());
    
    ifstream fil;
    fil.open("/Users/brian/Library/Developer/Xcode/DerivedData/csproject-ewtkybbytxrmoygdjpvtmhcsgjil/Build/Products/Debug/output", ios::in);
    string line;
    //int numSize;
    for(int i=0;i<26;i++){
        getline(fil, line);
        if(i == 12){ // fetch num of variables
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
    cout << "Phase 1 Finish" << endl;
    return num;
}

vector<int> phase2_mac(int var_id_counter, int &numSize, vector<int> &slotnet, list<string> &lshard, list<string> &lssoft, vector<int> &num){
    for(int i=0;i<slotnet.size();i++){
        lshard.push_back(to_string(num[slotnet[i]-1])+" 0");
    }
     ofstream file1("temp1.cnf");
     if(file1.is_open()){
         file1 << "c temp1.cnf" << endl;
         file1 << "p wcnf "<<var_id_counter-1<<' '<< lshard.size()+lssoft.size() <<' '<< lssoft.size()*2+1 <<endl;
         for(string l: lshard)
             file1 << lssoft.size()*2+1 << ' ' << l << endl;
         for(string l: lssoft)
             file1 << "2 " << l << endl;
     }
     file1.close();
    string command = "./open-wbo  /Users/brian/Library/Developer/Xcode/DerivedData/csproject-ewtkybbytxrmoygdjpvtmhcsgjil/Build/Products/Debug/temp1.cnf > output1";
    system(command.c_str());
    
    //ifstream fil;
    ifstream file2;
    file2.open("/Users/brian/Library/Developer/Xcode/DerivedData/csproject-ewtkybbytxrmoygdjpvtmhcsgjil/Build/Products/Debug/output1", ios::in);
    string line = "";
    for(int i=0;;i++){
        getline(file2, line);
        if(line[0] == 's') break;
    }
    //vector<int> num;
    num.clear();
    num.reserve(numSize);
    char c;
    file2 >> c;
    int tem;
    while(!file2.eof()){
        file2>>tem;
        num.push_back(tem);
    }
    return num;
}

vector<int> phase1_linux(int var_id_counter, int &numSize, list<string> &ls){
    ofstream file("temp.cnf");
    if(file.is_open()){
        file << "c temp.cnf" << endl;
        file << "p wcnf "<<var_id_counter-1<<' '<<ls.size()<<' '<<1<<endl;
        for(string l: ls)
            file << "1 " << l << endl;
    }
    file.close();

    string command = "./open-wbo temp.cnf > output";
    system(command.c_str());
    
    ifstream fil;
    string line;
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
    return num;
}

vector<int> phase2_linux(int var_id_counter, int &numSize, vector<int> &slotnet, list<string> &lshard, list<string> &lssoft, vector<int> &num){
    for(int i=0;i<slotnet.size();i++){
        lshard.push_back(to_string(num[slotnet[i]-1])+" 0");
    }
     ofstream file1("temp1.cnf");
     if(file1.is_open()){
         file1 << "c temp1.cnf" << endl;
         file1 << "p wcnf "<<var_id_counter-1<<' '<< lshard.size()+lssoft.size() <<' '<< lssoft.size()*2+1 <<endl;
         for(string l: lshard)
             file1 << lssoft.size()*2+1 << ' ' << l << endl;
         for(string l: lssoft)
             file1 << "2 " << l << endl;
     }
     file1.close();
    string command = "./open-wbo temp.cnf > output";
    system(command.c_str());
    
    //ifstream fil;
    ifstream file2;
    file2.open("output", ios::in);
    string line = "";
    for(int i=0;;i++){
        getline(file2, line);
        if(line[0] == 's') break;
    }
    //vector<int> num;
    num.clear();
    num.reserve(numSize);
    char c;
    file2 >> c;
    int tem;
    while(!file2.eof()){
        file2>>tem;
        num.push_back(tem);
    }
    return num;
}

void draw(int i, vector<vector<vector<Node>>> &map, vector<int> &num, vector<vector<pair<int, int>>> &P, vector<boundary> &set,
          int bsize, int GU, int size, vector<pair<int,int>> &mapsize){
    //for(int i = 0; i < set.size(); i++){
        for(int j = 0; j < map.at(i).size(); j++){
            for(int k = 0; k < map.at(i).at(0).size(); k++){
                map[i][j][k].bit = (num[map[i][j][k].var_id-1] > 0) ? true : false;
            }
        }
    //}

    // DFS from pin to find redundant cycles
    //for(int i = 0; i < map.size(); i++){
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
    //}

    //for(int i = 0; i < set.size(); i++){
        for(int j = 1; j < map.at(i).size()-1; j++){
            for(int k = 1; k < map.at(i).at(0).size()-1; k++){
                map[i][j][k].bit = (map[i][j][k].check) ? true : false;
            }
        }
    //}

    drawMap(map, size, num, mapsize, i);
}

#endif /* phase_hpp */
