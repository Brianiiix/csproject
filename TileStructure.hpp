using namespace std;

void TileStruct(list<string> &ls, vector<vector<vector<Node>>> &map, int nxn, TSoffset offset){
    //tile structure begin

    /*

    11-13-15-17-19  <--RowNow
    |            |
    31          39
    |            |
    51          59 
    |            |
    71          79
    |            |
    91-93-95-97-99
    ^
    |__ ColNow

    */
    int N13, N15, N17, N31, N39, N51, N59, N71, N79, N93, N95, N97; //node left of imply
    int ColNow, RowNow;
    int N33, N35, N37, N53, N55, N57, N73, N75, N77; //node right of imply
    int E21, E41, E61, E81, E12, E32, E52, E72, E92, E23, E43, E63, E83, E14, E34, E54, 
    E74, E94, E25, E45, E65, E85, E16, E36, E56, E76, E96, E27, E47, E67, E87, E18, E38, 
    E58, E78, E98, E29, E49, E69, E89; //edge

    for(int i = 0; i < 2; i++){//Group
        for(int RowNow = 1+offset.RL; RowNow + 8 + offset.RR < map[i].size()-1; RowNow += 8){
            for(int ColNow = 1+offset.CL; ColNow + 8 + offset.CR < map[i][0].size()-1; ColNow += 8){
                for(int z = 0; z < nxn*2-1; z++){
                    map[i][RowNow][ColNow+z].tilestruct = true;
                    map[i][RowNow+z][ColNow].tilestruct = true;
                    map[i][RowNow+nxn*2-2][ColNow+z].tilestruct = true;
                    map[i][RowNow+z][ColNow+nxn*2-2].tilestruct = true;
                }

                //node left of imply
                N13 = map[i][RowNow][ColNow+2].var_id;
                N15 = map[i][RowNow][ColNow+4].var_id;
                N17 = map[i][RowNow][ColNow+6].var_id;
                N31 = map[i][RowNow+2][ColNow].var_id;
                N39 = map[i][RowNow+2][ColNow+8].var_id;
                N51 = map[i][RowNow+4][ColNow].var_id;
                N59 = map[i][RowNow+4][ColNow+8].var_id;
                N71 = map[i][RowNow+6][ColNow].var_id;
                N79 = map[i][RowNow+6][ColNow+8].var_id;
                N93 = map[i][RowNow+8][ColNow+2].var_id;
                N95 = map[i][RowNow+8][ColNow+4].var_id;
                N97 = map[i][RowNow+8][ColNow+6].var_id;
                //node right of imply
                N33 = map[i][RowNow+2][ColNow+2].var_id;
                N35 = map[i][RowNow+2][ColNow+4].var_id;
                N37 = map[i][RowNow+2][ColNow+6].var_id;
                N53 = map[i][RowNow+4][ColNow+2].var_id;
                N55 = map[i][RowNow+4][ColNow+4].var_id;
                N57 = map[i][RowNow+4][ColNow+6].var_id;
                N73 = map[i][RowNow+6][ColNow+2].var_id;
                N75 = map[i][RowNow+6][ColNow+4].var_id;
                N77 = map[i][RowNow+6][ColNow+6].var_id;
                //edge
                E21 = map[i][RowNow+1][ColNow].var_id;
                E41 = map[i][RowNow+3][ColNow].var_id;
                E61 = map[i][RowNow+5][ColNow].var_id;
                E81 = map[i][RowNow+7][ColNow].var_id;
                E12 = map[i][RowNow][ColNow+1].var_id;
                E32 = map[i][RowNow+2][ColNow+1].var_id;
                E52 = map[i][RowNow+4][ColNow+1].var_id;
                E72 = map[i][RowNow+6][ColNow+1].var_id;
                E92 = map[i][RowNow+8][ColNow+1].var_id;
                E23 = map[i][RowNow+1][ColNow+2].var_id;
                E43 = map[i][RowNow+3][ColNow+2].var_id;
                E63 = map[i][RowNow+5][ColNow+2].var_id;
                E83 = map[i][RowNow+7][ColNow+2].var_id;
                E14 = map[i][RowNow][ColNow+3].var_id;
                E34 = map[i][RowNow+2][ColNow+3].var_id;
                E54 = map[i][RowNow+4][ColNow+3].var_id;
                E74 = map[i][RowNow+6][ColNow+3].var_id;
                E94 = map[i][RowNow+8][ColNow+3].var_id;
                E25 = map[i][RowNow+1][ColNow+4].var_id;
                E45 = map[i][RowNow+3][ColNow+4].var_id;
                E65 = map[i][RowNow+5][ColNow+4].var_id;
                E85 = map[i][RowNow+7][ColNow+4].var_id;
                E16 = map[i][RowNow][ColNow+5].var_id;
                E36 = map[i][RowNow+2][ColNow+5].var_id;
                E56 = map[i][RowNow+4][ColNow+5].var_id;
                E76 = map[i][RowNow+6][ColNow+5].var_id;
                E96 = map[i][RowNow+8][ColNow+5].var_id;
                E27 = map[i][RowNow+1][ColNow+6].var_id;
                E47 = map[i][RowNow+3][ColNow+6].var_id;
                E67 = map[i][RowNow+5][ColNow+6].var_id;
                E87 = map[i][RowNow+7][ColNow+6].var_id;
                E18 = map[i][RowNow][ColNow+7].var_id;
                E38 = map[i][RowNow+2][ColNow+7].var_id;
                E58 = map[i][RowNow+4][ColNow+7].var_id;
                E78 = map[i][RowNow+6][ColNow+7].var_id;
                E98 = map[i][RowNow+8][ColNow+7].var_id;
                E29 = map[i][RowNow+1][ColNow+8].var_id;
                E49 = map[i][RowNow+3][ColNow+8].var_id;
                E69 = map[i][RowNow+5][ColNow+8].var_id;
                E89 = map[i][RowNow+7][ColNow+8].var_id;

                // if both N31 and N13 are true, then constrain the road,
                // which pass through N33 (N31&N13 implies N33)
                //31 13
                ls.push_back(to_string(-N31)+' '+to_string(-N13)+' '+to_string(E23)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N13)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N13)+' '+to_string(E32)+" 0");
                
                //31 15
                ls.push_back(to_string(-N31)+' '+to_string(-N15)+' '+to_string(E32)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N15)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N15)+' '+to_string(E34)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N15)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N15)+' '+to_string(E25)+" 0");
                //31 17
                ls.push_back(to_string(-N31)+' '+to_string(-N17)+' '+to_string(E32)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N17)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N17)+' '+to_string(E34)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N17)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N17)+' '+to_string(E36)+" 0"); 
                ls.push_back(to_string(-N31)+' '+to_string(-N17)+' '+to_string(N37)+" 0"); 
                ls.push_back(to_string(-N31)+' '+to_string(-N17)+' '+to_string(E27)+" 0"); 
                //31 39
                ls.push_back(to_string(-N31)+' '+to_string(-N39)+' '+to_string(E32)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N39)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N39)+' '+to_string(E34)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N39)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N39)+' '+to_string(E36)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N39)+' '+to_string(N37)+" 0");  
                ls.push_back(to_string(-N31)+' '+to_string(-N39)+' '+to_string(E38)+" 0");
                //31 59
                ls.push_back(to_string(-N31)+' '+to_string(-N59)+' '+to_string(E32)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N59)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N59)+' '+to_string(E34)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N59)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N59)+' '+to_string(E45)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N59)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N59)+' '+to_string(E56)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N59)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N59)+' '+to_string(E58)+" 0");
                //31 79
                ls.push_back(to_string(-N31)+' '+to_string(-N79)+' '+to_string(E32)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N79)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N79)+' '+to_string(E34)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N79)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N79)+' '+to_string(E45)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N79)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N79)+' '+to_string(E65)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N79)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N79)+' '+to_string(E76)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N79)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N79)+' '+to_string(E78)+" 0");
                //31 97
                ls.push_back(to_string(-N31)+' '+to_string(-N97)+' '+to_string(E32)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N97)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N97)+' '+to_string(E34)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N97)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N97)+' '+to_string(E36)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N97)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N97)+' '+to_string(E47)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N97)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N97)+' '+to_string(E67)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N97)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N97)+' '+to_string(E87)+" 0");
                //31 95
                ls.push_back(to_string(-N31)+' '+to_string(-N95)+' '+to_string(E32)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N95)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N95)+' '+to_string(E34)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N95)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N95)+' '+to_string(E45)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N95)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N95)+' '+to_string(E65)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N95)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N95)+' '+to_string(E85)+" 0");
                //31 93
                ls.push_back(to_string(-N31)+' '+to_string(-N93)+' '+to_string(E32)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N93)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N93)+' '+to_string(E43)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N93)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N93)+' '+to_string(E63)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N93)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N31)+' '+to_string(-N93)+' '+to_string(E83)+" 0");
                //51 13
                ls.push_back(to_string(-N51)+' '+to_string(-N13)+' '+to_string(E52)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N13)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N13)+' '+to_string(E43)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N13)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N13)+' '+to_string(E23)+" 0");
                //51 15
                ls.push_back(to_string(-N51)+' '+to_string(-N15)+' '+to_string(E52)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N15)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N15)+' '+to_string(E54)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N15)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N15)+' '+to_string(E45)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N15)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N15)+' '+to_string(E25)+" 0");
                //51 17
                ls.push_back(to_string(-N51)+' '+to_string(-N17)+' '+to_string(E52)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N17)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N17)+' '+to_string(E54)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N17)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N17)+' '+to_string(E56)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N17)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N17)+' '+to_string(E47)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N17)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N17)+' '+to_string(E27)+" 0");
                //51 39
                ls.push_back(to_string(-N51)+' '+to_string(-N39)+' '+to_string(E52)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N39)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N39)+' '+to_string(E54)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N39)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N39)+' '+to_string(E45)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N39)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N39)+' '+to_string(E36)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N39)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N39)+' '+to_string(E38)+" 0");
                //51 59
                ls.push_back(to_string(-N51)+' '+to_string(-N59)+' '+to_string(E52)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N59)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N59)+' '+to_string(E54)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N59)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N59)+' '+to_string(E56)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N59)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N59)+' '+to_string(E58)+" 0");
                //51 79
                ls.push_back(to_string(-N51)+' '+to_string(-N79)+' '+to_string(E52)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N79)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N79)+' '+to_string(E54)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N79)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N79)+' '+to_string(E65)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N79)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N79)+' '+to_string(E76)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N79)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N79)+' '+to_string(E78)+" 0");
                //51 97
                ls.push_back(to_string(-N51)+' '+to_string(-N97)+' '+to_string(E52)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N97)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N97)+' '+to_string(E54)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N97)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N97)+' '+to_string(E56)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N97)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N97)+' '+to_string(E67)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N97)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N97)+' '+to_string(E87)+" 0");
                //51 95
                ls.push_back(to_string(-N51)+' '+to_string(-N95)+' '+to_string(E52)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N95)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N95)+' '+to_string(E54)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N95)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N95)+' '+to_string(E65)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N95)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N95)+' '+to_string(E85)+" 0");
                //51 93
                ls.push_back(to_string(-N51)+' '+to_string(-N93)+' '+to_string(E52)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N93)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N93)+' '+to_string(E63)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N93)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N51)+' '+to_string(-N93)+' '+to_string(E83)+" 0");
                //71 93
                ls.push_back(to_string(-N71)+' '+to_string(-N93)+' '+to_string(E72)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N93)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N93)+' '+to_string(E83)+" 0"); 
                //71 95
                ls.push_back(to_string(-N71)+' '+to_string(-N95)+' '+to_string(E72)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N95)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N95)+' '+to_string(E74)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N95)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N95)+' '+to_string(E85)+" 0");
                //71 97
                ls.push_back(to_string(-N71)+' '+to_string(-N97)+' '+to_string(E72)+" 0"); 
                ls.push_back(to_string(-N71)+' '+to_string(-N97)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N97)+' '+to_string(E74)+" 0"); 
                ls.push_back(to_string(-N71)+' '+to_string(-N97)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N97)+' '+to_string(E76)+" 0"); 
                ls.push_back(to_string(-N71)+' '+to_string(-N97)+' '+to_string(N77)+" 0"); 
                ls.push_back(to_string(-N71)+' '+to_string(-N97)+' '+to_string(E87)+" 0"); 
                //71 79
                ls.push_back(to_string(-N71)+' '+to_string(-N79)+' '+to_string(E72)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N79)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N79)+' '+to_string(E74)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N79)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N79)+' '+to_string(E76)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N79)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N79)+' '+to_string(E78)+" 0");
                //71 59
                ls.push_back(to_string(-N71)+' '+to_string(-N59)+' '+to_string(E72)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N59)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N59)+' '+to_string(E74)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N59)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N59)+' '+to_string(E65)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N59)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N59)+' '+to_string(E56)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N59)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N59)+' '+to_string(E58)+" 0");
                //71 39
                ls.push_back(to_string(-N71)+' '+to_string(-N39)+' '+to_string(E72)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N39)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N39)+' '+to_string(E74)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N39)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N39)+' '+to_string(E65)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N39)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N39)+' '+to_string(E45)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N39)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N39)+' '+to_string(E36)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N39)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N39)+' '+to_string(E38)+" 0");
                //71 17
                ls.push_back(to_string(-N71)+' '+to_string(-N17)+' '+to_string(E72)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N17)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N17)+' '+to_string(E74)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N17)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N17)+' '+to_string(E65)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N17)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N17)+' '+to_string(E56)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N17)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N17)+' '+to_string(E47)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N17)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N17)+' '+to_string(E27)+" 0");
                //71 15
                ls.push_back(to_string(-N71)+' '+to_string(-N15)+' '+to_string(E72)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N15)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N15)+' '+to_string(E74)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N15)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N15)+' '+to_string(E65)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N15)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N15)+' '+to_string(E45)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N15)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N15)+' '+to_string(E25)+" 0");
                //71 13
                ls.push_back(to_string(-N71)+' '+to_string(-N13)+' '+to_string(E72)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N13)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N13)+' '+to_string(E63)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N13)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N13)+' '+to_string(E43)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N13)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N71)+' '+to_string(-N13)+' '+to_string(E23)+" 0");
                //13 39
                ls.push_back(to_string(-N13)+' '+to_string(-N39)+' '+to_string(E23)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N39)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N39)+' '+to_string(E34)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N39)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N39)+' '+to_string(E36)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N39)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N39)+' '+to_string(E38)+" 0");
                //13 59
                ls.push_back(to_string(-N13)+' '+to_string(-N59)+' '+to_string(E23)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N59)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N59)+' '+to_string(E43)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N59)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N59)+' '+to_string(E54)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N59)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N59)+' '+to_string(E56)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N59)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N59)+' '+to_string(E58)+" 0");
                //13 79
                ls.push_back(to_string(-N13)+' '+to_string(-N79)+' '+to_string(E23)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N79)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N79)+' '+to_string(E43)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N79)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N79)+' '+to_string(E63)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N79)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N79)+' '+to_string(E74)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N79)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N79)+' '+to_string(E76)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N79)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N79)+' '+to_string(E78)+" 0");
                //13 97
                ls.push_back(to_string(-N13)+' '+to_string(-N97)+' '+to_string(E23)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N97)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N97)+' '+to_string(E43)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N97)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N97)+' '+to_string(E54)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N97)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N97)+' '+to_string(E56)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N97)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N97)+' '+to_string(E67)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N97)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N97)+' '+to_string(E87)+" 0");
                //13 95
                ls.push_back(to_string(-N13)+' '+to_string(-N95)+' '+to_string(E23)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N95)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N95)+' '+to_string(E43)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N95)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N95)+' '+to_string(E54)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N95)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N95)+' '+to_string(E65)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N95)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N95)+' '+to_string(E85)+" 0");
                //13 93
                ls.push_back(to_string(-N13)+' '+to_string(-N93)+' '+to_string(E23)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N93)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N93)+' '+to_string(E43)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N93)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N93)+' '+to_string(E63)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N93)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N13)+' '+to_string(-N93)+' '+to_string(E83)+" 0");
                //15 39
                ls.push_back(to_string(-N15)+' '+to_string(-N39)+' '+to_string(E25)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N39)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N39)+' '+to_string(E36)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N39)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N39)+' '+to_string(E38)+" 0");
                //15 59
                ls.push_back(to_string(-N15)+' '+to_string(-N59)+' '+to_string(E25)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N59)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N59)+' '+to_string(E45)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N59)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N59)+' '+to_string(E56)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N59)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N59)+' '+to_string(E58)+" 0");
                //15 79
                ls.push_back(to_string(-N15)+' '+to_string(-N79)+' '+to_string(E25)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N79)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N79)+' '+to_string(E45)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N79)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N79)+' '+to_string(E65)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N79)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N79)+' '+to_string(E76)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N79)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N79)+' '+to_string(E78)+" 0");
                //15 97
                ls.push_back(to_string(-N15)+' '+to_string(-N97)+' '+to_string(E25)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N97)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N97)+' '+to_string(E45)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N97)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N97)+' '+to_string(E56)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N97)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N97)+' '+to_string(E67)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N97)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N97)+' '+to_string(E87)+" 0");
                //15 95
                ls.push_back(to_string(-N15)+' '+to_string(-N95)+' '+to_string(E25)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N95)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N95)+' '+to_string(E45)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N95)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N95)+' '+to_string(E65)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N95)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N95)+' '+to_string(E85)+" 0");
                //15 93
                ls.push_back(to_string(-N15)+' '+to_string(-N93)+' '+to_string(E25)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N93)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N93)+' '+to_string(E45)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N93)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N93)+' '+to_string(E54)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N93)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N93)+' '+to_string(E63)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N93)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N15)+' '+to_string(-N93)+' '+to_string(E83)+" 0");
                //17 39
                ls.push_back(to_string(-N17)+' '+to_string(-N39)+' '+to_string(E27)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N39)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N39)+' '+to_string(E38)+" 0");
                //17 59
                ls.push_back(to_string(-N17)+' '+to_string(-N59)+' '+to_string(E27)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N59)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N59)+' '+to_string(E47)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N59)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N59)+' '+to_string(E58)+" 0");
                //17 79
                ls.push_back(to_string(-N17)+' '+to_string(-N79)+' '+to_string(E27)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N79)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N79)+' '+to_string(E47)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N79)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N79)+' '+to_string(E67)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N79)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N79)+' '+to_string(E78)+" 0");
                //17 97
                ls.push_back(to_string(-N17)+' '+to_string(-N97)+' '+to_string(E27)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N97)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N97)+' '+to_string(E47)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N97)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N97)+' '+to_string(E67)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N97)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N97)+' '+to_string(E87)+" 0");
                //17 95
                ls.push_back(to_string(-N17)+' '+to_string(-N95)+' '+to_string(E27)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N95)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N95)+' '+to_string(E47)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N95)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N95)+' '+to_string(E56)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N95)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N95)+' '+to_string(E65)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N95)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N95)+' '+to_string(E85)+" 0");
                //17 93
                ls.push_back(to_string(-N17)+' '+to_string(-N93)+' '+to_string(E27)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N93)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N93)+' '+to_string(E47)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N93)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N93)+' '+to_string(E56)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N93)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N93)+' '+to_string(E54)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N93)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N93)+' '+to_string(E63)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N93)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N17)+' '+to_string(-N93)+' '+to_string(E83)+" 0");
                //39 93
                ls.push_back(to_string(-N39)+' '+to_string(-N93)+' '+to_string(E38)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N93)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N93)+' '+to_string(E36)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N93)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N93)+' '+to_string(E34)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N93)+' '+to_string(N33)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N93)+' '+to_string(E43)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N93)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N93)+' '+to_string(E63)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N93)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N93)+' '+to_string(E83)+" 0");
                //39 95
                ls.push_back(to_string(-N39)+' '+to_string(-N95)+' '+to_string(E38)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N95)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N95)+' '+to_string(E36)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N95)+' '+to_string(N35)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N95)+' '+to_string(E45)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N95)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N95)+' '+to_string(E65)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N95)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N95)+' '+to_string(E85)+" 0");
                //39 97
                ls.push_back(to_string(-N39)+' '+to_string(-N97)+' '+to_string(E38)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N97)+' '+to_string(N37)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N97)+' '+to_string(E47)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N97)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N97)+' '+to_string(E67)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N97)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N39)+' '+to_string(-N97)+' '+to_string(E87)+" 0");
                //59 93
                ls.push_back(to_string(-N59)+' '+to_string(-N93)+' '+to_string(E58)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N93)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N93)+' '+to_string(E56)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N93)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N93)+' '+to_string(E54)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N93)+' '+to_string(N53)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N93)+' '+to_string(E63)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N93)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N93)+' '+to_string(E83)+" 0");
                //59 95
                ls.push_back(to_string(-N59)+' '+to_string(-N95)+' '+to_string(E58)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N95)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N95)+' '+to_string(E56)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N95)+' '+to_string(N55)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N95)+' '+to_string(E65)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N95)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N95)+' '+to_string(E85)+" 0");
                //59 97
                ls.push_back(to_string(-N59)+' '+to_string(-N97)+' '+to_string(E58)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N97)+' '+to_string(N57)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N97)+' '+to_string(E67)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N97)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N59)+' '+to_string(-N97)+' '+to_string(E87)+" 0");
                //79 93
                ls.push_back(to_string(-N79)+' '+to_string(-N93)+' '+to_string(E83)+" 0");
                ls.push_back(to_string(-N79)+' '+to_string(-N93)+' '+to_string(N73)+" 0");
                ls.push_back(to_string(-N79)+' '+to_string(-N93)+' '+to_string(E74)+" 0");
                ls.push_back(to_string(-N79)+' '+to_string(-N93)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N79)+' '+to_string(-N93)+' '+to_string(E76)+" 0");
                ls.push_back(to_string(-N79)+' '+to_string(-N93)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N79)+' '+to_string(-N93)+' '+to_string(E78)+" 0");
                //79 95
                ls.push_back(to_string(-N79)+' '+to_string(-N95)+' '+to_string(E85)+" 0");
                ls.push_back(to_string(-N79)+' '+to_string(-N95)+' '+to_string(N75)+" 0");
                ls.push_back(to_string(-N79)+' '+to_string(-N95)+' '+to_string(E76)+" 0");
                ls.push_back(to_string(-N79)+' '+to_string(-N95)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N79)+' '+to_string(-N95)+' '+to_string(E78)+" 0");
                //79 97
                ls.push_back(to_string(-N79)+' '+to_string(-N97)+' '+to_string(E78)+" 0");
                ls.push_back(to_string(-N79)+' '+to_string(-N97)+' '+to_string(N77)+" 0");
                ls.push_back(to_string(-N79)+' '+to_string(-N97)+' '+to_string(E87)+" 0");
            }
        }
    }

    //tile structure end
    vector<int> donotsetfalserow0, donotsetfalsecol0, donotsetfalserow1, donotsetfalsecol1;
    for(int i = 0; i < 2; i++){//G
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