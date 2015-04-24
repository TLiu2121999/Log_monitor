#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "Query.h"

using namespace std;

// function to load log file data to a hashmap whose structure is map<time, map<ip, map<cpuid, usage>>>
void loadData(string path, map<string, map<string, map<string,string>>> &data){
    ifstream file(path);
    string line;
    // read log file line by line
    while (getline(file, line)) {
        istringstream iss(line);
        vector<string> tokens{ istream_iterator<string>{iss}, istream_iterator<string>{} };// split one line log with space
        string timeStamp = tokens[0];
        string ip = tokens[1];
        string cpu = tokens[2];
        string usage = tokens[3];
        data[timeStamp][ip][cpu] = usage;
    }
}



int main(int argc, char *argv[]){
    if(argc < 2) {
        cout << "You must provide at least one argument" << endl;
        return 0;
    }
    string pathToRead = argv[1];
    cout << "Start to initialize, please wait." << endl;
    map<string, map<string, map<string,string>>> data;// use to store log data
    loadData(pathToRead, data);
    cout << "Initialize finished!" << endl;
    cout << "Please enter query in this way: QUERY 192.168.1.10 1 2014-10-31 00:00 2014-10-31 00:05\n"<< endl;
    // process user query request
    do {
        string input;
        getline(cin, input);
        if(input =="EXIT"){
            cout << "Exit the program" << endl;
            return 0;
        } else if(input.find("QUERY") == string::npos) {
            cout << "Please enter the correct input."<< endl;
        } else {
            Query q = Query(input);

            string res = q.query(data);
            cout << res << endl;
        }
    }while(true);
}