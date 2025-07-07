#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <iomanip>
#include <math.h>
#include <algorithm>
using namespace std;
struct activity
{
    int day;
    int start_time;
    int end_time;
};
class Salary_configs
{
public:
    string level;
    int base_salary;
    int salary_per_hour;
    int salary_per_extra_hour;
    int official_working_hours;
    int tax_percentage;
    Salary_configs(){};
    void print();
    void update_salary_parameters(string user_type);
    Salary_configs(string l, int b, int sph, int speh, int o, int t)
    {
        level = l;
        base_salary = b;
        salary_per_hour = sph;
        salary_per_extra_hour = speh;
        official_working_hours = o;
        tax_percentage = t;
    }
};
class Team
{
public:
    int team_id = 0;
    int team_head_id;
    string member_ids;
    int bonus_min_working_hours;
    int bonus_working_hours_max_variance;
    int bonus = 0;
    Team(){};
    void update_team_bonus(string user_type);
    Team(int t, int t_h, string m)
    {
        team_id = t;
        team_head_id = t_h;
        member_ids = m;
    }
};
class Employee
{
public:
    int id;
    string name;
    int age;
    string level;
    Team team;
    vector<activity> employee_activity;
    Salary_configs salary;
    float net_salary;
    float total_ear;
    Employee(){};
    int add_working_hours(string user_type);
    void delete_working_hours(string user_type);
    Employee(int i, string n, int a, string l)
    {
        id = i;
        name = n;
        age = a;
        level = l;
    }
};
class Company
{
public:
    vector<Employee> all_employees;
    vector<Team> all_teams;
    Company(){};
    void calculation_salary();
    void calculation_total_earning();
    void report_salaries();
    void report_employee_salary(int desired_id);
    void report_team_salary(int desired_id);
    int report_total_hours_per_day(int day1, int day2);
    int report_employee_per_hour(int start_hour, int end_hour);
};
int count_the_employees();
int count_the_teams();
int count_the_salary_configs();
vector<Employee> get_and_set_employees(int number_of_all_employees);
vector<Team> get_and_set_teams(int number_of_all_teams);
vector<Salary_configs> get_and_set_salary_configs(int number_of_all_salary_configs);
vector<Employee> specify_the_team_of_each_employee(vector<Employee> all_employees, vector<Team> all_teams);
vector<Employee> set_employees_activity(vector<Employee> all_employees);
vector<Employee> set_employees_salary(vector<Employee> all_employees, vector<Salary_configs> all_salary_configs);
string separate_command(string user_type);
bool sorting(const activity &c1, const activity &c2);
int main()
{
    int number_of_all_employees, number_of_all_teams, number_of_all_salary_configs;
    string user_type, command;
    number_of_all_employees = count_the_employees();
    vector<Employee> all_employees(number_of_all_employees);
    all_employees = get_and_set_employees(number_of_all_employees);
    number_of_all_teams = count_the_teams();
    vector<Team> all_teams(number_of_all_teams);
    all_teams = get_and_set_teams(number_of_all_teams);
    number_of_all_salary_configs = count_the_salary_configs();
    vector<Salary_configs> all_salary_configs(number_of_all_salary_configs);
    all_salary_configs = get_and_set_salary_configs(number_of_all_salary_configs);
    all_employees = specify_the_team_of_each_employee(all_employees, all_teams);
    all_employees = set_employees_activity(all_employees);
    all_employees = set_employees_salary(all_employees, all_salary_configs);
    Company company;
    // get the command
    while (getline(cin, user_type, '\n'))
    {
        all_employees = specify_the_team_of_each_employee(all_employees, all_teams);
        all_employees = set_employees_salary(all_employees, all_salary_configs);
        company.all_teams = all_teams;
        company.all_employees = all_employees;
        company.calculation_salary();
        company.calculation_total_earning();
        int i = 0, desired_id = 0, flag = 0, day1 = 0, day2 = 0, start_hour = 0, end_hour = 0;
        string s = "";
        command = separate_command(user_type);
        if (command.compare("report_salaries") == 0)
        {
            company.report_salaries();
        }
        if (command.compare("report_employee_salary") == 0)
        {
            while (user_type[i] != ' ')
            {
                i++;
            }
            s = user_type[i + 1];
            desired_id = stoi(s);
            company.report_employee_salary(desired_id);
        }
        if (command.compare("report_team_salary") == 0)
        {
            while (user_type[i] != ' ')
            {
                i++;
            }
            s = user_type[i + 1];
            desired_id = stoi(s);
            company.report_team_salary(desired_id);
        }
        if (command.compare("report_total_hours_per_day") == 0)
        {
            while (user_type[i] != ' ')
            {
                i++;
            }
            i++;
            while (user_type[i] != ' ')
            {
                s.push_back(user_type[i]);
                i++;
            }
            day1 = stoi(s);
            i++;
            s = "";
            while (user_type[i] != '\0')
            {
                s.push_back(user_type[i]);
                i++;
            }
            day2 = stoi(s);
            company.report_total_hours_per_day(day1, day2);
        }
        if (command.compare("report_employee_per_hour") == 0)
        {

            while (user_type[i] != ' ')
            {
                i++;
            }
            i++;
            while (user_type[i] != ' ')
            {
                s.push_back(user_type[i]);
                i++;
            }
            start_hour = stoi(s);
            i++;
            s = "";

            while (user_type[i] != '\0')
            {
                s.push_back(user_type[i]);
                i++;
            }
            end_hour = stoi(s);
            company.report_employee_per_hour(start_hour, end_hour);
        }
        if (command.compare("show_salary_config") == 0)
        {
            while (user_type[i] != ' ')
            {
                i++;
            }
            i++;
            while (user_type[i] != '\0')
            {
                s.push_back(user_type[i]);
                i++;
            }
            for (int i = 0; i < 4; i++)
                if (all_salary_configs[i].level == s)
                {
                    all_salary_configs[i].print();
                    flag = 1;
                }
            if (flag == 0)
                cout << "INVALID_LEVEL\n";
        }
        if (command.compare("update_salary_config") == 0)
        {
            while (user_type[i] != ' ')
            {
                i++;
            }
            i++;
            while (user_type[i] != ' ')
            {
                s.push_back(user_type[i]);
                i++;
            }
            for (int i = 0; i < 4; i++)
            {
                if (all_salary_configs[i].level == s)
                {
                    all_salary_configs[i].update_salary_parameters(user_type);
                    flag = 1;
                }
            }
            if (flag == 0)
                cout << "INVALID_LEVEL\n";
        }
        if (command.compare("add_working_hours") == 0)
        {
            while (user_type[i] != ' ')
            {
                i++;
            }
            i++;
            while (user_type[i] != ' ')
            {
                s.push_back(user_type[i]);
                i++;
            }
            for (int i = 0; i < number_of_all_employees; i++)
            {
                if (all_employees[i].id == stoi(s))
                {
                    all_employees[i].add_working_hours(user_type);
                    flag = 1;
                }
            }
            if (flag == 0)
                cout << "EMPLOYEE_NOT_FOUND\n";
        }
        if (command.compare("update_team_bonus") == 0)
        {
            while (user_type[i] != ' ')
            {
                i++;
            }
            i++;
            while (user_type[i] != ' ')
            {
                s.push_back(user_type[i]);
                i++;
            }
            desired_id = stoi(s);
            for (int i = 0; i < number_of_all_teams; i++)
            {
                if (all_teams[i].team_id == desired_id)
                {
                    all_teams[i].update_team_bonus(user_type);
                    flag = 1;
                }
            }
            if (flag == 0)
                cout << "TEAM_NOT_FOUND\n";
        }
        if (command.compare("delete_working_hours") == 0)
        {
            while (user_type[i] != ' ')
            {
                i++;
            }
            i++;
            while (user_type[i] != ' ')
            {
                s.push_back(user_type[i]);
                i++;
            }
            for (int i = 0; i < number_of_all_employees; i++)
            {
                if (all_employees[i].id == stoi(s))
                {
                    all_employees[i].delete_working_hours(user_type);
                    flag = 1;
                }
            }
            if (flag == 0)
                cout << "EMPLOYEE_NOT_FOUND\n";
        }
    }
}
int count_the_employees()
{
    ifstream infile;
    int n = 0;
    string str;
    infile.open("employees.csv");
    getline(infile, str, '\n');
    while (!infile.eof())
    {
        n++;
        getline(infile, str, '\n');
    }
    infile.close();
    return n;
}
vector<Employee> get_and_set_employees(int number_of_all_employees)
{
    ifstream infile;
    int id = 0, age = 0, n = 0, counter = 0, i = 0;
    string name, level, str, agee, idd;
    vector<Employee> all_employees(number_of_all_employees);
    infile.open("employees.csv");
    getline(infile, str, '\n');
    while (!infile.eof())
    {
        getline(infile, str, '\n');
        while (str[i] != ',')
        {
            idd.push_back(str[i]);
            i++;
        }
        id = stoi(idd);
        i++;
        while (str[i] != ',')
        {
            name.push_back(str[i]);
            i++;
        }
        i++;
        while (str[i] != ',')
        {
            agee.push_back(str[i]);
            i++;
        }
        age = stoi(agee);
        i++;
        while (str[i] != '\0')
        {
            level.push_back(str[i]);
            i++;
        }
        Employee e(id, name, age, level);
        all_employees[counter] = e;
        counter++;
        idd = "";
        name = "";
        level = "";
        agee = "";
        i = 0;
    }
    infile.close();
    return all_employees;
}
int count_the_teams()
{
    ifstream infile;
    int n = 0;
    string str;
    infile.open("teams.csv");
    getline(infile, str, '\n');
    while (!infile.eof())
    {
        n++;
        getline(infile, str, '\n');
    }
    infile.close();
    return n;
}
vector<Team> get_and_set_teams(int number_of_all_teams)
{
    ifstream infile;
    string str, team_id1, team_head_id1, memeber_ids, bonus_min_working_hours1, bonus_working_hours_max_variance1;
    int i = 0, counter = 0, team_id = 0, team_head_id = 0, bonus_min_working_hours = 0;
    double bonus_working_hours_max_variance;
    vector<Team> all_teams(number_of_all_teams);
    infile.open("teams.csv");
    getline(infile, str, '\n');
    while (!infile.eof())
    {
        getline(infile, str, '\n');
        while (str[i] != ',')
        {
            team_id1.push_back(str[i]);
            i++;
        }
        team_id = stoi(team_id1);
        i++;
        while (str[i] != ',')
        {
            team_head_id1.push_back(str[i]);
            i++;
        }
        team_head_id = stoi(team_head_id1);
        i++;
        while (str[i] != ',')
        {
            memeber_ids.push_back(str[i]);
            i++;
        }
        i++;
        while (str[i] != ',')
        {
            bonus_min_working_hours1.push_back(str[i]);
            i++;
        }
        bonus_min_working_hours = stoi(bonus_min_working_hours1);
        i++;
        while (str[i] != '\0')
        {
            bonus_working_hours_max_variance1.push_back(str[i]);
            i++;
        }
        bonus_working_hours_max_variance = stod(bonus_working_hours_max_variance1);
        Team t(team_id, team_head_id, memeber_ids);
        all_teams[counter] = t;
        counter++;
        team_id1 = "";
        team_head_id1 = "";
        memeber_ids = "";
        bonus_min_working_hours1 = "";
        bonus_working_hours_max_variance1 = "";
        i = 0;
    }
    infile.close();
    return all_teams;
}
int count_the_salary_configs()
{
    ifstream infile;
    int n = 0;
    string str;
    infile.open("salary_configs.csv");
    getline(infile, str, '\n');
    while (!infile.eof())
    {
        n++;
        getline(infile, str, '\n');
    }
    infile.close();
    return n;
}
vector<Salary_configs> get_and_set_salary_configs(int number_of_all_salary_configs)
{
    ifstream infile;
    int i = 0, counter = 0, base_salary = 0, salary_per_hour = 0, salary_per_extra_hour = 0, official_working_hours = 0, tax_percentage = 0;
    string str, level, base_salary1, salary_per_hour1, salary_per_extra_hour1, official_working_hours1, tax_percentage1;
    vector<Salary_configs> all_salary_configs(number_of_all_salary_configs);
    infile.open("salary_configs.csv");
    getline(infile, str, '\n');
    while (!infile.eof())
    {
        getline(infile, str, '\n');
        while (str[i] != ',')
        {
            level.push_back(str[i]);
            i++;
        }
        i++;
        while (str[i] != ',')
        {
            base_salary1.push_back(str[i]);
            i++;
        }
        base_salary = stoi(base_salary1);
        i++;
        while (str[i] != ',')
        {
            salary_per_hour1.push_back(str[i]);
            i++;
        }
        salary_per_hour = stoi(salary_per_hour1);
        i++;
        while (str[i] != ',')
        {
            salary_per_extra_hour1.push_back(str[i]);
            i++;
        }
        salary_per_extra_hour = stoi(salary_per_extra_hour1);
        i++;
        while (str[i] != ',')
        {
            official_working_hours1.push_back(str[i]);
            i++;
        }
        official_working_hours = stoi(official_working_hours1);
        i++;
        while (str[i] != '\0')
        {
            tax_percentage1.push_back(str[i]);
            i++;
        }
        tax_percentage = stoi(tax_percentage1);
        Salary_configs s(level, base_salary, salary_per_hour, salary_per_extra_hour, official_working_hours, tax_percentage);
        all_salary_configs[counter] = s;
        counter++;
        level = "";
        base_salary1 = "";
        salary_per_hour1 = "";
        salary_per_extra_hour1 = "";
        official_working_hours1 = "";
        tax_percentage1 = "";
        i = 0;
    }
    infile.close();
    return all_salary_configs;
}
bool sorting(const activity &c1, const activity &c2)
{
    return c1.day < c2.day;
}
vector<Employee> specify_the_team_of_each_employee(vector<Employee> all_employees, vector<Team> all_teams)
{
    string str;
    int n;
    for (int i = 0; i < all_teams.size(); i++)
    {
        str = "";
        str = all_teams[i].member_ids;
        for (int j = 0; j < str.size(); j++)
        {
            if (str[j] != '$')
            {
                for (int z = 0; z < all_employees.size(); z++)
                {
                    if (all_employees[z].id == int(str[j]) - 48)
                    {
                        all_employees[z].team = all_teams[i];
                    }
                }
            }
        }
    }
    return all_employees;
}
vector<Employee> set_employees_activity(vector<Employee> all_employees)
{
    ifstream infile;
    string str, id1, day1, start_time1, end_time1;
    int id, i = 0, day, start_time, end_time;
    infile.open("working_hours.csv");
    getline(infile, str, '\n');
    while (!infile.eof())
    {
        str = "";
        i = 0;
        getline(infile, str, '\n');
        while (str[i] != ',')
        {
            id1.push_back(str[i]);
            i++;
        }
        i++;
        id = stoi(id1);
        for (int j = 0; j < all_employees.size(); j++)
        {
            if (all_employees[j].id == id)
            {
                while (str[i] != ',')
                {
                    day1.push_back(str[i]);
                    i++;
                }
                day = stoi(day1);
                i++;
                while (str[i] != '-')
                {
                    start_time1.push_back(str[i]);
                    i++;
                }
                start_time = stoi(start_time1);
                i++;
                while (str[i] != '\0')
                {
                    end_time1.push_back(str[i]);
                    i++;
                }
                end_time = stoi(end_time1);
                (all_employees[j].employee_activity).push_back(activity({day, start_time, end_time}));
                id1 = "";
                day1 = "";
                start_time1 = "";
                end_time1 = "";
                break;
            }
        }
    }
    infile.close();
    return all_employees;
}
vector<Employee> set_employees_salary(vector<Employee> all_employees, vector<Salary_configs> all_salary_configs)
{
    int i = 0, j = 0;
    for (i = 0; i < all_employees.size(); i++)
    {
        for (j = 0; j < all_salary_configs.size(); j++)
        {
            if (all_employees[i].level == all_salary_configs[j].level)
            {
                all_employees[i].salary = all_salary_configs[j];
            }
        }
    }
    return all_employees;
}
string separate_command(string user_type)
{
    int i = 0, flag = 0;
    string command = "";
    for (int j = 0; j < user_type.size(); j++)
    {
        if (user_type[j] == ' ')
            flag = 1;
    }
    if (flag == 1)
    {
        while ((user_type[i] != ' '))
        {
            command.push_back(user_type[i]);
            i++;
        }
    }
    else
        while ((user_type[i] != '\0'))
        {
            command.push_back(user_type[i]);
            i++;
        }
    return command;
}
void Company::calculation_salary()
{
    float total_wh = 0;
    for (int i = 0; i < all_employees.size(); i++)
    {
        total_wh = 0;
        for (int j = 0; j < all_employees[i].employee_activity.size(); j++)
        {
            if (all_employees[i].employee_activity[j].day != 0)
                total_wh = total_wh + ((all_employees[i].employee_activity[j].end_time) - (all_employees[i].employee_activity[j].start_time));
        }
        if (total_wh <= all_employees[i].salary.official_working_hours)
        {
            all_employees[i].net_salary = (total_wh * all_employees[i].salary.salary_per_hour) + all_employees[i].salary.base_salary;
        }
        else
        {
            all_employees[i].net_salary = all_employees[i].salary.base_salary + (all_employees[i].salary.official_working_hours * all_employees[i].salary.salary_per_hour) + (total_wh - all_employees[i].salary.official_working_hours) * all_employees[i].salary.salary_per_extra_hour;
        }
    }
}
void Company ::calculation_total_earning()
{
    for (int i = 0; i < all_employees.size(); i++)
    {
        all_employees[i].total_ear = 0;
        all_employees[i].total_ear = all_employees[i].net_salary + (all_employees[i].net_salary * all_employees[i].team.bonus) / 100;
        all_employees[i].total_ear = all_employees[i].total_ear - ((all_employees[i].total_ear * all_employees[i].salary.tax_percentage) / 100);
    }
}
void Company::report_salaries()
{
    for (int i = 0; i < all_employees.size(); i++)
    {
        float total_wh = 0;
        cout << "ID: " << all_employees[i].id;
        cout << "\nName: " << all_employees[i].name;
        for (int j = 0; j < all_employees[i].employee_activity.size(); j++)
        {
            if (all_employees[i].employee_activity[j].day != 0)
                total_wh = total_wh + ((all_employees[i].employee_activity[j].end_time) - (all_employees[i].employee_activity[j].start_time));
        }
        cout << "\nTotal Working Hours: " << total_wh;
        cout << "\nTotal Earning: " << fixed << setprecision(0) << round(all_employees[i].total_ear);
        cout << "\n---\n";
    }
}
void Company::report_employee_salary(int desired_id)
{
    int present_days = 0, count = 1, flag = 0, z, i, j;
    float total_wh = 0;
    vector<int> a;
    for (i = 0; i < all_employees.size(); i++)
    {
        if (all_employees[i].id == desired_id)
        {
            cout << "ID: " << all_employees[i].id;
            cout << "\nName: " << all_employees[i].name;
            cout << "\nAge: " << all_employees[i].age;
            cout << "\nlevel: " << all_employees[i].level;
            if (all_employees[i].team.team_id == 0)
                cout << "\nTeam ID: N/A";
            else
                cout << "\nTeam ID: " << all_employees[i].team.team_id;
            for (j = 0; j < all_employees[i].employee_activity.size(); j++)
            {
                if (all_employees[i].employee_activity[j].day != 0)
                    total_wh = total_wh + ((all_employees[i].employee_activity[j].end_time) - (all_employees[i].employee_activity[j].start_time));
            }
            sort(all_employees[i].employee_activity.begin(), all_employees[i].employee_activity.end(), sorting);
            for (int j = 0; j < all_employees[i].employee_activity.size(); j++)
            {
                if (all_employees[i].employee_activity[j].day != 0)
                {
                    
                        if (all_employees[i].employee_activity[j].day != all_employees[i].employee_activity[j + 1].day)
                            present_days++;
                    }
                }
            
            cout << "\nTotal Working Hours: " << total_wh;
            cout << "\nAbsent Days: " << 30 - present_days;
            cout << "\nSalary: " << fixed << setprecision(0) << round(all_employees[i].net_salary);
            cout << "\nBonus: " << fixed << setprecision(0) << round(all_employees[i].team.bonus * all_employees[i].net_salary / 100);
            cout << "\nTax: " << fixed << setprecision(0) << round(((all_employees[i].net_salary) + (all_employees[i].team.bonus * all_employees[i].net_salary / 100)) * all_employees[i].salary.tax_percentage / 100);
            cout << "\nTotal Earning: " << round(all_employees[i].total_ear) << "\n";
            flag = 1;
        }
    }
    if (flag == 0)
        cout << "EMPLOYEE_NOT_FOUND\n";
}
void Company ::report_team_salary(int desired_id)
{
    int count = 0, flag = 0;
    float team_total_wh = 0;
    for (int i = 0; i < all_teams.size(); i++)
    {
        if (all_teams[i].team_id == desired_id)
        {
            cout << "ID: " << all_teams[i].team_id;
            cout << "\nHead ID: " << all_teams[i].team_head_id;
            for (int j = 0; j < all_employees.size(); j++)
            {
                if (all_employees[j].id == all_teams[i].team_head_id)
                    cout << "\nHead Name: " << all_employees[j].name;
            }
            for (int z = 0; z < all_employees.size(); z++)
            {
                if (all_employees[z].team.team_id == desired_id)
                {
                    count++;
                    for (int t = 0; t < all_employees[z].employee_activity.size(); t++)
                    {
                        if (all_employees[z].employee_activity[t].day != 0)
                            team_total_wh = team_total_wh + all_employees[z].employee_activity[t].end_time - all_employees[z].employee_activity[t].start_time;
                    }
                }
            }
            cout << "\nTeam Total Working Hours: " << fixed << setprecision(0) << team_total_wh;
            cout << "\nAverage Member Working Hour: " << fixed << setprecision(1) << (team_total_wh / count);
            cout << "\nBonus: " << all_teams[i].bonus;
            cout << "\n---\n";
            for (int n = 0; n < all_employees.size(); n++)
            {
                if (all_employees[n].team.team_id == desired_id)
                {
                    cout << "Member ID: " << all_employees[n].id;
                    cout << "\nTotal Earning: " << fixed << setprecision(0) << round(all_employees[n].total_ear);
                    cout << "\n---\n";
                }
            }
            flag = 1;
        }
    }
    if (flag == 0)
        cout << "TEAM_NOT_FOUND\n";
}
int Company ::report_total_hours_per_day(int day1, int day2)
{
    int n = day2 - day1 + 1;
    int all_days[2][20] = {0};
    float total_working_hours_of_that_day = 0;
    if ((day1 > day2) || (day1 > 30) || (day1 < 1) || (day2 > 30) || (day2 < 1))
    {
        cout << "INVALID_ARGUMENTS\n";
        return 0;
    }
    for (int i = day1; i <= day2; i++)
    {
        total_working_hours_of_that_day = 0;
        for (int j = 0; j < all_employees.size(); j++)
        {
            for (int z = 0; z < all_employees[j].employee_activity.size(); z++)
            {
                if (all_employees[j].employee_activity[z].day == i)
                    total_working_hours_of_that_day = total_working_hours_of_that_day + all_employees[j].employee_activity[z].end_time - all_employees[j].employee_activity[z].start_time;
            }
        }
        all_days[1][i - day1] = total_working_hours_of_that_day;
        all_days[0][i - day1] = i;
        if (i == day2)
        {
            cout << "Day #" << i << ": " << fixed << setprecision(0) << total_working_hours_of_that_day << "\n---\n";
        }
        else
            cout << "Day #" << i << ": " << fixed << setprecision(0) << total_working_hours_of_that_day << "\n";
    }
    int max = all_days[1][0];
    for (int i = 0; i < n; i++)
    {
        if (all_days[1][i] > max)
            max = all_days[1][i];
    }
    int min = all_days[1][0];
    for (int i = 0; i < n; i++)
    {
        if (all_days[1][i] < min)
            min = all_days[1][i];
    }
    cout << "Day(s) with Max Working Hours:";
    for (int i = 0; i < n; i++)
    {
        if (all_days[1][i] == max)
            cout << " " << all_days[0][i];
    }
    cout << "\nDay(s) with Min Working Hours:";
    for (int i = 0; i < n; i++)
    {
        if (all_days[1][i] == min)
            cout << " " << all_days[0][i];
    }
    cout << "\n";
}
int Company::report_employee_per_hour(int start_hour, int end_hour)
{
    int n = end_hour - start_hour;
    int count = 0, j = 0;
    int all_houres[2][20];
    float a[20];
    if ((start_hour > end_hour) || (start_hour > 24) || (start_hour < 0) || (end_hour > 24) || (end_hour < 0))
    {
        cout << "INVALID_ARGUMENTS\n";
        return 0;
    }
    for (int i = start_hour; i < end_hour; i++)
    {
        all_houres[0][i - start_hour] = i;
        all_houres[1][i - start_hour] = i + 1;
    }
    for (int t = 0; t < n; t++)
    {
        count = 0;
        for (int i = 0; i < all_employees.size(); i++)
        {
            for (int j = 0; j < all_employees[i].employee_activity.size(); j++)
            {
                if ((all_employees[i].employee_activity[j].start_time <= all_houres[t][0]) && (all_employees[i].employee_activity[j].end_time >= all_houres[t][1]))
                    count++;
            }
        }
        cout << all_houres[t][0] << "-" << all_houres[t][1] << fixed << setprecision(1) << count / 30 << "\n";
        a[j] = count / 30;
        j++;
    }
    float max = a[0];
    for (int i = 0; i < n; i++)
    {
        if (a[i] > max)
            max = a[i];
    }
    float min = a[0];
    for (int i = 0; i < n; i++)
    {
        if (a[i] < min)
            min = a[i];
    }
    cout << "Periods(s) with Max Working Hours:";
    for (int i = 0; i < n; i++)
    {
        if (a[i] == max)
            cout << " " << all_houres[0][i] << "-" << all_houres[1][i];
    }
    cout << "\nPeriods(s) with Min Working Hours:";
    for (int i = 0; i < n; i++)
    {
        if (a[i] == min)
            cout << " " << all_houres[0][i] << "-" << all_houres[1][i];
    }
    cout << "\n";
}
void Salary_configs::print()
{
    cout << "Base Salary: " << base_salary;
    cout << "\nSalary Per Hour: " << salary_per_hour;
    cout << "\nSalary Per Extra Hour: " << salary_per_extra_hour;
    cout << "\nOfficial Working Hours:" << official_working_hours;
    cout << "\vTax: " << tax_percentage << "%"
         << "\n";
}
void Salary_configs::update_salary_parameters(string user_type)
{
    int i = 0;
    string s, new_base_salary, new_salary_per_hour, new_salary_per_extra_hour, new_official_working_hours, new_tax_percentage;
    while (user_type[i] != ' ')
    {
        i++;
    }
    i++;
    while (user_type[i] != ' ')
    {
        i++;
    }
    i++;
    while (user_type[i] != ' ')
    {
        new_base_salary.push_back(user_type[i]);
        i++;
    }
    i++;
    if (new_base_salary != "-")
        base_salary = stoi(new_base_salary);
    while (user_type[i] != ' ')
    {
        new_salary_per_hour.push_back(user_type[i]);
        i++;
    }
    i++;
    if (new_salary_per_hour != "-")
        salary_per_hour = stoi(new_salary_per_hour);
    while (user_type[i] != ' ')
    {
        new_salary_per_extra_hour.push_back(user_type[i]);
        i++;
    }
    i++;
    if (new_salary_per_extra_hour != "-")
        salary_per_extra_hour = stoi(new_salary_per_extra_hour);
    while (user_type[i] != ' ')
    {
        new_official_working_hours.push_back(user_type[i]);
        i++;
    }
    i++;
    if (new_official_working_hours != "-")
        official_working_hours = stoi(new_official_working_hours);
    while (user_type[i] != '\0')
    {
        new_tax_percentage.push_back(user_type[i]);
        i++;
    }
    if (new_tax_percentage != "-")
        tax_percentage = stoi(new_tax_percentage);
    cout << "OK\n";
}
int Employee::add_working_hours(string user_type)
{
    int i = 0, day, period_start, period_end, flag = 0;
    string s = "";
    while (user_type[i] != ' ')
    {
        i++;
    }
    i++;
    while (user_type[i] != ' ')
    {
        s.push_back(user_type[i]);
        i++;
    }
    i++;
    s = "";
    while (user_type[i] != ' ')
    {
        s.push_back(user_type[i]);
        i++;
    }
    day = stoi(s);
    i++;
    s = "";
    while (user_type[i] != ' ')
    {
        s.push_back(user_type[i]);
        i++;
    }
    period_start = stoi(s);
    i++;
    s = "";
    while (user_type[i] != '\0')
    {
        s.push_back(user_type[i]);
        i++;
    }
    period_end = stoi(s);
    if ((period_start > period_end) || (period_start > 24) || (period_start < 0) || (period_end > 24) || (period_end < 0))
    {
        cout << "INVALID_ARGUMENTS\n";
        return 0;
    }
    for (int i = 0; i < employee_activity.size(); i++)
    {
        if (employee_activity[i].day == day)
        {
            if (((employee_activity[i].start_time < period_start) && (employee_activity[i].end_time < period_start) && (employee_activity[i].start_time < period_end) && (employee_activity[i].end_time < period_end)) || ((employee_activity[i].start_time > period_start) && (employee_activity[i].end_time > period_start) && (employee_activity[i].start_time > period_end) && (employee_activity[i].end_time > period_end)))
            {
                continue;
            }
            else
            {
                flag = 1;
            }
        }
    }
    if (flag == 0)
    {
        (employee_activity).push_back(activity({day, period_start, period_end}));
        cout << "OK\n";
    }
    else
    {
        cout << "INVALID_INTERVAL\n";
    }
}
void Employee::delete_working_hours(string user_type)
{
    int i = 0, day, flag = 0, n = 0;
    string s = "";
    while (user_type[i] != ' ')
    {
        i++;
    }
    i++;
    while (user_type[i] != ' ')
    {
        s.push_back(user_type[i]);
        i++;
    }
    i++;
    s = "";
    while (user_type[i] != '\0')
    {
        s.push_back(user_type[i]);
        i++;
    }
    int b = 0;
    day = stoi(s);
    for (int j = 0; j < employee_activity.size(); j++)
    {
        if (employee_activity[j].day == day)
        {
            employee_activity[j].day = 0;
            flag = 1;
            /* remove(employee_activity, j-n);

             n++;
             j=j-2;*/
        }
    }
    if (flag == 0)
        cout << "INVALID_ARGUMENTS\n";
    else
        cout << "OK\n";
}
void Team::update_team_bonus(string user_type)
{
    int i = 0;
    string new_bonus_percentage = "";
    while (user_type[i] != ' ')
    {
        i++;
    }
    i++;
    while (user_type[i] != ' ')
    {
        i++;
    }
    i++;
    while (user_type[i] != '\0')
    {
        new_bonus_percentage.push_back(user_type[i]);
        i++;
    }
    if ((stoi(new_bonus_percentage) <= 100) && (stoi(new_bonus_percentage) >= 0))
    {
        bonus = stoi(new_bonus_percentage);
        cout << "OK\n";
    }
    else
        cout << "INVALID_ARGUMENTS\n";
}
