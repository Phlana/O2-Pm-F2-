#include <utility>
#include <iostream>
// (file)stream for input and output from and to files
#include <fstream>
// for min
#include <algorithm>
#include <vector>



using namespace std;

/*
(only integer values)

input format:

m, n
a_1, b_1, c_1
a_2, b_2, c_2
...
a_i, b_i, c_i
...
a_n, b_n, c_n

where m is number of machines, n is number of jobs
where a_i, b_i, c_i are processing times of job i on machines A, B, and C respectively

output format:

(m, S_a1), S_b1, S_c1
(m, S_a2), S_b2, S_c2
...
(m, S_ai), S_bi, S_ci
...
(m, S_an), S_bn, S_cn
A, B, C
M

where S_ai, S_bi, S_ci are the starting times on machines A, B, and C respectively in the form
where m is the parallel machine number the specific job was processed on
where A, B, and C are the times machines A, B, and C finish respectively
where M is the makespan
*/

struct Input {
    int n, m;
    vector< vector<int> > array;
    Input();
    // void output(void);

    void decend_qsort(vector< vector< int > >&, int, int, int);
    void ascend_qsort(vector< vector< int > >&, int, int, int);
    void i_sort(vector< vector< int > >&);
    int LPT(vector< vector< int > >&, vector< vector< int > >&, int);
    int johnsons(vector< vector< int > >&, vector< vector< int > >&, int);

    int lower_bound(void);
    int Algorithm_A(void);
    int Algorithm_B1(void);
    int Algorithm_B2(void);
    // int Algorithm_B3(void);
};

void print_vec(vector< vector< int > >& prn) {
	for (int i = 0; i < prn.size(); i++) {
		cout << i << "  ";
		for (int j = 0; j < prn[0].size(); j++)
			cout << prn[i][j] << " ";
		cout << endl;
	}
}

// default constructor for Input class
Input::Input() {
	// cout << "input" << endl;
    // reading the input file
    ifstream in_file("input.txt");

    if (in_file.is_open()) {
        // first line contains m and n as inputs
        in_file >> m >> n;

        int line_count = 0;
        int a,b,c;
        while (in_file >> a >> b >> c) {
        	vector<int> row;
        	row.push_back(line_count+1);
        	row.push_back(a);
        	row.push_back(b);
        	row.push_back(c);

        	array.push_back(row);

	        // cout << m << " " << n << endl;
            // cout << line_count << "  " << a << " " << b << " " << c << endl;

            line_count++;
        }

        in_file.close();

    }
    else
        cout << "Error opening input file" << endl;
}

// // prints output to output file
// void Input::output() {
//     // init output file
//     ofstream out_file("output.txt");
//     if (out_file.is_open()) {
//         // print output to file
//         out_file << input_array << endl;
//     }
//     else
//         cout << "Error opening output file" << endl;

//     // closing output files
//     out_file.close();
// }

// decending quicksort with column input
void Input::decend_qsort(vector< vector< int > >& arr, int s, int e, int c) {
	// cout << "decend" << endl;
    int start = s, end = e;
    vector<int> tmp;
    // pivot
    int p = arr[s+(e-s)/2][c];

    while (start <= end) {
        while (arr[start][c] > p)
            start++;

        while (arr[end][c] < p)
            end--;

        if (start <= end) {
        	// swap
            tmp = arr[start];
            arr[start] = arr[end];
            arr[end] = tmp;
            
            start++;
            end--;
        }
    }

    if (s < end)
        decend_qsort(arr, s, end, c);
    if (start < e)
        decend_qsort(arr, start, e, c);
}

// ascending quicksort with column input
void Input::ascend_qsort(vector< vector< int > >& arr, int s, int e, int c) {
	// cout << "ascend" << endl;
    int start = s, end = e;
    vector<int> tmp;
    // pivot
    int p = arr[s+(e-s)/2][c];

    while (start <= end) {
        while (arr[start][c] < p)
            start++;

        while (arr[end][c] > p)
            end--;

        if (start <= end) {
        	// swap
            tmp = arr[start];
            arr[start] = arr[end];
            arr[end] = tmp;
            
            start++;
            end--;
        }
    }

    if (s < end)
        ascend_qsort(arr, s, end, c);
    if (start < e)
        ascend_qsort(arr, start, e, c);
}

