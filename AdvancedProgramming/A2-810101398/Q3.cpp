#include<iostream>
#include<string>
using namespace std;
string Move(int i,int j);
string Play(char Ground[9][9]);
int main(){
    char Ground[9][9];
    for(int i=0;i<9;i++){
        Ground[0][i]='X';
        Ground[8][i]='X';
        Ground[i][0]='X';
        Ground[i][8]='X';
    }
    for(int i=1;i<8;i++){
        for(int j=1;j<8;j++)
            cin>>Ground[i][j];
    }
    string resp=Play(Ground);
    if(resp=="FAIL")
        cout<<"Loser";
    else
        cout<<resp;
}
string Play(char Ground[9][9]){
    string way="";
    bool meet=false;
    int N_count=0;
    for(int i=1;i<8;i++){
        for(int j=1;j<8;j++){
            if(Ground[i][j]=='N'){
                N_count++;
                    if(Ground[i-1][j]=='N' && Ground[i-2][j]=='O'){
                        meet=true;
                        Ground[i][j]='O';
                        Ground[i-1][j]='O';
                        Ground[i-2][j]='N';
                        way=Play(Ground);
                        if (way=="FAIL"){
                            Ground[i][j]='N';
                            Ground[i-1][j]='N';
                            Ground[i-2][j]='O';
                            way="";
                        }
                        else
                            way=Move(i,j)+" UP"+"\n"+way;
                        if(way!="")
                            return way; 
                    }                        
                    if(Ground[i+1][j]=='N' && Ground[i+2][j]=='O'){
                        meet=true;
                        Ground[i][j]='O';
                        Ground[i+1][j]='O';
                        Ground[i+2][j]='N';
                        way=Play(Ground);
                        if (way=="FAIL"){
                            Ground[i][j]='N';
                            Ground[i+1][j]='N';
                            Ground[i+2][j]='O';
                            way="";
                        }
                        else
                            way=Move(i,j)+" DOWN"+"\n"+way;
                        if(way!="")
                            return way;
                    }   
                    if(Ground[i][j-1]=='N' && Ground[i][j-2]=='O'){
                            meet=true;
                            Ground[i][j]='O';
                            Ground[i][j-1]='O';
                            Ground[i][j-2]='N';
                            way=Play(Ground);
                            if (way=="FAIL"){
                                Ground[i][j]='N';
                                Ground[i][j-1]='N';
                                Ground[i][j-2]='O';
                                way="";
                            }
                            else
                                way=Move(i,j)+" LEFT"+"\n"+way;
                            if(way!="")
                                return way; 
                    }
                    if(Ground[i][j+1]=='N' && Ground[i][j+2]=='O'){
                        meet=true;
                        Ground[i][j]='O';
                        Ground[i][j+1]='O';
                        Ground[i][j+2]='N';
                        way=Play(Ground);
                        if (way=="FAIL"){
                            Ground[i][j]='N';
                            Ground[i][j+1]='N';
                            Ground[i][j+2]='O';
                             way="";
                        }
                        else
                            way=Move(i,j)+" RIGHT"+"\n"+way;
                        if(way!="")
                            return way;
                    }
            }
        }
    }
    if(meet) 
        return "FAIL"; 
    if(!meet){
        if (Ground[4][4]=='N' && N_count==1)
            return "";
        else
            return "FAIL";
    }
}
string Move(int i,int j){
    string str;
    if(i==1)
        str="A"+to_string(j);
    if(i==2)
        str="B"+to_string(j);
    if(i==3)
        str="C"+to_string(j);
    if(i==4)
        str="D"+to_string(j);
    if(i==5)
        str="E"+to_string(j);
    if(i==6)
        str="F"+to_string(j);
    if(i==7)
        str="G"+to_string(j);
    return str;
}