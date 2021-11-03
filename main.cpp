#include <iostream>
#include <fstream>

using namespace std;

struct matrix {
    int n; //от 4 до 16
    int **mas;
};

int fill_matrix(matrix *m, int n_start, int n_end, int next_num);

void printMatrix(matrix *m);

int lenInt(int x);

void read_input_file(int *n, matrix *m);

int main() {
    int n = 0;
    matrix my_matrix;
    read_input_file(&n, &my_matrix);
    //fill_matrix(&my_matrix, 0, my_matrix.n, 1);
    printMatrix(&my_matrix);
}

void read_input_file(int *n, matrix *m) {
    ifstream in;
    in.open("C:\\Users\\lenovo\\CLionProjects\\MatrixStruct\\input.txt", ios_base::in);
    if (!in.is_open()) {
        cerr << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }
    if (!(in >> *n)) {
        cerr << "Error reading file" << endl;
        exit(EXIT_FAILURE);
    }
    if (*n < 4 || *n > 16) {
        cerr << "Incorrect value" << endl;
        exit(EXIT_FAILURE);
    }
    m->n = *n;
    m->mas = new int *[*n];
    for (int i = 0; i < *n; i++) m->mas[i] = new int[*n];
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            if (!(in >> (m->mas[i][j]))) {
                cerr << "Error reading file" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    in.close();
}

int fill_matrix(matrix *m, int n_start, int n_end, int next_num) {
    int n = m->n;
    int **mas = m->mas;

    if (next_num == n * n + 1) return 0;

    for (int i = n_start; i < n_end; i++) {
        mas[i][n_start] = next_num++;
        if (next_num == n * n + 1) return 0;
    }
    for (int j = n_start + 1; j < n_end; j++) {
        mas[n_end - 1][j] = next_num++;
        if (next_num == n * n + 1) return 0;
    }
    for (int i = n_end - 2; i > n_start - 1; i--) {
        mas[i][n_end - 1] = next_num++;
        if (next_num == n * n + 1) return 0;
    }
    for (int i = n_start; i < n_end - 1; i++) {
        mas[i][n_end - 2] = next_num++;
        if (next_num == n * n + 1) return 0;
    }
    for (int j = n_end - 3; j > n_start; j--) {
        mas[n_end - 2][j] = next_num++;
        if (next_num == n * n + 1) return 0;
    }
    for (int i = n_end - 3; i > n_start - 1; i--) {
        mas[i][n_start + 1] = next_num++;
        if (next_num == n * n + 1) return 0;
    }
    for (int j = n_start + 2; j < n_end - 2; j++) {
        mas[n_start][j] = next_num++;
        if (next_num == n * n + 1) return 0;
    }
    for (int j = n_end - 3; j > n_start + 1; j--) {
        mas[n_start + 1][j] = next_num++;
        if (next_num == n * n + 1) return 0;
    }

    fill_matrix(m, n_start + 2, n_end - 2, next_num);


    return 0;
}

void printMatrix(matrix *m) {
    ofstream out;
    out.open("C:\\Users\\lenovo\\CLionProjects\\MatrixStruct\\output.txt", ios_base::out);
    if (!out.is_open()) {
        cerr << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }
    //
    //
    int n = m->n;
    int **mas = m->mas;
    int s = lenInt(n * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < (s - lenInt(mas[i][j])); k++) {
                out << ' ';
            }
            out << mas[i][j] << ' ';
        }
        out << endl;
    }
    out.close();
}

int lenInt(int x) {
    int len = 0;
    while (x != 0) {
        x /= 10;
        len++;
    }
    return len;
}