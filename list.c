#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *local = malloc(sizeof(List));
  local->current = NULL;
  local->head = NULL;
  local->tail = NULL;
  return local;
}

void * firstList(List * list) {
if(list->head == NULL) return NULL;
list->current = list->head;
return list->head->data;
}

void * nextList(List * list) {
  if(list->current == list->tail || list->current == NULL || list->head == NULL || list->head->next == NULL) return NULL;
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if(list->head == NULL) return NULL;
  list->current = list->tail;  
  return list->tail->data;
}

void * prevList(List * list) {
  if (list->head == NULL || list->current == list->head || list->current == NULL) return NULL;
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {

  Node *nuevo = createNode(data);
  if(list->head == NULL)
  {
    list->head = nuevo;
    list->tail = nuevo;
    nuevo->next = nuevo->prev;
    return;
  }
  nuevo->next = list->head;
  list->head = nuevo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}
 
void pushCurrent(List * list, void * data) {
  Node *nuevo = createNode(data);
  if(list->head == NULL)
  {
    list->head = nuevo;
    list->tail = nuevo;
    nuevo->next = nuevo->prev;
    return;
  }
  if (list->current == NULL) return;
  if(list->current == list->tail)
  {
    list->tail->next = nuevo;
    nuevo->next = NULL;
    nuevo->prev = list->tail;
    list->tail = nuevo;
    return;
  }
  nuevo->prev = list->current;
  nuevo->next = list->current->next;
  list->current->next = nuevo;
  list->current->next->next->prev = nuevo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  void* dato ;
  if(list->head == NULL || list->current == NULL) return NULL;
  
  if(list->current == list->tail)
  {
    dato = list->tail->data;
    list->tail->prev->next = NULL;
    list->tail->prev = list->tail;
    list->current = NULL;
    return dato;
  }
  if(list->head == list->tail)
  {
    dato = list->head->data;
    list->head = NULL;
    list->head->next = NULL;
    list->tail = NULL;
    list->tail->prev = NULL;
    list->current = NULL;
    list->current->next = NULL;
    list->current->prev = NULL;
    return dato;
  }
  if(list->current == list->head)
  {
    dato = list->head->data;
    list->head = list->head->next;
    list->head->prev = NULL;
    list->current = list->head;
    return dato;
  }
  dato =  list->current->data;
  list->current->prev->next = list->current->next;
  list->current->next->prev = list->current->prev;
  list->current = list->current->next;
  
  
  return dato;
}





void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
