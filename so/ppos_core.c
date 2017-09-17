#include "ppos.h"

#define MAXINT 32767
#define STACKSIZE 32768		/* tamanho de pilha das threads,
                             * retirado de contexts.c */

task_t *task_list, task_main, *curr_task;

//funcao que busca dentre todas as tasks uma que contenha o id informado
task_t* task_search (int id){
    task_t *aux;
    for (aux=task_list; (aux->id!=id)&&(aux!=task_list->prev); aux=aux->next);
    if (aux->id == id){
        return aux;
    }
    return NULL;
}

void ppos_init (){
    /* desativa o buffer da saida padrao (stdout), usado pela função printf */
    setvbuf (stdout, 0, _IONBF, 0) ;

    //Inicia a lista de tasks com uma task para a main
    getcontext(&(task_main.context));
    task_main.id = 0;
    task_main.prev = &task_main;
    task_main.next = &task_main;
    task_main.stack = malloc(STACKSIZE);
    task_list = &task_main;
    curr_task = &task_main;
}

int task_create (task_t *task, void (*start_routine)(void *),  void *arg){
    void *stack;

    if (getcontext(&(task->context))<0){
        printf("Falha em adquirir contexto\n");
        return -1;
    }

    stack = malloc(STACKSIZE);
    if(stack){
        task->context.uc_stack.ss_sp = stack;
        task->context.uc_stack.ss_size = STACKSIZE;
        task->context.uc_stack.ss_flags = 0;
        task->stack = stack;
    }else{
        printf("Falha na alocação de pilha\n");
        return -1;
    }

    task->context.uc_link = 0;

    makecontext(&(task->context), (void*)(*start_routine), 1, arg);
    if (task_list->prev->id<MAXINT){
        task->id = task_list->prev->id + 1;
    }else{
        int i=0;
        while(task_search(i)){
            if (i == MAXINT){
                printf("Quantidade de tasks excederam %d, impossibilitando id\n", MAXINT);
                return -1;
            }
            i++;
        }
        task->id = i;
    }
    task->prev = task_list->prev;
    task->next = task_list;
    task_list->prev->next = task;
    task_list->prev = task;
    return task->id;
}

int task_switch (task_t *task){
    if (task==NULL){
        printf("Erro: task informada inexistente\n");
        return -1;
    }
    task_t *aux = curr_task;
    curr_task = task;
    swapcontext(&(aux->context),&(curr_task->context));
    return 0;
}

void task_exit (int exitCode){
    task_switch(&task_main);
}

int task_id () {
    return curr_task->id;
}
