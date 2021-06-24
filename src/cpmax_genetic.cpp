#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <cstdlib>
#define WORKINGTIME 120
#define NBEST 3
using namespace std;

vector<vector<int> > bestGen;
int repeats[100];

void start(vector<int> jobs, int nProc) {

    int js = jobs.size();
	bestGen[0].resize(js);
	for (int j = 0; j < js; j++)//greedy no sort
		bestGen[0][j] = j % nProc;

    int maxi = 0, mini = 0; //longest processing time
	vector<int> proc(nProc);
	bestGen[1].resize(js);
	for (int i = 2; i < js; i++) {
		for (int j = 0; j < js; j++)
			if (jobs[j] > jobs[maxi]) maxi = j;

        for (int k = 0; k < proc.size(); k++)
            if (proc[k] < proc[mini]) mini = k;

		proc[mini] += jobs[maxi];
		bestGen[1][maxi] = mini;
		jobs[maxi] = -1;
	}

    bestGen[2].resize(js); //random population
    for (int j = 0; j < js; j++)
        bestGen[2][j] = (rand() % nProc);

}

int nRepeats() {
	int counter = 0;
	for (int i = 0; i < sizeof(repeats) / sizeof(int); i++)
		counter += repeats[i];
	return counter;
}
vector<int> makeChild(vector<int>& first, vector<int>& second) {
	vector<int> child;
	for (int i = 0; i < first.size(); i++) {
		if (rand() % 2) child.push_back(first[i]);
		else child.push_back(second[i]);
	}
	return child;
}

void crossOver(vector<vector<int>>& population) {
	population.clear();
	for (int i = 0; i < bestGen.size(); i++) {
		population.push_back(bestGen[i]);
		for (int j = 0; j < bestGen.size(); j++) {
			if (i != j)
                population.push_back(makeChild(bestGen[i], bestGen[j]));
		}
	}
}

void mutate(int nJobs, vector<vector<int> >& population, int nProc) {
	int mutprob = nRepeats();
	for (int i = 3; i < population.size(); i++) {
        for (int j = 0; j < (nJobs * (mutprob / 50)) / 100; j++)
            swap(population[i][rand() % nJobs], population[i][rand() % nJobs]);
	}
}
int countLongest(vector<int>& instance, vector<int>& jobs) {

	int maxi = 0, *tmp = new int[instance.size()]();
	for (int i = 0; i < instance.size(); i++) {
		tmp[instance[i]] += jobs[i];
		if (tmp[instance[i]] > maxi) maxi = tmp[instance[i]];
	}
	delete[]tmp;
	return maxi;
}
void sortp(vector<int>& sortedTimes, vector<vector<int> >& population) { //sort population
    int is = population.size();
	for (int i = 0; i < is; i++)
		for (int j = i; j < is; j++)
			if (sortedTimes[j] < sortedTimes[i]) {
				swap(sortedTimes[i], sortedTimes[j]);
				swap(population[i], population[j]);
			}
}

int selection(vector<vector<int> >& population, vector<int>& jobs, int nProc) {
	vector<int> populationTimes;
	int is = population.size();
	populationTimes.resize(is);
	mutate(jobs.size(), population, nProc);
	for (int i = 0; i < is; i++)
		populationTimes[i] = countLongest(population[i], jobs);

	sortp(populationTimes, population);
	bestGen.clear();
	for (int i = 0; i < NBEST; i++)
        bestGen.push_back(population[i]);

	return populationTimes[0];
}

int geneticAlgorithm(vector<vector<int>>& population, vector<int>& jobs, int nProc) {
	int tmp, nGens = 0, minimum = 10000000;
	clock_t begintime = clock();
	int time = 0;

	while (time < WORKINGTIME) {
		crossOver(population);
		tmp = selection(population, jobs, nProc);
		if (tmp == minimum)
            repeats[nGens % 100] = 1;
		else
            repeats[nGens % 100] = 0;

		if (tmp < minimum)
            minimum = tmp;
        nGens++;

		time = ((clock() - begintime) / CLOCKS_PER_SEC);

	}
	return minimum;
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	int nJobs, nProc, best, bestSolution=0;
	ifstream file;
	vector<int> jobs;
	vector<vector<int>> population;

	for (int i=0; i <= 1; i++) {
		bestGen.resize(NBEST);
		file.open(argv[1]);
		file >> nProc >> nJobs;
		jobs.resize(nJobs);
		for (int i = 0; i < nJobs; i++) file >> jobs[i];
		file.close();

		population.resize(NBEST * NBEST);
		start(jobs, nProc);
		best = geneticAlgorithm(population, jobs, nProc);
        if(i == 0)
            bestSolution = best;
        else
            if(best < bestSolution)
                bestSolution = best;

		population.clear();
		jobs.clear();
		bestGen.clear();
	}
	cout<<bestSolution<<endl;

	return 0;
}





