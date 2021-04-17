#ifndef GRAPH_HPP
#define GRAPH_HPP

#define L 10
#include <fstream>
#include <vector>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

class graph{
    private:
        unsigned int n;
        unsigned int errors;
        bool chargeType = false;

        unsigned short k_mer = 5;
        vector<string> loadedData;
        vector<vector<int>> G;
    public:
        graph();
        ~graph();
        void loadFile(string fileName);
        void getNandErrors(string name);
        bool matchWords(string first, string second, int k);
        void makeGraph();
        unsigned int getN();
        bool getType();


};

#endif