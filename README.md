## Vânatoarea Regală(tema P.A 2025)

## Structuri de date folosite :
enum statut - folosit pentru definirea stărilor sociale pentru participanți
participant -stochează informațiile de bază pentru fiecare participant la vanatoare
nod - structura unui nod în implementarea cozii
coada - structura care reprezintă coada propriu zis 
node - structura unui nod în BST
traseu -structura care stochează informații despre un traseu de vânătoare
part_cu_traseu- structura care asociază un participant cu un traseu
heap - structura care reprezintă un heap(utilizat ca o coadă cu priorități)
nod_lista - structura care stocheză un nod din lista de adiacență pentru reprezentarea grafului
graf - structura folosită pentru reprezentarea grafului

## Pas 1
   La acest pas a trebuit sa citesc cererile de participare din fisierul cu date de intrare si sa le stochez într-o coadă.
   Am început prin a crea propria biblioteca cu header-ul tema.h si fisierul sursa tema.c unde am scris implementarea tuturor functiilor folosite în acest proiect.În tema.h am creat structurile de date pentru tema. Am folosit următoarele funcții.
   - coada *creare_coada() .Are rolul de a inițializa o coadă.

   - void enq(coada *q, participant *p) . Această funcție adaugă un nou participant p la sfârșitul cozii q.

   - participant *creare_participant(char *linie) . Această funcție creează un participant prin parsarea unei linii citite din fișier.Alocă dinamic memorie pentru o nouă structură participant, folosind malloc.Verifică dacă a reușit alocarea.Folosește funcția strtok pentru a separa linia citită din fișier pe baza delimitatorilor ,respectând formatul precizat în cerință.Extrage statutul social ,numele complet,vârsta și experiența din linie.Alocă dinamic memorie pentru nume , folosind malloc , dimensionând memoria în funcție de lungimea numelui citit plus un spațiu pentru terminatorul null.Copiază numele extras în câmpul nume al structurii folosinf strcpy.Convertește sirul de caractere asociat vârstei cu atoi în int și îl stochează în câmpul vârstă.Convertește șirul de caractere asociat experienței în float folosind atof și îl stochează în câmpul experiență.Procesează șirul de caractere al statutului social: îl transformă în minuscule folosind tolower pentru a asigura o comparație case-insensitive, apoi compară cu șirurile "lord", "cavaler" și "aventurier" folosind strcmp pentru a atribui valoarea corespunzătoare câmpului statut din enumerația statut. Dacă statutul citit nu corespunde niciunei valori valide, se afișează o eroare și funcția returnează NULL.Returnează pointerul către structura participant nou creată și populată.
   - void citire_fisier(coada *q) . Această funcție citește datele candidaților din fișier și le bagă în coadă.

   - void scriere_fisier_test1(coada *q) . Această funcție scrie datele în fișier în formatul cerut.

   - void eliberare_mem(coada *q) . Această funcție elibereaza memoria cozii.

   ## Pas 2
   La acest pas a trebuit să preiau candidații stocați în coadă și să-i organizez în două BST-uri: unul pentru lorzi și unul pentru cavaleri și aventurieri.Inserarea în BST s-a facut pe baza experienței astfel încât arborii să fie ordonați.La final am scris conținutul în 2 fișiere , după cum a fost cerut.Am folosit următoarele funcții:

   - node *creere_nodbs(participant *p). Această funcție creează un nou nod pentru BST și efectuează o copie profundă a datelor participantului.Alocă dinamic memorie pentru o structură de tip node (care reprezintă un nod al BST-ului) folosind malloc.Alocă dinamic memorie pentru o nouă structură participant (copie) pentru a stoca o copie a datelor participantului original (p).Realizează o copie profundă a numelui participantului folosind strdup(p->nume). Astfel, noul nod BST va avea propria sa copie a șirului de caractere pentru nume, evitându-se problemele legate de dealocarea memoriei.Copiază celelalte câmpuri ale participantului (varsta, experienta, statut) în structura copie.Așează pointerul către structura participant copiată (copie) în câmpul date al noului nod BST.Initializează pointerii către subarborele stâng (stanga) și drept (dreapta) ai noului nod la NULL, deoarece este un nod nou inserat.Returnează pointerul către noul nod BST creat.

   - node *inserare_bst(node *root, participant *p) .Această funcție inserează un nou participant (p) în arborele binar de căutare având rădăcina root, menținând proprietatea BST (valorile din subarborele stâng sunt mai mici, iar cele din subarborele drept sunt mai mari decât valoarea nodului curent, în cazul nostru, pe baza experienței).

   - void stergere_din_coada(coada *q) .Această funcție se ocupă de ștergerea din coadă a primului element și eliberează memoria asociată participantului și nodului eliminat.

   - void construire_bsturi(coada *q, node **root_lorzi, node **root_cav_av) .Această funcție procesează fiecare participant din coada (q) și îl inserează în BST-ul corespunzător (lorzi sau cavaleri/aventurieri) și, în final, golește coada.

   - void eliberare_mem_bst(node *root).Această funcție se ocupă de eliberarea memoriei asociată BST-ului.

   - void parcurgere_lord(node *root, FILE *f). Această funcție parcurge recursiv arborele BST al lorzilor și scrie informațiile despre fiecare lord în fișierul specificat (f), în ordine descrescătoare a experienței.Se face o parcurgere inversă DREAPTA-RĂDĂCINĂ-STÂNGA pentru a obține o ordine descrescătoare a experienței.

   - void parcurgere_cav_av(node *root, FILE *f). Această funcție este similara cu parcurgere_lord, doar că o face pentru cavaleri și aventurieri.

   - void scriere_fis2_cav_av(node *root). Această funcție face scrierea datelor cavalerilor și aventurierilor din BST în fișier.

   - void scriere_fis2_lorzi(node *root) . Această funcție se ocupă de scrierea datelor lorzilor din BST în fișier dupa specificațiile din cerință.

  ## Pas 3
   La acest pas a trebuit să citesc lorzii care trebuie eliminați și să-i elimin și din BST-ul lorzilor ,menținând proprietățile acestuia.Am folosit următoarele funcții:
   - void citire_fisier_3(coada *q) . Această funcție se ocupă de citirea din fișier a datelor lorzilor care trebuie eliminați
   
   - node *minValueNode(node *root) - Găsește nodul cu cea mai mică valoare.

   - node *sterg_nodbst(node *root, participant *p)-Această funcție șterge un nod care conține un participant cu experiența specificată (p->experienta) din BST-ul având rădăcina root.Dacă-l găsește: * 0 sau 1 copil- Leagă părintele de copil și șterge nodul.
   * 2 copii: Găsește cel mai mic nod din subarborele drept (succesorul inordine), copiază valoarea acestuia în nodul de șters și apoi șterge succesorul din poziția sa originală. Complexitate : O(log n) -> in medie ,O(n)-> in cel mai rau caz.

   - void sterg_part(node **root, coada *q) . Această funcție procesează fiecare participant din coada de lorzi și apelează funcția sterg_nodbst pentru a-i șterge din BST-ul lorzilor. Complexitate timp: O(k *log n) in medie (k= nr lorzi de sters , n = nr lorzi initial in bst), O ( k * n) in cel mai rau caz. 
   
   - void scriere_fisier_3(node *root) . Această funție a fost folosită pentru a scrie în fișierul necesar pasului 3.

