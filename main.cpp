#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>

using namespace std;

double getCpuUsage() {
    long prevIdleTime = 0, prevTotalTime = 0;
    long user, nice, sys, idle, iowait, irq, softirq, steal;
    string cpu;

    ifstream fp("/proc/stat");
    string line;
    getline(fp, line);
    fp.close();

    istringstream iss(line);
    iss >> cpu >> user >> nice >> sys >> idle >> iowait >> irq >> softirq >> steal;

    long idleTime = idle + iowait;
    long totalTime = user + nice + sys + idle + irq + softirq + steal;

    double usage = 100.0 * (1.0 - (double)(idleTime - prevIdleTime) / (totalTime - prevTotalTime));

    prevIdleTime = idleTime;
    prevTotalTime = totalTime;

    return usage;
}

double getMemoryUsage() {
    static long prevIdleTime = 0, prevTotalTime = 0;
    long value, unit, totalMem, availableMem, freeMem;
    string key;

    ifstream fp("/proc/meminfo");
    string line;
    getline(fp, line);
    fp.close();

    istringstream iss(line);
    iss >> key >> value >> unit;

    if (key == "MemTotal:") {
        totalMem = value;
    } else if (key == "MemAvailable:") {
        availableMem = value;
    } else if (key == "MemFree:") {
        freeMem = value;
    }

    fp.close();

    long usedMem = totalMem - availableMem - freeMem;
    double usagePercent = (double)usedMem / totalMem * 100.0;

    cout << "Total Memory: " << totalMem / 1024 << " MB" << endl;
    cout << "Used Memory: " << usedMem / 1024 << " MB" << endl;
    cout << "Memory Usage: " << usagePercent << "%" << endl;

    return 1;
}


int main() {
    while (true) {
        cout << "Your CPU usage: " << getCpuUsage() << '%' << endl;
        getMemoryUsage();
        this_thread::sleep_for(chrono::seconds(1));
        system("clear");
    }
    return 0;
}
