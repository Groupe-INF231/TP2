
#include <stdio.h>
#include <stdlib.h>

// ===== Liste simplement chaînée =====
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Insertion triée
void insererTrieSimple(Node** head, int val) {
    Node* nouveau = malloc(sizeof(Node));
    nouveau->data = val;
    nouveau->next = NULL;

    if (*head == NULL || val < (*head)->data) {
        nouveau->next = *head;
        *head = nouveau;
        return;
    }

    Node* current = *head;
    while (current->next && current->next->data < val) {
        current = current->next;
    }

    nouveau->next = current->next;
    current->next = nouveau;
}

// Supprimer toutes les occurrences d'un élément
void supprimerOccurrences(Node** head, int val) {
    Node* temp;
    while (*head && (*head)->data == val) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    Node* current = *head;
    while (current && current->next) {
        if (current->next->data == val) {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}

void afficherListe(Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// ===== Liste doublement chaînée =====
typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

void insererTrieDouble(DNode** head, int val) {
    DNode* nouveau = malloc(sizeof(DNode));
    nouveau->data = val;
    nouveau->prev = NULL;
    nouveau->next = NULL;

    if (*head == NULL || val < (*head)->data) {
        nouveau->next = *head;
        if (*head) (*head)->prev = nouveau;
        *head = nouveau;
        return;
    }

    DNode* current = *head;
    while (current->next && current->next->data < val) {
        current = current->next;
    }

    nouveau->next = current->next;
    nouveau->prev = current;

    if (current->next)
        current->next->prev = nouveau;

    current->next = nouveau;
}

void afficherListeDouble(DNode* head) {
    while (head) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// ===== Liste simplement chaînée circulaire =====
typedef struct CNode {
    int data;
    struct CNode* next;
} CNode;

void insererTeteCirculaire(CNode** tail, int val) {
    CNode* nouveau = malloc(sizeof(CNode));
    nouveau->data = val;
    if (*tail == NULL) {
        nouveau->next = nouveau;
        *tail = nouveau;
    } else {
        nouveau->next = (*tail)->next;
        (*tail)->next = nouveau;
    }
}

void insererQueueCirculaire(CNode** tail, int val) {
    insererTeteCirculaire(tail, val);
    *tail = (*tail)->next;
}

void afficherListeCirculaire(CNode* tail) {
    if (!tail) return;
    CNode* courant = tail->next;
    do {
        printf("%d -> ", courant->data);
        courant = courant->next;
    } while (courant != tail->next);
    printf("(retour)\n");
}

// ===== Liste doublement chaînée circulaire =====
typedef struct DCNode {
    int data;
    struct DCNode* prev;
    struct DCNode* next;
} DCNode;

void insererTeteDCC(DCNode** head, int val) {
    DCNode* nouveau = malloc(sizeof(DCNode));
    nouveau->data = val;

    if (*head == NULL) {
        nouveau->next = nouveau;
        nouveau->prev = nouveau;
        *head = nouveau;
    } else {
        DCNode* tail = (*head)->prev;
        nouveau->next = *head;
        nouveau->prev = tail;
        tail->next = nouveau;
        (*head)->prev = nouveau;
        *head = nouveau;
    }
}

void insererQueueDCC(DCNode** head, int val) {
    insererTeteDCC(head, val);
    *head = (*head)->next;
}

void afficherListeDCC(DCNode* head) {
    if (!head) return;
    DCNode* courant = head;
    do {
        printf("%d <-> ", courant->data);
        courant = courant->next;
    } while (courant != head);
    printf("(retour)\n");
}

// ===== main =====
int main() {
    printf("1. Liste simplement chaînée - suppression d'occurrences:\n");
    Node* liste = NULL;
    insererTrieSimple(&liste, 3);
    insererTrieSimple(&liste, 1);
    insererTrieSimple(&liste, 2);
    insererTrieSimple(&liste, 2);
    insererTrieSimple(&liste, 4);
    afficherListe(liste);
    printf("Suppression de 2...\n");
    supprimerOccurrences(&liste, 2);
    afficherListe(liste);

    printf("\n2. Liste doublement chaînée - insertion triée:\n");
    DNode* dListe = NULL;
    insererTrieDouble(&dListe, 10);
    insererTrieDouble(&dListe, 5);
    insererTrieDouble(&dListe, 7);
    insererTrieDouble(&dListe, 12);
    afficherListeDouble(dListe);

    printf("\n3. Liste simplement chaînée circulaire - insertion tête et queue:\n");
    CNode* cListe = NULL;
    insererTeteCirculaire(&cListe, 3);
    insererQueueCirculaire(&cListe, 5);
    insererTeteCirculaire(&cListe, 1);
    afficherListeCirculaire(cListe);

    printf("\n4. Liste doublement chaînée circulaire - insertion tête et queue:\n");
    DCNode* dccListe = NULL;
    insererTeteDCC(&dccListe, 10);
    insererQueueDCC(&dccListe, 20);
    insererTeteDCC(&dccListe, 5);
    afficherListeDCC(dccListe);

    return 0;
}