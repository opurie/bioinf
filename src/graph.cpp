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
        reads.push_back(line);
    sort(reads.begin(), reads.end());
    //----------REMOVE REPETITION----------
    /*vector<string> delete_tab;
    for(int i = 0; i < reads.size()-1; i++){
        for (int j = i+1; j < reads.size(); j++){
            if(reads[i].compare(reads[j])==0){
                delete_tab.push_back(reads[i]);
            }
        }
    }
    for(int i = 0; i< delete_tab.size();i++){
        auto it = find(reads.begin(), reads.end(), delete_tab[i]);
        if(it!= reads.end()) reads.erase(it);
    }*/
    //---------------------------------------
    //----------RESIZE GRAPH-----------------
    graphSize = reads.size();
    G.resize(graphSize, vector<int, int>(graphSize));
}

int graph::overlap(string first, string second){
    for (int i = first.length(); i >= 1; i--)
        if(first.compare(first.length()-i, i, second, 0, i) == 0){
            return i;
        }
    return 0;
}
//zjebany kod do poprawienia
vector<int, int>  graph::overlapWithMistake(string first, string second){
    int len = second.length() - 1;
    bool mistake = false;
    vector<int, int> result = {0,0};
    for(int i = 0; i < first.length(); i++){
        if(i<2 && first[len - i] != second[i]){
            return result;
        }
        else if(i>=2){
            if(first[len-i]!=second[i] && !mistake){
                mistake = true;
                continue;
            }else if(first[len-i]!=second[i] && mistake)   
                return {i, 1};
        }
        if(i == len)
            return {i+1, 0};
    }
}
string graph::probe(string word,  int s, int r){
    string ret="";
    if(word.length() != s+r){
        return WRONG_PROBE;
    }
    for(int i = 0; i<word.length(); i++){
        if(i<s){
            ret += word[i];
        }else{
            for(int j = 0; j< s-1; j++){
                ret += 'U';
            }
            ret += word[i];
        }
    }
    return ret;
}