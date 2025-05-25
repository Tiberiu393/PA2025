#include "tema.h"

coada *creare_coada()
{
    coada *c = (coada *)malloc(sizeof(coada));
    if (c == NULL)
    {
        printf("Eroare la alocarea memoriei pentru coada\n");
        exit(1);
    }
    c->front = c->rear = NULL;
    return c;
}

void enq(coada *q, participant *p)
{
    nod *nod_nou = (nod *)malloc(sizeof(nod));
    if (nod_nou == NULL)
    {
        printf("Eroare la alocarea nodului\n");
        exit(1);
    }
    nod_nou->date = p;
    nod_nou->next = NULL;
    if (q->rear == NULL)
    {
        q->front = q->rear = nod_nou;
        return;
    }
    q->rear->next = nod_nou;
    q->rear = nod_nou;
}

participant *creare_participant(char *linie)
{
    participant *p = (participant *)malloc(sizeof(participant));
    if (p == NULL)
    {
        printf("Eroare la alocarea participantului\n");
        exit(1);
    }
    char *stat = strtok(linie, " ");
    char *nume = strtok(NULL, ";");
    char *experienta = strtok(NULL, ";");
    char *varsta = strtok(NULL, "\n");
    if (stat == NULL || nume == NULL || experienta == NULL || varsta == NULL)
    {
        printf("Eroare la citirea participantului\n");
        exit(1);
    }

    p->nume = (char *)malloc(strlen(nume) + 1);
    if (p->nume == NULL)
    {
        printf("Eroare la alocarea memoriei pentru nume\n");
        exit(1);
    }
    p->nume = strcpy(p->nume, nume);
    p->varsta = atoi(varsta);
    p->experienta = atof(experienta);
    for (int i = 0; i < strlen(stat); i++)
    {
        stat[i] = tolower(stat[i]);
    }
    if (strcmp(stat, "lord") == 0)
    {
        p->statut = LORD;
    }
    else if (strcmp(stat, "cavaler") == 0)
    {
        p->statut = CAVALER;
    }
    else if (strcmp(stat, "aventurier") == 0)
    {
        p->statut = AVENTURIER;
    }
    else
    {
        printf("Statut invalid: %s\n", stat);
        return NULL;
    }
    return p;
}
void citire_fisier(coada *q)
{
    FILE *f = fopen("Pas_1/candidati.csv", "r");
    if (f == NULL)
    {
        printf("Eroare la deschiderea fisierului \n");
        exit(1);
    }
    char linie[125];
    fgets(linie, sizeof(linie), f); // vreau sa citesc prima linie din fisier;
    while (fgets(linie, sizeof(linie), f) != NULL)
    {
        participant *p = creare_participant(linie);
        if (p != NULL)
        {
            enq(q, p);
        }
    }

    fclose(f);
}

void scriere_fisier_test1(coada *q)
{
    FILE *f = fopen("Pas_1/test_1.csv", "w");
    if (f == NULL)
    {
        printf("EROARE LA DESCHIDEREA FISIERULUI \n");
        exit(1);
    }
    fprintf(f, "Nume Experienta Varsta Statut_social\n");
    nod *curent = q->front;
    while (curent != NULL)
    {
        for (int i = 0; i < strlen(curent->date->nume); i++)
        {
            curent->date->nume[i] = tolower(curent->date->nume[i]);
        }
        curent->date->nume[0] = toupper(curent->date->nume[0]);
        for (int i = 1; i < strlen(curent->date->nume); i++)
        {
            if (curent->date->nume[i] == ' ')
            {
                curent->date->nume[i] = '-';

                if (curent->date->nume[i + 1] != '\0')
                    curent->date->nume[i + 1] = toupper(curent->date->nume[i + 1]);
            }
        }
        fprintf(f, "%s %.2f %d ", curent->date->nume, curent->date->experienta, curent->date->varsta);
        if (curent->date->statut == LORD)
        {
            fprintf(f, "LORD\n");
        }
        if (curent->date->statut == CAVALER)
        {
            fprintf(f, "CAVALER\n");
        }
        if (curent->date->statut == AVENTURIER)
        {
            fprintf(f, "AVENTURIER\n");
        }
        curent = curent->next;
    }
    fclose(f);
}
void eliberare_mem(coada *q)
{
    nod *temp = q->front;
    while (temp != NULL)
    {
        nod *next = temp->next;
        free(temp->date->nume);
        free(temp->date);
        free(temp);
        temp = next;
    }
    free(q);
}
// pentru pas 2

