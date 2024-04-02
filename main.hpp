#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int rewritesplitwords(string, char);
string MFN(string stname, int thisyear);


int rewritesplitwords(string filename, char delimiter) {
    ifstream file(filename);
    ofstream outfile("split.txt");
    string state, name;
    char gen;
    int year, cnt;
    int lineCount = 0;

    while (file >> state >> gen >> year >> name >> cnt) {
        outfile << state << "\t" << gen << "\t" << year << "\t" << name << "\t" << cnt << endl;
        lineCount++;
    }

    file.close();
    outfile.close();

    return lineCount;
}

string MFN(string stname, int thisyear) {
    ifstream infile("split.txt");
    string state, name, MFName;
    char gen;
    int year, cnt;
    int maxCount = 0;

    while (infile >> state >> gen >> year >> name >> cnt) {
        if (state == stname && year == thisyear && cnt > maxCount) {
            maxCount = cnt;
            MFName = name;
        }
    }

    infile.close();
    return MFName;
}