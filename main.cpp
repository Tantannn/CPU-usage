#include <iostream>
using namespace std;
#include <fstream>
// #include <string>

int main() {
    int c;
    ifstream fp("/proc/stat");

    string line;
    getline(fp, line);
    if (!fp.is_open()) {
        cerr << "Cannot open file" << endl;
        return 1;
    }
    while (fp >> c)
        cout << c << endl;
    return 0;
}
