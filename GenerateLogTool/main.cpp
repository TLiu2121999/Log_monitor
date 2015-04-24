#include <iostream>
#include "myTime.h"
#include <fstream>

using namespace std;

void generateLog(string path){
    ofstream log;
    log.open( path + "log.txt");
    my_time mt = my_time(2014, 10, 31);
    // writing simulate log into file
    for (int server = 0; server < 1000; server++) {
        for (int cpu = 0; cpu < 2; cpu++){
            mt.toLogUnixTime();// transfer human read time to Unix Time
            string ip = "192.168." + to_string(server/255+1) +"." + to_string(server%255);// generate ip
            for (int i = 0; i < 24; i++) {
                for (int j = 0; j < 60; j++) {
                    string log_item = mt.getUnixTimeStr() + " "
                                      + ip + " " + to_string(cpu)
                                      + " " + to_string(rand() % 101); // generate log item for certain ip and cpu at certain time
                    log << log_item;
                    log << "\n";
                    mt.addMin(); // add time
                }
            }
        }
    }
    log.close(); // finish generate simulate log file
}

int main(int argc,char *argv[]) {
    if(argc < 2) {
        cout << "You must provide at least one argument" << endl;
        return 0;
    }
    string pathToSave = argv[1];
    generateLog(pathToSave);
    cout << "The log file's directory is: " + pathToSave + "log.txt" +"\n";
}