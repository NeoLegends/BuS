#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stud_type_ {                  /* Struktur des Datensatzes:    */
    int matnum;                              /* Matrikelnummer, Vor-         */
    char vorname[20];                        /* und Nachname sind Eintraege. */
    char nachname[20];                       /* Die Datenbank ist eine       */
    struct stud_type_ *next_student;         /* einfach verkettete Liste     */
} stud_type;

/* Ist die Datenbank leer?      */
bool is_empty(stud_type** liste) {
    return *liste == NULL;
}

/* Einfuegen eines Elementes
 *
 * Bekommt einen Zeiger auf einen Zeiger der auf das 1. Element der Liste zeigt
 * Bekommt MatNr, Vorname und Nachname des Studenten der Eingefügt werden soll
 *
 */
void enqueue(stud_type** studenten_liste, int matnum, char vorname[20], char nachname[20])
{
    /* Deklariere benötigte Variablen */
    /* nein */

    /* Hol Speicher auf dem Heap an für den neuen Listen Eintrag */
    stud_type* type = malloc(sizeof(stud_type));

    /* Befüll den Speicher */
    type->matnum = matnum;
    type->next_student = 0;
    type->next_student = NULL;

    strcpy(type->vorname, vorname);
    strcpy(type->nachname, nachname);

    /* Füg den neuen Eintrag in die Liste ein */
    /* Ist die Liste leer ? */
    /* Sortier den Studenten aufsteigend nach Matrikelnummer ein */

    if (is_empty(studenten_liste)) {
        *studenten_liste = type;
    } else {
        stud_type *curr = *studenten_liste;
        while (curr->next_student != NULL && curr->matnum < matnum) {
            curr = curr->next_student;
        }

        stud_type *next = curr->next_student;
        type->next_student = next;
        curr->next_student = type;
    }
}

/* Löschen eines Elementes.
 *
 * Bekommt einen Zeiger auf einen Zeiger der auf das 1. Element der Liste zeigt
 * Bekommt die MatNr des Studenten der zu löschen ist
 *
 * Gibt 0 für einen Fehler zurück
 * Gibt 1 für Erfolg zurück
 */
int dequeue(stud_type** studenten_liste, int matnum)
{
    /* Deklariere benötigte Variablen */
    /* nein */

    /* Prüfe Randbedingungen */
    /* gibt keine */

    /* Speichere *Adresse* zum Pointer, der das Element hält */
    stud_type** cur = studenten_liste;
    while (*cur != NULL && (*cur)->matnum != matnum) {
        cur = &(*cur)->next_student;
    }

    if (*cur == NULL) {
        return 0; // nicht gefunden
    }

    /* Und raus damit. */
    free(*cur);
    *cur = (*cur)->next_student;

    return 1;
}

/* Auslesen eines Elementes
 *
 * Bekommt zeiger auf den Listenstart
 * Bekommt matnr des Studenten der ausgelesen werden soll
 *
 * Schreibt Vorname und Nachname in vorname und nachname
 */
int get_student(stud_type* studenten_liste, int matnum, char vorname[20], char nachname[20])
{
    stud_type *curr;

    /* Durchmustern der DB */
    curr = studenten_liste;
    while ((curr != NULL) && (curr->matnum < matnum)) {
        curr = curr->next_student;
    }

    if ((curr == NULL) || (curr->matnum != matnum)) {
        /* Rückgabewert: Fehler */
        return 0;
    } else {
       strncpy(vorname, curr->vorname, 20);
       strncpy(nachname, curr->nachname, 20);
        /* Rückgabewert: OK */
       return 1;
   }
}

typedef struct sorted_list_ {
    stud_type* element;
    struct sorted_list_* next;
} sorted_list;

void insert_sorted(sorted_list** head, sorted_list* el, int (*comparator)(stud_type* a, stud_type* b)) {
    while ((*head) != NULL && comparator((*head)->element, el->element) < 0) {
        head = &(*head)->next;
    }

    el->next = *head;
    *head = el;
}

sorted_list* sortier_liste(stud_type** list, int (*comparator)(stud_type* a, stud_type* b)) {
    // O(n^2) but fuck it

    sorted_list* result = NULL;
    stud_type* cur = *list;
    while (cur != NULL) {
        sorted_list* el = malloc(sizeof(sorted_list));
        el->element = cur;
        el->next = NULL;
        insert_sorted(&result, el, comparator);

        cur = cur->next_student;
    }

    return result;
}

