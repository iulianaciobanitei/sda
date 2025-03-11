#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 3  // Nivelul maxim permis

// Structura unui nod din skip list
typedef struct node {
    int value;              // Valoarea nodului
    struct node** forward;  // Array de pointeri catre nodurile de la nivelurile superioare
} Node;

// Structura skip list
typedef struct skiplist {
    int level;      // Nivelul curent al listei
    int max_level;  // Nivelul maxim al listei
    float p;        // Probabilitatea pentru generarea unui nivel suplimentar
    Node* header;   // Nodul header (dummy)
} SkipList;

// Functie pentru crearea unui nod cu un anumit nivel
Node* create_node(int value, int level) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->value = value;
    n->forward = (Node**)malloc((level + 1) * sizeof(Node*));
    for (int i = 0; i <= level; i++) {
        n->forward[i] = NULL;
    }
    return n;
}

// Functie pentru initializarea unei skip list
SkipList* create_skiplist(int max_level, float p) {
    SkipList* list = (SkipList*)malloc(sizeof(SkipList));
    list->level = 0;
    list->max_level = max_level;
    list->p = p;
    // Nodul header are o valoare fictiva (-1) si este alocat la maximul nivelurilor
    list->header = create_node(-1, max_level);
    return list;
}

// Functie pentru generarea unui nivel aleator pentru un nou nod
int random_level(SkipList* list) {
    int level = 0;
    while (((float)rand() / RAND_MAX) < list->p && level < list->max_level) {
        level++;
    }
    return level;
}

// Inserarea unei valori in skip list
void insert(SkipList* list, int value) {
    Node* current = list->header;
    // Array de pointeri pentru actualizarea legaturilor la fiecare nivel
    Node** update = (Node**)malloc((list->max_level + 1) * sizeof(Node*));

    // Parcurgem lista de la nivelul superior pana la nivelul 0
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];

    // Daca valoarea nu exista deja, o inseram
    if (current == NULL || current->value != value) {
        int rlevel = random_level(list);
        // Daca nivelul generat este mai mare decat nivelul curent, actualizam vectorul update
        if (rlevel > list->level) {
            for (int i = list->level + 1; i <= rlevel; i++) {
                update[i] = list->header;
            }
            list->level = rlevel;
        }
        Node* n = create_node(value, rlevel);
        // Re-legam pointerii la toate nivelele pana la rlevel
        for (int i = 0; i <= rlevel; i++) {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
        printf("Inserare: %d\n", value);
    }
    free(update);
}

// Stergerea unei valori din skip list
void delete_node(SkipList* list, int value) {
    Node* current = list->header;
    Node** update = (Node**)malloc((list->max_level + 1) * sizeof(Node*));

    // Parcurgem lista pentru a gasi nodul de sters
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];

    if (current != NULL && current->value == value) {
        // Actualizam legaturile pentru a sari peste nodul ce se sterge
        for (int i = 0; i <= list->level; i++) {
            if (update[i]->forward[i] != current)
                break;
            update[i]->forward[i] = current->forward[i];
        }
        free(current->forward);
        free(current);
        printf("Stergere: %d\n", value);
        // Reducem nivelul listei daca este necesar
        while (list->level > 0 && list->header->forward[list->level] == NULL) {
            list->level--;
        }
    }
    else {
        printf("Valoarea %d nu a fost gasita.\n", value);
    }
    free(update);
}

// Cautarea unei valori in skip list
Node* search(SkipList* list, int value) {
    Node* current = list->header;
    // Parcurgem lista de la nivelul superior pana la nivelul 0
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->value < value) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    if (current && current->value == value) {
        printf("Valoarea %d a fost gasita.\n", value);
        return current;
    }
    printf("Valoarea %d nu a fost gasita.\n", value);
    return NULL;
}

// Afisarea skip list-ului, nivel cu nivel
void display_list(SkipList* list) {
    printf("Skip List:\n");
    for (int i = 0; i <= list->level; i++) {
        Node* node = list->header->forward[i];
        printf("Nivel %d: ", i);
        while (node) {
            printf("%d ", node->value);
            node = node->forward[i];
        }
        printf("\n");
    }
}

// Functia principala de testare
int main() {
    // Initializam generatorul de numere aleatorii
    srand((unsigned)time(NULL));

    // Cream o skip list cu nivel maxim MAX_LEVEL si probabilitate 0.5
    SkipList* list = create_skiplist(MAX_LEVEL, 0.5);

    // Inseram cateva valori
    insert(list, 3);
    insert(list, 6);
    insert(list, 7);
    insert(list, 9);
    insert(list, 12);
    insert(list, 19);
    insert(list, 17);
    insert(list, 26);
    insert(list, 21);
    insert(list, 25);

    // Afisam skip list-ul
    display_list(list);

    // Cautam o valoare
    search(list, 19);

    // Stergem o valoare
    delete_node(list, 19);

    // Afisam lista dupa stergere
    display_list(list);

    return 0;
}