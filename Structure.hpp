#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <algorithm>
#include <set>

//#define NET_BIT 5
#define EPS 1e-9

using namespace std;

int SAT_BOOL_VAR_ID = 1;
vector <string> DIMACS_line;
int DIMACS_NUM = 0;
vector <string> Soft_DIMACS_line;
int Soft_DIMACS_NUM = 0;
int total_soft_weight = 0;
int NET_BIT = 6;

int net_bit_num = 0;
int node_num = 0;
int net_num = 0;
int edge_num = 0;

class Node_bit{
	public:
		int var_id;
		// SAT value
		bool bit;
};

class Node{
	public:
		int x; 
		int y;

		int real_x;
		int real_y;

		int cost;
        
		// S = Slot, E = Edge, P = Pin, G = Grid, X = nothing
		char type = 'X';
		int var_id;
		bool bit;

		void SetUp(int _x,int _y){
			x = _x;
			y = _y;
			//var_id = var;
		}
};

bool comp_Node(Node first,Node second)
{
    return (first.cost < second.cost);
}

class Edge{
	public:
		int x, y;
		int dir; // 0: hor, 1: ver

		void SetUp(int _x, int _y, int _dir)
		{
			x = _x;
			y = _y;
			dir = _dir;
		}
};


class Rect{
	
	public:
		int LB_x;
		int LB_y;
		int RT_x;
		int RT_y;
		
		int net;

		int ds;
		
		void SetRect(int n,int lbx, int lby, int rtx,int rty, int _ds = 0){
			LB_x = lbx;
			LB_y = lby;
			RT_x = rtx;
			RT_y = rty;
			net = n;
			ds = _ds;
		}
	
};