int compare_name(stud_type* a, stud_type* b) {
    return strcmp(a->nachname, b->nachname);
}

int compare_surname(stud_type* a, stud_type* b) {
    return strcmp(a->vorname, b->vorname);
}

/* Test der Listenfunktionen  */
int main(void)
{
    /* Initialisierung der Datenbank */
    stud_type *studenten_liste = NULL;
    /* platz für vorname */
    char vorname[20];
    /* platz für nachname */
    char nachname[20];
    /* zeiger für iteration */
    stud_type *curr;

    printf(">>> Fuege neuen Studenten in die Liste ein: Eddard Stark [1234] ...\n");
    enqueue(&studenten_liste, 1234, "Eddard", "Stark");
    printf(">>> Fuege neuen Studenten in die Liste ein: Jon Snow [5678] ...\n");
    enqueue(&studenten_liste, 5678, "Jon", "Snow");
    printf(">>> Fuege neuen Studenten in die Liste ein: Tyrion Lannister [9999] ...\n");
    enqueue(&studenten_liste, 9999, "Tyrion", "Lannister");
    printf(">>> Test, ob die Matrikelnummer 1289 bereits erfasst wurde ...\n");

    if(get_student(studenten_liste, 815, vorname, nachname)) {
        printf("    Matrikelnummer %4i: %s %s\n", 1289, vorname, nachname);
    } else {
        printf("    Matrikelnummer %4i ist unbekannt\n", 1289);
    }

    printf(">>> Fuege neuen Studenten in die Liste ein: Daenerys Targaryen [1289] ...\n");
    enqueue(&studenten_liste, 1289, "Daenerys", "Targaryen");
    printf(">>> Loesche die Matrikelnummer 1234 ...\n");

    if(dequeue(&studenten_liste, 1234)) {
        printf("    Matrikelnummer %4i geloescht\n", 1234);
    } else {
        printf("    Matrikelnummer %4i war nicht erfasst\n", 1234);
    }

    printf(">>> Test ob die Studentenliste leer ist ...\n");

    if(is_empty(&studenten_liste)) {
        printf("    Die Studentenliste ist leer \n");
    } else {
        printf("    Die Studentenliste ist nicht leer \n");
    }

    printf(">>> Test, ob die Matrikelnummer 5678 bereits erfasst wurde ...\n");

    if(get_student(studenten_liste, 5678, vorname, nachname)) {
        printf("    Matrikelnummer %4i: %s %s\n", 5678, vorname, nachname);
    } else {
        printf("    Matrikelnummer %4i ist unbekannt\n", 5678);
    }

    printf(">>> Loesche die Matrikelnummer 9998 ...\n");

    if(dequeue(&studenten_liste, 9998)) {
        printf("    Matrikelnummer %4i geloescht\n", 9998);
    } else {
        printf("    Matrikelnummer %4i war nicht erfasst\n", 9998);
    }

    printf(">>> Loesche die Matrikelnummer 5678 ...\n");

    if(dequeue(&studenten_liste, 5678)) {
        printf("    Matrikelnummer %4i geloescht\n", 5678);
    } else {
        printf("    Matrikelnummer %4i war nicht erfasst\n", 5678);
    }

    printf(">>> Gebe alle erfassten Studenten aus ...\n");
    curr = studenten_liste;

    while(curr != NULL) {
        printf("    Matrikelnummer %4i: %s %s\n", curr->matnum, curr->vorname, curr->nachname);
        curr = curr->next_student;
    }

    sorted_list* sorted = sortier_liste(&studenten_liste, compare_name);
    printf(">>> Nach Nachname sortiert...\n");
    while (sorted != NULL) {
        stud_type* el = sorted->element;
        printf("    Matrikelnr %4i %s %s\n", el->matnum, el->vorname, el->nachname);
        sorted = sorted->next;
    }

    sorted_list* sorted2 = sortier_liste(&studenten_liste, compare_surname);
    printf(">>> Nach Vorname sortiert...\n");
    while (sorted2 != NULL) {
        stud_type* el = sorted2->element;
        printf("    Matrikelnr %4i %s %s\n", el->matnum, el->vorname, el->nachname);
        sorted2 = sorted2->next;
    }

    return 0;
}
