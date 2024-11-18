#include <bits/stdc++.h>
using namespace std;

/* definim valoarea numarului de produse pentru
care putem calcula direct, practic un caz de baza */
#define DOESNT_EXISTS -1

// template pentru minimul a trei numere
template<typename T>
inline T min_3(T a, T b, T c) {
    if (a <= b && a <= c) {
        return a;
    }

    if (b <= a && b <= c) {
        return b;
    }

    return c;
}

// template pentru copierea unui vector in alt vector
template<typename T>
void copy_vec(vector<T>& v1, vector<T>& v2, int size) {
    int i;

    for (i = 0; i < size; i++) {
        v1[i] = v2[i];
    }
}

// template pentru eliminarea duplicatelor
template<typename T>
int remove_duplicates(vector<T>& v, int size) {
    int i, j = 0;

    for (i = 0; i < size - 1; i++) {
        if (v[i] != v[i + 1]) {
            v[j] = v[i];
            j++;
        }
    }

    // copiam ultimul element (mereu unic)
    v[j++] = v[size - 1];

    return j;
}

// functie calcul discount 2 produse
inline double dis_for_2(int prod1, int prod2) {
    return prod1 + prod2 - min(prod1, prod2) / 2.0;
}

// functie calcul discount 3 produse
inline double dis_for_3(int prod1, int prod2, int prod3) {
    return prod1 + prod2 + prod3 - min_3(prod1, prod2, prod3);
}

bool compare_prices_asc(double price1, double price2) {
    return price1 < price2;
}

void sort_prices(vector<double>& prices, int nr) {
    auto end = prices.begin() + nr;

    sort(prices.begin(), end, compare_prices_asc);
}

/* functie pentru calculul matricii de preturi posibile (si dimeniunea 
coloanelor) pentru cazurile de baza */
void simple_get_base_offers(vector<int>& pr_v, vector<int>& nr,
                            vector<vector<double>>& dp_all_p, int k, int n) {
    if (n >= 3) {
        dp_all_p[2][0] = dis_for_3(pr_v[0], pr_v[1], pr_v[2]);
        dp_all_p[2][1] = dis_for_2(pr_v[0], pr_v[1]) + pr_v[2];
        dp_all_p[2][2] = pr_v[0] +  dis_for_2(pr_v[1], pr_v[2]);
        dp_all_p[2][3] = pr_v[0] + pr_v[1] + pr_v[2];

        nr[2] = remove_duplicates(dp_all_p[2], 4);
        sort_prices(dp_all_p[2], nr[2]);
        /* returnam minimul deoarece in cazul in care k este mai mic devine 
        redundant sa tinem minte mai multe posibilitati */
        nr[2] = min(k, nr[2]);
    }

    if (n >= 2) {
        dp_all_p[1][0] = dis_for_2(pr_v[0], pr_v[1]);
        dp_all_p[1][1] = pr_v[0] + pr_v[1];

        nr[1] = remove_duplicates(dp_all_p[1], 2);
        nr[1] = min(k, nr[1]);
    }

    if (n >= 1) {
        dp_all_p[0][0] = pr_v[0];

        nr[0] = 1;
        nr[0] = min(k, nr[0]);
    }
}

// pentru cazurile de baza (n <= 3) putem obtine rezultatul direct
double get_simple_case_k_pr(vector<int>& nr, vector<vector<double>>& dp_all_p,
                            int k, int n) {
    if (n == 1) {
        if (k == 1) {
            return dp_all_p[0][0];
        }
    }

    if (n == 2) {
        if (k <= nr[1]) {
            return dp_all_p[1][k - 1];
        }
    }

    if (n == 3) {
        if (k <= nr[2]) {
            return dp_all_p[2][k - 1];
        }
    }

    return 0;
}

