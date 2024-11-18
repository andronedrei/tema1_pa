#include <bits/stdc++.h>
using namespace std;

#define MOD ((int)1e9 + 7)
#define HOR_ZONE 'H'
#define VER_ZONE 'V'

typedef long long int lli;

// functie eficienta de calcul al exponentului unui numar natural - O(log(exp))
lli my_pow(lli base, lli exponent) {
    lli rez = 1;  // <=> exp = 0

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            rez *= base;
            rez %= MOD;
            exponent--;
        }

        base *= base;
        base %= MOD;
        exponent /= 2;
    }

    return rez;
}

/* functie care calculeaza noul numar de variante pe baza celui precedent 
cunoscandu-se orientarile bucatii precedente si celei curente */
lli dynamic_next_step(lli rez_so_far, char type_left, char type_right) {
    if (type_left == VER_ZONE && type_right == VER_ZONE) {
        return rez_so_far * 2;
    }
    if (type_left == VER_ZONE && type_right == HOR_ZONE) {
        return rez_so_far * 2;
    }
    if (type_left == HOR_ZONE && type_right == VER_ZONE) {
        return rez_so_far;
    }
    if (type_left == HOR_ZONE && type_right == HOR_ZONE) {
        return rez_so_far * 3;
    }

    // se ajunge aici daca input-ul a fost invalid
    return 0;
}

/* functie care calculeaza noul numar de variante pe baza unui tipar 
repetitiv al aceleiasi orientari */
lli dynamic_n_same_steps(lli rez_so_far, lli n, char type)  {
    if (type == VER_ZONE) {
        return rez_so_far * my_pow(2, n);
    }
    if (type == HOR_ZONE) {
        return rez_so_far * my_pow(3, n);
    }

    // se ajunge aici daca input-ul a fost invalid
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("colorare.in");
    ofstream fout("colorare.out");

    // 3 tipuri de culori
    lli x, rez = 0;
    int i, k;
    char type, prev_type;

    fin >> k;
    // citim prima zona
    fin >> x;
    fin >> type;
    // calcuam numarul de variante pentru prima zona
    if (type == VER_ZONE) {
        rez = 3;
    } else {
        rez = 6;
    }
    prev_type = type;
    /* calculam numarul de variante luand in considerare restul de bucati
    din primul grup */
    rez = dynamic_n_same_steps(rez, x - 1, type) % MOD;

    // calculam numarul de variante folosind restul de grupuri citite
    for (i = 1; i < k; i++) {
        fin >> x;
        fin >> type;
        // calculam separat primul pas, doar aici se poate schimba tipul
        rez = dynamic_next_step(rez, prev_type, type) % MOD;
        prev_type = type;
        // calculam pentru restul de bucati din grup
        rez = dynamic_n_same_steps(rez, x - 1, type) % MOD;
    }
    fin.close();

    fout << rez << "\n";
    fout.close();
    return 0;
}
