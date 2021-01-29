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
        
		// S = Slot, E = Edge, P = Pin, G = Grid, B = boundary X = nothing
		char type = 'X';
		// from which ddr
		int group;
		int var_id;
        int pin_id;
    	int net_id[5] = {0};
		bool bit;
		// check redundant cycles
		bool check = false;

		bool tilestruct = false;
		void SetUp(int _x,int _y){
			x = _x;
			y = _y;
			//var_id = var;
		}
};

struct TSoffset{
	// Row/Column offset from Left/Right
	int RL, RR, CL, CR;
	void SetUp(int rl, int rr, int cl, int cr){
		RL = rl, RR = rr, CL = cl, CR = cr;
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

void drawMap(vector<vector<vector<Node>>> &map, int groupSize, vector<int> &num, vector<pair<int,int>> &mapsize, int i){
	//for(int i = 0; i < groupSize; i++){
		cout << "\n---Grid map " << i << "---";
		cout << "(" << mapsize[i].first << " x " << mapsize[i].second << ")" << endl;
		cout << " ";
		for(int I = 0; I < map.at(i).at(0).size(); I++){
			if(I%10 == 0 || I%10 == 5)
				cout << I % 10;
			else
				cout << " ";
		}
		cout << endl;
		for(int j = 0; j < map.at(i).size(); j++){
			if(j%10 == 0 || j%10 == 5)
				cout<< j % 10;
			else
				cout << " ";
			for(int k = 0; k < map.at(i).at(0).size(); k++){
				switch (map[i][j][k].type){
					case 'X' : cout << ' '; break;
					case 'G' :
						if(map[i][j][k].bit)
							cout << '.';
						//cout << ((num[map[i][j][k].net_id[0]-1])>0?1:0)+((num[map[i][j][k].net_id[1]-1]>0)?2:0)+
                    	//((num[map[i][j][k].net_id[2]-1]>0)?4:0)+((num[map[i][j][k].net_id[3]-1]>0)?8:0)+((num[map[i][j][k].net_id[4]-1]>0)?16:0);
						else if(map[i][j][k].tilestruct)
							cout << '#';
						else
							cout << ' ';
						break;
					case 'E' :
						if(map[i][j][k].bit)
							cout << ((k % 2 == 0)?'-':'|'); 						
							//cout << ((num[map[i][j][k].net_id[0]-1])>0?1:0)+((num[map[i][j][k].net_id[1]-1]>0)?2:0)+
                    	//((num[map[i][j][k].net_id[2]-1]>0)?4:0)+((num[map[i][j][k].net_id[3]-1]>0)?8:0)+((num[map[i][j][k].net_id[4]-1]>0)?16:0);
						else if(map[i][j][k].tilestruct)
							cout << '#';
						else
							cout << ' ';
						break;
					case 'P' :
						//if(i == 0)
							//cout << map[i][j][k].group;
						//else
							//cout << 'x';
						cout << ((num[map[i][j][k].net_id[0]-1])>0?1:0)+((num[map[i][j][k].net_id[1]-1]>0)?2:0)+
                    	((num[map[i][j][k].net_id[2]-1]>0)?4:0)+((num[map[i][j][k].net_id[3]-1]>0)?8:0)+((num[map[i][j][k].net_id[4]-1]>0)?16:0);
						break;
                    case 'S' : //cout << 'S'; break;
						if(j == 0)
							cout << (((num[map[i][j+1][k].net_id[0]-1])>0?1:0)+((num[map[i][j+1][k].net_id[1]-1]>0)?2:0)+
                    		((num[map[i][j+1][k].net_id[2]-1]>0)?4:0)+((num[map[i][j+1][k].net_id[3]-1]>0)?8:0)+((num[map[i][j+1][k].net_id[4]-1]>0)?16:0))%10;
						else
							cout << (((num[map[i][j-1][k].net_id[0]-1])>0?1:0)+((num[map[i][j-1][k].net_id[1]-1]>0)?2:0)+
                    		((num[map[i][j-1][k].net_id[2]-1]>0)?4:0)+((num[map[i][j-1][k].net_id[3]-1]>0)?8:0)+((num[map[i][j-1][k].net_id[4]-1]>0)?16:0))%10;
						break;
                    case 'B' : cout << '#'; break;
				}
			}
			if(j%10 == 0 || j%10 == 5)
				cout<< j % 10;
			else
				cout << " ";
			cout << endl;
		}
		cout << " ";
		for(int I = 0; I < map.at(i).at(0).size(); I++){
			if(I%10 == 0 || I%10 == 5)
				cout << I % 10;
			else
				cout << " ";
		}
		cout << endl;
	//}
}

// map before routing
void drawMap0(vector<vector<vector<Node>>> &map, int groupSize, vector<pair<int,int>> &mapsize){
	for(int i = 0; i < groupSize; i++){
		cout << "\n---Grid map " << i << "---";
		cout << "(" << mapsize[i].first << " x " << mapsize[i].second << ")" << endl;
		cout << " ";
		for(int I = 0; I < map.at(i).at(0).size(); I++){
			if(I%10 == 0 || I%10 == 5)
				cout << I % 10;
			else
				cout << " ";
		}
		cout << endl;
		for(int j = 0; j < map.at(i).size(); j++){
			if(j%10 == 0 || j%10 == 5)
				cout<< j % 10;
			else
				cout << " ";
			for(int k = 0; k < map.at(i).at(0).size(); k++){
				switch (map[i][j][k].type){
					case 'X' : cout << ' '; break;
					case 'G' :
						if(map[i][j][k].tilestruct)
							cout << 'G';
						else
							cout << ' ';
						break;
					case 'E' :
						if(map[i][j][k].tilestruct)
							cout << 'E';
						else
							cout << ' ';
						break;
					case 'P' :
						//if(i == 0)
							//cout << map[i][j][k].group;
						//else
							//cout << 'x';
						cout << (map[i][j][k].net_id[0]>0?1:0)+(map[i][j][k].net_id[1]?2:0)+
                    	(map[i][j][k].net_id[2]?4:0)+(map[i][j][k].net_id[3]?8:0)+(map[i][j][k].net_id[4]?16:0); break;
						break;
                    case 'S' : cout << 'S'; break;
						//cout << ((num[map[i][j][k].net_id[0]-1])>0?1:0)+((num[map[i][j][k].net_id[1]-1]>0)?2:0)+
                    	//((num[map[i][j][k].net_id[2]-1]>0)?4:0)+((num[map[i][j][k].net_id[3]-1]>0)?8:0)+((num[map[i][j][k].net_id[4]-1]>0)?16:0); break;
                    case 'B' : cout << '#'; break;
				}
			}
			if(j%10 == 0 || j%10 == 5)
				cout<< j % 10;
			else
				cout << " ";
			cout << endl;
		}
		cout << " ";
		for(int I = 0; I < map.at(i).at(0).size(); I++){
			if(I%10 == 0 || I%10 == 5)
				cout << I % 10;
			else
				cout << " ";
		}
		cout << endl;
	}
}

struct slot{
    int i, j, k;

    void setup(int _i, int _j, int _k)
    {
        i = _i;
        j = _j;
        k = _k;
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
