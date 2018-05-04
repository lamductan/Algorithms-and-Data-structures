#include <iostream>
#include <string>
#include <vector>
using namespace std;

void computeD(string P, vector<int>& D) {
    int m = P.length();
    D.resize(0x7f - 0x20);
    for(int i = 0x20; i < 0x7f; i++)
        D[i - 0x20] = m;
   for(int i = 0; i < m - 1; ++i)
            D[P[i] - 0x20] = m - i - 1;
}

vector<int> HorsPool_Search(const string& T, string P) {
    vector<int> D, res;
    computeD(P, D);
    int n = T.length();
    int m = P.length();
    int i = m - 1, k;
    while (i < n) {
        k = 0;
        while ((k < m) && (P[m - k - 1] == T[i - k])) k++;
        if (k == m) res.push_back(i - m + 1);
        i += D[T[i] - 0x20];
    }
    return res;
}

int main() {
    freopen("input1.txt", "r", stdin);
    string T, P;
    getline(cin, T);
    getline(cin, P);
    vector<int> pos = HorsPool_Search(T, P);
    for(int i = 0; i < pos.size(); ++i)
        cout << pos[i] << " ";
    cout << endl;

    fclose(stdin);
    return 0;
}
