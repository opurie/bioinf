#include "../include/graph.hpp"

void graph::getNandErrors(string name){
    bool first_dot = false, first_type = false;
    string s_count = "", error = "";
    for(char letter: name){
        if(letter == '.')
            first_dot = true;
        if(letter == '+'){
            first_type = true;
            chargeType = true;
        }
        else if(letter == '-')
            first_type = true;
          
        if(first_dot && !first_type){
            s_count += letter;
        }
        else if(first_dot && first_type){
            errors += letter;
        }
    }
    n = atoi(s_count.c_str()) + 9;
    errors = atoi(error.c_str());
}
void graph::loadFile(string fileName){
    getNandErrors(fileName);
    fstream input(fileName, fstream::in);
    string line;
    while(getline(input, line))
        loadedData.push_back(line);
}

bool graph::matchWords(string first, string second, int k){
    if(first.compare(first.size()-k, k, second, 0, k) == 0){
        return true;
    }
    return false;
}