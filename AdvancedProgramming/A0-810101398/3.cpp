#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int n;
    cin >>n;
    vector<int> status(n);
    for(int i=0;i<n;i++)
    {
        int p,q,m,sum=0,a=0,b=0,w=0,z=0;
        cin>>p;
        cin>>q;
        cin>>m;
        status[i]=1;
            for(int j=0;j<m;j++)
            {
               cin>>a;
               cin>>b;
             sum=sum+(b-a);
            if ((b-a)>q)
             {
                status[i]=0;
             }
            else if(q>p)
             {
                status[i]=0;
             }
            else if (sum>p)
             {
                status[i]=0;
             }
            }
    }
for(int i=0;i<n;i++)
cout<<status[i];
}
