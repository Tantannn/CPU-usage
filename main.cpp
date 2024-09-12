#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
using namespace std;

double getCpuUsage() {
    long prevIdleTime = 0, prevTotalTime = 0;
    long user, nice, sys, idle, iowait, irq, softirq, cpu, steal;

    ifstream fp("/proc/stat");
    string line;
    getline(fp, line);
    // fp.close();

    istringstream iss(line);
    iss >> cpu >> user >> nice >> sys >> idle >> iowait >> irq >> softirq >> steal;

    long idleTime = idle + iowait;
    long total = user + nice + sys + idle + irq + softirq;

    double usage = 100.0 * (1.0 - (double)(idleTime - prevIdleTime) / (total - prevTotalTime));

    prevIdleTime = idle;
    prevTotalTime = total;

        cout << prevIdleTime << endl;
        cout << idle << endl;
        cout << iowait << endl;
    return usage;
}

int main() {
    // if (!fp.is_open()) {
    //     cerr << "Cannot open file" << endl;
    //     return 1;
    // }
    //
    while (true) {
        cout << getCpuUsage() << endl;
        cout << "hello" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        // system("clear");
    }
    return 0;
}
