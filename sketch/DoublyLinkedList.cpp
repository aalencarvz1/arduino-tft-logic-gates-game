#include "DoublyLinkedList.h"
#include <Arduino.h>  // Dependência do Arduino para gerenciamento de memória

// Construtor que inicializa a lista vazia
DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
}

DoublyLinkedList::~DoublyLinkedList() {
  Node* current = head;
  while (current != nullptr) {
    if (current->data != nullptr) {
      delete current->data;
    }
    if (current->prev != nullptr) {
      delete current->prev;
    }
    current = current->next;      
  }  
  if (head != nullptr) {
    delete head;
  }
  if (tail != nullptr) {
    delete tail;
  }
}


// Método para adicionar um novo nó ao final da lista
void DoublyLinkedList::add(void* newData) {
    Node* newNode = new Node();
    newNode->data = newData;
    newNode->next = nullptr;
    newNode->prev = tail;

    if (tail != nullptr) {
        tail->next = newNode;
    }
    tail = newNode;

    if (head == nullptr) {
        head = newNode;
    }
}

// Método para remover o primeiro nó que contém o ponteiro "data"
void DoublyLinkedList::remove(void* searchData) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == searchData) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }

            delete current;
            return;
        }
        current = current->next;
    }
}

// Método para pesquisar por um nó que contenha o ponteiro "data"
Node* DoublyLinkedList::search(void* searchData) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == searchData) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Método para remover todos os nós e limpar a lista
void DoublyLinkedList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}
