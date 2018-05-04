#include <bits/stdc++.h>
using namespace std;

void computePI(string P, vector<int>& pi) {
    int m = P.length();
    int k;
    pi.resize(m + 1);
    pi[1] = k = 0;
    for(int q = 2; q <= m; ++q) {
        while (k && (P[k] != P[q - 1])) k = pi[k];
        if (P[k] == P[q - 1]) k++;
        pi[q] = k;
    }
}

vector<int> KMP_Search(const string& T, string P) {
    vector<int> pi, res;
    computePI(P, pi);
    int q = 0;
    int n = T.length();
    int m = P.length();
    for(int i = 0; i < n; ++i) {
        while (q && (P[q] != T[i])) q = pi[q];
        if (P[q] == T[i]) q++;
        if (q == m) {
            res.push_back(i - m + 1);
            q = pi[q];
        }
    }
    return res;
}

int main() {
    freopen("input1.txt", "r", stdin);
    string T, P;
    getline(cin, T);
    getline(cin, P);
    vector<int> pos = KMP_Search(T, P);
    for(int i = 0; i < pos.size(); ++i)
        cout << pos[i] << " ";
    cout << endl;

    fclose(stdin);
    
    system("pause");
    getchar();
    return 0;
}
