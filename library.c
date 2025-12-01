#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "library.h"
//создамем дек


Elem *BegL;
Elem *EndL;
Elem *BegL_Piram;
Elem *EndL_Piram;
Elem *p,*pk,*po;
int count_elements=0;
char enter[1000];
char enter_piram[1000];
void change_elements(Elem *p, Elem *pk)
{  
    if( (p==BegL) && (pk==EndL) ) 
    {
        pk->prev->next=p;
        p->prev=pk->prev;
        p->next->prev=pk;
        pk->next=p->next;
        p->next=NULL;
        p->prev=NULL;
        BegL=pk;
        EndL=p;

    
    
    }
    
    else if(p==BegL)
    {
        
        Elem *p_help=p->next;
        p->next=pk->next;
        pk->next->prev=p;
        p_help->prev=pk;
        pk->next=p_help;
        
        p_help=pk->prev;
        p_help->next=p;
        
        p->prev=p_help;
        pk->prev=NULL;
        BegL=pk;
    
    }
    else if(pk==EndL){
        
        Elem *p_help=p->next;
        p->next=NULL;
        pk->next=p_help;
        pk->next->prev=pk;
        
        p_help=p->prev;
        p->prev=pk->prev;
        pk->prev->next=p;
        pk->prev=p_help;
        pk->prev->next=pk;
        EndL=p;
        
    }
    else{
        Elem *p_help=p->next;
        p->next=pk->next;
        p->next->prev=p;
        pk->next=p_help;
        pk->next->prev=pk;

        p_help=p->prev;
        p->prev=pk->prev;
        pk->prev->next=p;
        pk->prev=p_help;
        pk->prev->next=pk;
    }


}


//функция ввода чисел
void start_enter(FILE *file)
{
    BegL=NULL;
    EndL=NULL;
    BegL_Piram=NULL;
    EndL_Piram=NULL;
    int first_inf=0;
    
    printf("Введите числа через пробел(Не больше 1000 символов):\n");
    fgets(enter, sizeof(enter),stdin);
    enter[strcspn(enter,"\n")]=0; //убираем знак \n в конце строки
    char *res;
    int error_enter=0;
    int error_true=0;
    res = strtok(enter, " ");

    while(res!=NULL)
    {
        for(int i=0; i<strlen(res);i++)
        {
            if(!(isdigit(res[i])) && !(res[i]=='-'))
            {
                error_enter+=1;
                error_true=1;
                break;
            }
        }
        if ( (strlen(res)>10)  || (strlen(res)==10) && (res[0]>2) ) 
        {
            error_enter+=1;
            error_true=1;
        }
        if(error_true==0){

            p = (Elem *) malloc(sizeof(Elem));
            po = (Elem *) malloc(sizeof(Elem));
            if( (p==NULL) || (po==NULL) ) printf("Ошибка выделенгия памяти\n");
            else if(first_inf==0)
            {
                p->inf=atoi(res);
                p->prev=NULL;
                p->next=NULL;
                BegL=p;
                EndL=p;
                po->inf=atoi(res);
                po->prev=NULL;
                po->next=NULL;
                BegL_Piram=po;
                EndL_Piram=po;
                first_inf=1;
                count_elements+=1;
            }
            else{
                
                p->inf=atoi(res);
                p->prev=EndL;
                EndL->next=p;
                p->next=NULL;
                EndL=p;
                po->inf=atoi(res);
                po->prev=EndL_Piram;
                EndL_Piram->next=po;
                po->next=NULL;
                EndL_Piram=po;
                count_elements+=1;
            
            }
            
            
        }
        error_true=0;
        res = strtok(NULL, " ");
    }


    
    //Вывод Введеных чисел
    fputs("Введеные числа:\n",file);
    
    pk=BegL;
    
    while (pk!=EndL)
    {
        
        fprintf(file,"%d ",pk->inf);
        
        pk=pk->next;
        
    }
    fprintf(file,"%d\n",pk->inf);
    
    printf("Найдено ошибок: %d\n", error_enter);
}

void delete_dek()
{
    Elem *po=BegL->next;
    
    while(po!=EndL)
    {
        free(po->prev);
        po=po->next;
    }
    free(EndL);
    BegL=NULL;
    EndL==NULL;
}


void bubble_sort(FILE *file,FILE *file_graphic)
{
    time_t start_time,end_time;
    double time_go;
    
    for(int i=0;i<count_elements-1;i++)
    {
        pk=BegL;
        start_time=time(NULL);
        for(int j=0; j<count_elements-1;j++)
        {
            
            
            if(pk->inf>pk->next->inf) 
            {
                
                change_elements(pk,pk->next);
            }
            else pk=pk->next;
            
            
        }    
        end_time=time(NULL);
        time_go=difftime(end_time, start_time);
        //fprintf(file_graphic,"%.2f ",time_go*100000000000000000000000000000000);

        

    }
    fprintf(file_graphic,"\n");
    pk=BegL;
    fputs("Сортированные числа:\n",file);
    while (pk!=EndL)
    {
        
        fprintf(file,"%d ",pk->inf);
        pk=pk->next;
    }
    fprintf(file,"%d\n",pk->inf);
    
}

int find_element_by_num(int num){
    Elem *pl=BegL;
    for (int i=0; i<num-1;i++) pl=pl->next;
    return pl->inf;
}

Elem *find_element_by_count(int num){
    Elem *pl=BegL;
    for (int i=0; i<num-1;i++) pl=pl->next;
    return pl;
}

int find_element_by_way(Elem *p){
    Elem *pl=BegL;
    while (pl!=p) pl=pl->next;
    return pl->inf;
}


