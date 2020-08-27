#include <iostream>
#include <string>
#include <limits.h>
#include <vector>
using namespace std;

struct pinpair{
    int first_x;
    int first_y;
    int second_x;
    int second_y;
};

struct boundary{
    int top;
    int down;
    int left;
    int right;
    // C = CPU, T = Top left, t = Top right, B = Bottom left, b = Bottom right
    char loc = 'C';
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

boundary findboundary(vector<pinpair> &pp, int num)
{
    int top = 0;
    int down = INT_MAX;
    int left = INT_MAX;
    int right = 0;
    if(num == 1){
        for(int i = 0; i < pp.size(); i++)
        {
            top = (pp[i].first_y > top) ? pp[i].first_y : top;
            down = (pp[i].first_y < down) ? pp[i].first_y : down;
            left = (pp[i].first_x < left) ? pp[i].first_x : left;
            right = (pp[i].first_x > right) ? pp[i].first_x : right;
        }
    }
    if(num == 2){
        for(int i = 0; i < pp.size(); i++)
        {
            top = (pp[i].second_y > top) ? pp[i].second_y : top;
            down = (pp[i].second_y < down) ? pp[i].second_y : down;
            left = (pp[i].second_x < left) ? pp[i].second_x : left;
            right = (pp[i].second_x > right) ? pp[i].second_x : right;
        }
    }
    boundary b;
    b.top = top;
    b.down = down;
    b.left = left;
    b.right = right;
    return b;
}
