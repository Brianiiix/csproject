#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <algorithm>
#include <set>

#include "Structure.hpp"

using namespace std;

void output_gds(vector<Rect> &rect_list, string &gds_name);

int cross(int ox, int oy, int ax, int ay, int bx, int by)
{
   long long temp = static_cast<long long>(ax-ox) * static_cast<long long>(by-oy) - static_cast<long long>(ay-oy) * static_cast<long long>(bx-ox);

    if (temp > 0)
        return 1;
    else if (temp < 0)
        return -1;
    else
        return 0;
}

bool intersection(int px, int py, int p1x, int p1y, int p2x, int p2y)
{
    return px >= min(p1x, p2x)
        && px <= max(p1x, p2x)
        && py >= min(p1y, p2y)
        && py <= max(p1y, p2y);
}

bool intersect(int a1x, int a1y, int a2x, int a2y, int b1x, int b1y, int b2x, int b2y)
{
    if (max(a1x, a2x) < min(b1x, b2x) ||
        max(a1y, a2y) < min(b1y, b2y) ||
        max(b1x, b2x) < min(a1x, a2x) ||
        max(b1y, b2y) < min(a1y, a2y)) {
        return false;
    }

    int c1 = cross(a1x, a1y, a2x, a2y, b1x, b1y);
    int c2 = cross(a1x, a1y, a2x, a2y, b2x, b2y);
    int c3 = cross(b1x, b1y, b2x, b2y, a1x, a1y);
    int c4 = cross(b1x, b1y, b2x, b2y, a2x, a2y);
 
    // 端點不共線
    if (c1 * c2 < 0 && c3 * c4 < 0) return true;
    // 端點共線
    if (c1 == 0 && intersection(a1x, a1y, a2x, a2y, b1x, b1y)) return true;
    if (c2 == 0 && intersection(a1x, a1y, a2x, a2y, b2x, b2y)) return true;
    if (c3 == 0 && intersection(b1x, b1y, b2x, b2y, a1x, a1y)) return true;
    if (c4 == 0 && intersection(b1x, b1y, b2x, b2y, a2x, a2y)) return true;
    return false;
}

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
      std::string::size_type pos1, pos2;
      pos2 = s.find(c);
      pos1 = 0;
      while(std::string::npos != pos2)
      {
        v.push_back(s.substr(pos1, pos2-pos1));
     
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
      }
      if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}