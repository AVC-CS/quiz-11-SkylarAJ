#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Name {
    string stname;
    string gender;
    string name;
    int count;
};

int rewritesplitwords(string filename, char delimiter) {
    ifstream inputFile(filename);
    ofstream outputFile("split.txt");

    if (!inputFile.is_open()) {
        cout << "Error: Unable to open file " << filename << endl;
        return -1;
    }

    string line;
    int cnt = 0;
    while (getline(inputFile, line)) {
        ++cnt;
        stringstream ss(line);
        string token;

        // Create a struct Name based on split words
        struct Name nameData;
        getline(ss, nameData.stname, delimiter);
        getline(ss, nameData.gender, delimiter);
        ss >> nameData.count;
        ss.ignore(); // Skip comma
        getline(ss, nameData.name, delimiter);

        // Write the struct with spaces (tabs) into the new file
        outputFile << nameData.stname << "\t" << nameData.gender << "\t"
                   << nameData.count << "\t" << nameData.name << endl;
    }

    inputFile.close();
    outputFile.close();

    return cnt;
}

string MFN(string state, int thisyear) {
    ifstream inputFile("split.txt");
    if (!inputFile.is_open()) {
        cout << "Error: Unable to open file split.txt" << endl;
        return "";
    }

    map<string, int> nameCount; // Map to store name and its count
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string stname, gender, name;
        int count;
        ss >> stname >> gender >> count >> name;

        // Check if it matches the given state and year
        if (stname == state && count == thisyear) {
            // Increment count for the name
            nameCount[name]++;
        }
    }

    inputFile.close();

    // Find the most frequently used name
    string mostFrequentName;
    int maxCount = 0;
    for (const auto& pair : nameCount) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequentName = pair.first;
        }
    }

    return mostFrequentName;
}