#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

// Estrutura para o nó da lista duplamente encadeada
struct Node {
    void* data;       // Ponteiro genérico para qualquer objeto
    Node* next;       // Ponteiro para o próximo nó
    Node* prev;       // Ponteiro para o nó anterior
};

// Estrutura que gerencia a lista duplamente encadeada
struct DoublyLinkedList {
    Node* head;       // Apontador para o início da lista
    Node* tail;       // Apontador para o final da lista

    DoublyLinkedList();       // Construtor
    ~DoublyLinkedList();

    void add(void* newData);  // Método para adicionar um novo nó ao final
    void remove(void* searchData); // Método para remover o nó que contém o ponteiro
    Node* search(void* searchData); // Método para pesquisar por um ponteiro de dado
    void clear();             // Método para limpar a lista
};

#endif