## Pas 4
  La acest pas a trebuit să selectez primii 4 lorzi și primii 4 cavaleri/aventurieri cu cea mai mare experiență din BST-urile anterioare , de a le asigna trasee din fișier și de a stoca aceste informații într-un max-heap ordonat descrecător

 - heap *create(int capacitate) . Creează și inițializează o structură de heap cu o capacitate dată.
 
 - void resize(heap *h). Redimensionează dinamic array-ul de elemente al heap-ului atunci când capacitatea este depășită.
 
 - void inserare_heap(heap *h, part_cu_traseu *p) .Inserează un nou element (p, care conține un participant și un traseu) în heap, menținând proprietatea de max-heap (elementul cu cea mai mare experiență este la rădăcină).

 - void citeste_traseu(traseu trasee[], int *nr_trasee) .Citește informațiile despre trasee din fișierul Pas_4/trasee.csv și le stochează într-un array de structuri traseu.
 
 - void scriere_fisier4(heap *h). Scrie datele din coada cu priorități (heap) în fișierul Pas_4/test_4.csv în formatul specificat.

---   Am ales să declar doi vectori globali si 2 variabile globale pentru că mi s-a părut o metodă rapidă de a avea toți lorzii și toți cavalerii/aventurierii ordonați după experiență.În plus, la început m-am gândit că s-ar putea să am nevoie de toți acești candidați ordonați și în alte părți ale programului, nu doar pentru selecția asta de 8. 
 - void parcurgerein(node *root) , void parcurgere_in_cav(node *root). Traversează recursiv BST-ul. Începe cu subarborele drept (cei cu experiență mai mare), apoi procesează nodul curent, apoi subarborele stâng (cei cu experiență mai mică). Pentru fiecare participant vizitat, alocă memorie pentru numele său și copiază toate datele participantului în vectorul corespunzător. 

 - bst_to_vector_simplu și bst_to_vector_cav: Resetează indexul (index1 sau index2) la 0 și apoi apelează funcția de parcurgere (parcurgerein sau parcurgerein_cav) pentru a popula vectorul cu participanții ordonați descrescător după experiență
 
 - void filtrare_part(participant vector_lorzi[], participant vector_cavaleri[], int index1, int index2, traseu trasee[], int nr_trasee, heap *h).Această funcție selectează primii 4 lorzi și primii 4 cavaleri/aventurieri cu cea mai mare experiență din vectorii creați, le asignează trasee și îi introduce în heap-ul cu priorități.Folosește indici (lord_nr, cavaler_nr, traseu_nr) pentru a urmări câți participanți din fiecare categorie au fost adăugați și care este următorul traseu disponibil.Într-o buclă, alternează extragerea unui lord și a unui cavaler/aventurier din vectorii sortați (începând de la indexul 0, care are cea mai mare experiență).