node *creere_nodbs(participant *p)
{
    node *nou = malloc(sizeof(node));
    if (!nou)
    {
        perror("Eroare la alocare nod");
        exit(1);
    }

    participant *copie = malloc(sizeof(participant));
    if (!copie)
    {
        perror("Eroare la alocare participant");
        exit(1);
    }

    copie->nume = strdup(p->nume); // Copie adâncă
    copie->varsta = p->varsta;
    copie->experienta = p->experienta;
    copie->statut = p->statut;

    nou->date = copie;
    nou->stanga = nou->dreapta = NULL;

    return nou;
}

node *inserare_bst(node *root, participant *p)
{
    if (root == NULL)
    {
        return creere_nodbs(p); // deja face deep copy
    }

    if (p->experienta < root->date->experienta)
    {
        root->stanga = inserare_bst(root->stanga, p);
    }
    else
    {
        root->dreapta = inserare_bst(root->dreapta, p);
    }

    return root;
}

void stergere_din_coada(coada *q)
{
    if (q->front == NULL)
        return;

    nod *temp = q->front;

    // ELIBERĂM STRUCTURA PARTICIPANT ÎNTÂI
    if (temp->date != NULL)
        free(temp->date->nume);
    free(temp->date);

    if (q->front == q->rear)
    {
        q->front = q->rear = NULL;
    }
    else
    {
        q->front = q->front->next;
    }

    free(temp);
}

void construire_bsturi(coada *q, node **root_lorzi, node **root_cav_av)
{
    while (q->front != NULL)
    {
        participant *p = q->front->date;
        if (p->statut == LORD)
            *root_lorzi = inserare_bst(*root_lorzi, p);
        else
            *root_cav_av = inserare_bst(*root_cav_av, p);

        stergere_din_coada(q);
    }
}

void eliberare_mem_bst(node *root)
{
    if (root == NULL)
        return;
    eliberare_mem_bst(root->stanga);
    eliberare_mem_bst(root->dreapta);
    free(root->date->nume);
    free(root->date);
    free(root);
}
void parcurgere_lord(node *root, FILE *f)
{
    if (root == NULL)
        return;
    parcurgere_lord(root->dreapta, f);
    fprintf(f, "%s %.2f %d LORD\n", root->date->nume, root->date->experienta, root->date->varsta);
    parcurgere_lord(root->stanga, f);
}
void scriere_fis2_lorzi(node *root)
{
    FILE *f = fopen("Pas_2/test_2_lorzi.csv", "w");
    if (f == NULL)
    {
        printf("Eroare la incercarea de deschidere a fisierului\n");
        exit(1);
    }
    fprintf(f, "Nume Experienta Varsta Statut_social\n");
    parcurgere_lord(root, f);
    fclose(f);
}
void parcurgere_cav_av(node *root, FILE *f)
{
    if (root == NULL)
        return;
    parcurgere_cav_av(root->dreapta, f);

    if (root->date->statut == CAVALER)
        fprintf(f, "%s %.2f %d CAVALER\n", root->date->nume, root->date->experienta, root->date->varsta);
    if (root->date->statut == AVENTURIER)
        fprintf(f, "%s %.2f %d AVENTURIER\n", root->date->nume, root->date->experienta, root->date->varsta);
    parcurgere_cav_av(root->stanga, f);
}

void scriere_fis2_cav_av(node *root)
{
    FILE *f = fopen("Pas_2/test_2_cavaleri_aventurieri.csv", "w");
    if (f == NULL)
    {
        printf("Eroare la incercarea de deschidere a fisierului\n");
        exit(1);
    }
    fprintf(f, "Nume Experienta Varsta Statut_social\n");
    parcurgere_cav_av(root, f);
    fclose(f);
}

