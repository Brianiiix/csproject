#include <iostream>
#include <string>
#include <limits.h>
#include <vector>
using namespace std;

struct boundary{
    int top;
    int down;
    int left;
    int right;
    // C = CPU, T = Top left, t = Top right, B = Bottom left, b = Bottom right, X:default
    char loc = 'X';
    void setUp(int _top, int _down, int _left, int _right){
        top = _top;
        down = _down;
        left = _left;
        right = _right;
    }
};

int exactgrid(int a, int unit)
{
    if(a-(a/unit*unit) > (unit/2) || a-(a/unit*unit) < -(unit/2))
        return (a/unit+1)*unit;
    else
        return a/unit*unit;
}

boundary findBoundary(vector<pair<int,int>> &P){
    int top = 0;
    int down = INT_MAX;
    int left = INT_MAX;
    int right = 0;
    for(int i = 0; i < P.size(); i++){
        top = (P[i].second > top) ? P[i].second : top;
        down = (P[i].second < down) ? P[i].second : down;
        left = (P[i].first < left) ? P[i].first : left;
        right = (P[i].first > right) ? P[i].first : right;
    }
    
    boundary b;
    b.setUp(top, down, left, right);

    return b;
}