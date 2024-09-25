#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <MemoryUsage.h>  // Inclui a biblioteca MemoryUsage

template <typename T>
struct Node {
    T* data;        // Ponteiro para o objeto do tipo T
    Node<T>* next;  // Ponteiro para o próximo nó
    Node<T>* prev;  // Ponteiro para o nó anterior
};

template <typename T>
class DoubleLinkedList {
  public:
    Node<T>* head;
    Node<T>* tail;
    DoubleLinkedList() : 
      head(nullptr), tail(nullptr) 
    {
      Serial.println("INIT DoubleLinkedList<T>::DoubleLinkedList");
      Serial.println("END DoubleLinkedList<T>::DoubleLinkedList");
    }

    ~DoubleLinkedList() {
      Serial.println("INIT DoubleLinkedList<T>::~DoubleLinkedList");
      clear();  // Remove todos os nós e libera memória
      Serial.println("END DoubleLinkedList<T>::~DoubleLinkedList");
    }

    void add(T* data) {
      Serial.println("INIT DoubleLinkedList<T>::add");
      FREERAM_PRINT; 
      Node<T>* newNode = new Node<T>();
      Serial.println("oky0");
      newNode->data = data;      
      newNode->next = nullptr;
      newNode->prev = tail;
      Serial.println("oky1");

      if (tail != nullptr) {
          tail->next = newNode;
      }
      Serial.println("oky2");
      tail = newNode;
  
      if (head == nullptr) {
          head = newNode;
      }
      Serial.println("END DoubleLinkedList<T>::add");
    }

    void remove(T* data) {
      Serial.println("INIT DoubleLinkedList<T>::remove");
      Node<T>* current = head;

      while (current != nullptr) {
          if (current->data == data) {
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

              delete current->data;  // Chama o destrutor do objeto armazenado
              delete current;        // Libera o nó
              if (current == tail) {
                tail = nullptr;
              } 
              if (current == head) {
                head = nullptr;
              }
              return;
          }
          current = current->next;
      }
      Serial.println("END DoubleLinkedList<T>::remove");
    }

    void clear() {
      Serial.println("INIT DoubleLinkedList<T>::clear");
      Node<T>* current = head;

      while (current != nullptr) {
          Node<T>* nextNode = current->next;
          delete current->data;  // Chama o destrutor do objeto
          delete current;        // Libera o nó
          current = nextNode;
      }
      head = nullptr;
      tail = nullptr;
      Serial.println("END DoubleLinkedList<T>::clear");
    }    
};

#endif
