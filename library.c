#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "library.h"
#include <time.h>
//создамем дек

FILE *file;
FILE *file_read;
FILE *file_graphics;
Elem *BegL;
Elem *EndL;
Elem *BegL_Piram;
Elem *EndL_Piram;
Elem *p,*pk,*po;
int count_elements=0;
int choice_of_doing=0;
char enter_next[100];
char *enter;
clock_t start, end;
double cpu_time_used;
void program_going(int num, char *files[])
{
    
    if(start_file(num,files)==0) hand_enter();
    else if(start_file(num,files)==1)
    {
        file_graphics = fopen("graphics.txt","w");
        fclose(file_graphics);
    }
    else if(start_file(num,files)==2) 
    {
        print_file();
        hand_enter();
    }
    else if(start_file(num,files)==3)
    {
        printf("Извините, не найдено такого файла\n");
        hand_enter();
    }
    

}

void print_file()
{
    file = fopen("sort.txt","r");
    if(file==NULL)
    { 
        printf("файл не найден\n");
        
    }
    else
    {
        fseek(file,0,SEEK_END);
        long file_size = ftell(file);
        fseek(file,0,SEEK_SET);
        
        if( (file_size==0) || (file_size==17))
        {
            printf("Файл пуст\n");
            fclose(file);
        }
        else
        {
            
            char *str = (char *)malloc((file_size+1)*sizeof(char));
            
            if(str==NULL)
            {
                printf("Не удалось выделить память");
                fclose(file);
            }
            else
            {
                for(int i=0; i<4;i++){
                    fgets(str,file_size+1,file);
                    printf("%s",str);
                }
                
                free(str);
                fclose(file);
                
            }
        }
    }
    
    

}
void hand_enter(){
    while(1)
    {
        BegL=NULL;
        EndL=NULL;
        BegL_Piram=NULL;
        EndL_Piram=NULL;
        p=NULL;
        pk=NULL;
        po=NULL;
        count_elements=0;
        file = fopen("sort.txt","w");
        file_graphics = fopen("graphics.txt","a");
        if(start_enter(file)==0)
        {
            
            if(count_elements==1)
            {
                fputs("Отсортированные числа:\n",file);
                fprintf(file,"%s\n",enter);
            }
            if(count_elements>=2) 
            {   
                start=clock();
                bubble_sort(file);
                end=clock();
                cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
                fprintf(file_graphics,"%d %f ", count_elements, cpu_time_used);
            
            }
            if(count_elements>=3)
            { 
                start=clock();
                sort_piram(file);
                end=clock();
                cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
                fprintf(file_graphics,"%f\n",cpu_time_used);
                
            }
        }
        else fputs("Нет входных данных\n",file);
        fclose(file);
        fclose(file_graphics);
        printf("%d\n", count_elements);
        printf("ЕСЛИ ХОТИТЕ ПРОДОЛЖИТЬ НАЖМИТЕ 1, ИНАЧЕ ДРУГУЮ КНОПКУ\n");
        fgets(enter_next, sizeof(enter_next),stdin);
        enter_next[strcspn(enter_next,"\n")]=0;
        if(atoi(enter_next)!=1) break;
    }



}

int start_file(int num, char *files[])
{   
    
    int true=0;
    for(int i=0; i<num; i++)
    {
        if(strcmp(files[i],"--file")==0)
        {
            true=1;
            continue;
        }

        if(true==1)
        {
            if(strcmp(files[i],"graphics.txt")==0) return 1;
            else if(strcmp(files[i],"sort.txt")==0) return 2;
            else return 3;
            true=0;
        }
    }

    return 0;


}



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
int start_enter(FILE *file)
{
    file_read = fopen("file_read.txt","r");
    BegL=NULL;
    EndL=NULL;
    BegL_Piram=NULL;
    EndL_Piram=NULL;
    int first_inf=0;
    if(file_read==NULL)
    { 
        printf("файл не найден\n");
        return 1;
    }
    else
    {
        fseek(file_read,0,SEEK_END);
        long file_size = ftell(file_read);
        fseek(file_read,0,SEEK_SET);
        if( (file_size==0))
        {
            printf("Файл пуст\n");
            fclose(file_read);
            return 1;
        }
        else
        {
            
            enter = (char *)malloc((file_size+1)*sizeof(char));
            
            if(enter==NULL)
            {
                printf("Не удалось выделить память");
                fclose(file_read);
            }
            else
            {
                fgets(enter,file_size+1,file_read);
                fclose(file_read);
                
            }
        }
    }
    enter[strcspn(enter,"\n")]=0; 
    
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
    return 0;
    
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


void bubble_sort(FILE *file)
{
    
    
    for(int i=0;i<count_elements-1;i++)
    {
        
        pk=BegL;
        
        for(int j=0; j<count_elements-1;j++)
        {
            
            
            if(pk->inf>pk->next->inf) 
            {
                
                change_elements(pk,pk->next);
                
            }
            else pk=pk->next;
            
            
        }    
        

        

    }
    
    pk=BegL;
    fputs("Сортированные числа:\n",file);
    while (pk!=EndL)
    {
        
        fprintf(file,"%d ",pk->inf);
        pk=pk->next;
    }
    fprintf(file,"%d\n",pk->inf);
    delete_dek();
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


void sort_piram(FILE *file)
{
    if(count_elements>2)
    {
        BegL=BegL_Piram;
        EndL=EndL_Piram;
        pk=BegL;
        



    
        //создаём нижний ряд
        for(int i=(count_elements/2); i>=0; i--)
        {
            int root=i;
            int bottom=count_elements;
            int maxChild;
            int done =0;
            
            while( (root*2<=bottom) && (!done))
            {
                
                if(root*2==bottom) maxChild=root*2;
                
                else if(find_element_by_num(root*2)<find_element_by_num(root*2+1))
                {
                    
                    maxChild= root*2;
                }
                else 
                {
                    
                    maxChild = root*2+1;
                }
                if(find_element_by_num(root)>find_element_by_num(maxChild))
                {
                    
                    change_elements(find_element_by_count(root),find_element_by_count(maxChild));
                    root=maxChild;
                    
                
                }
                else done=1;
                
                
            
            }
            
        }

        

        for(int i = count_elements; i>=2; i--)
        {
            
            change_elements(find_element_by_count(0),find_element_by_count(i));
            
            int root=1;
            int bottom=i-1;
            int maxChild;
            int done =0;
            
            while( (root*2<=bottom) && (!done))
            {
                
                if(root*2==bottom) maxChild=root*2;
                
                else if(find_element_by_num(root*2)<find_element_by_num(root*2+1))
                {
                    
                    maxChild= root*2;
                }
                else 
                {
                    
                    maxChild = root*2+1;
                }
                if(find_element_by_num(root)>find_element_by_num(maxChild))
                {
                    
                    change_elements(find_element_by_count(root),find_element_by_count(maxChild));
                    root=maxChild;
                    
                
                }
                else done=1;
                
                
            
            }
        }
        
        pk=BegL;
            
        while (pk!=EndL)
        {
                
            fprintf(file,"%d ",pk->inf);
            pk=pk->next;
        }
        fprintf(file,"%d\n",pk->inf);
    }
    delete_dek();
}