// insertion sort for LPT
void Input::i_sort(vector< vector< int > >& mac) {
	// cout << "isort" << endl;
	int key;
	vector<int> temp;

	temp = mac[m-1];

	int j = m-2;

	while (j >= 0 && (mac[j][1] <= temp[1])) {
		// shift
    	mac[j+1] = mac[j];
        j--;
    }
    mac[j+1] = temp;
}

// LPT with number of machines as input
int Input::LPT(vector< vector< int > >& lpt_arr, vector< vector< int > >& start_lpt, int s) { // start_lpt should be empty
	// cout << "LPT func" << endl;
	// sort by column 1
	// decend_qsort(lpt_arr, 0, n-1, 1);
	decend_qsort(lpt_arr, 0, lpt_arr.size()-1, 1);

	// start m machines
	vector< vector<int> > machine;
	for (int i = m; i > 0; i--) {
		vector<int> row;

		row.push_back(i-1);
		row.push_back(s);

		machine.push_back(row);
	}

	// vector< vector< int > > start_lpt; ///////////////////
	for (int i = 0; i < n; i++) {
		vector<int> row;
		row.push_back(-1);
		row.push_back(-1);

		start_lpt.push_back(row);
	}

	int count = 0;

	int index;
	while (count < lpt_arr.size()) {
		// save start time
		start_lpt[ lpt_arr[count][0]-1 ][1] = machine[m-1][1];
		// and machine number
		start_lpt[ lpt_arr[count][0]-1 ][0] = machine[m-1][0];

		// adding time to last element on machine
		machine[m-1][1] += lpt_arr[count][1];

		// resort
		i_sort(machine);

		count++;
	}

    int LPT_makespan = machine[0][1];

    // cout << "LPT machines " << LPT_makespan << endl;
    // for (int i = 0; i < n; i++)
    // 	cout << i << ": " << i+1 << " " << start_lpt[i][0] << "  " << start_lpt[i][1] << endl;
    // //          iteration    job number    machine                    start time

    return LPT_makespan;
}

// johnsons algorithm
int Input::johnsons(vector< vector< int > >& johnson_arr, vector< vector< int > >& start_johnson, int s) {
	// cout << "johnsons func" << endl;
    // splitting johnson_arr
    int tmp;
    int start = 0, end = johnson_arr.size()-1;
    while (start < end) {
        while (johnson_arr[start][2] < johnson_arr[start][3])
            start++;
        while (johnson_arr[end][2] > johnson_arr[end][3])
            end--;
        if (johnson_arr[start][2] > johnson_arr[start][3] && johnson_arr[end][2] < johnson_arr[end][3]) { // johnson_arr[start] and johnson_arr[end] swap
            for (int i = 0; i < 4; i++) {
                tmp = johnson_arr[start][i];
                johnson_arr[start][i] = johnson_arr[end][i];
                johnson_arr[end][i] = tmp;
            }
            start++;
            end--;
        }
    }
    // grabbing index
    int index;
    for (int i = 0; i < johnson_arr.size(); i++) {
        if (johnson_arr[i][2] > johnson_arr[i][3]) {
            index = i;
            break;
        }
    }
    // sorting two parts of johnson_arr
    ascend_qsort(johnson_arr, 0, index-1, 2);
    decend_qsort(johnson_arr, index, johnson_arr.size()-1, 3);

    // start 2 machines as flowshop
    int flowshop[2] = {s, johnson_arr[0][2]+s};

	// vector< vector< int > > start_johnson; ////////////////////
	for (int i = 0; i < n; i++) {
		vector<int> row;
		row.push_back(-1);
		row.push_back(-1);
		row.push_back(-1);

		start_johnson.push_back(row);
	}

    // for each job save job number and start time b and c
    for (int i = 0; i < johnson_arr.size(); i++) { 
    	start_johnson[i][0] = johnson_arr[i][0];
    	start_johnson[i][1] = flowshop[0];
    	flowshop[0] += johnson_arr[i][2];

    	if (flowshop[0] > flowshop[1])
    		flowshop[1] = flowshop[0];

    	start_johnson[i][2] = flowshop[1];
	    flowshop[1] += johnson_arr[i][3];
    }

    int johnsons_makespan = flowshop[1];

    // cout << "johnsons machines " << johnsons_makespan << endl;
    // for (int i = 0; i< n; i++)
    // 	cout << i << ": " << start_johnson[i][0] << "  " << start_johnson[i][1] << "  " << start_johnson[i][2] << endl;
    // //          iteration    job number                     B start time                   C start time

    return johnsons_makespan;
}

