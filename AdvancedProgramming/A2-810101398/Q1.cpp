#include<iostream>
#include<string>
#include<vector>
using namespace std;
string p(vector<int>arr,int pre,bool max);
int main(){
    int n,x;
    cin>>n;
    vector<int>arr;
    for(int i=0;i<n;i++){
        cin>>x;
        arr.push_back(x);
    }
    cout<<p(arr,0,true);
}
string p(vector<int>arr,int pre,bool max){
    int i;
    if(arr[0]==0 && pre==0){
        return "0";
    }
    if(max){ 
        if(arr[0]>=pre)
            i=arr[0];
        else
            i=pre;
    }
    else{
        if(arr[0]<pre)
            i=arr[0];
        else
            i=pre;
    }
    if(i<arr.size()){
        pre=arr[0];
        arr.erase(arr.begin(),arr.begin()+i);
        return to_string(pre)+" "+p(arr,pre,!max);
    }
    return to_string(arr[0]);
}