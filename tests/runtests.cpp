#include "openshop.h"
#include "create.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

float standard_deviation(vector<float>& data, float avg) {
	float s_d = 0;
	for (int i = 0; i < data.size(); i++)
		s_d += pow(data[i] - avg, 2);
	return sqrt(s_d/data.size());
}

int main () {
	srand(time(NULL));

	int jobs, machines = 20, range, num_runs = 100;
	cin >> jobs, range;

	float avg_times[machines][2];
	for (int m = 0; m < machines; m++) {
		float ratio = 0;
		vector<float> values;
		for (int run = 0; run < num_runs; run++) {
			create(jobs*10, m+1, pow(2, range));
			Input a;
			float value = a.run();
			values.push_back(value);
			ratio += value;
		}
		ratio /= num_runs;
		// average ratio of C_max to LB
		avg_times[m][0] = ratio;
		// standard deviation
		avg_times[m][1] = standard_deviation(values, ratio);
	}

	ofstream outfile("job, range" + to_string(jobs) + " " + to_string(range));

	for (int i = 0; i < machines; i++)
		outfile << i << "  " << avg_times[i][0] << " " << avg_times[i][1] << endl;

	return 0;
}