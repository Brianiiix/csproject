#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
// fileName = "./case/1.brd_input.pCSet" 
// fileName2 = "./case/1.brd_input.sCSet"
// typeName = "DEFAULT"
// typeName2 = "DEFAULT"
// return -88888888 == wrong file typeName
int findType(string fileName, string typeName, string fileName2, string typeName2){
    ifstream file;
    string line;
    int ans = 0, check = 0;
    file.open(fileName);
    if(file.is_open()){
        while(getline(file, line)){
            stringstream ss(line);
            string s1, s2;
            ss >> s1 >> s2;
            if(s2 == typeName){
                getline(file, line);
                ss.clear();
                ss.str(line);
                ss >> s1 >> s2;
                ans += stoi(s2) * 100;
                check = 1;
                break;
            }
        }
    }
    file.close();
    if(!check){
        return -88888888;
    }
    check = 0;
    file.open(fileName2);
    if(file.is_open()){
        while(getline(file, line)){
            stringstream ss(line);
            string s1, s2;
            ss >> s1 >> s2;
            if(s2 == typeName2){
                getline(file, line);
                ss.clear();
                ss.str(line);
                ss >> s1 >> s2;
                ans += stoi(s2) * 100;
                check = 1;
                break;
            }
        }
    }
    if(!check){
        return -88888888;
    }
    file.close();
    return ans;
}