Pentru fiecare participant selectat, creează o structură part_cu_traseu, copiază informațiile participantului și îi asignează următorul traseu disponibil din lista de trasee. Inserează această structură în heap-ul cu priorități. Bucla continuă până când sunt selectați 4 lorzi și 4 cavaleri/aventurieri sau până când nu mai sunt trasee disponibile. Complexitate : temporala - O(1) deoarece se executa de un nr constant de ori, spatiala :O(1)-nr constant de variabile

##  Pas 5
 La acest pas a trebuit să recalculez experiența fiecărui participant din coada cu priorități prin adăugarea sumei numerelor pădurilor prin care trece fiecare.
 - void heapify_down(heap *h, int i) Această funcție este utilizată pentru restabilirea proprietății de max-heap

 - void recalc_experienta(heap *h) . Această funcție recalculează experiența pentru fiecare participant din heap, apoi reordonează heapul pentru a menține proprietatea de max-heap.Complexitate -Timp: O(h->dim * log h->dim). Pentru un număr mic constant de elemente (<= 8), practic O(1), Spațiu: O(log h->dim). Pentru un număr mic constant de elemente, practic O(1).

##  Pas 6
- void scriere_fisier6(heap *h) . Se ocupă de scrierea în fișier

##  Pas 7
În acest pas, construim un graf orientat care reprezintă pădurile regale și drumurile dintre ele. Apoi, generăm toate traseele posibile care încep dintr-o pădure fără drumuri de intrare (grad de intrare zero) și se termină într-o pădure fără drumuri de ieșire (grad de ieșire zero). Aceste trasee sunt apoi stocate în ordine lexicografică într-un fișier.
  - void adaugare_lista(graf *g, int iesire, int intrare) -Functie pentru adaugarea de elemente in lista de adiacenta, considerand muchiile din fisier
  - graf *creare_graf() - creeaza graful .Calculează gradul de intrare și gradul de ieșire pentru fiecare vârf pe măsură ce citește arcele din fișier.
  - void DFS(graf *g, int curent, int *vizitat, int len, int *traseu, int *finale, int nr_finale, char **rez, int *k). Aceasta functie implementează algoritmul de căutare în adâncime (DFS) pentru a găsi toate traseele de la un nod de start (curent) către oricare dintre nodurile finale specificate în array-ul finale.vizitat = vector pentru a urmări nodurile vizitate în timpul unei parcurgeri pentru a evita ciclurile.  
  rez: Un array de pointeri la șiruri de caractere unde sunt stocate traseele găsite.
  - void sursa_dest(graf *g, int *surse, int *nr_surse, int *destinatii, int *nr_destinatii): Identifică nodurile sursă (cu grad de intrare 0) și nodurile destinație (cu grad de ieșire 0) în graf. Stochează nodurile sursă în array-ul surse și nodurile destinație în array-ul destinatii.
  
  - void generat_trasee(graf *g, int *surse, int nr_surse, int *destinatii, int nr_destinatii, char ***rez, int *k).Inițializează array-urile vizitat și traseu pentru algoritmul DFS.Alocă memorie pentru array-ul de rezultate rez.Iterează prin toate nodurile sursă și apelează funcția DFS pentru a găsi toate traseele către nodurile destinație. 

  - int compare_routes(const char *a, const char *b): O funcție de comparare personalizată pentru a compara două trasee (reprezentate ca șiruri de caractere cu numere separate prin spații) în ordine lexicografică. Compară numerele din trasee, nu caracterele individuale.Practic am construit un numar format din cifrele traseelor, deoarece am dat de o problema cand am incercat cu strcmp,ci la numerele mai mari de 10 se facea gresit comprarea ASCII

  Pentru sortare am folosit merge-sort , deoarece are o complexitate  O(n log n)