void citire_fisier_3(coada *q)
{
    FILE *f = fopen("Pas_3/contestatii.csv", "r");
    if (f == NULL)
    {
        printf("Eroare la deschiderea acestui fisier\n");
        exit(1);
    }
    char linie[125];
    fgets(linie, sizeof(linie), f);
    while (fgets(linie, sizeof(linie), f) != NULL)
    {
        participant *p = creare_participant(linie);
        if (p != NULL)
        {
            enq(q, p);
        }
    }
    fclose(f);
} // fac o coada cu participantii pe care trb sa ii sterg

node *minValueNode(node *root)
{
    while (root && root->stanga != NULL)
        root = root->stanga;
    return root;
}

node *sterg_nodbst(node *root, participant *p)
{
    if (root == NULL)
        return root;

    if (p->experienta < root->date->experienta)
        root->stanga = sterg_nodbst(root->stanga, p);
    else if (p->experienta > root->date->experienta)
        root->dreapta = sterg_nodbst(root->dreapta, p);
    else
    {
        // Gasit nodul
        if (root->stanga == NULL)
        {
            node *temp = root->dreapta;
            free(root->date->nume);
            free(root->date);
            free(root);
            return temp;
        }
        else if (root->dreapta == NULL)
        {
            node *temp = root->stanga;
            free(root->date->nume);
            free(root->date);
            free(root);
            return temp;
        }

        // Caut succesorul in dreapta
        node *succ = minValueNode(root->dreapta);

        free(root->date->nume);
        root->date->nume = strdup(succ->date->nume);
        root->date->experienta = succ->date->experienta;
        root->date->varsta = succ->date->varsta;
        root->date->statut = succ->date->statut;

        // Stergem succesorul
        root->dreapta = sterg_nodbst(root->dreapta, succ->date);
    }
    return root;
}

void sterg_part(node **root, coada *q)
{
    while (q->front != NULL)
    {
        participant *p;
        p = (participant *)malloc(sizeof(participant));
        if (p == NULL)
        {
            printf("Eroare la alocarea memoriei pentru participant\n");
            exit(1);
        }
        p->statut = q->front->date->statut;
        p->experienta = q->front->date->experienta;
        p->varsta = q->front->date->varsta;
        p->nume = (char *)malloc(strlen(q->front->date->nume) + 1);
        if (p->nume == NULL)
        {
            printf("Eroare la alocarea memoriei pentru nume\n");
            exit(1);
        }
        p->nume = strcpy(p->nume, q->front->date->nume);
        *root = sterg_nodbst(*root, p);
        stergere_din_coada(q);
        free(p->nume);
        free(p);
    }
}

void scriere_fisier_3(node *root)
{
    FILE *f = fopen("Pas_3/test_3_lorzi.csv", "w");
    if (f == NULL)
    {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }
    fprintf(f, "Nume Experienta Varsta Statut_social\n");
    parcurgere_lord(root, f);
    fclose(f);
}

// pas 4
heap *create(int capacitate)
{

    heap *h = (heap *)malloc(sizeof(heap));
    if (h == NULL)
    {
        printf("Eroare la alocarea memoriei necesare pentru heap \n");
        exit(1);
    }
    h->dim = 0;
    h->capacitate = capacitate;
    h->date = (part_cu_traseu *)malloc(capacitate * sizeof(part_cu_traseu));
    if (h->date == NULL)
    {
        printf("Eroare la alocarea memoriei");
        exit(1);
    }

    return h;
}

void resize(heap *h)
{
    h->capacitate *= 2;
    part_cu_traseu *v = (part_cu_traseu *)realloc(h->date, h->capacitate * sizeof(part_cu_traseu));
    if (v == NULL)
    {
        printf("Eroare la realocarea memoriei\n");
        h->capacitate /= 2;
        exit(1);
    }
    else
    {
        h->date = v;
    }
}

