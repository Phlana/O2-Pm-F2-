#include <utility>
#include <iostream>
// (file)stream for input and output from and to files
#include <fstream>
// for min
// #include <algorithm>
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
    // int n = 10;
    // int array[10][4] = { {1, 1, 2, 3}, {2, 9, 31, 14}, {3, 35, 23, 12}, {4, 21, 34, 11}, {5, 6, 8, 15}, {6, 4, 7, 6}, {7, 12, 29, 10}, {8, 13, 17, 25}, {9, 22, 20, 30}, {10, 16, 19, 18} };
    int n, m;
    // int array[99999][4];
    vector< vector<int> > array;
    Input();
    // void output(void);
    // void decend_qsort(int[][4], int, int, int);
    // void ascend_qsort(int[][4], int, int, int);
    void decend_qsort(vector< vector< int > >&, int, int, int);
    void ascend_qsort(vector< vector< int > >&, int, int, int);
    void i_sort(vector< vector< int > >&);
    void LPT(vector< vector< int > >&);
    void johnsons(vector< vector< int > >&);
};

// default constructor for Input class
Input::Input() {
	// cout << "input" << endl;
    // reading the input file
    ifstream in_file("input.txt");

    if (in_file.is_open()) {
        // first line contains m and n as inputs
        in_file >> m >> n;

        // creating the dimensions of the 2D array
        // array = new int*[n];
        // for (int i = 0; i < n; i++) {
        //  array[i] = new int[4];
        // }

        cout << m << " " << n << endl;

        // array[n][4];

        int line_count = 0;
        int a,b,c;
        while (in_file >> a >> b >> c) {
        	vector<int> row;
        	row.push_back(line_count+1);
        	row.push_back(a);
        	row.push_back(b);
        	row.push_back(c);

        	array.push_back(row);

            // array[line_count][0] = line_count;
            // array[line_count][1] = a;
            // array[line_count][2] = b;
            // array[line_count][3] = c;

            cout << line_count << "  " << a << " " << b << " " << c << endl;

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
// void Input::decend_qsort(int arr[][4], int s, int e, int c) {
void Input::decend_qsort(vector< vector< int > >& arr, int s, int e, int c) {
	// cout << "decend" << endl;
    int start = s, end = e;
    int tmp;
    // pivot
    int p = arr[s+(e-s)/2][c];

    while (start <= end) {
        while (arr[start][c] > p)
            start++;

        while (arr[end][c] < p)
            end--;

        if (start <= end) {
            for (int i = 0; i < 4; i++) {
                tmp = arr[start][i];
                arr[start][i] = arr[end][i];
                arr[end][i] = tmp;
            }
            
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
    int tmp;
    // pivot
    int p = arr[s+(e-s)/2][c];

    while (start <= end) {
        while (arr[start][c] < p)
            start++;

        while (arr[end][c] > p)
            end--;

        if (start <= end) {
            for (int i = 0; i < 4; i++) {
                tmp = arr[start][i];
                arr[start][i] = arr[end][i];
                arr[end][i] = tmp;
            }
            
            start++;
            end--;
        }
    }

    if (s < end)
        ascend_qsort(arr, s, end, c);
    if (start < e)
        ascend_qsort(arr, start, e, c);
}

// LPT with number of machines as input
void Input::i_sort(vector< vector< int > >& mac) {
	// cout << "isort" << endl;
	int key;
	vector<int> temp;

	temp = mac[m-1];

	key = mac[m-1][1];

	int j = m-2;

	while (j >= 0 && mac[j][1] < key) {
		// shift
    	mac[j+1] = mac[j];
        j--;
    }

    mac[j+1][0] = (int)temp[0];
    mac[j+1][1] = (int)temp[1];
}

int max(vector< vector< int > >& vec, int m) {
	int count = 0;
	int max = vec[count][1];
	while (count < m) {
		if (max < vec[count][1])
			max = vec[count][1];
		count++;
	}
	return max;
}

void Input::LPT(vector< vector< int > >& lpt_arr) {
	// cout << "LPT func" << endl;
	// sort by column 1
	decend_qsort(lpt_arr, 0, n-1, 1);

	// start m machines
	vector< vector<int> > machine;
	for (int i = m; i > 0; i--) {
		vector<int> row;

		row.push_back(i-1);
		row.push_back(0);

		machine.push_back(row);
	}
	// save start time a
	int start_lpt[n][2];
	int count = 0;

	int index;
	while (count < n) {
		// save start time
		start_lpt[ lpt_arr[count][0]-1 ][1] = machine[m-1][1];
		// and machine number
		start_lpt[ lpt_arr[count][0]-1 ][0] = machine[m-1][0];

		// adding time to last element on machine
		machine[m-1][1] += lpt_arr[count][1];
		// resort


		// index = find_index(machine, m, 0, m-1);
		i_sort(machine);


		// // insert
		// vector<int> tmp;
		// tmp = machine[m-1];
		// machine.pop_back();
		// machine.insert(machine.begin()+index, tmp);

		count++;
	}


    int LPT_makespan = max(machine, m);
    cout << "LPT machines " << LPT_makespan << endl;

    for (int i = 0; i < n; i++)
    	cout << i << ": " << i+1 << " " << start_lpt[i][0] << "  " << start_lpt[i][1] << endl;
    //          iteration    job number    machine                    start time
}

// johnsons algorithm
void Input::johnsons(vector< vector< int > >& johnson_arr) {
	// cout << "johnsons func" << endl;
    // splitting johnson_arr
    int tmp;
    int start = 0, end = n-1;
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
    for (int i = 0; i < n; i++) {
        if (johnson_arr[i][2] > johnson_arr[i][3]) {
            index = i;
            break;
        }
    }
    // sorting two parts of johnson_arr
    ascend_qsort(johnson_arr, 0, index-1, 2);
    decend_qsort(johnson_arr, index, n-1, 3);

    // start 2 machines as flowshop
    int flowshop[2] = {0, johnson_arr[0][2]};
    int start_johnson[n][3];

    // save job number and start time b and c
    start_johnson[0][0] = johnson_arr[0][0];
    start_johnson[0][1] = flowshop[0];
	flowshop[0] += johnson_arr[0][2];
	
	start_johnson[0][2] = flowshop[1];
	flowshop[1] += johnson_arr[0][3];

    for (int i = 1; i < n; i++) { 
    	// for each job
    	start_johnson[i][0] = johnson_arr[i][0];
    	start_johnson[i][1] = flowshop[0];
    	flowshop[0] += johnson_arr[i][2];

    	if (flowshop[0] > flowshop[1]) {
    		flowshop[1] = flowshop[0];
    	}
    	start_johnson[i][2] = flowshop[1];
	    flowshop[1] += johnson_arr[i][3];
    	
    }

    int johnsons_makespan = flowshop[1];

    cout << "johnsons machines " << johnsons_makespan << endl;

    for (int i = 0; i< n; i++)
    	cout << i << ": " << start_johnson[i][0] << "  " << start_johnson[i][1] << "  " << start_johnson[i][2] << endl;
    //          iteration    job number                     B start time                   C start time
}

void Algorithm_A() {

}

int main() {
    Input a;

    a.LPT(a.array);

    cout << "LPT" << endl;

    // LPT
    for (int i = 0; i < a.n; i++)
        cout << i << ": " << a.array[i][0] << "   " << a.array[i][1] << endl;

    a.johnsons(a.array);

    cout << "johnsons" << endl;

    // johnsons
    for (int i = 0; i < a.n; i++)
        cout << i << ": " << a.array[i][0] << "   " << a.array[i][2] << " " << a.array[i][3] << endl;

    return 0;
}