int Input::Algorithm_A() {
	// first the job list is sorted decending column 1
	decend_qsort(array, 0, n-1, 1);
	// split job schedule 
	vector< vector< int > > J_1; // subset 1
	vector< vector< int > > J_2; // subset 2
	for (int i = 0; i < m; i++) {
		// put job i in subset 1
		J_1.push_back(array[i]);
	}
	for (int i = m; i < n; i++) {
		// put job i in subset 1
		J_2.push_back(array[i]);
	}

    vector< vector< int > > LPT_schedule_1;
    vector< vector< int > > LPT_schedule_2;
    vector< vector< int > > johnson_schedule_1;
    vector< vector< int > > johnson_schedule_2;

	// get LPT schedule
	int LPT_makespan_1 = LPT(J_1, LPT_schedule_1, 0);
	int johnsons_makespan_1 = johnsons(J_2, johnson_schedule_1, 0);
	int T_1 = max(LPT_makespan_1, johnsons_makespan_1);

	int LPT_makespan_2 =LPT(J_2, LPT_schedule_2, T_1);
	int johnsons_makespan_2 = johnsons(J_1, johnson_schedule_2, T_1);
	int T_2 = max(LPT_makespan_2, johnsons_makespan_2);

	// output to file
    ofstream out_file;
    out_file.open("output.txt", ofstream::trunc);

    if (out_file.is_open()) {
        out_file << "Algorithm A: " << T_2 << endl;
        out_file << "A" << endl;
        for (int i = 0; i < LPT_schedule_1.size(); i++)
        	if (LPT_schedule_1[i][0] >= 0)
	        	out_file << i+1 << " " << LPT_schedule_1[i][0] << " " << LPT_schedule_1[i][1] << endl;
        for (int i = 0; i < LPT_schedule_2.size(); i++)
        	if (LPT_schedule_2[i][0] >= 0)
        		out_file << i+1 << " " << LPT_schedule_2[i][0] << " " << LPT_schedule_2[i][1] << endl;
        out_file << "B and C" << endl;
        for (int i = 0; i < J_2.size(); i++)
        	out_file << johnson_schedule_1[i][0] << " " << johnson_schedule_1[i][1] << " " << johnson_schedule_1[i][2] << endl;
    	for (int i = 0; i < J_1.size(); i++)
        	out_file << johnson_schedule_2[i][0] << " " << johnson_schedule_2[i][1] << " " << johnson_schedule_2[i][2] << endl;
    }
    else
        cout << "Error opening output file" << endl;

	// closing output files
    out_file.close();

	return T_2;
}

// Finds lower bound LB
int Input::lower_bound() {
	// sum of processing times on the three machines
	int A = 0, B = 0, C = 0;
	int tmp;
	int job_time = -1;
	for (int i = 0; i < n; i++) {
		A += array[i][1];
		B += array[i][2];
		C += array[i][3];
		tmp = array[i][1] + array[i][2] + array[i][3];
		if (tmp > job_time)
			job_time = tmp;
	}
	// dummy schedule
	vector< vector< int > > schedule;

	int j_make = johnsons(array, schedule, 0);
	int LB = max( max( max( max(A, B), C), j_make), job_time); // calculate lower bound

	return LB;
}

// Algorithm B1 assumes only one parallel machine and there exists an a_j, where a_j < LB/3
int Input::Algorithm_B1() {
	// find lower bound

	// sum of processing times on the three machines
	int A = 0, B = 0, C = 0;
	int tmp;
	int job_time = -1;
	for (int i = 0; i < n; i++) {
		A += array[i][1];
		B += array[i][2];
		C += array[i][3];
		tmp = array[i][1] + array[i][2] + array[i][3];
		if (tmp > job_time)
			job_time = tmp;
	}
	// dummy schedule
	vector< vector< int > > sch;

	int j_make = johnsons(array, sch, 0);
	int LB = max( max( max( max(A, B), C), j_make), job_time); // calculate lower bound

	// take out job J_l, where a_l is >= LB/3
	vector<int> J_l;
	vector< vector< int > > J;
	bool removed = false;
	for (int i = 0; i < n; i++) {
		if (array[i][1] < LB/3 || removed) // only remove one job
			J.push_back(array[i]);
		else {
			J_l = array[i];
			removed = true;
		}
	}

	if (!removed)
		return -1;

	vector< vector< int > > schedule;
	j_make = johnsons(J, schedule, 0);

	int T_1 = max(J_l[1], B - J_l[2]);
	int T_2 = max(J_l[1], j_make);
	int T_3 = max(T_1 + J_l[2], j_make);

	int B_make = max(T_2 + A - J_l[1], T_3 + J_l[3]);

	// output to file
	ofstream out_file;
    out_file.open("output.txt", ofstream::app);

    if (out_file.is_open()) {
        out_file << "Algorithm B1: " << B_make << endl;
        out_file << "A" << endl;
        out_file << J_l[0] << " " << J_l[1] << endl;
        int start = T_2;
        for (int i = 0; i < J.size(); i++) {
        	out_file << J[i][0] << " " << start << endl;
        	start += J[i][1];
        }
        out_file << "B and C" << endl;
        for (int i = 0; i < J.size(); i++)
        	out_file << schedule[i][0] << " " << schedule[i][1] << " " << schedule[i][2] << endl;
        out_file << J_l[0] << " " << T_1 << " " << T_3 << endl;
    }
    else
        cout << "Error opening output file" << endl;

	// closing output files
    out_file.close();

	return B_make;
}

