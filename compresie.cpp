#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("compresie.in");
    ofstream fout("compresie.out");

    int i, n, m, index1 = 0, index2 = 0, max_len = 0;
    lli sum_seq_1, sum_seq_2;

    fin >> n;
    // citim primul sir de numere
    vector<int> seq1(n + 1);
    for (i = 0; i < n; i++) {
        fin >> seq1[i];
    }

    fin >> m;
    // citim al doilea sir de numere
    vector<int> seq2(m + 1);
    for (i = 0; i < m; i++) {
        fin >> seq2[i];
    }
    fin.close();

    /* initializam variabilele in care vom retine sumele 
    partiale calculate pana la o anumita iteratie pentru care se 
    poate realiza o compresie la suma respectiva */
    sum_seq_1 = seq1[index1];
    sum_seq_2 = seq2[index2];

    /* parcurgem sirurile pana cand unul se termina. Formam sumele
    de compresie in mod "lacom" */
    while (index1 < n && index2 < m) {
        /* cazul in care cele doua sume partiale (sau elemente in caz 
        favorabil) sunt egale si se poate realiza o compresie */
        if (sum_seq_1 == sum_seq_2) {
            index1++;
            index2++;
            // initializam sumele partiale cu urmatorii termeni
            sum_seq_1 = seq1[index1];
            sum_seq_2 = seq2[index2];

            // incrementam lungimea sirului compresat ce se obtine
            max_len++;
        /* in cazul in care prima suma e mai mare decat a doua trebuie 
        sa "echilibram" sumele luand un element din a doua */ 
        } else if (sum_seq_1 > sum_seq_2) {
            index2++;
            sum_seq_2 += seq2[index2];
        // analog ca in cazul precedent
        } else {
            index1++;
            sum_seq_1 += seq1[index1];
        }
    }

    // daca am epuizat doar unul din siruri compresia e imposibila
    if (index1 < n || index2 < m) {
        fout << -1 << "\n";
    } else {
        fout << max_len << "\n";
    }
    fout.close();
    return 0;
}
