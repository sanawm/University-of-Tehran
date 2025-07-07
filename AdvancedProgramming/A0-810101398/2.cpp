#include<iostream>
using namespace std;
int main(){
    int n=0,p=0,q=0,m=0;
    int i=0,j=1;
    int a=0,b=0,c=0,flag=0,max=0;

    cin>>n;
    int result[n][2];
    while(i<n){
        cin>>p;
        cin>>q;
        cin>>m;
        c=0;
        j=1;
        flag=0;
        max=0;
        while(j<=m){
            cin>>a;
            cin>>b;
            if((b-a)>q){
                if((b-a)>max)
                    max=b-a;
            flag=1;
            }
            c=c+(b-a);
            j++;
        }
        if((flag==1)&&(c<=p)){
            result[i][1]=(max)-q;
            result[i][0]=0;
        }
        if((flag==1)&&(c>p)){
            result[i][1]=(max)-q;
            result[i][0]=c-p;
        }
        if((flag==0)&&(c>p)){
            result[i][0]=c-p;
            result[i][1]=0;
        }
        if((flag==0)&&(c<p)){
            result[i][0]=0;
            result[i][1]=0;
        }
        i++;
    }
    for(i=0;i<n;i++)
        cout<<result[i][0]<<" "<<result[i][1]<<"\n";

}
