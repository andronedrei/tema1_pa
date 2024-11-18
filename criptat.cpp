#include <bits/stdc++.h>
using namespace std;

#define MAX_TYPES 8

typedef long long int lli;

int nr_found_ch = 0;

template<typename T>
inline void copy_vec(vector<T>& v1, vector<T>& v2, int size) {
    int i;

    for (i = 0; i < size; i++) {
        v1[i] = v2[i];
    }
}

typedef struct letter_data {
    int nr;  // numarul de aparitii ale literei in cuvant
    int len;  // numarul total ce caractere ale cuvantului
    int gain;  // "profitul generat" de cuvant in raport cu litera

    // functie folosita in "problema ghiozdanului"
    int get_weight() {
        return gain * (-1);
    }

    // functie de cost pentru o alegere "lacoma" optima
    void compute_gain() {
        gain = 2 * nr - len;
    }

    void set_data(int nr_ch, int new_len) {
        nr = nr_ch;
        len = new_len;
        compute_gain();
    }

    void set_data_not_found(int new_len) {
        nr = 0;
        len = new_len;
        compute_gain();
    }

    void print_data() {
        cout << nr << "/" << len << " $ => " << gain << " | " << "\n";
    }
} let_d;

// functie folosita pentru a sorta descrescator dupa profit
bool compare_gains_desc(let_d d1, let_d d2) {
    return d1.gain > d2.gain;
}

// aflam dinamic lungimea pentru cuvintele "neprofitabile"
inline lli dinamic_length(vector<let_d>& cur_ch_vec, int ind, lli gain) {
    int i, nr_words = cur_ch_vec.size() - ind;
    int cur_weight, cur_len;
    lli cap;
    // retinem doar ultimele 2 linii pentru eficienta
    vector<vector<lli>> dp(2, vector<lli>(gain + 1, 0));

    // cazurile de baza cu 0 cuvinte
    for (cap = 0; cap <= gain; cap++) {
        dp[0][cap] = 0;
    }

    // primul cuvant: index 1 in dp pe linie si index ind in ch_vec
    for (i = 1; i <= nr_words; i++) {
        for (cap = 0; cap <= gain; cap++) {
            // nu folosesc obiectul i => soluția de la pasul i - 1
            dp[1][cap] = dp[0][cap];

            cur_weight = cur_ch_vec[ind + i - 1].get_weight();
            cur_len = cur_ch_vec[ind + i - 1].len;
            if (cap >= cur_weight) {
                lli sol_aux = dp[0][cap - cur_weight] + cur_len;

                dp[1][cap] = max(dp[1][cap], sol_aux);
            }
        }
        // actualizam ultimele 2 linii
        copy_vec(dp[0], dp[1], gain + 1);
    }

    return dp[0][gain];
}

lli get_greedy_length(vector<let_d>& ch_vec) {
    int ind, len = ch_vec.size();
    lli tot_gain = 0;
    lli tot_len = 0;

    /* calculam in mod "lacom" lungimea cuvantului obtinut
    din cuvintele profitabile pentru caracterul curent */
    for (ind = 0; ind < len && ch_vec[ind].gain >= 0; ind++) {
        tot_gain += ch_vec[ind].gain;
        tot_len += ch_vec[ind].len;
    }

    /* vazul cand nu pot obtine un cuvant cu mai mult de jumatate 
    din litere egale cu litera curenta */
    if (tot_gain <= 0) {
        return 0;
    }

    // daca nu mai am "profit ramas" pentru cuvintele "neprofitabile"
    if (ind == len || tot_gain == 1) {
        return tot_len;
    }

    /* Observam ca putem acum sa tratam problema ghiozdanului. Putem
    considera acum ca avem un ghiozdan cu capacitatea "tot_gain". 
    "Greutatea" unui obiect este inversul campului "gain" (acesta va fi
    negativ pentru elementele ramase), iar "costul" este campul length */
    return tot_len + dinamic_length(ch_vec, ind, tot_gain - 1);
}

inline void set_zero(int* v, int size) {
    for (int i = 0; i < size; i++) {
        v[i] = 0;
    }
}

/* functie folosita ca sa determinam numarul de aparitii ale fiecarei
litere dintr-un nou cuvant, fara sa cunoastem inca literele */
int get_nr_each(string word, int* nr_each, char* found_ch) {
    int len = word.size();
    bool exists;

    set_zero(nr_each, nr_found_ch);
    for (int i = 0; i < len; i++) {
        exists = false;
        for (int j = 0; j < nr_found_ch; j++) {
            if (word[i] == found_ch[j]) {
                exists = true;
                nr_each[j]++;
            }
        }
        // adaugam in vector noul caracter gasit
        if (exists == false && nr_found_ch < MAX_TYPES) {
            // am gasit o noua litera
            found_ch[nr_found_ch] = word[i];
            nr_each[nr_found_ch] = 1;
            nr_found_ch++;
        }
    }

    // returnam lungimea cuvantului
    return len;
}

// functie folosita dupa ce am determinat toate cele 8 litere
int get_nr_each_ok(string s, int* nr_each, char* found_types) {
    int len = s.size();

    set_zero(nr_each, nr_found_ch);
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < nr_found_ch; j++) {
            if (s[i] == found_types[j]) {
                nr_each[j]++;
            }
        }
    }

    return len;
}

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("criptat.in");
    ofstream fout("criptat.out");

    int i, j, nr_words, word_len;
    char found_types_ch[MAX_TYPES];
    int nr_each_ch[MAX_TYPES];
    // vector cu lungimile celor 8 parole maximale
    lli greedy_lengths[MAX_TYPES];
    string new_word;

    fin >> nr_words;
    // vector cu vectorii datelor unei litere in raport cu un cuvant
    vector<vector<let_d>> gains_table(MAX_TYPES, vector<let_d>(nr_words));

    for (i = 0; i < nr_words; i++) {
        fin >> new_word;

        // aflam numarul de aparitii in noul cuvant ale fiecarui caracter
        if (nr_found_ch < MAX_TYPES) {
            word_len = get_nr_each(new_word, nr_each_ch, found_types_ch);
        } else {
            word_len = get_nr_each_ok(new_word, nr_each_ch, found_types_ch);
        }

        // adaugam in tabela de cost datele gasite
        for (j = 0; j < nr_found_ch; j++) {
            gains_table[j][i].set_data(nr_each_ch[j], word_len);
        }
        /* adaugam in tabela de cost datele pentru caracterele care inca
        nu au fost gasite */
        for (; j < MAX_TYPES; j++) {
            gains_table[j][i].set_data_not_found(word_len);
        }
    }
    fin.close();

    // sortam dupa castigul aferent datele pentru fiecare din cele 8 caractere
    for (i = 0; i < nr_found_ch; i++) {
        sort(gains_table[i].begin(), gains_table[i].end(), compare_gains_desc);

        // aflam lungimea parolei obtinute pentru un caracter
        greedy_lengths[i] = get_greedy_length(gains_table[i]);
    }

    // calculam parola maxima (maximul celor 8 parole)
    word_len = 0;
    for (i = 0; i < nr_found_ch; i++) {
        if (greedy_lengths[i] > word_len) {
            word_len = greedy_lengths[i];
        }
    }
    fout << word_len << "\n";
    fout.close();
    return 0;
}
