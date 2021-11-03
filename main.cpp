#include <iostream>
#include <fstream>

using namespace std;

struct matrix {
    int n; //от 4 до 16
    int m;
    double **mas;
};

int fill_matrix(matrix &m, int n_start, int n_end, int next_num);

void printMatrix(matrix &mat);

int lenInt(int x);

void read_input_file(int &n, matrix &mat);

void mul(matrix &mat, int i, double k);

void gsv(matrix &mat);

void sum(matrix &mat, int i0, int i1, double k);

void inverse(matrix &mat);

int main() {
    int n = 0;
    matrix my_matrix;
    read_input_file(n, my_matrix);
//    fill_matrix(my_matrix, 0, my_matrix.n, 1);
    matrix obratnaya = my_matrix;
    obratnaya.n = n;
    obratnaya.m = n;
    inverse(obratnaya);
//    printMatrix(my_matrix);
    printMatrix(obratnaya);
}

void read_input_file(int &n, matrix &mat) {
    ifstream in;
    in.open("C:\\Users\\lenovo\\CLionProjects\\MatrixStruct\\input.txt", ios_base::in);
    if (!in.is_open()) {
        cerr << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }
    if (!(in >> n)) {
        cerr << "Error reading file" << endl;
        exit(EXIT_FAILURE);
    }
    if (n < 4 || n > 16) {
        cerr << "Incorrect value" << endl;
        exit(EXIT_FAILURE);
    }
    mat.n = n;
    mat.m = n;
    mat.mas = new double *[n];
    for (int i = 0; i < n; i++) mat.mas[i] = new double[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(in >> (mat.mas[i][j]))) {
                cerr << "Error reading file" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    in.close();
}

int fill_matrix(matrix &mat, int n_start, int n_end, int next_num) {
    int n = mat.n;
    double **mas = mat.mas;

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

    fill_matrix(mat, n_start + 2, n_end - 2, next_num);
    return 0;
}

void printMatrix(matrix &mat) {
    ofstream out;
    out.open("C:\\Users\\lenovo\\CLionProjects\\MatrixStruct\\output.txt", ios_base::out);
    if (!out.is_open()) {
        cerr << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }
    //
    //
    int n = mat.n;
    int m = mat.m;
    double **mas = mat.mas;
    int s = lenInt(n * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
//            for (int k = 0; k < (s - lenInt(mas[i][j])); k++) {
//                out << ' ';
//            }
            out.width(s + 2);
            out.precision(2);
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

void gsv(matrix &mat) {
    for (int j = 0; j < mat.n; j++) {
        if (mat.mas[j][j] != 0) mul(mat, j, 1 / mat.mas[j][j]);
        for (int i = 0; i < mat.n; i++) {
            if (i == j) continue;
            sum(mat, i, j, -(mat.mas[i][j]));
        }
    }
}


void mul(matrix &mat, int i, double k) {
    for (int j = 0; j < (mat.m); j++) {
        mat.mas[i][j] *= k;
    }
}

void sum(matrix &mat, int i0, int i1, double k) {
    for (int j = 0; j < mat.m; j++) {
        mat.mas[i0][j] += (mat.mas[i1][j] * k);
    }
}

void inverse(matrix &mat) {
    double **nmas = new double *[mat.n];
    for (int i = 0; i < mat.n; i++) {
        nmas[i] = new double[mat.n * 2];
        for (int j = 0; j < mat.n * 2; j++) {
            if (j < mat.n) {
                nmas[i][j] = mat.mas[i][j];
            } else if (j == i + mat.n) {
                nmas[i][j] = 1;
            } else {
                nmas[i][j] = 0;
            }

        }
    }
    matrix nmat;
    nmat.n = mat.n;
    nmat.m = mat.n * 2;
    nmat.mas = nmas;
    gsv(nmat);
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.n; j++){
            mat.mas[i][j] = nmat.mas[i][j+mat.n];
        }
    }
    for (int i = 0; i < mat.n; i++) {
        delete[] nmas[i];
    }
    delete[] nmas;
}