// Algorithm B2 assumes only one parallel machine and for all a_j, where a_j < LB/3
int Input::Algorithm_B2() {
	// find lower bound
	int LB = lower_bound();

	// make sure no jobs are >= LB/3
	for (int i = 0; i < n; i++)
		if (array[i][1] >= LB/3)
			return -1;

	// computing initial schedule
	vector< vector< int > > schedule;
	johnsons(array, schedule, 0);
	// start 3 machines
	vector< vector< int > > A;
	vector< vector< int > > B;
	vector< vector< int > > C;

	vector<int> A_row(2,0);
	vector<int> B_row(2,0);
	vector<int> C_row;
	C_row.push_back(0);
	C_row.push_back(array[0][2]);

	// constructing inital schedule with johnsons at 0 and A at 0
	for (int i = 0; i < n; i++) {
		A_row[0] = array[i][0];
		B_row[0] = array[i][0];
		C_row[0] = array[i][0];

		A.push_back(A_row);
		B.push_back(B_row);

		A_row[1] = A_row[1] + array[i][1];
		B_row[1] = B_row[1] + array[i][1];
		if (C_row[1] >= B_row[1]) {
			C.push_back(C_row);
			C_row[1] = C_row[1] + array[i][1];
		}
		else {
			C.push_back(B_row);
			C_row[1] = B_row[1] + array[i][1];
		}
	}

	// now delay C so that all jobs are processed cosecuitively
	for (int i = n-2; i >= 0; i--) {
		int dif = C[i+1][1] - C[i][1] + array[i][3];
		C[i][1] += dif;
	}

	// now shift both B and C schedules so that each job does not collide with jobs in A
	for (int i = n-1; i >= 0; i--) {
		if (B[i][1] < A[i][1] + array[i][1]) { // start time of B < end time of A
			// take difference and add to all values of B and C
			int dif = A[i][1] + array[i][1] - B[i][1];
			for (int j = 0; j < n; j++) {
				B[j][1] += dif;
				C[j][1] += dif;
			}
		}
	}

	// T_0 has been found
	int T_0 = B[0][1];

	// find delta and delta_1
	int delta;
	int job;
	for (int i = n-1; i >= 0; i--) {
		if (A[i][1] < T_0) {
			delta = T_0 - A[i][1];
			job = i;
			break;
		}
	}

	int delta_1 = C[0][1] - B[0][1];

}


int main() {
    Input a;

    // a.LPT(a.array);

    // cout << "LPT" << endl;

    // // LPT
    // for (int i = 0; i < a.n; i++)
    //     cout << i << ": " << a.array[i][0] << "   " << a.array[i][1] << endl;

    // a.johnsons(a.array);

    // cout << "johnsons" << endl;

    // // johnsons
    // for (int i = 0; i < a.n; i++)
    //     cout << i << ": " << a.array[i][0] << "   " << a.array[i][2] << " " << a.array[i][3] << endl;

    // cout << "ALGORITHM A" << endl;
    int A_make = a.Algorithm_A();
    cout << "ALG_A makespan " << A_make << endl;

    // cout << "ALGORITHM B1" << endl;
    int B1_make = a.Algorithm_B1();
    cout << "ALG_B1 makespan " << B1_make << endl;

    // cout << "ALGORITHM B2" << endl;
    int B2_make = a.Algorithm_B2();
    cout << "ALG_B2 makespan " << B2_make << endl;

    // cout << "ALGORITHM B3" << endl;
    // int B3_make = a.Algorithm_B3();
    // cout << "ALG_B3 makespan " << B3_make << endl;

    return 0;
}
