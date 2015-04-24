
#ifndef GENERATOR_MYTIME_H
#define GENERATOR_MYTIME_H

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>

#include <ctime>
#include <time.h>

using namespace std;
// my_time class is a class to help transfer human read time to unix timestamp
class my_time{
public:
    my_time(int y, int m, int d) {
        year = y;
        mon = m;
        day = d;
        hour = 0;
        min = 0;
    }
    // function to transfer human read time to unix timestamp
    void toLogUnixTime(){
        struct tm t = {0};
        t.tm_year = year-1900;
        t.tm_mon = mon-1;
        t.tm_mday = day;
        t.tm_hour = hour-8;
        t.tm_min = min;
        unix_time_str = to_string(mktime(&t));
        unix_time = atoi(unix_time_str.c_str());
    }
    // help function to add time for log genarator
    string addMin(){
        unix_time += 60;
        unix_time_str = to_string(unix_time);
        return unix_time_str;
    }
    string getUnixTimeStr(){
        return unix_time_str;
    }
private:
    int year;
    int mon;
    int day;
    int hour;
    int min;
    int unix_time;
    string unix_time_str;
};




#endif //GENERATOR_MYTIME_H
