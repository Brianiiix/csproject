#include <ctime>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#define EPS 1e-9
using namespace std;

class OutputRect{
	public:
		int LB_x,LB_y;
		int RT_x,RT_y;
		int layer;
		int data_structure;
		void setup(int _LB_x,int _LB_y,int _RT_x,int _RT_y,int Layer = 0, int DS = 0){
			LB_x = _LB_x;
			LB_y = _LB_y;
			RT_x = _RT_x;
			RT_y = _RT_y;
			layer= Layer;
			data_structure = DS;
		}
};

class Line_Box{
	public:
		int src_x,src_y;
		int tar_x,tar_y;
		int layer;
		int data_structure;
		void setup(int sx, int sy, int tx, int ty,int Layer = 0, int DS = 0){
			src_x = sx;
			src_y = sy;
			tar_x = tx;
			tar_y = ty;
			layer= Layer;
			data_structure = DS;
		}
};

void outputGDS(string &layout_name, vector <OutputRect> &rec_list, vector <Line_Box> &line_list,vector< vector<int> > &crossing_line)
{
	auto Normalize = [&](const int &number) -> double {
		return static_cast<double>(number) / 1000.0 + EPS;
	};
	
	FILE* ofile = fopen("temp.gdt", "wb");

	if (ofile == nullptr) {
		//cout << "Error: cannot open output file " << filename << '\n';
		return;
	}
	
	// get current time, and output to a string
	time_t rawtime;
	struct tm * timeinfo = nullptr;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	char timeseq[25];
	// tm_year is the years counted from 1900 A.D.
	sprintf(timeseq, "%d-%02d-%02d %02d:%02d:%02d", timeinfo->tm_year + 1900, timeinfo->tm_mon+1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	
	// gdt header
	fputs("gds2{600\n", ofile);
	fprintf(ofile, "m=%s a=%s\n", timeseq, timeseq);
	fputs("lib 'lib' 0.00025 2.5e-10\n", ofile);

	// output layout info
	fprintf(ofile, "cell{c=%s m=%s '%s'\n", timeseq, timeseq, layout_name.c_str());
	
	for(int i = 0; i < line_list.size(); i++){
		
		Line_Box rec = line_list.at(i);
		
		int width = 2;
		
		fprintf(ofile, "b{%d dt%d xy(%.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf)}\n", rec.layer, rec.data_structure, Normalize(rec.src_x + width) , 
                Normalize(rec.src_y) , Normalize(rec.src_x - width) , Normalize(rec.src_y), Normalize(rec.tar_x - width), Normalize(rec.tar_y), Normalize(rec.tar_x + width), Normalize(rec.tar_y));

	}
	
	for(int i = 0; i < rec_list.size(); i++){
		
		OutputRect rec = rec_list.at(i);
		
		fprintf(ofile, "b{%d dt%d xy(%.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf)}\n", rec.layer, rec.data_structure, Normalize(rec.LB_x) , 
                Normalize(rec.LB_y) , Normalize(rec.RT_x) , Normalize(rec.LB_y), Normalize(rec.RT_x), Normalize(rec.RT_y), Normalize(rec.LB_x), Normalize(rec.RT_y));

	}

	for (int i = 0; i < crossing_line.size(); i++)
	{
		if (crossing_line.at(i).size() == 8){
			fprintf(ofile, "b{%d dt%d xy(%.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf)}\n", i, 255, Normalize(crossing_line.at(i).at(0)),
					Normalize(crossing_line.at(i).at(1)), Normalize(crossing_line.at(i).at(2)), Normalize(crossing_line.at(i).at(3)), Normalize(crossing_line.at(i).at(4)), Normalize(crossing_line.at(i).at(5)), Normalize(crossing_line.at(i).at(6)), Normalize(crossing_line.at(i).at(7)));
		}
	}
	
	fputs("}\n}\n", ofile);
	fclose(ofile);
	
	
	string command = "./gdt2gds temp.gdt " + layout_name + ".gds";
    system(command.c_str());
    //system("rm temp.gdt");
}