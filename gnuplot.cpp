#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "gnuplot-iostream.h"

using namespace std;

int main() {
	int selection;
	cout << "Enter plot (0, 1, 2, 3): ";
	cin >> selection;

	string garbage;

	Gnuplot gp;

	ifstream in_file("input.txt");

	vector< vector< int > > runtimes;
	int m, n;
	// grabbing runtimes
	if (in_file.is_open()) {
        // first line contains m and n as inputs
        in_file >> m >> n;

        int a,b,c;
        while (in_file >> a >> b >> c) {
        	vector<int> row;
        	row.push_back(a);
        	row.push_back(b);
        	row.push_back(c);

        	runtimes.push_back(row);
        }

        in_file.close();
    }
    else
        cout << "Error opening input file" << endl;

	ifstream out_file("output.txt");

	int A_make, B1_make = 1, B2_make, B3_make;
	int job, machine, start, start2;
	string titleA, titleB1, titleB2, titleB3;

	// the first line is Algorithm A
	getline(out_file, titleA);
	// the second line is makespan or -1
	out_file >> A_make;
	if (selection == 0)
		gp << "set title '" << titleA << ": " << A_make << "'\n";

	if (A_make != -1) {
		if (selection == 0) {
			gp << "set term wxt 0 size 1600,700\n";
			gp << "set xrange [0:" << A_make << "]\nset yrange [0:" << 2+m << "]\n";
	    	// the next n lines are the job start times on A machines if second line not -1
	    	for (int i = 0; i < n; i++) {
	    		out_file >> job >> machine >> start;
	    		// draw rectangle
	    		gp << "set object " << i+1 << " rect from " << start << "," << 1+m-machine << " to " << start+runtimes[job-1][0] << "," << 1+m-machine+0.5 << "\n";
	    		// draw job number
	    		gp << "set label '" << job << "' at " << start+runtimes[job-1][0]/(float)2 << "," << 1+m-machine+0.25 << " center\n";
	    	}

	    	// the next n lines are the job start times on machines B and C resepectively if second line not -1
	    	for (int i = 0; i < n; i++) {
	    		out_file >> job >> start >> start2;
	    		// draw rectangle for machine B
	    		gp << "set object " << n+i+1 << " rect from " << start << ",1 to " << start+runtimes[job-1][1] << ",1.5\n";
	    		// draw job number for job on machine B
	    		gp << "set label '" << job << "' at " << start+runtimes[job-1][1]/(float)2 << ",1.25 center\n";
	    		// draw rectangle for machine C
	    		gp << "set object " << 2*n+i+1 << " rect from " << start2 << ",0 to " << start2+runtimes[job-1][2] << ",0.5\n";
	    		// draw job number for job on machine C
	    		gp << "set label '" << job << "' at " << start2+runtimes[job-1][2]/(float)2 << ",0.25 center\n";
	    	}

	    	gp << "plot 0\nreplot 1\n";
			for (int i = 0; i < m; i++) {
				gp << "replot " << 2+i << "\n";
			}

			gp << "set terminal pdf size 1600,700\nset output 'AlgorithmA.pdf'\n";
			gp << "replot\n";
		}
		else {
			// skip 2n lines
			for (int i = 0; i < n*2; i++)
				getline(out_file, garbage);
		}
    }
    if (A_make == -1 && selection == 0)
    	cout << "Output does not exist for Algorithm A" << endl;
	// Algorithm A finished
	getline(out_file, garbage);

    // the first line is Algorithm B1
	getline(out_file, titleB1);
	// the second line is makespan or -1
	out_file >> B1_make;
	if (selection == 1)
		gp << "set title '" << titleB1 << ": " << B1_make << "'\n";

	if (B1_make != -1) {
		if (selection == 1) {
			gp << "set term wxt 1 size 1600,700\n";
			gp << "set xrange [0:" << B1_make << "]\nset yrange [0:3]\n";
	    	// the next n lines are the job start times on machine A if second line not -1
	    	for (int i = 0; i < n; i++) {
	    		out_file >> job >> start;
	    		// draw rectangle
	    		gp << "set object " << 3*n+i+1 << " rect from " << start << ",2 to " << start+runtimes[job-1][0] << ",2.5\n";
	    		// draw job number
	    		gp << "set label '" << job << "' at " << start+runtimes[job-1][0]/(float)2 << ",2.25 center\n";
	    	}

	    	// the next n lines are the job start times on machines B and C resepectively if second line not -1
	    	for (int i = 0; i < n; i++) {
	    		out_file >> job >> start >> start2;
	    		// draw rectangle for machine B
	    		gp << "set object " << 4*n+i+1 << " rect from " << start << ",1 to " << start+runtimes[job-1][1] << ",1.5\n";
	    		// draw job number for job on machine B
	    		gp << "set label '" << job << "' at " << start+runtimes[job-1][1]/(float)2 << ",1.25 center\n";
	    		// draw rectangle for machine C
	    		gp << "set object " << 5*n+i+1 << " rect from " << start2 << ",0 to " << start2+runtimes[job-1][2] << ",0.5\n";
	    		// draw job number for job on machine C
	    		gp << "set label '" << job << "' at " << start2+runtimes[job-1][2]/(float)2 << ",0.25 center\n";
	    	}

	    	gp << "plot 0\nreplot 1\nreplot 2\n";
	    	gp << "set terminal pdf\nset output 'AlgorithmB1.pdf'\n";
			gp << "replot\n";
		}
		else {
			// skip 2n lines
			for (int i = 0; i < n*2; i++)
				getline(out_file, garbage);
		}
	}
	if (B1_make == -1 && selection == 1) {
		cout << "Output does not exist for Algorithm B1" << endl;
	}

	// Algorithm B1 finished
	getline(out_file, garbage);

	// the first line is Algorithm B2
	getline(out_file, titleB2);
	// the second line is makespan or -1
	out_file >> B2_make;
	if (selection == 2)
		gp << "set title '" << titleB2 << ": " << B2_make << "'\n";

	if (B2_make != -1) {
		if (selection == 2) {
			gp << "set term wxt 2 size 1600,700\n";
			gp << "set xrange [0:" << B2_make << "]\nset yrange [0:3]\n";
	    	// the next n lines are the job start times on machine A if second line not -1
	    	for (int i = 0; i < n; i++) {
	    		out_file >> job >> start;
	    		// draw rectangle
	    		gp << "set object " << 6*n+i+1 << " rect from " << start << ",2 to " << start+runtimes[job-1][0] << ",2.5\n";
	    		// draw job number
	    		gp << "set label '" << job << "' at " << start+runtimes[job-1][0]/(float)2 << ",2.25 center\n";
	    	}

	    	// the next n lines are the job start times on machines B and C resepectively if second line not -1
	    	for (int i = 0; i < n; i++) {
	    		out_file >> job >> start >> start2;
	    		// draw rectangle for machine B
	    		gp << "set object " << 7*n+i+1 << " rect from " << start << ",1 to " << start+runtimes[job-1][1] << ",1.5\n";
	    		// draw job number for job on machine B
	    		gp << "set label '" << job << "' at " << start+runtimes[job-1][1]/(float)2 << ",1.25 center\n";
	    		// draw rectangle for machine C
	    		gp << "set object " << 8*n+i+1 << " rect from " << start2 << ",0 to " << start2+runtimes[job-1][2] << ",0.5\n";
	    		// draw job number for job on machine C
	    		gp << "set label '" << job << "' at " << start2+runtimes[job-1][2]/(float)2 << ",0.25 center\n";
	    	}

	    	gp << "plot 0\nreplot 1\nreplot 2\n";
	    	gp << "set terminal pdf\nset output 'AlgorithmB2.pdf'\n";
			gp << "replot\n";
		}
		else {
			// skip 2n lines
			for (int i = 0; i < n*2; i++)
				getline(out_file, garbage);
		}	
	}
	if (B2_make == -1 && selection == 2)
		cout << "Output does not exist for Algorithm B2" << endl;
	// Algorithm B2 finished
	getline(out_file, garbage);

	// the first line is Algorithm B3
	getline(out_file, titleB3);
	// the second line is makespan or -1
	out_file >> B3_make;
	if (selection == 3)
		gp << "set title '" << titleB3 << ": " << B3_make << "'\n";

	if (B3_make != -1) {
		if (selection == 3) {
			gp << "set term wxt 3 size 1600,700\n";
			gp << "set xrange [0:" << B3_make << "]\nset yrange [0:3]\n";
	    	// the next n lines are the job start times on machine A if second line not -1
	    	for (int i = 0; i < n; i++) {
	    		out_file >> job >> start;
	    		// draw rectangle
	    		gp << "set object " << 9*n+i+1 << " rect from " << start << ",2 to " << start+runtimes[job-1][0] << ",2.5\n";
	    		// draw job number
	    		gp << "set label '" << job << "' at " << start+runtimes[job-1][0]/(float)2 << ",2.25 center\n";
	    	}

	    	// the next n lines are the job start times on machines B and C resepectively if second line not -1
	    	for (int i = 0; i < n; i++) {
	    		out_file >> job >> start >> start2;
	    		// draw rectangle for machine B
	    		gp << "set object " << 10*n+i+1 << " rect from " << start << ",1 to " << start+runtimes[job-1][1] << ",1.5\n";
	    		// draw job number for job on machine B
	    		gp << "set label '" << job << "' at " << start+runtimes[job-1][1]/(float)2 << ",1.25 center\n";
	    		// draw rectangle for machine C
	    		gp << "set object " << 11*n+i+1 << " rect from " << start2 << ",0 to " << start2+runtimes[job-1][2] << ",0.5\n";
	    		// draw job number for job on machine C
	    		gp << "set label '" << job << "' at " << start2+runtimes[job-1][2]/(float)2 << ",0.25 center\n";
	    	}

	    	gp << "plot 0\nreplot 1\nreplot 2\n";
	    	gp << "set terminal pdf\nset output 'AlgorithmB3.pdf'\n";
			gp << "replot\n";
		}
		else {
			// skip 2n lines
			for (int i = 0; i <= n*2; i++)
				getline(out_file, garbage);
		}
	}
	if (B3_make == -1 && selection == 3)
		cout << "Output does not exist for Algorithm B3" << endl;
	// Algorithm B3 finished
	

	return 0;
}