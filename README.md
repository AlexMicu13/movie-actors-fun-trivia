Micu Alexandru 311CCb
Tema 3 SD - Grafuri

Headere folosite pentru mai multe sau toate cerintele:
    -> Timp de executie: 3 ore
    -> graph.h : Pentru rezolvarea temei trebuie implementat un graf cu liste
                 de adiacenta la care am adaugat un trie modificat pentru
                 sortarea eficienta a numelor actorilor, atribuinndu-le si un
                 id in varful cuvantului din trie (impreuna cu numele lor ca sa
                 nu fie nevoie sa reconstruiesc numele acestora)
    
    -> reading.h : Am avut nevoie sa fac o functie speciala pentru cititul
                   inputului dat astfel incat: citesc numarul de filme si
                   pentru fiecare film citesc numele, numarul de actor si
                   actorii si pentru fiecare actor verific daca este deja in
                   graf sau nu prin intermediul trie-ului si am 2 cazuri:
                   1. Daca este deja in graf ii adaug id-ul in vectorul de
                   id-uri pentru inserarea muchiilor absente
                   2. Daca nu este in graf il adaug si adaug noul id in
                   vectorul de id-uri
                   Dupa ce il adaug pe in vectorul de id-uri verific pentru
                   fiecare id deja adaugat daca exista muchii intre ele si daca
                   nu, adaug muchie intre cei doi actori
    
    -> trie.h : E structura de date preferata de mine pentru stocarea si
                sortarea eficienta a numelelor actorilor oferiind flexibilitate
                din punct de vedere al faptului ca pot sa adaug id-urile si 
                numele complet in nodurile terminale pentru a fii usor de
                manevrat si deja sortate, iar accesarea se face pe modelul
                DFS.

Task1 - Productia maxima
    -> Timp de executie: 1 ora 30 de minute
    -> Am aplicat o cautare in adancime pe graf pentru fiecare componenta 
       conexa, bagam nodurile gasite intr-un pointer si daca se intampla ca
       aceea componenta conexa sa fie cea mai mare pana in acel moment
       inlocuiam vectorul de noduri principal si modificam si marimea maxima.
    -> Pentru afisare cautam printr-o parcurgere in adancime toate id-urile in 
       trie si daca gaseam un id in trie afisam acel nume deoarece aveam
       garantia ca e ordonat lexicografic datoria proprietatilor trie-ului in
       parcurgerea in adancime 

Task2 - Gradul de inrudire
    -> Timp de executie: 30 de minute
    -> Pentru acest task am implementat o parcurgere in latime modificata
       astfel incat sa porneasca de la nodul primului actor citit, sa modifice 
       gradele de rudenie ale vecinilor si asa mai departe pana gasea nodul
       celui de al doilea actor, in momentul in care returnam drumul. Daca
       se golea coada si nu a gasit deja un drum intre cele 2 noduri inseamna
       ca nu sunt in aceeasi componenta, deci nu exista drumuri intre ele si 
       astfel returneaza -1

Task3 - Muchiile critice
    -> Timp de executie: 1 ora
    -> Pentru rezolvarea acestui task am aplicat algoritmul lui Tarjan pentru
       punti care consta in gasirea nodurilor cu timpul de descoperire mai mic
       decat minimul unui alt nod care este legat printr-o muchie de primul dar
       nu este parintele actual al acelui nod
    -> Pentru implementarea acestui algoritm a fost nevoie de o parcurgere in 
       adancime modificata pentru stocarea muchiilor critice (nodurile ordonate
       lexicografic in muchie) pe intregul graf si pentru afisarea in ordine
       alfabetica m-am folosit de functia standard qsort cu functia de 
       comparatie construita astfel incat sa compare primul actor din fiecare 
       muchie si sa returneze rezultatul daca sunt diferiti, iar daca e acelasi
       actor in ambele muchii pe prima pozitie sa compare actorii de pe a doua
       pozitie
