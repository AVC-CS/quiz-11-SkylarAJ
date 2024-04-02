#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;
int rewritesplitwords(string, char);
string MFN(string stname, int thisyear);

struct Name {
    string stname;
    string gender;
    string name;
    int count;
};

int rewritesplitwords(string filename, char delimiter) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return 0;
    }

    ofstream outFile("split.txt");
    if (!outFile.is_open()) {
        cerr << "Error: Unable to create/open split.txt file" << endl;
        return 0;
    }

    string line;
    int cnt = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        if (tokens.size() == 4) {
            Name name;
            name.stname = tokens[0];
            name.gender = tokens[1];
            name.name = tokens[2];
            name.count = stoi(tokens[3]);
            outFile << name.stname << '\t' << name.gender << '\t' << name.name << '\t' << name.count << endl;
            cnt++;
        }
    }

    file.close();
    outFile.close();
    return cnt;
}

string MFN(string stname, int thisyear) {
    ifstream file("split.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open split.txt file" << endl;
        return "";
    }

    map<string, int> nameCount;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string state, gender, name;
        int count;
        ss >> state >> gender >> name >> count;
        if (state == stname) {
            nameCount[name] += count;
        }
    }

    file.close();

    string mostFrequentName;
    int maxCount = 0;
    for (const auto& entry : nameCount) {
        if (entry.second > maxCount) {
            mostFrequentName = entry.first;
            maxCount = entry.second;
        }
    }

    return mostFrequentName;
}