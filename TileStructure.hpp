using namespace std;

void EdgeIdNotTheSame(list<string> &ls, int a, int b, int c1, int c2, int c3, int c4, int c5, int d1, int d2, int d3, int d4, int d5){

                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(-c2)+' '+to_string(-c3)+' '
                        +to_string(-c4)+' '+to_string(-c5)+' '+to_string(-d1)+' '+to_string(-d2)+' '+to_string(-d3)+' '
                        +to_string(-d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(-c2)+' '+to_string(-c3)+' '
                        +to_string(-c4)+' '+to_string(c5)+' '+to_string(-d1)+' '+to_string(-d2)+' '+to_string(-d3)+' '
                        +to_string(-d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(-c2)+' '+to_string(-c3)+' '
                        +to_string(c4)+' '+to_string(-c5)+' '+to_string(-d1)+' '+to_string(-d2)+' '+to_string(-d3)+' '
                        +to_string(d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(-c2)+' '+to_string(c3)+' '
                        +to_string(-c4)+' '+to_string(-c5)+' '+to_string(-d1)+' '+to_string(-d2)+' '+to_string(d3)+' '
                        +to_string(-d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(c2)+' '+to_string(-c3)+' '
                        +to_string(-c4)+' '+to_string(-c5)+' '+to_string(-d1)+' '+to_string(d2)+' '+to_string(-d3)+' '
                        +to_string(-d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(-c2)+' '+to_string(-c3)+' '
                        +to_string(-c4)+' '+to_string(-c5)+' '+to_string(d1)+' '+to_string(-d2)+' '+to_string(-d3)+' '
                        +to_string(-d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(c2)+' '+to_string(-c3)+' '
                        +to_string(-c4)+' '+to_string(-c5)+' '+to_string(d1)+' '+to_string(d2)+' '+to_string(-d3)+' '
                        +to_string(-d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(-c2)+' '+to_string(c3)+' '
                        +to_string(-c4)+' '+to_string(-c5)+' '+to_string(d1)+' '+to_string(-d2)+' '+to_string(d3)+' '
                        +to_string(-d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(-c2)+' '+to_string(-c3)+' '
                        +to_string(c4)+' '+to_string(-c5)+' '+to_string(d1)+' '+to_string(-d2)+' '+to_string(-d3)+' '
                        +to_string(d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(-c2)+' '+to_string(-c3)+' '
                        +to_string(-c4)+' '+to_string(c5)+' '+to_string(d1)+' '+to_string(-d2)+' '+to_string(-d3)+' '
                        +to_string(-d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(c2)+' '+to_string(c3)+' '
                        +to_string(-c4)+' '+to_string(-c5)+' '+to_string(-d1)+' '+to_string(d2)+' '+to_string(d3)+' '
                        +to_string(-d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(c2)+' '+to_string(-c3)+' '
                        +to_string(c4)+' '+to_string(-c5)+' '+to_string(-d1)+' '+to_string(d2)+' '+to_string(-d3)+' '
                        +to_string(d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(c2)+' '+to_string(-c3)+' '
                        +to_string(-c4)+' '+to_string(c5)+' '+to_string(-d1)+' '+to_string(d2)+' '+to_string(-d3)+' '
                        +to_string(-d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(-c2)+' '+to_string(c3)+' '
                        +to_string(c4)+' '+to_string(-c5)+' '+to_string(-d1)+' '+to_string(-d2)+' '+to_string(d3)+' '
                        +to_string(d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(-c2)+' '+to_string(c3)+' '
                        +to_string(-c4)+' '+to_string(c5)+' '+to_string(-d1)+' '+to_string(-d2)+' '+to_string(d3)+' '
                        +to_string(-d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(-c2)+' '+to_string(-c3)+' '
                        +to_string(c4)+' '+to_string(c5)+' '+to_string(-d1)+' '+to_string(-d2)+' '+to_string(-d3)+' '
                        +to_string(d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(c2)+' '+to_string(c3)+' '
                        +to_string(-c4)+' '+to_string(-c5)+' '+to_string(d1)+' '+to_string(d2)+' '+to_string(d3)+' '
                        +to_string(-d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(c2)+' '+to_string(-c3)+' '
                        +to_string(c4)+' '+to_string(-c5)+' '+to_string(d1)+' '+to_string(d2)+' '+to_string(-d3)+' '
                        +to_string(d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(c2)+' '+to_string(-c3)+' '
                        +to_string(-c4)+' '+to_string(c5)+' '+to_string(d1)+' '+to_string(d2)+' '+to_string(-d3)+' '
                        +to_string(-d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(-c2)+' '+to_string(c3)+' '
                        +to_string(c4)+' '+to_string(-c5)+' '+to_string(d1)+' '+to_string(-d2)+' '+to_string(d3)+' '
                        +to_string(d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(-c2)+' '+to_string(c3)+' '
                        +to_string(-c4)+' '+to_string(c5)+' '+to_string(d1)+' '+to_string(-d2)+' '+to_string(d3)+' '
                        +to_string(-d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(-c2)+' '+to_string(-c3)+' '
                        +to_string(c4)+' '+to_string(c5)+' '+to_string(d1)+' '+to_string(-d2)+' '+to_string(-d3)+' '
                        +to_string(d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(c2)+' '+to_string(c3)+' '
                        +to_string(c4)+' '+to_string(-c5)+' '+to_string(-d1)+' '+to_string(d2)+' '+to_string(d3)+' '
                        +to_string(d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(c2)+' '+to_string(c3)+' '
                        +to_string(-c4)+' '+to_string(c5)+' '+to_string(-d1)+' '+to_string(d2)+' '+to_string(d3)+' '
                        +to_string(-d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(c2)+' '+to_string(-c3)+' '
                        +to_string(c4)+' '+to_string(c5)+' '+to_string(-d1)+' '+to_string(d2)+' '+to_string(-d3)+' '
                        +to_string(d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(-c2)+' '+to_string(c3)+' '
                        +to_string(c4)+' '+to_string(c5)+' '+to_string(-d1)+' '+to_string(-d2)+' '+to_string(d3)+' '
                        +to_string(d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(c2)+' '+to_string(c3)+' '
                        +to_string(c4)+' '+to_string(-c5)+' '+to_string(d1)+' '+to_string(d2)+' '+to_string(d3)+' '
                        +to_string(d4)+' '+to_string(-d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(c2)+' '+to_string(c3)+' '
                        +to_string(-c4)+' '+to_string(c5)+' '+to_string(d1)+' '+to_string(d2)+' '+to_string(d3)+' '
                        +to_string(-d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(c2)+' '+to_string(-c3)+' '
                        +to_string(c4)+' '+to_string(c5)+' '+to_string(d1)+' '+to_string(d2)+' '+to_string(-d3)+' '
                        +to_string(d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(-c2)+' '+to_string(c3)+' '
                        +to_string(c4)+' '+to_string(c5)+' '+to_string(d1)+' '+to_string(-d2)+' '+to_string(d3)+' '
                        +to_string(d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(-c1)+' '+to_string(c2)+' '+to_string(c3)+' '
                        +to_string(c4)+' '+to_string(c5)+' '+to_string(-d1)+' '+to_string(d2)+' '+to_string(d3)+' '
                        +to_string(d4)+' '+to_string(d5)+" 0");
                        ls.push_back(to_string(-a)+' '+to_string(-b)+' '+to_string(c1)+' '+to_string(c2)+' '+to_string(c3)+' '
                        +to_string(c4)+' '+to_string(c5)+' '+to_string(d1)+' '+to_string(d2)+' '+to_string(d3)+' '
                        +to_string(d4)+' '+to_string(d5)+" 0");    
}

void TileStruct(list<string> &ls, vector<vector<vector<Node>>> &map, int nxn, TSoffset offset){
    /*
         top
     11-13-...-1x  <--RowNow
     |          |
     31        3x
left |          | right
     .          . 
     .          .
     .          .
     |          |
     x1-x3-...-xx
     ^   bottom
     |______________ColNow

    SideLen = x
    */
    int SideLen = 9; //default = 9
    int ColNow, RowNow;
    for(int i = 0; i < map.size(); i++){//Group
        for(int RowNow = 1+offset.RL; RowNow + 8 + offset.RR < map[i].size()-1; RowNow += 8){
            for(int ColNow = 1+offset.CL; ColNow + 8 + offset.CR < map[i][0].size()-1; ColNow += 8){
                for(int z = 0; z < nxn*2-1; z++){
                    map[i][RowNow][ColNow+z].tilestruct = true;
                    map[i][RowNow+z][ColNow].tilestruct = true;
                    map[i][RowNow+nxn*2-2][ColNow+z].tilestruct = true;
                    map[i][RowNow+z][ColNow+nxn*2-2].tilestruct = true;
                }
                

                /*
                    FFFFT
                    T___|
                */
/*                for(int m = 2; m < SideLen-1; m+=2){
                    for(int n = 0; n < m; n+=2){
                        for(int l = 0; l < 5; l++){
                            ls.push_back(to_string(-map[i][RowNow][ColNow+m].var_id)+' '+to_string(-map[i][RowNow+2][ColNow].var_id)+' '
                            +to_string(-map[i][RowNow][ColNow+m].net_id[l])+' '+to_string(-map[i][RowNow+2][ColNow].net_id[l])+' '+
                            to_string(-map[i][RowNow][ColNow+n].var_id));
                            ls.push_back(to_string(-map[i][RowNow][ColNow+m].var_id)+' '+to_string(-map[i][RowNow+2][ColNow].var_id)+' '
                            +to_string(map[i][RowNow][ColNow+m].net_id[l])+' '+to_string(map[i][RowNow+2][ColNow].net_id[l])+' '+
                            to_string(-map[i][RowNow][ColNow+n].var_id));
                        }                        
                    }
                }
                /*
                    FT
                    F
                    T
                */
/*               for(int m = 2; m < SideLen-1; m+=2){
                    for(int n = 0; n < m; n+=2){
                        for(int l = 0; l < 5; l++){
                            ls.push_back(to_string(-map[i][RowNow][ColNow+2].var_id)+' '+to_string(-map[i][RowNow+m][ColNow].var_id)+' '
                            +to_string(-map[i][RowNow][ColNow+2].net_id[l])+' '+to_string(-map[i][RowNow+m][ColNow].net_id[l])+' '+
                            to_string(-map[i][RowNow+n][ColNow].var_id));
                            ls.push_back(to_string(-map[i][RowNow][ColNow+2].var_id)+' '+to_string(-map[i][RowNow+m][ColNow].var_id)+' '
                            +to_string(map[i][RowNow][ColNow+2].net_id[l])+' '+to_string(map[i][RowNow+m][ColNow].net_id[l])+' '+
                            to_string(-map[i][RowNow+n][ColNow].var_id));
                        }                        
                    }
                }
                /*
                

                    ***TF
                       |F
                       _T
                */
/*                for(int m = 2; m < SideLen-1; m+=2){
                    for(int n = 0; n < m; n+=2){
                        for(int l = 0; l < 5; l++){
                            ls.push_back(to_string(-map[i][RowNow][ColNow+SideLen-3].var_id)+' '+to_string(-map[i][RowNow+m][ColNow+SideLen-1].var_id)+' '
                            +to_string(-map[i][RowNow][ColNow+SideLen-3].net_id[l])+' '+to_string(-map[i][RowNow+m][ColNow+SideLen-1].net_id[l])+' '+
                            to_string(-map[i][RowNow+n][ColNow+SideLen-1].var_id));
                            ls.push_back(to_string(-map[i][RowNow][ColNow+SideLen-3].var_id)+' '+to_string(-map[i][RowNow+m][ColNow+SideLen-1].var_id)+' '
                            +to_string(map[i][RowNow][ColNow+SideLen-3].net_id[l])+' '+to_string(map[i][RowNow+m][ColNow+SideLen-1].net_id[l])+' '+
                            to_string(-map[i][RowNow+n][ColNow+SideLen-1].var_id));
                        }                        
                    }
                }
                /*
                    TFFF
                       T
                */
/*                for(int m = 2; m < SideLen-1; m+=2){
                    for(int n = m+2; n < SideLen; n+=2){
                        for(int l = 0; l < 5; l++){
                            ls.push_back(to_string(-map[i][RowNow][ColNow+m].var_id)+' '+to_string(-map[i][RowNow+2][ColNow+SideLen-1].var_id)+' '
                            +to_string(-map[i][RowNow][ColNow+m].net_id[l])+' '+to_string(-map[i][RowNow+2][ColNow+SideLen-1].net_id[l])+' '+
                            to_string(-map[i][RowNow][ColNow+n].var_id));
                            ls.push_back(to_string(-map[i][RowNow][ColNow+m].var_id)+' '+to_string(-map[i][RowNow+2][ColNow+SideLen-1].var_id)+' '
                            +to_string(map[i][RowNow][ColNow+m].net_id[l])+' '+to_string(map[i][RowNow+2][ColNow+SideLen-1].net_id[l])+' '+
                            to_string(-map[i][RowNow][ColNow+n].var_id));
                        }                        
                    }
                }


                /*
                      T
                  TFFFF
                */    
/*                for(int m = 2; m < SideLen-1; m+=2){
                    for(int n = m+2; n < SideLen; n+=2){
                        for(int l = 0; l < 5; l++){
                            ls.push_back(to_string(-map[i][RowNow+SideLen-3][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+m].var_id)+' '
                            +to_string(-map[i][RowNow+SideLen-3][ColNow+SideLen-1].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+m].net_id[l])+' '+
                            to_string(-map[i][RowNow+SideLen-1][ColNow+n].var_id));
                            ls.push_back(to_string(-map[i][RowNow+SideLen-3][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+m].var_id)+' '
                            +to_string(-map[i][RowNow+SideLen-3][ColNow+SideLen-1].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+m].net_id[l])+' '+
                            to_string(-map[i][RowNow+SideLen-1][ColNow+n].var_id));
                        }                        
                    }
                }
                /*
                    T
                    F
                ***TF
                */
/*                for(int m = 2; m < SideLen-1; m+=2){
                    for(int n = m+2; n < SideLen; n+=2){
                        for(int l = 0; l < 5; l++){
                            ls.push_back(to_string(-map[i][RowNow+SideLen-1][ColNow+SideLen-3].var_id)+' '+to_string(-map[i][RowNow+m][ColNow+SideLen-1].var_id)+' '
                            +to_string(-map[i][RowNow+SideLen-1][ColNow+SideLen-3].net_id[l])+' '+to_string(-map[i][RowNow+m][ColNow+SideLen-1].net_id[l])+' '+
                            to_string(-map[i][RowNow+n][ColNow+SideLen-1].var_id));
                            ls.push_back(to_string(-map[i][RowNow+SideLen-1][ColNow+SideLen-3].var_id)+' '+to_string(-map[i][RowNow+m][ColNow+SideLen-1].var_id)+' '
                            +to_string(map[i][RowNow+SideLen-1][ColNow+SideLen-3].net_id[l])+' '+to_string(map[i][RowNow+m][ColNow+SideLen-1].net_id[l])+' '+
                            to_string(-map[i][RowNow+n][ColNow+SideLen-1].var_id));
                        }                        
                    }
                }

                /*
                    T
                    F
                    FT
                */
 /*               for(int m = 2; m < SideLen-1; m+=2){
                    for(int n = m+2; n < SideLen; n+=2){
                        for(int l = 0; l < 5; l++){
                            ls.push_back(to_string(-map[i][RowNow+SideLen-1][ColNow+2].var_id)+' '+to_string(-map[i][RowNow+m][ColNow].var_id)+' '
                            +to_string(-map[i][RowNow+SideLen-1][ColNow+2].net_id[l])+' '+to_string(-map[i][RowNow+m][ColNow].net_id[l])+' '+
                            to_string(-map[i][RowNow+n][ColNow].var_id));
                            ls.push_back(to_string(-map[i][RowNow+SideLen-1][ColNow+2].var_id)+' '+to_string(-map[i][RowNow+m][ColNow].var_id)+' '
                            +to_string(map[i][RowNow+SideLen-1][ColNow+2].net_id[l])+' '+to_string(map[i][RowNow+m][ColNow].net_id[l])+' '+
                            to_string(-map[i][RowNow+n][ColNow].var_id));
                        }                        
                    }
                }
                /*
                    *
                    * 
                    T
                    FFFT
                */
/*                for(int m = 2; m < SideLen-1; m+=2){
                    for(int n = 0; n < m; n+=2){
                        for(int l = 0; l < 5; l++){
                            ls.push_back(to_string(-map[i][RowNow+SideLen-3][ColNow].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+m].var_id)+' '
                            +to_string(-map[i][RowNow+SideLen-3][ColNow].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+m].net_id[l])+' '+
                            to_string(-map[i][RowNow+SideLen-1][ColNow+n].var_id));
                            ls.push_back(to_string(-map[i][RowNow+SideLen-3][ColNow].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+m].var_id)+' '
                            +to_string(map[i][RowNow+SideLen-3][ColNow].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+m].net_id[l])+' '+
                            to_string(-map[i][RowNow+SideLen-1][ColNow+n].var_id));
                        }                        
                    }
                }
*/                
                for(int j = 2; j <= SideLen-3; j+=2){
                    for(int k = 2; k <= SideLen-3; k+=2){
                        //left top
                        /*
                                       top
                                        |
                                        |
                                left---mid
                        */
/*                        for(int m = 1; m < k; m++){  //left to mid
                             

                            for(int l = 0; l < 5; l++){                       
                                //CNF(a & b & (c xnor d)) implies e) --> (¬a ∨ ¬b ∨ ¬c ∨ ¬d ∨ e) ∧ (¬a ∨ ¬b ∨ c ∨ d ∨ e), 
                                //c and d mean net_id
                                
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                            }                         
                        }
                        for(int m = 1; m <= j; m++){  //mid to top
                            for(int l = 0; l < 5; l++){                                             
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+k].var_id)+" 0");
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+k].var_id)+" 0");
                            }                         
                        }
 */                       
                        

                        //left right
                        int mid = SideLen/2;
                       /* for(int m = 1; m < mid; m++){ //left to mid
                            for(int l = 0; l < 5; l++){                       
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                            }
                                                 
                        }
                        for(int m = 0; m <= abs(j-k); m++){ //mid to mid
                            for(int l = 0; l < 5; l++){ 
                                if(j-k > 0){
                                    ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                    +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                    +to_string(map[i][RowNow+j-m][ColNow+mid].var_id)+" 0");
                                    ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                    +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                    +to_string(map[i][RowNow+j-m][ColNow+mid].var_id)+" 0");
                                }                      
                                else{
                                    ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                    +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                    +to_string(map[i][RowNow+j+m][ColNow+mid].var_id)+" 0");
                                    ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                    +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                    +to_string(map[i][RowNow+j+m][ColNow+mid].var_id)+" 0");
                                }
                            }                      
                        }
                        for(int m = mid+1; m < SideLen-1; m++){ //mid to right
                            for(int l = 0; l < 5; l++){                       
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                +to_string(map[i][RowNow+k][ColNow+m].var_id)+" 0");
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                +to_string(map[i][RowNow+k][ColNow+m].var_id)+" 0");
                            }
                        }
                       */ //left bottom 
/*                        for(int m = 1; m < k; m++){  //left to mid
                            for(int l = 0; l < 5; l++){                                                     
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                            }                         
                        }
                        for(int m = 0; m < SideLen-j-1; m++){  //mid to bottom
                            for(int l = 0; l < 5; l++){                                             
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j+m][ColNow+k].var_id)+" 0");
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j+m][ColNow+k].var_id)+" 0");
                            }                         
                        }
*/                        //right top
                        for(int m = k+1; m < SideLen-1; m++){  //right to mid
                            for(int l = 0; l < 5; l++){                       
                                
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(-map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                            }                         
                        }
                        for(int m = 1; m <= j; m++){  //mid to top
                            for(int l = 0; l < 5; l++){                                             
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(-map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+k].var_id)+" 0");
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+k].var_id)+" 0");
                            }                         
                        }
                        //right bottom
 /*                       for(int m = k+1; m < SideLen-1; m++){  //right to mid
                            for(int l = 0; l < 5; l++){                                                     
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                            }                         
                        }
                        for(int m = 0; m < SideLen-j-1; m++){  //mid to bottom
                            for(int l = 0; l < 5; l++){                                             
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j+m][ColNow+k].var_id)+" 0");
                                ls.push_back(to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j+m][ColNow+k].var_id)+" 0");
                            }                         
                        }
 */                       //top to bottom **slow**
 /*                       for(int m = 1; m < mid; m++){ //top to mid
                            for(int l = 0; l < 5; l++){                       
                                ls.push_back(to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+j].var_id)+" 0");
                                ls.push_back(to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+j].var_id)+" 0");
                            }
                                                 
                        }
                        for(int m = 0; m <= abs(j-k); m++){ //mid to mid
                            for(int l = 0; l < 5; l++){ 
                                if(j-k > 0){
                                    ls.push_back(to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                    +to_string(-map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                    +to_string(map[i][RowNow+mid][ColNow+j-m].var_id)+" 0");
                                    ls.push_back(to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                    +to_string(map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                    +to_string(map[i][RowNow+mid][ColNow+j-m].var_id)+" 0");
                                }                      
                                else{
                                    ls.push_back(to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                    +to_string(-map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                    +to_string(map[i][RowNow+mid][ColNow+j+m].var_id)+" 0");
                                    ls.push_back(to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                    +to_string(map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                    +to_string(map[i][RowNow+mid][ColNow+j+m].var_id)+" 0");
                                }
                            }                      
                        }
                        for(int m = mid+1; m < SideLen-1; m++){ //mid to bottom
                            for(int l = 0; l < 5; l++){                       
                                ls.push_back(to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+k].var_id)+" 0");
                                ls.push_back(to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+k].var_id)+" 0");
                            }
                        }
*/
                        
                    }
                } 
                //boundary of tile can't have two node that have the same net_id
              /*  for(int m = 0; m < SideLen-1; m++){
                    for(int n = m+1; n < SideLen; n++){
                       //top
                        EdgeIdNotTheSame(ls, map[i][RowNow][ColNow+m].var_id,
                        map[i][RowNow][ColNow+n].var_id,
                        map[i][RowNow][ColNow+m].net_id[0],
                        map[i][RowNow][ColNow+m].net_id[1],
                        map[i][RowNow][ColNow+m].net_id[2],
                        map[i][RowNow][ColNow+m].net_id[3],
                        map[i][RowNow][ColNow+m].net_id[4],
                        map[i][RowNow][ColNow+n].net_id[0],
                        map[i][RowNow][ColNow+n].net_id[1],
                        map[i][RowNow][ColNow+n].net_id[2],
                        map[i][RowNow][ColNow+n].net_id[3],
                        map[i][RowNow][ColNow+n].net_id[4]);
                        //left
                        EdgeIdNotTheSame(ls, map[i][RowNow+m][ColNow].var_id,
                        map[i][RowNow+n][ColNow].var_id,
                        map[i][RowNow+m][ColNow].net_id[0],
                        map[i][RowNow+m][ColNow].net_id[1],
                        map[i][RowNow+m][ColNow].net_id[2],
                        map[i][RowNow+m][ColNow].net_id[3],
                        map[i][RowNow+m][ColNow].net_id[4],
                        map[i][RowNow+n][ColNow].net_id[0],
                        map[i][RowNow+n][ColNow].net_id[1],
                        map[i][RowNow+n][ColNow].net_id[2],
                        map[i][RowNow+n][ColNow].net_id[3],
                        map[i][RowNow+n][ColNow].net_id[4]);
                        //right
                        EdgeIdNotTheSame(ls, map[i][RowNow+m][ColNow+SideLen-1].var_id,
                        map[i][RowNow+n][ColNow+SideLen-1].var_id,
                        map[i][RowNow+m][ColNow+SideLen-1].net_id[0],
                        map[i][RowNow+m][ColNow+SideLen-1].net_id[1],
                        map[i][RowNow+m][ColNow+SideLen-1].net_id[2],
                        map[i][RowNow+m][ColNow+SideLen-1].net_id[3],
                        map[i][RowNow+m][ColNow+SideLen-1].net_id[4],
                        map[i][RowNow+n][ColNow+SideLen-1].net_id[0],
                        map[i][RowNow+n][ColNow+SideLen-1].net_id[1],
                        map[i][RowNow+n][ColNow+SideLen-1].net_id[2],
                        map[i][RowNow+n][ColNow+SideLen-1].net_id[3],
                        map[i][RowNow+n][ColNow+SideLen-1].net_id[4]);
                        //bottom
                        EdgeIdNotTheSame(ls, map[i][RowNow+SideLen-1][ColNow+m].var_id,
                        map[i][RowNow+SideLen-1][ColNow+n].var_id,
                        map[i][RowNow+SideLen-1][ColNow+m].net_id[0],
                        map[i][RowNow+SideLen-1][ColNow+m].net_id[1],
                        map[i][RowNow+SideLen-1][ColNow+m].net_id[2],
                        map[i][RowNow+SideLen-1][ColNow+m].net_id[3],
                        map[i][RowNow+SideLen-1][ColNow+m].net_id[4],
                        map[i][RowNow+SideLen-1][ColNow+n].net_id[0],
                        map[i][RowNow+SideLen-1][ColNow+n].net_id[1],
                        map[i][RowNow+SideLen-1][ColNow+n].net_id[2],
                        map[i][RowNow+SideLen-1][ColNow+n].net_id[3],
                        map[i][RowNow+SideLen-1][ColNow+n].net_id[4]);

                    }
                }  */
            }
    
        }
    }
    vector<int> donotsetfalserow0, donotsetfalsecol0, donotsetfalserow1, donotsetfalsecol1;
    for(int i = 0; i < map.size(); i++){//G
        for(int j = 0; j < map.at(i).size(); j++){
            for(int k = 0; k < map.at(i).at(0).size(); k++){
                if(map[i][j][k].type == 'P'){
                    if(i==0){
                        donotsetfalserow0.push_back(j);
                        donotsetfalsecol0.push_back(k);
                    }
                    else{
                        donotsetfalserow1.push_back(j);
                        donotsetfalsecol1.push_back(k);
                    }
                }
                else if(map[i][j][k].type == 'S'){
                    if(i==0){
                        donotsetfalserow0.push_back(j);
                        donotsetfalsecol0.push_back(k);
                    }
                    else{
                        donotsetfalserow1.push_back(j);
                        donotsetfalsecol1.push_back(k);
                    }
                }
            }
        }
    }
    //row
    for(int i = 0; i < 2; i++){//G
        for(int j=1+offset.RL; j+offset.RR<map[i].size()-1; j+=nxn*2-2){
            for(int k=1+offset.CL; k+offset.CR<map[i][0].size()-1; k+=1){
                if(map[i][j][k].type == 'E' && i==0){
                    vector<int>::iterator itR = find(donotsetfalserow0.begin(), donotsetfalserow0.end(), j);
                    if(itR == donotsetfalserow0.end()){
                        ls.push_back(to_string(-map[i][j][k].var_id)+" 0");
                        map[i][j][k].tilestruct = false;
                    }else{
                        cout << "";
                    }
                }
                if(map[i][j][k].type == 'E' && i==1){
                    vector<int>::iterator itR = find(donotsetfalserow1.begin(), donotsetfalserow1.end(), j);
                    if(itR == donotsetfalserow1.end()){
                        ls.push_back(to_string(-map[i][j][k].var_id)+" 0");
                        map[i][j][k].tilestruct = false;
                    }else{
                        cout << "";
                    }
                }
            }
        }
    }
}