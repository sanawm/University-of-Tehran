#include<iostream>
using namespace std;
int waze(int x,int y,int n);
int main(){
    int n;
    cin>>n;
    cout<<waze(0,0,n);
}
int waze(int x,int y,int n){
    if(x==n)
        return 1;
    if(y==n)
        return waze(x+1,y,n);
    if(x==y)
        return waze(x,y+1,n);
    else
        return waze(x+1,y,n)+waze(x,y+1,n);
}