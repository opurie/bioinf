#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <fstream>
#include <vector>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <iostream>

#define L 10
#define WRONG_PROBE "false"
using namespace std;


class graph{
    private:
        unsigned int n;
        unsigned int errors;
        bool chargeType = false;
        char weak[2]={'A', 'T'};
        char strong[2]={'C', 'G'};
        unsigned short graphSize;
        vector< string > reads;
        vector< vector<int, int> > G;
    public:
        graph();
        ~graph();
        void loadFile(string fileName);
        void getNandErrors(string name);
        int overlap(string first, string second);
        vector<int, int> overlapWithMistake(string first, string second);
        string probe(string word,int s, int r);
        void makeGraph();
        unsigned int getN();
        bool getType();


};

#endif