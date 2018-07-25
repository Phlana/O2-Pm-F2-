#ifndef CREATE_H
#define CREATE_H

#include <stdlib.h>
#include <fstream>

void create(int n, int m, int range) {
	// opening output file
	ofstream out_file("input.txt");
	// printing m and n to file
	out_file << m << " " << n << endl;
	// randomising values
    for (int i = 0; i < n; i++)
    	out_file << rand()%range + 1 << " " << rand()%range + 1<< " " << rand()%range + 1 << endl;
}

#endif