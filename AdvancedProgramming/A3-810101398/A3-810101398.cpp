#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
struct Teachers
{
    string teacher_name;
    int number_of_free_days;
    vector<string> free_days;
    int number_of_courses;
    vector<string> courses;
    int teacher_day[5] = {0};
    vector<int> teacher_course;
    int teacher_id;
};
struct Courses
{
    string course_name;
    string day1;
    string day2;
    string start_time;
    string end_time;
    int course_day[2];
    int course_time[3] = {0};
    int course_id;
};
struct Co_Tea
{
    string c_name;
    string t_name;
    int c_time;
    int first_day;
    int second_day;
    int flag = 0;
    int classs = 0;
    int c_id;
    int t_id;
};
vector<Teachers> Get_and_fix_teachers(int how_many_teachers);
vector<Courses> Get_and_fix_courses(int how_many_courses);
bool Sorting_courses(const Courses &c1, const Courses &c2);
bool Sorting_teachers(const Teachers &c1, const Teachers &c2);
bool Sorting_alphabetical(const Courses &c1, const Courses &c2);
bool Final_sorting(const Co_Tea &c1, const Co_Tea &c2);
vector<Courses> Process_on_all_courses(vector<Courses> all_courses, int how_many_courses);
vector<Teachers> Process_on_all_teachers(vector<Teachers> all_teachers, vector<Courses> all_courses, int how_many_teachers, int how_many_courses);
vector<Co_Tea> Main_process(vector<Teachers> all_teachers, vector<Courses> all_courses, int how_many_teachers, int how_many_courses, int number_of_all_situation);
int Count_all_situation(vector<Teachers> all_teachers, vector<Courses> all_courses, int how_many_teachers, int how_many_courses);
void Final_process_and_print(vector<Teachers> all_teachers, vector<Courses> all_courses, vector<Co_Tea> all_situation, int how_many_teachers, int how_many_courses, int number_of_all_situation);
int main()
{
    int how_many_teachers, how_many_courses, number_of_all_situation;
    cin >> how_many_teachers;
    cin.ignore();
    vector<Teachers> all_teachers(how_many_teachers);
    all_teachers = Get_and_fix_teachers(how_many_teachers);
    sort(all_teachers.begin(), all_teachers.end(), Sorting_teachers); // sort teachers
    cin >> how_many_courses;
    cin.ignore();
    vector<Courses> all_courses(how_many_courses);
    all_courses = Get_and_fix_courses(how_many_courses);
    sort(all_courses.begin(), all_courses.end(), Sorting_alphabetical); // sort alphabetically courses
    for (int i = 0; i < how_many_courses; i++)                          // course id
        all_courses[i].course_id = i;
    all_courses = Process_on_all_courses(all_courses, how_many_courses);
    sort(all_courses.begin(), all_courses.end(), Sorting_courses);
    all_teachers = Process_on_all_teachers(all_teachers, all_courses, how_many_teachers, how_many_courses);

    number_of_all_situation = Count_all_situation(all_teachers, all_courses, how_many_teachers, how_many_courses);

    vector<Co_Tea> all_situation(number_of_all_situation);
    all_situation = Main_process(all_teachers, all_courses, how_many_teachers, how_many_courses, number_of_all_situation);
    Final_process_and_print(all_teachers, all_courses, all_situation, how_many_teachers, how_many_courses, number_of_all_situation);
}
vector<Teachers> Get_and_fix_teachers(int how_many_teachers)
{
    vector<Teachers> all_teachers(how_many_teachers);
    string str, word;
    int n, j, z;
    for (int i = 0; i < how_many_teachers; i++)
    {
        word = "";
        getline(cin, str, '\n');
        j = 0;
        while (str[j] != ' ')
        { // recognize teacher_name
            word.push_back(str[j]);
            j++;
        }
        all_teachers[i].teacher_name = word;
        word = "";
        j++;
        n = int(str[j]) - 48;
        j += 2;
        all_teachers[i].number_of_free_days = n;
        if (all_teachers[i].number_of_free_days != 0)
        {
            for (z = 0; z < n; z++)
            {
                while (str[j] != ' ')
                { // recognize free_days of the teacher
                    word.push_back(str[j]);
                    j++;
                }
                all_teachers[i].free_days.push_back(word);
                word = "";
                j++;
            }
        }
        word = "";
        n = int(str[j]) - 48;
        j += 2;
        all_teachers[i].number_of_courses = n;
        if (all_teachers[i].number_of_courses != 0)
        {
            for (z = 0; z < n - 1; z++)
            {
                while (str[j] != ' ')
                {
                    word.push_back(str[j]);
                    j++;
                }
                all_teachers[i].courses.push_back(word);
                word = "";
                j++;
            }
            word = "";
            while (str[j] != '\0')
            {
                word.push_back(str[j]);
                j++;
            }
            all_teachers[i].courses.push_back(word);
        }
    }
    return all_teachers;
}
vector<Courses> Get_and_fix_courses(int how_many_courses)
{
    vector<Courses> all_courses(how_many_courses);
    string str, word;
    int n, j, z;
    for (int i = 0; i < how_many_courses; i++)
    {
        word = "";
        getline(cin, str, '\n');
        j = 0;
        while (str[j] != ' ')
        { // recognize name of the course
            word.push_back(str[j]);
            j++;
        }
        all_courses[i].course_name = word;
        word = "";
        j++;
        while (str[j] != ' ')
        { // recognize day1
            word.push_back(str[j]);
            j++;
        }
        all_courses[i].day1 = word;
        word = "";
        j++;
        while (str[j] != ' ')
        { // recognize day2
            word.push_back(str[j]);
            j++;
        }
        all_courses[i].day2 = word;
        word = "";
        j++;
        while (str[j] != ' ')
        { // recognize start_time
            word.push_back(str[j]);
            j++;
        }
        all_courses[i].start_time = word;
        word = "";
        j++;
        while (str[j] != '\n')
        { // recognize end_time
            word.push_back(str[j]);
            j++;
        }
        all_courses[i].end_time = word;
    }
    return all_courses;
}
bool Sorting_courses(const Courses &c1, const Courses &c2)
{
    if (c1.course_day[0] == c2.course_day[0])
    {
       // if (c1.course_time[0] == c2.course_time[0])
    
           /* if (c1.course_time[1] == c2.course_time[1])
            {
                if (c1.course_time[2] == c2.course_time[2])*/
                   // return c1.course_name < c2.course_name;
             /*   else
                    return c1.course_time[2] == 1;
            }
            else
                return c1.course_time[1] > c2.course_time[1];*/
    
        //else
            return  c1.course_name < c2.course_name;
    }
    else
        return c1.course_day[0] < c2.course_day[0];
}
bool Sorting_teachers(const Teachers &c1, const Teachers &c2)
{
    if (c1.number_of_free_days == c2.number_of_free_days)
        return c1.teacher_name < c2.teacher_name;
    else
        return c1.number_of_free_days < c2.number_of_free_days;
}
bool Sorting_alphabetical(const Courses &c1, const Courses &c2)
{
    return c1.course_name < c2.course_name;
}
bool Final_sorting(const Co_Tea &c1, const Co_Tea &c2)
{
    if (c1.c_id == c2.c_id)
        return c1.classs < c2.classs;
    else
        return c1.c_id < c2.c_id;
}
vector<Courses> Process_on_all_courses(vector<Courses> all_courses, int how_many_courses)
{
    int i = 0;
    for (i = 0; i < how_many_courses; i++)
    {
        if (all_courses[i].day1 == "Saturday")
        {
            all_courses[i].course_day[0] = 0;
        }
        if (all_courses[i].day1 == "Sunday")
        {
            all_courses[i].course_day[0] = 1;
        }
        if (all_courses[i].day1 == "Monday")
        {
            all_courses[i].course_day[0] = 2;
        }
        if (all_courses[i].day1 == "Tuesday")
        {
            all_courses[i].course_day[0] = 3;
        }
        if (all_courses[i].day1 == "Wednesday")
        {
            all_courses[i].course_day[0] = 4;
        }
        if (all_courses[i].day2 == "Saturday")
        {
            all_courses[i].course_day[1] = 0;
        }
        if (all_courses[i].day2 == "Sunday")
        {
            all_courses[i].course_day[1] = 1;
        }
        if (all_courses[i].day2 == "Monday")
        {
            all_courses[i].course_day[1] = 2;
        }
        if (all_courses[i].day2 == "Tuesday")
        {
            all_courses[i].course_day[1] = 3;
        }
        if (all_courses[i].day2 == "Wednesday")
        {
            all_courses[i].course_day[1] = 4;
        }
        if (all_courses[i].course_day[0] > all_courses[i].course_day[1])
        {
            int temp = all_courses[i].course_day[0];
            all_courses[i].course_day[0] = all_courses[i].course_day[1];
            all_courses[i].course_day[1] = temp;
        }
    }
    for (i = 0; i < how_many_courses; i++)
    {
        if ((all_courses[i].start_time <= "07:30") && (all_courses[i].end_time >= "09:00"))
            all_courses[i].course_time[0] = 1;
        if ((all_courses[i].start_time <= "09:30") && (all_courses[i].end_time >= "11:00"))
            all_courses[i].course_time[1] = 1;
        if ((all_courses[i].start_time <= "11:30") && (all_courses[i].end_time >= "13:00"))
            all_courses[i].course_time[2] = 1;
    }
    return all_courses;
}
vector<Teachers> Process_on_all_teachers(vector<Teachers> all_teachers, vector<Courses> all_courses, int how_many_teachers, int how_many_courses)
{
    int i, j, t;
    for (i = 0; i < how_many_teachers; i++)
    {
        all_teachers[i].teacher_id = i; // teacher id
        for (j = 0; j < all_teachers[i].number_of_free_days; j++)
        {
            if (all_teachers[i].free_days[j] == "Saturday")
                all_teachers[i].teacher_day[0] = 1;
            if (all_teachers[i].free_days[j] == "Sunday")
                all_teachers[i].teacher_day[1] = 1;
            if (all_teachers[i].free_days[j] == "Monday")
                all_teachers[i].teacher_day[2] = 1;
            if (all_teachers[i].free_days[j] == "Tuesday")
                all_teachers[i].teacher_day[3] = 1;
            if (all_teachers[i].free_days[j] == "Wednesday")
                all_teachers[i].teacher_day[4] = 1;
        }
    }
    vector<int> test(how_many_courses);
    for (i = 0; i < how_many_teachers; i++)
    {
        for (j = 0; j < how_many_courses; j++)
        {
            for (t = 0; t < all_teachers[i].number_of_courses; t++)
            {
                if (all_teachers[i].courses[t] == all_courses[j].course_name)
                {
                    test[j] = 1;
                    break;
                }
            }
        }
        all_teachers[i].teacher_course = test;
        for (int n = 0; n < how_many_courses; n++)
            test[n] = 0;
    }
    return all_teachers;
}
int Count_all_situation(vector<Teachers> all_teachers, vector<Courses> all_courses, int how_many_teachers, int how_many_courses)
{
    int counter = 0, i, j;
    for (i = 0; i < how_many_courses; i++)
    {
        for (j = 0; j < how_many_teachers; j++)
        {
            if (all_teachers[j].teacher_course[i] == 1)
            {
                if ((all_teachers[j].teacher_day[all_courses[i].course_day[0]] == 1) && (all_teachers[j].teacher_day[all_courses[i].course_day[1]] == 1))
                {
                    if (all_courses[i].course_time[0] == 1)
                        counter++;
                    if (all_courses[i].course_time[1] == 1)
                        counter++;
                    if (all_courses[i].course_time[2] == 1)
                        counter++;
                }
            }
        }
    }
    return counter;
}
vector<Co_Tea> Main_process(vector<Teachers> all_teachers, vector<Courses> all_courses, int how_many_teachers, int how_many_courses, int number_of_all_situation)
{
    vector<Co_Tea> all_situation(number_of_all_situation);
    int counter = 0, i, j;
    for (i = 0; i < how_many_courses; i++)
    {
        for (j = 0; j < how_many_teachers; j++)
        {
            if (all_teachers[j].teacher_course[i] == 1)
            { // If the teacher teaches the course
                if ((all_teachers[j].teacher_day[all_courses[i].course_day[0]] == 1) && (all_teachers[j].teacher_day[all_courses[i].course_day[1]] == 1))
                {
                    if (all_courses[i].course_time[0] == 1)
                    {
                        all_situation[counter].t_name = all_teachers[j].teacher_name;
                        all_situation[counter].c_name = all_courses[i].course_name;
                        all_situation[counter].c_time = 0;
                        all_situation[counter].first_day = all_courses[i].course_day[0];
                        all_situation[counter].second_day = all_courses[i].course_day[1];
                        all_situation[counter].c_id = all_courses[i].course_id;
                        all_situation[counter].t_id = all_teachers[j].teacher_id;
                        counter++;
                    }
                    if (all_courses[i].course_time[1] == 1)
                    {
                        all_situation[counter].t_name = all_teachers[j].teacher_name;
                        all_situation[counter].c_name = all_courses[i].course_name;
                        all_situation[counter].c_time = 1;
                        all_situation[counter].first_day = all_courses[i].course_day[0];
                        all_situation[counter].second_day = all_courses[i].course_day[1];
                        all_situation[counter].c_id = all_courses[i].course_id;
                        all_situation[counter].t_id = all_teachers[j].teacher_id;
                        counter++;
                    }
                    if (all_courses[i].course_time[2] == 1)
                    {
                        all_situation[counter].c_id = all_courses[i].course_id;
                        all_situation[counter].t_name = all_teachers[j].teacher_name;
                        all_situation[counter].c_name = all_courses[i].course_name;
                        all_situation[counter].c_time = 2;
                        all_situation[counter].first_day = all_courses[i].course_day[0];
                        all_situation[counter].second_day = all_courses[i].course_day[1];
                        all_situation[counter].t_id = all_teachers[j].teacher_id;
                        counter++;
                    }
                }
            }
        }
    }
    return all_situation;
}
void Final_process_and_print(vector<Teachers> all_teachers, vector<Courses> all_courses, vector<Co_Tea> all_situation, int how_many_teachers, int how_many_courses, int number_of_all_situation)
{

    int s1[5][3] = {0}, s2[5][3] = {0}, ts1[how_many_teachers][5][3] = {0};
    int c1[how_many_courses] = {0}, c2[how_many_courses] = {0};
    for (int i = 0; i < number_of_all_situation; i++) // fix program of class 1
    {
        if ((s1[all_situation[i].first_day][all_situation[i].c_time] == 0) && (s1[all_situation[i].second_day][all_situation[i].c_time] == 0) && (c1[all_situation[i].c_id] == 0) )
        {
            s1[all_situation[i].first_day][all_situation[i].c_time] = 1;
            s1[all_situation[i].second_day][all_situation[i].c_time] = 1;
            all_situation[i].flag = 1;
            all_situation[i].classs = 1;
            c1[all_situation[i].c_id] = 1;
            ts1[all_situation[i].t_id][all_situation[i].first_day][all_situation[i].c_time] = 1;
            ts1[all_situation[i].t_id][all_situation[i].second_day][all_situation[i].c_time] = 1;
        }
    }
    for (int i = 0; i < number_of_all_situation; i++)
    {
        if (all_situation[i].flag == 0)
        {
            if ((s2[all_situation[i].first_day][all_situation[i].c_time] == 0) && (s2[all_situation[i].second_day][all_situation[i].c_time] == 0) && (c2[all_situation[i].c_id] == 0) && (ts1[all_situation[i].t_id][all_situation[i].first_day][all_situation[i].c_time] == 0) && (ts1[all_situation[i].t_id][all_situation[i].second_day][all_situation[i].c_time] == 0))
            {
                s2[all_situation[i].first_day][all_situation[i].c_time] = 1;
                s2[all_situation[i].second_day][all_situation[i].c_time] = 1;
                all_situation[i].classs = 2;
                all_situation[i].flag = 1;
                c2[all_situation[i].c_id] = 1;
            }
        }
    }
    sort(all_courses.begin(), all_courses.end(), Sorting_alphabetical);
    for (int i = 0; i < how_many_courses; i++)
    {
        cout << all_courses[i].course_name << "\n";
        if (c1[all_courses[i].course_id] == 1)
        {
            for (int j = 0; j < number_of_all_situation; j++)
            {
                if (all_situation[j].c_name == all_courses[i].course_name)
                {
                    if (all_situation[j].classs == 1)
                    {
                        if (all_situation[j].c_time == 0)
                            cout << all_situation[j].t_name << ": "
                                 << "07:30 09:00\n";
                        if (all_situation[j].c_time == 1)
                            cout << all_situation[j].t_name << ": "
                                 << "09:30 11:00\n";
                        if (all_situation[j].c_time == 2)
                            cout << all_situation[j].t_name << ": "
                                 << "11:30 13:00\n";
                    }
                }
            }
        }
        else
            cout << "Not Found\n";

        if (c2[all_courses[i].course_id] == 1)
        {
            for (int j = 0; j < number_of_all_situation; j++)
            {
                if (all_situation[j].c_name == all_courses[i].course_name)
                {
                    if (all_situation[j].classs == 2)
                    {
                        if (all_situation[j].c_time == 0)
                            cout << all_situation[j].t_name << ": "
                                 << "07:30 09:00\n";
                        if (all_situation[j].c_time == 1)
                            cout << all_situation[j].t_name << ": "
                                 << "09:30 11:00\n";
                        if (all_situation[j].c_time == 2)
                            cout << all_situation[j].t_name << ": "
                                 << "11:30 13:00\n";
                    }
                }
            }
        }
        else
            cout << "Not Found\n";
    }
}
