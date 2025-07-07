#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n=0,p=0,q=0,m=0;
    int i=1,j=1;
    int a=0,b=0,c=0,count=0,flag=0;
    cin>>n;
    vector<int> result(n);
    while(i<=n){
        cin>>p;
        cin>>q;
        cin>>m;
        c=0;
        j=1;
        flag=0;
        while(j<=m){
            cin>>a;
            cin>>b;
            if((b-a)>q){
                flag=1;
            }
            c=c+(b-a);
            j++;
        }
        if(flag==1){
            result[count]=0;
            count++;
            
        }
        else if(c>p){
            result[count]=0;
            count++;
        }
        else{
            result[count]=1;
            count++;
        }
        i++;
    }
    for(i=0;i<n;i++)
        cout<<result[i];
    cout<<"\n";
}
