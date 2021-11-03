#include <iostream>
#include <fstream>

using namespace std;

struct matrix {
    int n = 0; //от 4 до 16
    int **mas;
};

int fill_matrix(matrix *m, int n_start, int n_end, int next_num);

int main() {
    int n = 0;
    ifstream in;
    matrix my_matrix;
    //
    //
    in.open("C:\\Users\\lenovo\\CLionProjects\\MatrixStruct\\input.txt", ios_base::in);
    if ( !in.is_open() ) {
        cerr << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }
    if ( !(in >> n) ) {
        cerr << "Error reading file" << endl;
        exit(EXIT_FAILURE);
    }
    in.close();
    //
    //
    my_matrix.n = n;
    my_matrix.mas = new int *[n];
    for (int i = 0; i < n; i++) my_matrix.mas[i] = new int[n];
    //
    //
    fill_matrix(&my_matrix, 0, my_matrix.n, 1);
    //
    //
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << my_matrix.mas[i][j] << ' ';
        }
        cout << endl;
    }

}

int fill_matrix(matrix *m, int n_start, int n_end, int next_num){
    int n = m -> n;
    int **mas = m -> mas;

    if (next_num == n * n + 1) return 0;

    for (int i = n_start; i < n_end; i++){
        mas[i][n_start] = next_num++;
        if (next_num == n * n + 1) return 0;
    }
    for (int j = n_start + 1; j < n_end; j++){
        mas[n_end - 1][j] = next_num++;
        if (next_num == n * n + 1) return 0;
    }
    for (int i = n_end - 2; i > n_start - 1; i--){
        mas[i][n_end - 1] = next_num++;
        if (next_num == n * n + 1) return 0;
    }
    for (int i = n_start; i < n_end - 1; i++){
        mas[i][n_end - 2] = next_num++;
        if (next_num == n * n + 1) return 0;
    }
    for (int j = n_end - 3; j > n_start; j--){
        mas[n_end - 2][j] = next_num++;
        if (next_num == n * n + 1) return 0;
    }
    for (int i = n_end - 3; i > n_start - 1; i--){
        mas[i][n_start + 1] = next_num++;
        if (next_num == n * n + 1) return 0;
    }
    for (int j = n_start + 2; j < n_end - 2; j++){
        mas[n_start][j] = next_num++;
        if (next_num == n * n + 1) return 0;
    }
    for (int j = n_end - 3; j > n_start + 1; j--){
        mas[n_start + 1][j] = next_num++;
        if (next_num == n * n + 1) return 0;
    }

    fill_matrix(m, n_start + 2,n_end - 2, next_num);

    return 0;
}