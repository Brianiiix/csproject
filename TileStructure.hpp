using namespace std;

void TileStruct(list<string> &ls, vector<vector<vector<Node>>> &map, int nxn, TSoffset offset1, TSoffset offset2, vector<vector<vector<int>>> &netBox){
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
    int SideLen = 2*nxn-1; //default = 9
    int cnt = 0;
    for(int i = 0; i < map.size(); i++){//Group
        TSoffset offset;
        if(i==0){offset=offset1;}
        else if(i==1){offset=offset2;}
        for(int RowNow = 1+offset.RL; RowNow + SideLen-1 + offset.RR < map[i].size()-1; RowNow += SideLen-1){
            for(int ColNow = 1+offset.CL; ColNow + SideLen-1 + offset.CR < map[i][0].size()-1; ColNow += SideLen-1){cnt++;
                //crossroad control
                //topleft
                if(map[i][RowNow][ColNow].type != 'P') {
                    ls.push_back("1 "+to_string(-map[i][RowNow+1][ColNow].var_id)+" 0");
                    ls.push_back("1 "+to_string(-map[i][RowNow][ColNow+1].var_id)+" 0");
                }
                ls.push_back("1 "+to_string(-map[i][RowNow+3][ColNow].var_id)+" 0");
                ls.push_back("1 "+to_string(-map[i][RowNow][ColNow+3].var_id)+" 0");
                //topright
                if(map[i][RowNow][ColNow+SideLen-1].type != 'P') {
                    ls.push_back("1 "+to_string(-map[i][RowNow+1][ColNow+SideLen-1].var_id)+" 0");
                    ls.push_back("1 "+to_string(-map[i][RowNow][ColNow+SideLen-2].var_id)+" 0");
                }
                ls.push_back("1 "+to_string(-map[i][RowNow+3][ColNow+SideLen-1].var_id)+" 0");
                ls.push_back("1 "+to_string(-map[i][RowNow][ColNow+SideLen-4].var_id)+" 0");
                //botleft
                if(map[i][RowNow+SideLen-1][ColNow].type != 'P') {
                    ls.push_back("1 "+to_string(-map[i][RowNow+SideLen-2][ColNow].var_id)+" 0");
                    ls.push_back("1 "+to_string(-map[i][RowNow+SideLen-1][ColNow+1].var_id)+" 0");
                }
                ls.push_back("1 "+to_string(-map[i][RowNow+SideLen-1][ColNow+3].var_id)+" 0");
                ls.push_back("1 "+to_string(-map[i][RowNow+SideLen-4][ColNow].var_id)+" 0");
                //botright 
                if(map[i][RowNow+SideLen-1][ColNow+SideLen-1].type != 'P') {
                    ls.push_back("1 "+to_string(-map[i][RowNow+SideLen-2][ColNow+SideLen-1].var_id)+" 0");
                    ls.push_back("1 "+to_string(-map[i][RowNow+SideLen-1][ColNow+SideLen-2].var_id)+" 0");
                }
                ls.push_back("1 "+to_string(-map[i][RowNow+SideLen-1][ColNow+SideLen-4].var_id)+" 0");
                ls.push_back("1 "+to_string(-map[i][RowNow+SideLen-4][ColNow+SideLen-1].var_id)+" 0");

                for(int z = 0; z < nxn*2-1; z++){
                    map[i][RowNow][ColNow+z].tilestruct = true;
                    map[i][RowNow+z][ColNow].tilestruct = true;
                    map[i][RowNow+nxn*2-2][ColNow+z].tilestruct = true;
                    map[i][RowNow+z][ColNow+nxn*2-2].tilestruct = true;
                }
                bool hasPin = 0;
                //if edge has pin then no rule
                /*for(int a = 0; a < SideLen; a+=1){
                    //for(int b = 0; b < SideLen; b+=1){
                        if(map[i][RowNow+a][ColNow].type == 'P') hasPin = 1;
                        if(map[i][RowNow+a][ColNow+SideLen-1].type == 'P') hasPin = 1;
                        if(map[i][RowNow+SideLen-1][ColNow+a].type == 'P') hasPin = 1;
                        if(map[i][RowNow][ColNow+a].type == 'P') hasPin = 1;
                        //if(cnt == 5) cout << map[i][RowNow+a][ColNow+b].type << " ";
                    //}
                    //if(cnt == 5) cout << endl;
                }*/
                //if tile has pin then no rule
                /*for(int a = 0; a < SideLen; a+=1){
                    for(int b = 0; b < SideLen; b+=1){
                        if(map[i][RowNow+a][ColNow+b].type == 'P') hasPin = 1;                        
                    }
                }
                if(hasPin == 1) continue;*/

                //mono start
                for(int z = 0; z < netBox[0].size(); z++){
                    int dec = z, temp[5] = {0};
                    for(int T = 0; T < 5; T++){
                        temp[T] = dec % 2;
                        dec /= 2;
                    }
                    string top_str = "1 ", left_str = "1 ", right_str = "1 ", bot_str = "1 ";
                    for(int j = 2; j <= SideLen-5; j+=2){
                        for(int k = j+2; k <= SideLen-3; k+=2){
                            for(int T = 0; T < 5; T++){
                                top_str += (temp[T])?(to_string(-map[i][RowNow][ColNow+j].net_id[T])):(to_string(map[i][RowNow][ColNow+j].net_id[T]));
                                top_str += " ";
                                right_str += (temp[T])?(to_string(-map[i][RowNow+j][ColNow+SideLen-1].net_id[T])):(to_string(map[i][RowNow+j][ColNow+SideLen-1].net_id[T]));
                                right_str += " ";
                                left_str += (temp[T])?(to_string(-map[i][RowNow+j][ColNow].net_id[T])):(to_string(map[i][RowNow+j][ColNow].net_id[T]));
                                left_str += " ";
                                bot_str += (temp[T])?(to_string(-map[i][RowNow+SideLen-1][ColNow+j].net_id[T])):(to_string(map[i][RowNow+SideLen-1][ColNow+j].net_id[T]));
                                bot_str += " ";
                            }
                            for(int T = 0; T < 5; T++){
                                top_str += (temp[T])?(to_string(-map[i][RowNow][ColNow+k].net_id[T])):(to_string(map[i][RowNow][ColNow+k].net_id[T]));
                                top_str += " ";
                                right_str += (temp[T])?(to_string(-map[i][RowNow+k][ColNow+SideLen-1].net_id[T])):(to_string(map[i][RowNow+k][ColNow+SideLen-1].net_id[T]));
                                right_str += " ";
                                left_str += (temp[T])?(to_string(-map[i][RowNow+k][ColNow].net_id[T])):(to_string(map[i][RowNow+k][ColNow].net_id[T]));
                                left_str += " ";
                                bot_str += (temp[T])?(to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[T])):(to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[T]));
                                bot_str += " ";
                            }            
                        }
                    }
                    top_str += "0";
                    right_str += "0";
                    left_str += "0";
                    bot_str += "0";
                    ls.push_back(top_str);
                    ls.push_back(right_str);
                    ls.push_back(left_str);
                    ls.push_back(bot_str);
                }
                //mono end


                //else cout << cnt << " no pin" << endl;
                //if(cnt == 5) cout << RowNow << " " << ColNow << endl;            
                for(int j = 2; j <= SideLen-3; j+=2){
                    //one in implies one out                    
                    //if(hasPin == 0){//cout << cnt <<" don't have pin"<<endl;
                    //top
                        /*ls.push_back("1 "+to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(map[i][RowNow+2][ColNow].var_id)+' '
                        +to_string(map[i][RowNow+4][ColNow].var_id)+' '+to_string(map[i][RowNow+6][ColNow].var_id)+' '
                        +to_string(map[i][RowNow+2][ColNow+SideLen-1].var_id)+' '+to_string(map[i][RowNow+4][ColNow+SideLen-1].var_id)+' '
                        +to_string(map[i][RowNow+6][ColNow+SideLen-1].var_id)+' '+to_string(map[i][RowNow+SideLen-1][ColNow+2].var_id)+' '
                        +to_string(map[i][RowNow+SideLen-1][ColNow+4].var_id)+' '+to_string(map[i][RowNow+SideLen-1][ColNow+6].var_id)+" 0");
                    //left
                        ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(map[i][RowNow][ColNow+2].var_id)+' '
                        +to_string(map[i][RowNow][ColNow+4].var_id)+' '+to_string(map[i][RowNow][ColNow+6].var_id)+' '
                        +to_string(map[i][RowNow+2][ColNow+SideLen-1].var_id)+' '+to_string(map[i][RowNow+4][ColNow+SideLen-1].var_id)+' '
                        +to_string(map[i][RowNow+6][ColNow+SideLen-1].var_id)+' '+to_string(map[i][RowNow+SideLen-1][ColNow+2].var_id)+' '
                        +to_string(map[i][RowNow+SideLen-1][ColNow+4].var_id)+' '+to_string(map[i][RowNow+SideLen-1][ColNow+6].var_id)+" 0");
                    //bottom
                        ls.push_back("1 "+to_string(-map[i][RowNow+SideLen-1][ColNow+j].var_id)+' '+to_string(map[i][RowNow+2][ColNow].var_id)+' '
                        +to_string(map[i][RowNow+4][ColNow].var_id)+' '+to_string(map[i][RowNow+6][ColNow].var_id)+' '
                        +to_string(map[i][RowNow+2][ColNow+SideLen-1].var_id)+' '+to_string(map[i][RowNow+4][ColNow+SideLen-1].var_id)+' '
                        +to_string(map[i][RowNow+6][ColNow+SideLen-1].var_id)+' '+to_string(map[i][RowNow][ColNow+2].var_id)+' '
                        +to_string(map[i][RowNow][ColNow+4].var_id)+' '+to_string(map[i][RowNow][ColNow+6].var_id)+" 0");
                    //right
                        ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(map[i][RowNow][ColNow+2].var_id)+' '
                        +to_string(map[i][RowNow][ColNow+4].var_id)+' '+to_string(map[i][RowNow][ColNow+6].var_id)+' '
                        +to_string(map[i][RowNow+2][ColNow].var_id)+' '+to_string(map[i][RowNow+4][ColNow].var_id)+' '
                        +to_string(map[i][RowNow+6][ColNow].var_id)+' '+to_string(map[i][RowNow+SideLen-1][ColNow+2].var_id)+' '
                        +to_string(map[i][RowNow+SideLen-1][ColNow+4].var_id)+' '+to_string(map[i][RowNow+SideLen-1][ColNow+6].var_id)+" 0");
                       
                    //}
                    //else cout << cnt << " has pin"  << endl;

                    /*if(cnt == 31){
                            cout <<"KJHGJYG "<< to_string(map[i][RowNow+j][ColNow+SideLen-1].var_id)<<" " << to_string(map[i][RowNow][ColNow+2].var_id)<<" " 
                            << to_string(map[i][RowNow][ColNow+4].var_id)<<" "  << to_string(map[i][RowNow][ColNow+6].var_id) <<" " 
                            << to_string(map[i][RowNow+2][ColNow].var_id)<<" "  << to_string(map[i][RowNow+4][ColNow].var_id)<<" " 
                            << to_string(map[i][RowNow+6][ColNow].var_id)<<" "  << to_string(map[i][RowNow+SideLen-1][ColNow+2].var_id)<<" " 
                            << to_string(map[i][RowNow+SideLen-1][ColNow+4].var_id)<<" "  << to_string(map[i][RowNow+SideLen-1][ColNow+6].var_id) << endl;
                            for(int g = 0; g < 5; g++){
                                cout << to_string(map[i][RowNow+j][ColNow+SideLen-1].net_id[g]) << " ";
                            }
                            cout << endl;
                            cout << to_string(map[i][RowNow+j][ColNow+SideLen-1].var_id) << endl;
                        }*/
                    
                    for(int k = 2; k <= SideLen-3; k+=2){
                        //left top
                        /*
                                       top
                                        |
                                        |
                                left---mid
                        */    //  /*
                        for(int m = 1; m < k; m++){  //left to mid
                             

                            for(int l = 0; l < 5; l++){                       
                                //CNF(a & b & (c xnor d)) implies e) --> (¬a ∨ ¬b ∨ ¬c ∨ ¬d ∨ e) ∧ (¬a ∨ ¬b ∨ c ∨ d ∨ e), 
                                //c and d mean net_id
                                
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                            }                         
                        }
                        for(int m = 1; m <= j; m++){  //mid to top
                            for(int l = 0; l < 5; l++){                                             
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+k].var_id)+" 0");
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+k].var_id)+" 0");
                            }                         
                        }
                        
                        

                        //left right
                        int mid = SideLen/2;
                       
                        for(int m = 1; m < mid; m++){ //left to mid
                            for(int l = 0; l < 5; l++){                       
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                            }
                                                 
                        }
                        
                        for(int m = 0; m <= abs(j-k); m++){ //mid to mid
                            for(int l = 0; l < 5; l++){ 
                                if(j-k > 0){
                                    ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                    +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                    +to_string(map[i][RowNow+j-m][ColNow+mid].var_id)+" 0");
                                    ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                    +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                    +to_string(map[i][RowNow+j-m][ColNow+mid].var_id)+" 0");
                                }                      
                                else{
                                    ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                    +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                    +to_string(map[i][RowNow+j+m][ColNow+mid].var_id)+" 0");
                                    ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                    +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                    +to_string(map[i][RowNow+j+m][ColNow+mid].var_id)+" 0");
                                }
                            }                      
                        }
                       
                        for(int m = mid+1; m < SideLen-1; m++){ //mid to right
                            for(int l = 0; l < 5; l++){                       
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                +to_string(map[i][RowNow+k][ColNow+m].var_id)+" 0");
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+k][ColNow+SideLen-1].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow+k][ColNow+SideLen-1].net_id[l])+' '
                                +to_string(map[i][RowNow+k][ColNow+m].var_id)+" 0");
                            }
                        }
                        //left bottom 
                        for(int m = 1; m < k; m++){  //left to mid
                            for(int l = 0; l < 5; l++){                                                     
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                            }                         
                        }
                        for(int m = 0; m < SideLen-j-1; m++){  //mid to bottom
                            for(int l = 0; l < 5; l++){                                             
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j+m][ColNow+k].var_id)+" 0");
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j+m][ColNow+k].var_id)+" 0");
                            }                         
                        }
                        //right top
                        for(int m = k+1; m < SideLen-1; m++){  //right to mid
                            for(int l = 0; l < 5; l++){                       
                                
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(-map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                            }                         
                        }
                        for(int m = 1; m <= j; m++){  //mid to top
                            for(int l = 0; l < 5; l++){                                             
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(-map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+k].var_id)+" 0");
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(map[i][RowNow][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+k].var_id)+" 0");
                            }                         
                        }
                        //right bottom
                        for(int m = k+1; m < SideLen-1; m++){  //right to mid
                            for(int l = 0; l < 5; l++){                                                     
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j][ColNow+m].var_id)+" 0");
                            }                         
                        }
                        for(int m = 0; m < SideLen-j-1; m++){  //mid to bottom
                            for(int l = 0; l < 5; l++){                                             
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j+m][ColNow+k].var_id)+" 0");
                                ls.push_back("1 "+to_string(-map[i][RowNow+j][ColNow+SideLen-1].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow+j][ColNow+SideLen-1].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+j+m][ColNow+k].var_id)+" 0");
                            }                         
                        }
                        //top to bottom **slow**
                        for(int m = 1; m < mid; m++){ //top to mid
                            for(int l = 0; l < 5; l++){                       
                                ls.push_back("1 "+to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+j].var_id)+" 0");
                                ls.push_back("1 "+to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+j].var_id)+" 0");
                            }
                                                 
                        }
                        for(int m = 0; m <= abs(j-k); m++){ //mid to mid
                            for(int l = 0; l < 5; l++){ 
                                if(j-k > 0){
                                    ls.push_back("1 "+to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                    +to_string(-map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                    +to_string(map[i][RowNow+mid][ColNow+j-m].var_id)+" 0");
                                    ls.push_back("1 "+to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                    +to_string(map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                    +to_string(map[i][RowNow+mid][ColNow+j-m].var_id)+" 0");
                                }                      
                                else{
                                    ls.push_back("1 "+to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                    +to_string(-map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                    +to_string(map[i][RowNow+mid][ColNow+j+m].var_id)+" 0");
                                    ls.push_back("1 "+to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                    +to_string(map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                    +to_string(map[i][RowNow+mid][ColNow+j+m].var_id)+" 0");
                                }
                            }                      
                        }
                        for(int m = mid+1; m < SideLen-1; m++){ //mid to bottom
                            for(int l = 0; l < 5; l++){                       
                                ls.push_back("1 "+to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(-map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+k].var_id)+" 0");
                                ls.push_back("1 "+to_string(-map[i][RowNow][ColNow+j].var_id)+' '+to_string(-map[i][RowNow+SideLen-1][ColNow+k].var_id)+' '
                                +to_string(map[i][RowNow][ColNow+j].net_id[l])+' '+to_string(map[i][RowNow+SideLen-1][ColNow+k].net_id[l])+' '
                                +to_string(map[i][RowNow+m][ColNow+k].var_id)+" 0");
                            }
                        }

                    //    */
                    }       
                } 
                
            }
    
        }
    }
    vector<int> donotsetfalserow0, donotsetfalsecol0, donotsetfalserow1, donotsetfalsecol1;/*
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
    }*/
    //row
    /*
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
    }*/
}
