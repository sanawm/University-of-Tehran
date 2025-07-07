#include<iostream>
#include<vector>
#include<cstring>
#include<fstream>
using namespace std;

struct each_days{
    string data;
    string day;
    string month;
    string year;
    vector<string>diary;
    int diary_line=0;
    int characters=0;
    int positive_words=0;
};
typedef struct each_days each_days;

string first_word(string str);
string data(string str);
int counting_characters(vector<each_days>all_days,int count_days);
int counting_positive_words(vector<each_days>all_days,int current_day);
vector<int> recognize_the_longest_day(vector<each_days>all_days,int count_days);
vector<int> recognize_the_best_day(vector<each_days>all_days,int count_days);
int summary_of_diary(vector<each_days>all_days,int current_day);
void if_two_day_are_same(vector<int>a,vector<each_days>all_days);

int main(){
    vector<each_days>all_days(50);
    vector<int>a; //To simplify
    int count_days=-1,current_day=0;
    string str,data_to_show;
    int truee=1;

    while(truee){
        
        while(getline(cin,str,'\n')){
            
            if(first_word(str).compare("start_day ")==0){
                count_days++;
                all_days[count_days].data=data(str);
                string data_=data(str);
                all_days[count_days].day=data_.substr(0,2);
                all_days[count_days].month=data_.substr(3,2);
                all_days[count_days].year=data_.substr(6,4);
            }

            else if(first_word(str).compare("show_day ")==0){
                data_to_show=data(str);
                for(int i=0;i<=count_days;i++){
                    if((all_days[i].data).compare(data_to_show)==0){
                        for(int x=0;x<all_days[i].diary_line;x++)
                            cout<<all_days[i].diary[x]<<"\n";
                    }
                }
            }

            else if(first_word(str).compare("show_the_longest_day")==0){
                for(int i=0;i<=count_days;i++)
                   all_days[i].characters=counting_characters(all_days,i);
                for(int i=0;i<=count_days;i++)
                    all_days[i].characters=counting_positive_words(all_days,i);
                a=recognize_the_longest_day(all_days,count_days);
                if(a.size()==1){
                    current_day=a[0];
                    cout<<all_days[current_day].data<<"\n";
                    summary_of_diary(all_days,current_day);
                }
                else
                    if_two_day_are_same(a,all_days);
            }

            else if(first_word(str).compare("show_the_best_day")==0){
                for(int i=0;i<=count_days;i++)
                    all_days[i].positive_words=counting_positive_words(all_days,i);
                for(int i=0;i<=count_days;i++)
                    all_days[i].characters=counting_characters(all_days,i);
                a=recognize_the_best_day(all_days,count_days);
                if(a.size()==1){
                    current_day=a[0];
                    cout<<all_days[current_day].data<<"\n";
                    summary_of_diary(all_days,current_day);
                }
                else{
                    if_two_day_are_same(a,all_days);
                }
            }
            
            else{ //write diary for last started day
                all_days[count_days].diary.push_back(str);
                (all_days[count_days].diary_line)++;
            }
    
        }
    }

}


string first_word(string str){ //separate the first word to recognize the command
    string word;
    int str_size = str.size();
    for(int i = 0; i < str_size; i++){
        word.push_back(str[i]);
        if(str[i] == ' ') 
            break;
    }
    
    return word;
}
string data(string str){ //to find the data that user wants
    int i=1;
    string word="";
    int str_size = str.size();
    while(str[i]!=' ')
        i++;
    for(int j=i+1;j<str_size;j++){
        word.push_back(str[j]);
        if(str[j] == '\n')
            break;
    }
    return word;
}
int counting_characters(vector<each_days>all_days,int count_days){//function that get the day and return that how many chararcters it has
    int characters=0;
    for(int x=0;x<(all_days[count_days].diary_line);x++){
        characters+=(all_days[count_days].diary[x].size());                
    }   
    return characters;
}
vector<int> recognize_the_longest_day(vector<each_days>all_days,int count_days){
    vector<int>same_number_of_characters;
    int max=all_days[0].characters;
    for(int i=1;i<=count_days;i++){
        if(all_days[i].characters>max)
            max=all_days[i].characters;
    }
    for(int i=0;i<=count_days;i++){
        if(all_days[i].characters==max)
            same_number_of_characters.push_back(i);
    }
    return same_number_of_characters;
}
int summary_of_diary(vector<each_days>all_days,int current_day){
    string str="";
    if(all_days[current_day].characters<=20){
        for(int x=0;x<all_days[current_day].diary_line;x++)
            cout<<all_days[current_day].diary[x]<<"\n";
        return 0;
    }
    else{
        for(int x=0;x<all_days[current_day].diary_line;x++){
                str=str+all_days[current_day].diary[x]+"\n";
            }
    }
    cout<<str.substr(0,20)<<"...\n";
}
int counting_positive_words(vector<each_days>all_days,int current_day){
    fstream file;
    string positive_word;
    string str;
    int slen=0,wordlen=0;
    int i=0,j=0,count=0;
        for(int z=0;z<all_days[current_day].diary_line;z++){
            file.open("positive-words.txt",ios::in);
            positive_word="";
            str=all_days[current_day].diary[z];
            slen = str.size();
            while(getline(file,positive_word)){
                wordlen = positive_word.size();
                for(i=0;i<slen; i++){
                    for(j=0;j<wordlen; j++){
                        if(str[i+j]!=positive_word[j])
                            break;
                    }
                    if(j ==wordlen){
                        count++;
                    }
                }
            }
            file.close();
        }
    return count;
}
void if_two_day_are_same(vector<int>a,vector<each_days>all_days){
    int current_day=0,flag=0,size=0;
    string min;
    size=a.size();
    min=all_days[0].year;
    current_day=0;
    for(int i=1;i<size;i++){
        if(all_days[i].year<min){
            min=all_days[i].year;
            flag=1;
            current_day=i;
        }
    }
    if(flag==1){
        cout<<all_days[current_day].data<<"\n";
        summary_of_diary(all_days,current_day);
    }
    else{
        min=all_days[0].month;
        current_day=0;
        for(int i=1;i<size;i++){
            if(all_days[i].month<min){
                min=all_days[i].month;
                flag=1;
                current_day=i;
            }
        }
        if(flag==1){
            cout<<all_days[current_day].data<<"\n";
            summary_of_diary(all_days,current_day);
        }
        else{
            min=all_days[0].day;
            current_day=0;
            for(int i=1;i<size;i++){
                if(all_days[i].month>min){
                    min=all_days[i].month;
                    flag=1;
                    current_day=i;
                }
            }
            if(flag==1){
                cout<<all_days[current_day].data<<"\n";
                summary_of_diary(all_days,current_day);
            }
        }
    }
}
vector<int> recognize_the_best_day(vector<each_days>all_days,int count_days){
    vector<int>same_number_of_positive_words;
    int max=all_days[0].positive_words;
    for(int i=1;i<=count_days;i++){
        if(all_days[i].positive_words>max)
            max=all_days[i].positive_words;
    }
    for(int i=0;i<=count_days;i++){
        if(all_days[i].positive_words==max)
            same_number_of_positive_words.push_back(i);
    }
    return same_number_of_positive_words;
}