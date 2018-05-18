#include <iostream>
// (file)stream for input and output from and to files
#include <fstream>
// for quicksort
#include <algorithm>

using namespace std;

/*
input format:
m, n
a_1, b_1, c_1
a_2, b_2, c_2
...
a_i, b_i, c_i
...
a_n, b_n, c_n

where m is number of machines, n is number of jobs
a_i, b_i, c_i are processing times of job i on machines A, B, and C respectively.
*/

struct Input {
	int m,n;
	int** input_array;
	int** output_array;
	Input();
	void LPT(void);
	void johnsons(void);
};

// default constructor for Input class
Input::Input() {
	// reading the input file
	ifstream in_file("input.txt");

	if (in_file.is_open()) {
		// first line contains m and n inputs
		in_file >> m >> n;

		// creating the dimensions of the 2D array
		input_array = new int*[n];
		for (int i = 0; i < n; i++) {
			input_array[i] = new int[3];
		}

		int line_count = 0;
		int a,b,c;
		while (in_file >> a >> b >> c) {
			input_array[line_count][0] = a;
			input_array[line_count][1] = b;
			input_array[line_count][2] = c;

			line_count++;
		}

		in_file.close();

		// for (int x = 0; x < n; x++)
		// 	for (int y = 0; y < 3; y++)
		// 		cout << "input_array[" << x << "][" << y << "] is: " << input_array[x][y] << endl;

	}
	else
		cout << "Error opening input file" << endl;
}

// Longest Processing Time algorithm
void LPT() {
	/*
	assigns a schedule for parallel machines
	only uses each first value in 2D array
	*/

}

// Johnson's algorithm
void johnsons() {
	/*
	assigns a schedule for flowshop
	uses each second and third values in 2D array
	*/

}


int main() {
	Input inarray;

	// init output file
	ofstream out_file("output.txt");
	if (out_file.is_open()) {
		// print output to file
	}
	else
		cout << "Error opening output file" << endl;

	// closing output files
	out_file.close();

	for (int x = 0; x < inarray.n; x++)
			for (int y = 0; y < 3; y++)
				cout << "input_array[" << x << "][" << y << "] is: " << inarray.input_array[x][y] << endl;

	return 0;
}