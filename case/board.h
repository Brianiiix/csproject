#ifndef BOARD_H 
#define BOARD_H


class Obstacle{
    public:
    // LBx, LBy, RTx, RTy, Layer
        int LBx;
        int LBy;
        int RTx;
        int RTy;
        int Layer;
        int net; 

        int center_x;
        int center_y;
        int size;

        void setup(int _LBx, int _LBy, int _RTx, int _RTy, int _Layer, int _net, int _center_x = -1,int _center_y = -1,int _size = -1){
            LBx = _LBx;
            LBy = _LBy;
            RTx = _RTx;
            RTy = _RTy;
            Layer = _Layer;
            net = _net;

            center_x = _center_x;
            center_y = _center_y;
            size = _size;
        }
};

class pin{
    public:
    std::string name;
    int x;
    int y;
    int pinNo;

    int pin_x;
    int pin_y;
    int new_x;
    int new_y;
	int net;
};

struct edge{
    int start;
    int end;
};

#endif
