#include<iostream>
#include<string>
using namespace std;
string to_upper(string line);
int main() {
    string line;
    while (getline(cin, line)) {
    cout << to_upper(line) << endl;
    }
    return 0;
}
string to_upper(string line)
{
    if(line.length()>1){
        if (line[0] >= 'a' && line[0] <= 'z')
            return char(line[0]-32)+to_upper(line.substr(1));
        else
            return line[0]+to_upper(line.substr(1));
    }
    else if(line.length()==1){
        if (line[0] >= 'a' && line[0] <= 'z'){
            string s(1,line[0]-32);
            return s;
        }
        else
            return line.substr(0);
    }
}