#include <bits/stdc++.h>
using namespace std;

#define ERR 1e-3

typedef long long int lli;

// structura care retine datele unui server
typedef struct server {
    lli pow;
    lli lim;

// functie care calculeaza puterea individuala a unui server
    double get_server_power(double input) {
        return pow - abs(input - lim);
    }
} server;

// functie care calculeaza puterea unui sistem de servere
double get_system_power(vector<server>& servers, int size, double input) {
    double cur_power;
    double min_power = servers[0].get_server_power(input);

    // cautam serverul cu output minim de putere
    for (int i = 1; i < size; i++) {
        cur_power = servers[i].get_server_power(input);
        if (cur_power < min_power) {
            min_power = cur_power;
        }
    }

    return min_power;
}

/* functie care foloseste cautearea binara intr-un interval ca sa 
gaseasca valoarea alimentarii pentru care se obtine putere maxima */
double bsearch_pow_sys(vector<server>& serv, int nr, double low, double high) {
    double mid, mid_sys_p;
    double low_mid_offset, mid_high_offset;
    double low_sys_p = get_system_power(serv, nr, low);
    double high_sys_p = get_system_power(serv, nr, high);

    do {
        mid = (low + high) / 2;
        mid_sys_p = get_system_power(serv, nr, mid);
        // diferentele intre output-urile de putere
        low_mid_offset = abs(mid_sys_p - low_sys_p);
        mid_high_offset = abs(mid_sys_p - high_sys_p);
        /*  verifiam daca punctul de putere putere maxima este
        chiar echidistant fata de capetele intervalului de cautare */
        if (abs(low_mid_offset - mid_high_offset) < ERR) {
            break;
        } else if (low_mid_offset < mid_high_offset) {
            // cazul in care punctul de putere maxima e in prima jumatate
            high = mid;
            high_sys_p = mid_sys_p;
        } else {
            // cazul in care punctul de putere maxima e in a doua jumatate
            low = mid;
            low_sys_p = mid_sys_p;
        }
    // cautam pana cand intervalul de cautare devine suficient de mic
    } while (abs(high_sys_p - low_sys_p) >= ERR);

    return mid_sys_p;
}

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("servere.in");
    ofstream fout("servere.out");

    int n, i;
    double input;
    double low, high;

    fin >> n;
    vector<server> servers(n);

    // citim puterile serverelor
    for (i = 0; i < n; i++) {
        fin >> input;
        servers[i].pow = input;
    }

    // citim pragurile de alimentare optime si determinam capetele
    // intervalului de cautare (adica punctele in care toate functiile
    // de putere ale serverelor devin crescatoare respectiv descrescatoare)
    fin >> input;
    servers[0].lim = input;
    low = input;
    high = input;

    for (i = 1; i < n; i++) {
        fin >> input;
        servers[i].lim = input;
        /* verificam daca trebuie sa actualizam capetele intervalului 
        de cautare */
        if (input < low) {
            low = input;
        }
        if (input > high) {
            high = input;
        }
    }
    fin.close();

    // afisam rezultatul cu o precizie de o zecimala
    fout << fixed << setprecision(1) << bsearch_pow_sys(servers, n, low, high);
    fout << "\n";
    fout.close();
    return 0;
}
