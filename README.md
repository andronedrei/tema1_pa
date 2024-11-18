# Androne Andrei 322CC

# Problema "Servere":
    O expresie de forma f(x) =  A - | x - B | isi atinge maximul A
in punctul x = B. Pentru x < B avem f(x) = A - B + x, adica functie
crescatoare, iar pentru x > B avem f(x) = A + B - x, adica functie
descrescatoare. In cazul nostru pentru x < min(toate pragurile limita)
deducem ca functiile output de putere sunt crescatoare pentru toate
serverele, in timp ce pentru x > max(toate pragurile limita) acestea sunt
descrescatoare. In conluzie minimul maxim se obtine pentru un input x
de putere in intervalul [min(praguri), max(praguri)]. In plus, functia
cautata (minimul maxim pentru outputurile de putere) va fi crescatoare
pana in punctul critic din intervalul de referinta, dupa care va deveni 
descrescatoare. Comparam diferentele intre capetele intervalelor 
(f(min(praguri), f(mijloc))) si (f(mijloc), f(max(praguri))) ca sa
determinam intervalul in care se afla punctul critic, dupa care repetam
procedeul actualizand capetele si spargand in doua noul interval.

    Complexitate spatiala: 
        - O(n) (vectorul de structui care retine datele
serverelor)

    Complexitate temporala: 
        - O(n) - iterarea prin vector necesara calculului
minimului de output de putere pentru cele n servere pentru o putere
x de input
        - O(log(D)) - cautarea binara in interval (D = dimensiune
interval.)
    Total: O(n* log(D)) (iteram la fiecare etapa a cautarii binare)
(daca consideram ca dimensiunea intervalului este proportionala cu
numarul de servere, intrucat mai multe servere <=> sanse mai mari ca
diferenta maxima dintre 2 praguri sa fie mai mare, atunci avem 
O(n * log(n)))

# Problema "Colorare"
    Observam ca numarul de tablouri distincte care se pot realiza
la un anumit pas depinde de numarul total de posibilitati de la
pasul precedent si de tipurile zonelor adiacete. (verticale sau
orizontale).
    Pentru cazul initial avem A(3, 1) = 3 variante la zona 
verticala si A(3, 2) = 6 la o zona orizontala cu 2 "parti" una
peste cealalta. (A = aranjamente). Fie f(x) numarul de
posibilitati de la pasul x. Daca ultima zona a fost orizontala
si noi adaugam o noua zona orizontala, atunci numarul total nou
de posibilitati va fi f(x) * A(3, 2). Analog se analizeaza
celelalte 3 cazuri de tipuri de zone consecutive.
    Pentru bonus se observa ca fiecare succesiune de zone
consecutive de acelasi tip produce un rezultat de forma m * f(x).
Deci dupa k pasi consecutivi obtinem pow(m, k) * f(x), iar puterea
unui numar natural se poate calcula in log(n) folosind "Divide et 
Impera".


    Complexitate spatiala: 
        - O(1) (mentinem doar date legate de
iteratia trecuta si cea curenta)

    Complexitate temporala:
        - O(n) daca k -> n (practic nu prea avem zone consecutive
la fel)
        - O(log(n)) daca k -> 1 (multe grupuri de zone consecutive)
        - In medie: O(k * (log(n/k))) = O(K * log(n)) - O(k * log(k))
~= O(k * log(n))

# Problema "Compresie"
    Pentru a reduce datele retinute, vom folosi doua variabile pe post
de sume partiale in care vom adauga termeni noi in mod "lacom" pentru
a echilibra cat mai bine sumele pana in punctul in care se poate
realiza o compresie favorabila.

    Complexitate spatiala: 
        - O(1) (date legate doar de iteratia curenta
si cea precedenta)

    Complexitate temporala: 
        - O(n + m) (trebuie iterat prin fiecare
vector)

# Problema "Criptat"
    Observam ca problema poate fi sparta in 8 subprobleme identice
pentru cele 8 caractere aparute in cuvinte. Parola ce mai lunga
va fi maximul celor 8 parole obtinute.
    Fie subproblema care trateaza caracterul x. Cuvintele care contin
caracterul x de cel putin jumatate de ori vor fi mereu adaugate la
parola maxima, deoarece cresc lungimea fara sa mareasca
constramgerile. Pentru a ilustra mai bine acest concept folosim o
functie de profit, unde cuvintele cu propietatea de mai sus au
profitul cel putin 0. Dupa adaugarea tuturor cuvintelor profitabile,
tratam problema ghiozdanului pentru a "baga" in ghiozdan cuvintele
cu un anumit cost ( <=> rofit negativ) care dau lungimea cea mai
lunga.

    Complexitate spatiala: 
        O(n) - retinerea datele fiecarei
litere in raport cu fiecare cuvant, adica o matrice 8 x n
        O(n) - matricea dp (2 x gain) 
    Total: O(n)

    Complexitate temporala: 
        - O(n) - partea de citire si pregatire a 
datelor (se fac 8 analize pe L charactere pentru fiecare din cele n
cuvinte, dar 8 x L suficient de mic incat sa consideram ca nu
influenteaza)
        - O(n * log(n)) - sortarea dupa profit a cuvintelor
        - O(n) - alegerea cuvintelor profitabile in mod "lacom"
        - O(n ^ 2) (* intr-un caz in care avem multe cuvinte cu un profit 
mare (n / 2 de exemplu) si multe  cuvinte neprofitabiile ramase pentru 
care trebuie sa facem problema ghiozdanului (n / 2 de exemplu), avem
m * (n / 2) * (n / 2) iteratii in problema ghiozdanului, unde m profitul
mediu al cuvintelor profitabile)
    Total: O(n ^ 2) in (*), iar daca domina cuvintele profitabile pentru
o subproblema, atunci implicit domina cuvintele neprofitabile pentru
celelalte subprobleme si complexitatea temporala devine O(n * log(n)),
intrucat problema ghiozdanului devine minimala.

# Problema "Oferta"
    Observam ca un produs adaugat la pasul x poate influenta cel mult 
produsele adaugate la pasii x - 1 si x - 2. (un discount se aplica pe 
grupuri de maxim 3 produse). Fie f(x) numarul de oferte posibile cu
primele x produse. Asadar:
    - x formeaza o noua oferta unica cu fiecare din cele f(x - 1) 
oferte precedente
    - x si x - 1 pot fi luate separat sau impreuna, formand teoretic
2 noi oferte pentru fiecare din cele f(x - 2) oferte precedente, 
dar cazul in care sunt luate separat se incadreaza in analiza precedenta, 
deci doar f(x - 2) oferte noi
    - analog pentru cazul in care consideram x, x - 1, x - 2, obtinem 
f(x - 3) ofete noi, restul se repeta si sunt redundant de considerat
    In total f(x) = f(x - 1) + f(x - 2) + f(x - 3). Cu toate acestea, noi
vom folosi interclasarea ofertelor precedente pentru a mentine ofertele
calculate ordonate (in complexitate liniara), deci raman relevante decat 
k oferte din cele mentionate. Astfel, numarul de oferte relevante si 
calculate la un pas va fi min(k, f(x - 1) + f(x - 2) + f(x - 3)),
efectuandu-se n pasi.

    Complexitate spatiala:
        - O(k) - (matrice 3 x k de oferte si vector auxiliar 
de lungime 3 * k)

    Complexitate temporala:
        - O(k) - interclasarea
        - O(n) - citirea celor n preturi si efectuarea calculeror
relevante
    Total: O(k * n)
