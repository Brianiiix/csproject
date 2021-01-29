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
            file << l << endl;
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

#endif /* phase_hpp */
