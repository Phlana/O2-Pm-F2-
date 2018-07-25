#ifndef OPENSHOP_H
#define OPENSHOP_H

#include <vector>

using namespace std;

struct Input {
    int n, m;
    vector< vector<int> > array;
    Input();

    void decend_qsort(vector< vector< int > >&, int, int, int);
    void ascend_qsort(vector< vector< int > >&, int, int, int);
    void i_sort(vector< vector< int > >&);
    int LPT(vector< vector< int > >&, vector< vector< int > >&, int);
    int johnsons(vector< vector< int > >&, vector< vector< int > >&, int);

    int lower_bound(void);
    int Algorithm_A(void);
    int Algorithm_B1(void);
    int Algorithm_B2_3(void);

    float run(void);
};

#endif