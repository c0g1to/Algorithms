#include <iostream>
#include <vector>
#include "edx-io.hpp"
//#include "../mooc/edx-io.hpp"

// doesn't work

using namespace std;

void print_arr(vector<vector<char>> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

string matrix_to_string(vector<vector<char>> &vec) {
    string input;
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); j++) {
            input += vec[i][j];
        }
        input += '!';
    }
    return input;
}

void counting_sort(vector<vector<char>> &vec, vector<int> &order, int digit) {
    vector<vector<int>> counter(26);
    vector<vector<char>> new_vec(vec.size(), vector<char>(vec[0].size()));
    vector<int> new_order(vec.size());
    for (int i = 0; i < vec.size(); i++) {
        counter[vec[i][digit] - 'a'].push_back(i);
    }
    for (int letter = 0, iter = 0; letter < counter.size(); letter++) {
        for (int k = 0; k < counter[letter].size(); k++) {
            int position = counter[letter][k];
            new_vec[iter] = vec[position];
            new_order[iter] = order[position];
            iter++;
        }
    }
    vec = new_vec;
    order = new_order;
}

int main() {
    edx_io io = edx_io();
    int n, m, k;

    io >> n >> m >> k;
    vector<vector<char>> matrix(n, vector<char>(m));
    vector<int> order(n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            io >> matrix[j][i];
        }
    }
    for (int i = 0; i < n; i++) {
        order[i] = i + 1;
    }

    print_arr(matrix);

    for (int i = n - 1; i >= n - k && i >= 0; i--) {
        counting_sort(matrix, order, i);
    }

    print_arr(matrix);

    for (int i = 0; i < n; i++) {
        cout << order[i] << ' ';
    }

    for (int i = 0; i < n; i++) {
        io << order[i] << ' ';
    }
    return 0;
}



//WORKING CODE:

//#include <vector>
//#include <array>
//#include <string>
//#include "edx-io.hpp"
//
//using namespace std;
//
//int main() {
//
//    int m, n, k;
//    io >> m >> n >> k;
//
//    /*FILE *in;
//    in = fopen("input.txt", "r");
//    fscanf(in, "%d %d %d", &m, &n, &k);*/
//
//    int c = 26;                      // количество разных знчений char
//    vector<string> strs(n);
//    for (int i = 0; i < n; i++) {
//        io >> strs[i];
//    }
//
//    vector<int> imIxs;               // промежуточные индексы для сортировки подсчётом
//    vector<array<int, 2>> resIxs;    // индексы в strs, хранящие сортировку; нужен, чтобы не копировать строки каждую итерацию
//    bool re = false;                 // второй индекс в массиве resIxs для отделения последовательных итераций цифровой сортировки
//    resIxs.resize(m);
//    for (int i = 0; i < m; i++)
//        resIxs[i][re] = i;
//
//    // цикл цифровой сортировки
//    for (int j = n - 1; j >= n - k; j--) {
//        // сортировка подсчётом
//        imIxs.assign(c, 0);
//
//        for (int i = 0; i < m; i++)
//            imIxs[strs[j][resIxs[i][re]] - 'a']++;
//
//        int sum = 0, temp;
//        for (int i = 0; i < c; i++) {
//            temp = imIxs[i];
//            imIxs[i] = sum;
//            sum += temp;
//        }
//
//        for (int i = 0; i < m; i++)
//            resIxs[imIxs[strs[j][resIxs[i][re]] - 'a']++][re ^ 1] = resIxs[i][re];
//
//        re ^= true;
//    }
//
//    //FILE *out = fopen("output.txt", "w");
//    for (int i = 0; i < m - 1; i++) {
//        //fprintf(out, "%d ", resIxs[i][re] + 1);
//        io << resIxs[i][re] + 1 << ' ';
//    }
//    io << resIxs[m - 1][re] + 1 << ' ';
//    //fprintf(out, "%d", resIxs[m - 1][re] + 1);
//
//    //fclose(out);
//
//    return 0;
//}

