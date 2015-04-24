#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <string>
#include <stdlib.h>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;
// a class to help user process log query
class Query {
public:
    Query(string q){
        analyzeQuery(q);
    }
    // analyze query and store it to private data
    void analyzeQuery(string query){
        istringstream iss(query);
        vector<string> tokens{istream_iterator<string>{iss},
                              istream_iterator<string>{}};// split query with space
        ip = tokens[1];
        cpu = tokens[2];
        startTime = tokens[3]+" "+tokens[4];
        startTimeUT =toUnixTimestamp(startTime);
        endTime = tokens[tokens.size()-2] + " "+tokens[tokens.size()-1];
        endTimeUT = toUnixTimestamp(endTime);
    }

    // processing query and return result
    string query(map<string, map<string, map<string,string>>> &data) {
        string res = "CPU" + cpu + " " + "usage on" + " " + ip + ":\n";
        string query_item;
        int queryNum = (atoi(endTimeUT.c_str()) - atoi(startTimeUT.c_str())) / 60;
        int queryTime = atoi(startTimeUT.c_str());
        for (int i = 0; i <= queryNum; i++) {

            string queryTimestr = to_string(queryTime);
            query_item = data[queryTimestr][ip][cpu];
            res += "(" + fromUnixTimestamp(queryTimestr)+", "+query_item+"%"+"),";
            queryTime += 60;
        }
        return res;
    }
    // time help function, help to transfer human read time to tm struct
    void splitTimeStr(tm &tm, string t){
        tm.tm_year = atoi(t.substr(0, 4).c_str()) - 1900;
        tm.tm_mon = atoi(t.substr(5, 2).c_str()) - 1;
        tm.tm_mday = atoi(t.substr(8, 2).c_str());
        tm.tm_hour = atoi(t.substr(11, 2).c_str())-8;
        tm.tm_min = atoi(t.substr(14, 2).c_str());
    }
    // helping transfer human read date to unix timestamp
    string toUnixTimestamp(string t){

        struct tm tm = { 0 };
        splitTimeStr(tm, t);
        time_t temp = mktime(&tm);
        string res = to_string(temp);
        return res;
    }
    // helping transfer unix timestamp to human read date
    string fromUnixTimestamp(string ut){
        int temp = atoi(ut.c_str());
        time_t t = temp;
        struct tm *tm = std::gmtime(&t);
        char date[20];
        strftime(date, sizeof(date), "%Y-%m-%d %H:%M", tm);
        string res(date);
        return res;
    }

private:
    string ip;
    string cpu;
    string startTime;
    string startTimeUT;
    string endTime;
    string endTimeUT;
};