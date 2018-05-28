#include <iostream>
// (file)stream for input and output from and to files
#include <fstream>
// for min
#include <algorithm>

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
    int n,m;
    int array[][4];

    Input();
    // void output(void);
    void decend_qsort(int[][4], int, int, int);
    void ascend_qsort(int[][4], int, int, int);
    void LPT(void );
    void johnsons(void);
};

// default constructor for Input class
Input::Input() {
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

        cout << n << endl;
        array[n][4];

        int line_count = 0;
        int a,b,c;
        while (in_file >> a >> b >> c) {
            array[line_count][0] = line_count+1;
            array[line_count][1] = a;
            array[line_count][2] = b;
            array[line_count][3] = c;

            cout << line_count << "  " << a << " " << b << " " << c << endl;

            line_count++;
        }

        in_file.close();

        // for (int x = 0; x < n; x++)
        //  for (int y = 0; y < 4; y++)
        //      cout << "array[" << x << "][" << y << "] is: " << array[x][y] << endl;

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
void Input::decend_qsort(int arr[][4], int s, int e, int c) {
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
void Input::ascend_qsort(int arr[][4], int s, int e, int c) {
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
void Input::LPT() {
    // sort by column 1
    decend_qsort(array, 0, n-1, 1);

    // start m machines
    int machine[m] = {};
    // save start time a
    int start[n][2];
    int index = 0;
    while (index < n) {
        // find index of minimum element
        int* d = min_element(machine,machine+m); //
       	int ind = d-machine; //

       	start[array[index][0]-1][0] = ind+1;
       	start[array[index][0]-1][1] = machine[ind];

       	machine[ind] += array[index][1];

       	index++;

    }
    cout << "LPT machines" << endl;

    for (int i = 0; i< n; i++)
    	cout << i << ": " << start[i][0] << "  " << start[i][1] << endl;

}

// johnsons algorithm
void Input::johnsons() {
    // splitting array
    int tmp;
    int start = 0, end = n-1;
    while (start < end) {
        while (array[start][2] < array[start][3])
            start++;
        while (array[end][2] > array[end][3])
            end--;
        if (array[start][2] > array[start][3] && array[end][2] < array[end][3]) { // array[start] and array[end] swap
            for (int i = 0; i < 4; i++) {
                tmp = array[start][i];
                array[start][i] = array[end][i];
                array[end][i] = tmp;
            }
            start++;
            end--;
        }
    }
    // grabbing index
    int index;
    for (int i = 0; i < n; i++) {
        if (array[i][2] > array[i][3]) {
            index = i;
            break;
        }
    }
    // sorting two parts of array
    ascend_qsort(array, 0, index-1, 2);
    decend_qsort(array, index, n-1, 3);
}

int main() {

    Input a;

    a.LPT();

    cout << "LPT" << endl;

    // LPT
    for (int i = 0; i < a.n; i++)
        cout << i << ": " << a.array[i][0] << "   " << a.array[i][1] << endl;

    a.johnsons();

    cout << "johnsons" << endl;

    // johnsons
    for (int i = 0; i < a.n; i++)
        cout << i << ": " << a.array[i][0] << "   " << a.array[i][2] << " " << a.array[i][3] << endl;

    return 0;
}