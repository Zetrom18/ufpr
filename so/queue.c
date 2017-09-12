#include <stdio.h>
#include "queue.h"

void queue_append (queue_t **queue, queue_t *elem){
    if (queue==NULL){
        puts("Fila informada nao existente");
    }else if (elem==NULL){
        puts("Elemento informado nao existe");
    }else if ((elem->next!=NULL)||(elem->prev!=NULL)){
        puts("Elemento informado ja se encontra em outra fila");
    }else if (*queue==NULL){
        *queue = elem;
        elem->next = elem;
        elem->prev = elem;
    }else{
        queue_t *head = *queue;
        head->prev->next = elem;
        elem->prev = (*queue)->prev;
        head->prev = elem;
        elem->next = head;
    }
}

queue_t *queue_remove (queue_t **queue, queue_t *elem){
    if (queue==NULL){
        puts("Fila informada nao existente");
        return NULL;
    }else if (*queue==NULL){
        puts("File informada esta vazia");
        return NULL;
    }else if (elem==NULL){
        puts("Elemento informado nao existe");
        return NULL;
    }else{
        queue_t *aux = *queue;
        if(aux!=elem){
            aux = aux->next;
            while ((aux!=elem)&&(aux!=*queue)){
                aux = aux->next;
            }
            if(aux!=elem){
                puts("Elemento nao encontrado na fila");
                return NULL;
            }
        }else{
            *queue = elem->next;
        }
        if(elem==elem->next){
            *queue = NULL;
        }else{
            elem->prev->next = elem->next;
            elem->next->prev = elem->prev;
        }
        elem->next = NULL;
        elem->prev = NULL;
        return elem;
    }
}

int queue_size (queue_t *queue){
    if (queue==NULL){
        return 0;
    }
    int i;
    queue_t *aux;
    for(aux=queue->next,i=1;aux!=queue;i++,aux=aux->next);
    return i;
}

void queue_print (char *name, queue_t *queue, void print_elem (void*)){
    printf("%s[", name);
    queue_t *head = queue;
    if (head!=NULL){
        queue_t *aux = head;
        print_elem(aux);
        for (aux=head->next; aux!=head; aux=aux->next){
            print_elem(aux);
            printf(" ");
        }
    }
    puts("]");
}