/* functie care interclaseaza noile posibilitati de preturi (obtinute 
prin adaugarea elementului cu index "cur") si alege doar primele k 
posibilitati. Mentine astfel vectorii de posibilitati de preturi 
sortati */
inline int interclass_triple_pr(vector<int>& pr, vector<int>& nr,
                                vector<vector<double>>& dp_all_p,
                                vector<double>& aux, int k) {
    int i = 0, j = 0, l = 0, r = 0;
    double pr0, pr1, pr2, min_price;

    // prima oferta noua de 3 cu noul produs
    pr0 = dp_all_p[0][0] + dis_for_3(pr[0], pr[1], pr[2]);
    // prima oferta noua de 2 cu noul produs
    pr1 = dp_all_p[1][0] + dis_for_2(pr[1], pr[2]);
    // prima varianta in care nu se alege nicio oferta
    pr2 = dp_all_p[2][0] + pr[2];

    // interclasam vectorii pana unul dintre ei e epuizat
    while (i < nr[0] && j < nr[1] && l < nr[2]) {
        // aflam cea mai buna oferta formata
        min_price = min_3(pr0, pr1, pr2);

        // calculam noile posibilitai de preturi pe baza iteratiilor precedente
        if (pr0 == min_price) {
            i++;
            // formam o noua oferta de 3
            pr0 = dp_all_p[0][i] + dis_for_3(pr[0], pr[1], pr[2]);
        }
        if (pr1 == min_price) {
            j++;
            // formam o noua oferta de 2
            pr1 = dp_all_p[1][j] + dis_for_2(pr[1], pr[2]);
        }
        if (pr2 == min_price) {
            l++;
            // formam o noua varinata fara oferta
            pr2 = dp_all_p[2][l] + pr[2];
        }

        aux[r] = min_price;
        r++;
        if (r == k) {
            return r;
        }
    }

    // in functie de cei doi vectori ramasi ii interclasam si pe acestia
    while (i < nr[0] && j < nr[1]) {
        min_price = min(pr0, pr1);

        if (pr0 == min_price) {
            i++;
            pr0 = dp_all_p[0][i] + dis_for_3(pr[0], pr[1], pr[2]);
        }
        if (pr1 == min_price) {
            j++;
            pr1 = dp_all_p[1][j] + dis_for_2(pr[1], pr[2]);
        }

        aux[r] = min_price;
        r++;
        if (r == k) {
            return r;
        }
    }

    while (i < nr[0] && l < nr[2]) {
        min_price = min(pr0, pr2);

        if (pr0 == min_price) {
            i++;
            pr0 = dp_all_p[0][i] + dis_for_3(pr[0], pr[1], pr[2]);
        }
        if (pr2 == min_price) {
            l++;
            pr2 = dp_all_p[2][l] + pr[2];
        }

        aux[r] = min_price;
        r++;
        if (r == k) {
            return r;
        }
    }

    while (j < nr[1] && l < nr[2]) {
       min_price = min(pr1, pr2);

        if (pr1 == min_price) {
            j++;
            pr1 = dp_all_p[1][j] + dis_for_2(pr[1], pr[2]);
        }
        if (pr2 == min_price) {
            l++;
            pr2 = dp_all_p[2][l] + pr[2];
        }

        aux[r] = min_price;
        r++;
        if (r == k) {
            return r;
        }
    }

    /* in cazul in care nu s-a atins dimensiunea "k" adaugam la vectorul 
    construit ofertele ramase */
    for (i; i < nr[0]; i++) {
        aux[r] = dp_all_p[0][i] + dis_for_3(pr[0], pr[1], pr[2]);
        r++;
    }
    for (j; j < nr[1]; j++) {
        aux[r] = dp_all_p[1][j] + dis_for_2(pr[1], pr[2]);
        r++;
    }
    for (l; l < nr[2]; l++) {
        aux[r] = dp_all_p[2][l] + pr[2];
        r++;
    }

    return min(r, k);
}

/* functie care actualizeaza matricea de posibilitati de oferte si numarul 
relevant al acestora din iteratiile precedente */
void dynamic_all_prices(vector<int>& pr, vector<int>& nr,
                        vector<vector<double>>& dp_all_p,
                        vector<double>& aux, int k) {
    int aux_nr;

    aux_nr = interclass_triple_pr(pr, nr, dp_all_p, aux, k);

    nr[0] = nr[1];
    nr[1] = nr[2];
    nr[2] = aux_nr;

    copy_vec(dp_all_p[0], dp_all_p[1], nr[0]);
    copy_vec(dp_all_p[1], dp_all_p[2], nr[1]);
    copy_vec(dp_all_p[2], aux, nr[2]);
}

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("oferta.in");
    ofstream fout("oferta.out");

    int i, base_case_limit, n, k, new_price;
    double result_found;

    fin >> n;
    fin >> k;
    // vector cu cele 3 preturi de produse relevante pentru pasul curent
    vector<int> prices(3, 0);
    /* vector cu numarul de preturi de oferte relevante din
    ultimele 3 iteratii */
    vector<int> dp_nr(3, 0);
    // matrice cu ofertele relevante din ultimele 3 iteratii
    vector<vector<double>> dp_all_prices(3, vector<double>(max(k, 4) + 1, 0));
    // vector auxiliar in care interclasam
    vector<double> aux_prices(3 * max(k, 4) + 1, 0);

    base_case_limit = min(n, 3);
    for (i = 0; i < base_case_limit; i++) {
        fin >> prices[i];
    }
    // calculam cazurile de baza
    simple_get_base_offers(prices, dp_nr, dp_all_prices, k, n);
    result_found = get_simple_case_k_pr(dp_nr, dp_all_prices, k, n);

    for (i; i < n; i++) {
        fin >> new_price;
        // actualizam preturile relevante
        prices[0] = prices[1];
        prices[1] = prices[2];
        prices[2] = new_price;
        dynamic_all_prices(prices, dp_nr, dp_all_prices, aux_prices, k);
    }
    fin.close();

    // verificam daca am obtinut rezultatul dintr-un caz de baza
    if (result_found == 0) {
        if (dp_nr[2] >= k) {
            result_found = dp_all_prices[2][k - 1];
        } else {
            result_found = -1;
        }
    }

    fout << fixed << setprecision(1) << result_found << "\n";
    fout.close();
    return 0;
}
