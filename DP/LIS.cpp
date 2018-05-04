#include <iostream>
using namespace std;

const int MAX = 1000;
void input(int *a, int &n) {
    freopen("input.txt", "r", stdin);
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
}

void LIS(int *a, int *S, int n, int &lenS) {
    int P[MAX], M[MAX];
    M[0] = 0, M[1] = 0, P[0] = 0;
    int L = 1;
    for(int i = 1; i < n; i++) {
        int j;
        for(j = 1; j <= L; j++)
            if (a[M[j]] >= a[i]) break;
        P[i] = M[j - 1];
        M[j] = i;
        if (j > L) L = j;
    }
    lenS = L;
    int k = M[L];
    for(int i = L - 1; i; i--) {
        S[i] = a[k];
        k = P[k];
    }
}

int main() {
    int a[MAX], n;
    input(a, n);
    int S[MAX], L;
    LIS(a, S, n, L);
    for(int i = 0; i < L; i++)
        cout << S[i] << " ";
    cout << endl;
    return 0;
}
