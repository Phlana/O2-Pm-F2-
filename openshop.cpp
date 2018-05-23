#include <iostream>
// (file)stream for input and output from and to files
#include <fstream>
// for quicksort
#include <algorithm>
#include <utility>

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
	int m, n;
	int** input_array;
	int** output_array;
	Input();
	void print_input(void) {
		// for (int x = 0; x < n; x++)
		// 	for (int y = 0; y < 4; y++)
		// 		cout << "[" << x << "][" << y << "] is: " << input_array[x][y] << endl;
		for (int x = 0; x < n; x++) {
			cout << x << ": " << input_array[x][0] << "  " << input_array[x][1] << " " << input_array[x][2] << " " << input_array[x][3] << endl;
		}
	}
	int** modified_qsort(int**, int, int);
	int** _2qsort(int**, int, int);
	void LPT(void);
	void johnsons(void);

	void output(void);
};

// default constructor for Input class
Input::Input() {
	// reading the input file
	ifstream in_file("input.txt");

	if (in_file.is_open()) {
		// first line contains m and n as inputs
		in_file >> m >> n;

		// creating the dimensions of the 2D array
		input_array = new int*[n];
		for (int i = 0; i < n; i++) {
			input_array[i] = new int[4];
		}

		int line_count = 0;
		int a,b,c;
		while (in_file >> a >> b >> c) {
			input_array[line_count][0] = line_count+1;
			input_array[line_count][1] = a;
			input_array[line_count][2] = b;
			input_array[line_count][3] = c;

			line_count++;
		}

		in_file.close();

		// for (int x = 0; x < n; x++)
		// 	for (int y = 0; y < 4; y++)
		// 		cout << "input_array[" << x << "][" << y << "] is: " << input_array[x][y] << endl;

	}
	else
		cout << "Error opening input file" << endl;
}

// modified quicksort for sorting second value from largest to shortest
int** Input::modified_qsort(int** arr, int s, int e) {
    int start = s, end = e;
    int tmp;
    int pivot = arr[s+(e-s)/2][1];

    while (start <= end) {
        while (arr[start][1] > pivot)
            start++;

        while (arr[end][1] < pivot)
            end--;

        if (start <= end) {
            for (int index = 0; index < 4; index++) {
                tmp = arr[start][index];
                arr[start][index] = arr[end][index];
                arr[end][index] = tmp;
            }

            start++;
            end--;
        }
    }
    if (s < end)
        return modified_qsort(arr, s, end);
    if (start < e)
        return modified_qsort(arr, start, e);
}

// Longest Processing Time algorithm
void Input::LPT() {
	/*
	assigns a schedule for parallel machines
	only uses each second value in 2D array
	*/
	cout << "LPT start" << endl;
	// copying the array
	int** qsort_array;
	qsort_array = new int*[n];
		for (int i = 0; i < n; i++) {
			qsort_array[i] = new int[4];
		}

	for (int x = 0; x < n; x++)
		for (int y = 0; y < 4; y++)
			qsort_array[x][y] = input_array[x][y];
	
	modified_qsort(qsort_array, 0, n-1);

	for (int x = 0; x < n; x++)
		cout << x << ": " << qsort_array[x][0] << "  " << qsort_array[x][1] << " " << qsort_array[x][2] << " " << qsort_array[x][3] << endl;

	cout << "LTP finish" << endl;
}

// modified quicksort for sorting from third and fourth value
int** _2qsort(int**, int, int) {

}

// Johnson's algorithm
void Input::johnsons() {
	/*
	assigns a schedule for flowshop
	uses each third and fourth values in 2D array
	*/
	cout << "johnsons" << endl;
	// copying the array
	int** _2sort_array;
	_2sort_array = new int*[n];
		for (int i = 0; i < n; i++) {
			_2sort_array[i] = new int[4];
		}

	for (int x = 0; x < n; x++)
		for (int y = 0; y < 4; y++)
			_2sort_array[x][y] = input_array[x][y];

	_2qsort(_2sort_array, 0, n-1);

	for (int x = 0; x < n; x++) {
		cout << x << ": " << _2sort_array[x][0] << "  " << _2sort_array[x][1] << " " << _2sort_array[x][2] << " " << _2sort_array[x][3] << endl;

}

// prints output to output file
void Input::output() {
	// init output file
	ofstream out_file("output.txt");
	if (out_file.is_open()) {
		// print output to file
		out_file << input_array << endl;
	}
	else
		cout << "Error opening output file" << endl;

	// closing output files
	out_file.close();
}


int main() {
	Input inarray;
	inarray.LPT();
	// inarray.modified_qsort(inarray.input_array, 0, inarray.n-1);
	inarray.print_input();
	inarray.output();
	return 0;
}