void inserare_heap(heap *h, part_cu_traseu *p)
{
    int i = h->dim;
    if (h->dim == h->capacitate)
    {
        resize(h);
    }

    // Alocă memorie direct în structura heap
    h->date[i].p = (participant *)malloc(sizeof(participant));
    if (h->date[i].p == NULL)
        exit(1);
    h->date[i].p->nume = strdup(p->p->nume);
    if (h->date[i].p->nume == NULL)
        exit(1);
    h->date[i].p->experienta = p->p->experienta;
    h->date[i].p->varsta = p->p->varsta;
    h->date[i].p->statut = p->p->statut;

    h->date[i].t = (traseu *)malloc(sizeof(traseu));
    if (h->date[i].t == NULL)
        exit(1);
    strcpy(h->date[i].t->nume, p->t->nume);
    h->date[i].t->nr_paduri = p->t->nr_paduri;
    for (int j = 0; j < h->date[i].t->nr_paduri; j++)
    {
        h->date[i].t->paduri[j] = p->t->paduri[j];
    }

    h->dim++;
    while (i > 0 && h->date[i].p->experienta > h->date[(i - 1) / 2].p->experienta)
    {

        part_cu_traseu temp = h->date[i];
        h->date[i] = h->date[(i - 1) / 2];
        h->date[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

void citeste_traseu(traseu trasee[], int *nr_trasee)
{
    FILE *f = fopen("Pas_4/trasee.csv", "r");
    if (f == NULL)
    {
        printf("Eroare la citirea din fisier");
        exit(1);
    }
    char linie[100];
    *nr_trasee = 0;
    while (fgets(linie, sizeof(linie), f) != NULL)
    {
        linie[strcspn(linie, "\n")] = 0; // eliminam newline-ul
        char *token = strtok(linie, ":");
        if (!token)
            continue;
        strncpy(trasee[*nr_trasee].nume, token, sizeof(trasee[*nr_trasee].nume));
        token = strtok(NULL, ";");
        trasee[*nr_trasee].nr_paduri = 0;
        char *p = strtok(token, " ");
        while (p != NULL && trasee[*nr_trasee].nr_paduri < 10)
        {
            trasee[*nr_trasee].paduri[trasee[*nr_trasee].nr_paduri++] = atoi(p);
            p = strtok(NULL, " ");
        }
        (*nr_trasee)++;
    }
    fclose(f);
}

node *max_din_bst(node *root)
{
    if (root == NULL)
        return NULL;
    while (root && root->dreapta != NULL)
        root = root->dreapta;
    return root;
}

participant *copie_participant(participant *src)
{
    participant *dst = (participant *)malloc(sizeof(participant));
    if (!dst)
    {
        exit(1);
    }
    dst->nume = strdup(src->nume);
    dst->experienta = src->experienta;
    dst->varsta = src->varsta;
    dst->statut = src->statut;
    return dst;
}

void scriere_fisier4(heap *h)
{
    FILE *f = fopen("Pas_4/test_4.csv", "w");
    if (f == NULL)
    {
        printf("Eroare la deschiderea fisierului");
        exit(1);
    }
    fprintf(f, "Nume_Traseu - Nume_Participant (Experienta_participant)\n");
    int i;
    for (i = 0; i < h->dim; i++)
    {
        if (h->date[i].p == NULL)
        {
            printf("Eroare: h->date[%d].p este NULL\n", i);
            continue;
        }
        char *name = h->date[i].p->nume;
        if (h->date[i].p->nume == NULL)
        {
            printf("Eroare: h->date[%d].p->nume este NULL\n", i);
            continue;
        }
        char a[100];
        strcpy(a, name);
        for (int j = 0; a[j]; j++)
        {
            if (a[j] == ' ')
                a[j] = '-';
        }

        // punem prima literă cu majusculă și literele după cratimă
        a[0] = toupper(a[0]);
        for (int j = 1; a[j]; j++)
        {
            if (a[j - 1] == '-')
                a[j] = toupper(a[j]);
            else
                a[j] = tolower(a[j]);
        }
        fprintf(f, "%s - %s (%.2f)\n", h->date[i].t->nume, a, h->date[i].p->experienta);
    }

    fclose(f);
}
int index1 = 0;
int index2 = 0;
participant vector_lorzi[18];    // Vector global pentru a stoca participanții
participant vector_cavaleri[33]; // Vector global pentru a stoca participanții

void parcurgerein(node *root)
{
    if (root == NULL)
        return;

    parcurgerein(root->dreapta);

    if (root->date != NULL && index1 < 100)
    {
        vector_lorzi[index1].varsta = root->date->varsta;
        vector_lorzi[index1].experienta = root->date->experienta;
        vector_lorzi[index1].statut = root->date->statut;

        vector_lorzi[index1].nume = malloc(strlen(root->date->nume) + 1);
        strcpy(vector_lorzi[index1].nume, root->date->nume);

        index1++;
    }

    parcurgerein(root->stanga);
}

void bst_to_vector_simplu(node *root)
{
    index1 = 0; // Reseteaza indexul
    parcurgerein(root);
}
void scriere_vect()
{
    for (int i = 0; i < index1; i++)
    {
        printf("%s %.2f %d\n", vector_lorzi[i].nume, vector_lorzi[i].experienta, vector_lorzi[i].varsta);
    }
}
void parcurgerein_cav(node *root)
{
    if (root == NULL)
        return;
    parcurgerein_cav(root->dreapta);
    if (root->date != NULL && index2 < 100)
    {
        vector_cavaleri[index2].varsta = root->date->varsta;
        vector_cavaleri[index2].experienta = root->date->experienta;
        vector_cavaleri[index2].statut = root->date->statut;

        vector_cavaleri[index2].nume = malloc(strlen(root->date->nume) + 1);
        strcpy(vector_cavaleri[index2].nume, root->date->nume);

        index2++;
    }
    parcurgerein_cav(root->stanga);
    //  parcurgerein_cav(root->dreapta);
}
void scriere_vect_cav()
{
    for (int i = 0; i < index2; i++)
    {
        printf("%s %.2f %d\n", vector_cavaleri[i].nume, vector_cavaleri[i].experienta, vector_cavaleri[i].varsta);
    }
}
void bst_to_vector_cav(node *root)
{
    index2 = 0; // Reseteaza indexul
    parcurgerein_cav(root);
}

void filtrare_part(participant vector_lorzi[], participant vector_cavaleri[], int index1, int index2, traseu trasee[], int nr_trasee, heap *h)
{
    int lord_nr = 0;
    int cavaler_nr = 0;
    int traseu_nr = 0;
    int lord_ad = 0;
    int cavaler_ad = 0;
    while ((lord_ad < 4) || (cavaler_ad < 4))
    {
        if ((lord_ad < 4 || lord_nr < 4) && traseu_nr < nr_trasee)
        {
            part_cu_traseu *pt = (part_cu_traseu *)malloc(sizeof(part_cu_traseu));
            if (pt == NULL)
            {
                printf("Eroare la alocarea memoriei pentru part_cu_traseu\n");
                exit(1);
            }
            pt->p = copie_participant(&vector_lorzi[lord_nr]);
            pt->t = &trasee[traseu_nr++];
            inserare_heap(h, pt);
            printf("Traseu: %s, Participant: %s, Experienta: %.2f\n", pt->t->nume, pt->p->nume, pt->p->experienta);
            free(pt->p->nume);
            free(pt->p);
            free(pt);
            lord_ad++;
            lord_nr++;
        }
        if ((cavaler_ad < 4 || cavaler_nr < 4) && traseu_nr < nr_trasee)
        {
            part_cu_traseu *pt = (part_cu_traseu *)malloc(sizeof(part_cu_traseu));
            if (pt == NULL)
            {
                printf("Eroare la alocarea memoriei pentru part_cu_traseu\n");
                exit(1);
            }
            pt->p = copie_participant(&vector_cavaleri[cavaler_nr]);
            pt->t = &trasee[traseu_nr++];
            inserare_heap(h, pt);
            printf("Traseu: %s, Participant: %s, Experienta: %.2f\n", pt->t->nume, pt->p->nume, pt->p->experienta);
            free(pt->p->nume);
            free(pt->p);
            free(pt);
            cavaler_ad++;
            cavaler_nr++;
        }
        if ((lord_ad < 4 && lord_nr >= 18 && cavaler_ad < 4) ||
            (cavaler_ad < 4 && cavaler_nr >= 33 && lord_ad < 4))
        {
            if (traseu_nr < nr_trasee)
            {
                traseu_nr++;
            }
        }
    }
}
void eliberare_heap(heap *h)
{
    if (h == NULL)
    {
        return;
    }
    if (h->date != NULL)
    {
        for (int i = 0; i < h->dim; i++)
        {
            if (h->date[i].p != NULL)
            {
                if (h->date[i].p->nume != NULL)
                {
                    free(h->date[i].p->nume);
                }
                free(h->date[i].p);
            }
            if (h->date[i].t != NULL)
            {
                free(h->date[i].t);
            }
        }
        free(h->date);
    }
    free(h);
}

void eliberare_mem_vector_cavaleri(participant vector_cavaleri[], int nr_cavaleri)
{
    for (int i = 0; i < nr_cavaleri; i++)
    {
        if (vector_cavaleri[i].nume != NULL)
        {
            free(vector_cavaleri[i].nume);
            vector_cavaleri[i].nume = NULL;
        }
    }
}
void eliberare_vectl(participant vector_lorzi[], int nr_lorzi)
{
    for (int i = 0; i < nr_lorzi; i++)
    {
        if (vector_lorzi[i].nume != NULL)
        {
            free(vector_lorzi[i].nume);
            vector_lorzi[i].nume = NULL;
        }
    }
}
// pas 5
int left_child(heap *h, int i)
{
    int poz = 2 * i + 1;
    if (poz > h->dim - 1 || i < 0)
        return -1; // practic nu are copil stang

    return poz;
}
int right_child(heap *h, int i)
{
    int poz = 2 * i + 2;
    if (poz > h->dim - 1 || i < 0)
        return -1;

    return poz;
}
void heapify_down(heap *h, int i)
{
    int l, r, max = i;
    l = left_child(h, i);
    r = right_child(h, i);
    if (l == -1 && r == -1)
        return;
    if (l != -1 && h->date[l].p->experienta > h->date[max].p->experienta)
        max = l;
    if (r != -1 && h->date[r].p->experienta > h->date[max].p->experienta)
        max = r;
    if (max != i)
    {
        part_cu_traseu aux = h->date[i];
        h->date[i] = h->date[max];
        h->date[max] = aux;
        heapify_down(h, max);
    }
}

void recalc_experienta(heap *h)
{
    if (h == NULL)
        return;

    for (int i = 0; i < h->dim; i++)
    {
        int suma_pad = 0;
        for (int j = 0; j < h->date[i].t->nr_paduri; j++)
        {
            suma_pad = suma_pad + h->date[i].t->paduri[j]; // calculez suma parcurcand padurile
        }
        h->date[i].p->experienta = h->date[i].p->experienta + suma_pad; // actualizez experienta
    }
    for (int i = h->dim / 2 - 1; i >= 0; i--)
    {
        heapify_down(h, i);
    }
}
void scriere_fisier5(heap *h)
{
    FILE *f = fopen("Pas_5/test_5.csv", "w");
    if (f == NULL)
    {
        printf("Eroare la deschiderea fisierului");
        exit(1);
    }
    fprintf(f, "Nume_Traseu - Nume_Participant (Experienta_participant)\n");
    int i;
    for (i = 0; i < h->dim; i++)
    {
        if (h->date[i].p == NULL)
        {
            printf("Eroare: h->date[%d].p este NULL\n", i);
            continue;
        }
        char *name = h->date[i].p->nume;
        if (h->date[i].p->nume == NULL)
        {
            printf("Eroare: h->date[%d].p->nume este NULL\n", i);
            continue;
        }
        char a[100];
        strcpy(a, name);
        for (int j = 0; a[j]; j++)
        {
            if (a[j] == ' ')
                a[j] = '-';
        }

        // punem prima literă cu majusculă și literele după cratimă
        a[0] = toupper(a[0]);
        for (int j = 1; a[j] != '\0'; j++)
        {
            if (a[j - 1] == '-')
                a[j] = toupper(a[j]);
            else
                a[j] = tolower(a[j]);
        }
        fprintf(f, "%s - %s (%.2f)\n", h->date[i].t->nume, a, h->date[i].p->experienta);
    }

    fclose(f);
}

void scriere_fisier6(heap *h)
{
    FILE *f = fopen("Pas_6/test_6.csv", "w");
    if (f == NULL)
    {
        printf("Nu se poate deschide fisierul");
        exit(1);
    }
    fprintf(f, "Nume Experienta_totala\n");
    int i;
    for (i = 0; i < 3; i++)
    {
        part_cu_traseu max = h->date[0];
        if (max.p == NULL)
        {
            printf("Eroare: h->date[%d].p este NULL\n", i);
            continue;
        }
        char *name = max.p->nume;
        if (max.p->nume == NULL)
        {
            printf("Eroare: \n");
            continue;
        }
        char a[100];
        strcpy(a, name);

        // punem prima literă cu majusculă și literele după cratimă
        a[0] = toupper(a[0]);
        for (int j = 1; a[j]; j++)
        {
            if (a[j - 1] == '-')
                a[j] = toupper(a[j]);
            else
                a[j] = tolower(a[j]);
        }
        fprintf(f, "%s %.2f\n", max.p->nume, max.p->experienta);
        h->date[0] = h->date[h->dim - 1];
        h->dim--;
        heapify_down(h, 0);
        free(max.p->nume);
        free(max.p);
        free(max.t);
    }

    fclose(f);
}

// pas 7
void adaugare_lista(graf *g, int iesire, int intrare)
{
    nod_lista *new = (nod_lista *)malloc(sizeof(nod_lista));
    if (new == NULL)
    {
        printf("EROARE LA ALOCARE");
        exit(1);
    }
    new->varf_nr = intrare;
    new->next = NULL;
    if (g->a[iesire] == NULL)
    {
        g->a[iesire] = new;
    }
    else
    {
        nod_lista *temp = g->a[iesire];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new;
    }
    g->E++;
}
graf *creare_graf()
{
    FILE *f = fopen("Pas_7/drumuri.csv", "r");
    if (f == NULL)
    {
        printf("Fisierul drumuri.csv nu se poate deschide\n");
        return NULL;
    }

    graf *g = (graf *)malloc(sizeof(graf));
    if (g == NULL)
    {
        printf("Nu s-a putut aloca memoria pentru graf\n");
        fclose(f);
        return NULL;
    }
    g->V = 11; // Setez direct numarul de varfuri
    g->E = 0;
    g->grade_intrare = (int *)calloc(g->V, sizeof(int));
    if (g->grade_intrare == NULL)
    {
        printf("Eroare la alocare");
        exit(1);
    }

    g->grade_iesire = (int *)calloc(g->V, sizeof(int));
    if (g->grade_iesire == NULL)
    {
        printf("Eroare la alocare");
        exit(1);
    }
    g->a = (nod_lista **)malloc(g->V * sizeof(nod_lista *));
    if (g->a == NULL)
    {
        printf("Eroare la alocarea memoriei pentru lista de adiacenta\n");
        free(g);
        fclose(f);
        return NULL;
    }
    for (int i = 0; i < g->V; i++)
    {
        g->a[i] = NULL;
    }

    int iesire, intrare;
    while (fscanf(f, "%d %d", &iesire, &intrare) == 2)
    {
        adaugare_lista(g, iesire, intrare);
        g->grade_iesire[iesire]++;
        g->grade_intrare[intrare]++;
    }
    fclose(f);
    return g;
}

void printGraph(graf *g)
{
    for (int i = 0; i < g->V; i++)
    {
        printf("Lista de adiacență pentru nodul %d: ", i);
        nod_lista *p = g->a[i];
        while (p)
        {
            printf("%d -> ", p->varf_nr);
            p = p->next;
        }
        printf("NULL\n");
    }
}

void DFS(graf *g, int curent, int *vizitat, int len, int *traseu, int *finale, int nr_finale, char **rez, int *k)
{
    vizitat[curent] = 1;
    traseu[len++] = curent;
    // ne uitam daca e final
    int e_final = 0;
    for (int i = 0; i < nr_finale; i++)
    {
        if (curent == finale[i])
        {
            e_final = 1;
            break;
        }
    }
    if (e_final)
    {
        char buffer[300] = "";
        char temp[16];
        for (int i = 0; i < len; i++)
        {
            sprintf(temp, "%d", traseu[i]);
            strcat(buffer, temp);
            if (i != len - 1)
                strcat(buffer, " ");
        }
        rez[*k] = strdup(buffer);
        (*k)++;
    }
    // parcurg lista de adiacenta
    nod_lista *p = g->a[curent];
    while (p != NULL)
    {
        if (!vizitat[p->varf_nr])
        {
            DFS(g, p->varf_nr, vizitat, len, traseu, finale, nr_finale, rez, k);
        }
        p = p->next;
    }
    vizitat[curent] = 0; // il debifam pentru alte trasee
}
// caut nodurile de plecare

void sursa_dest(graf *g, int *surse, int *nr_surse, int *destinatii, int *nr_destinatii)
{
    *nr_surse = 0;
    *nr_destinatii = 0;
    for (int i = 0; i < g->V; i++)
    {
        if (g->grade_intrare[i] == 0)
        {
            surse[(*nr_surse)++] = i;
        }
        if (g->grade_iesire[i] == 0)
        {
            destinatii[(*nr_destinatii)++] = i;
        }
    }
}

void generat_trasee(graf *g, int *surse, int nr_surse, int *destinatii, int nr_destinatii, char ***rez, int *k)
{
    int *vizitat = calloc(g->V, sizeof(int));
    int *traseu = calloc(g->V, sizeof(int));
    *rez = malloc(1000 * sizeof(char *));
    *k = 0;
    for (int i = 0; i < nr_surse; i++)
    {
        DFS(g, surse[i], vizitat, 0, traseu, destinatii, nr_destinatii, *rez, k);
    }
    free(vizitat);
    free(traseu);
}

int compare_routes(const char *a, const char *b)
{
    while (*a && *b)
    {
        // Sărim peste spațiile din ambele șiruri
        while (*a == ' ')
            a++;
        while (*b == ' ')
            b++;

        // Luăm un număr din a
        int num1 = 0;
        while (*a >= '0' && *a <= '9')
        {
            num1 = num1 * 10 + (*a - '0');
            a++;
        }

        // Luăm un număr din b
        int num2 = 0;
        while (*b >= '0' && *b <= '9')
        {
            num2 = num2 * 10 + (*b - '0');
            b++;
        }

        // Comparăm numerele
        if (num1 < num2)
            return -1;
        if (num1 > num2)
            return 1;
        // Dacă sunt egale, mergem la următorul
    }

    // Dacă unul a terminat și altul nu, cel mai scurt e mai mic
    if (*a)
        return 1;
    if (*b)
        return -1;

    return 0; // sunt egale
}

// Interclasare pentru mergesort
void interclasare(char **rez, int st, int mij, int dr)
{
    int n1 = mij - st + 1;
    int n2 = dr - mij;

    char **L = malloc(n1 * sizeof(char *));
    char **R = malloc(n2 * sizeof(char *));

    for (int i = 0; i < n1; i++)
        L[i] = rez[st + i];
    for (int i = 0; i < n2; i++)
        R[i] = rez[mij + 1 + i];

    int i = 0, j = 0, k = st;

    while (i < n1 && j < n2)
    {
        if (compare_routes(L[i], R[j]) <= 0)
            rez[k++] = L[i++];
        else
            rez[k++] = R[j++];
    }

    while (i < n1)
        rez[k++] = L[i++];
    while (j < n2)
        rez[k++] = R[j++];

    free(L);
    free(R);
}

// MergeSort pe vector de stringuri
void mergeSort(char **rez, int st, int dr)
{
    if (st < dr)
    {
        int mij = st + (dr - st) / 2;
        mergeSort(rez, st, mij);
        mergeSort(rez, mij + 1, dr);
        interclasare(rez, st, mij, dr);
    }
}
void scrie_trasee_cu_prefix(char **rez, int k, const char *nume_fisier)
{
    FILE *f = fopen(nume_fisier, "w");
    if (!f)
    {
        printf("Eroare la deschiderea fisierului %s\n", nume_fisier);
        return;
    }

    for (int i = 0; i < k; i++)
    {
        fprintf(f, "T%d: %s\n", i + 1, rez[i]);
    }

    fclose(f);
}
void eliberare_graf(graf *g)
{
    if (!g)
        return;

    for (int i = 0; i < g->V; i++)
    {
        nod_lista *p = g->a[i];
        while (p)
        {
            nod_lista *temp = p;
            p = p->next;
            free(temp);
        }
    }

    free(g->a);
    free(g->grade_intrare);
    free(g->grade_iesire);
    free(g);
}
