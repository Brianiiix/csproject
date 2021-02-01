#include <vector>
#include <map>
#include <algorithm>
using namespace std;

map<int, int> v_pin;
vector<map<int, int>> v_temp;


//num = number of pin in each layer, m = number of total pin, begin and level should be 0 while calling
//output(store in v_temp) would be like 01234 01235 01236 01245 01246 ...
void rec(int level, int num, int m, int begin){
    if(level != num){
        for(int i = begin; i < m; i++){
            v_pin[level] = i;
            level++;
            rec(level, num, m, i+1);
            level--;
        }
    }
    else{
        v_temp.push_back(v_pin);

    }
}

//comb = all combination generated by function rec, num = number of pin in each layer
map<int, int> cross(vector<map<int, int>> comb, vector< vector< pair<int, int> > > &Pin, int num){
    //min num of cross time currently
    int min = 1000;
    map<int, int> ans;
    for(int i = 0; i < comb.size(); i++){
        int max = 0, cnt = 0;
        for(int j = 0; j < num; j++){
            if(Pin[1][comb[i][j]].second > max){
                max = Pin[1][comb[i][j]].second;
            }
            else{
                cnt++;
            }            
        }
        if(cnt < min){
            min = cnt;
            ans = comb[i];
        }
    }
    return ans;
}

bool equal(pair<int, int> p1, pair<int, int> p2){
    if(p1.first == p2.first && p1.second == p2.second) return 1;
    else return 0;
}

//from index of P to layer#
//num = how many layer
map<int, int> layer(int num, vector< vector< pair<int, int> > > P){

    vector< vector< pair<int, int> > > Pin = P;
    //bubble sort
    for(int i = 0; i < Pin[0].size()-1; i++){
        for(int j = i+1; j < Pin[0].size(); j++){
            if(Pin[0][i].second > Pin[0][j].second){
                pair<int, int> tmp = Pin[0][i];
                Pin[0][i] = Pin[0][j];
                Pin[0][j] = tmp;
                pair<int, int> tmp2 = Pin[1][i];
                Pin[1][i] = Pin[1][j];
                Pin[1][j] = tmp2;
            }
        }
    }
    int numInEach = (Pin[0].size() % num == 0) ? Pin[0].size()/num : Pin[0].size()/num + 1;
    int lastPin = Pin[0].size();
    for(int i = 0; i < num-1; i++){
        v_temp.clear();
        rec(0, numInEach, lastPin, 0);
        map<int, int> ans = cross(v_temp, Pin, numInEach);
        for(int j = 0; j < numInEach; j++){
            auto itt1 = Pin[0].begin(), itt2 = Pin[1].begin();
            for(int k = 0; k < ans[j]-j; k++) {itt1++; itt2++;}
            //move the element to the back of vector
            rotate(itt1, itt1+1, Pin[0].end());
            rotate(itt2, itt2+1, Pin[1].end());
        }
        lastPin -= numInEach;
    }
    map<int, int> ans;
    for(int i = 0; i < P[0].size(); i++){
        for(int j = 0; j < Pin[0].size(); j++){
            if(equal(Pin[0][i], P[0][j]) == 1){
                //cout << i << " " << j << "test" << endl;
                if(j < P[0].size()%numInEach) ans[i] = 0;
                else ans[i] = (P[0].size()%numInEach == 0) ? ((j-(P[0].size()%numInEach))/numInEach) : ((j-(P[0].size()%numInEach))/numInEach)+1;
                break;
            }
        }
    }

    return ans;
}