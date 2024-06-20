#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vadefs.h>

typedef struct ListNode{
    int data;
    struct ListNode* next;
} ListNode;
 
ListNode* list_new() {
    ListNode *new_list=malloc(sizeof(ListNode));
    new_list->next=NULL;
    return new_list;
} //просто вернёт NULL


void list_free(ListNode* head) {
    ListNode *bufer=head;
    while (head != NULL)
    {
        bufer=head->next;
        free(head);
        head=bufer;
    }    
}
 
ListNode* list_add(ListNode* where, int new_data) {
    ListNode *new_elem=malloc(sizeof(ListNode));
    new_elem->data=new_data;
    if(where->next != NULL){
        ListNode *next=where->next;
        where->next=new_elem;
        new_elem->next=next;
    } else {
        where->next=new_elem;
        new_elem->next=NULL;
    }
    
    return new_elem;
} //вернёт ссылку на новый узел списка

int list_delete(ListNode *head, ListNode *where) {
    //if we try remove the head of our list
    if(head == where) {
        return 0;
    }
    
    if(head->next != NULL) {
        ListNode *find_elem = head;

        while (find_elem->next->data != where->data)
        {
            find_elem=find_elem->next;            
            if(find_elem->next == NULL) break;
        }  

        if(find_elem->next->data == where->data) {
            int return_data = where->data;
            if(where->next != NULL) {
                find_elem->next=where->next;
            } else {
                //if it first or last elem
                find_elem->next = NULL;
            }
            free(where);
            return return_data;
        }

    } else {
        //проверка, вдруг мы в голову где-то что-то записали.
        return head->data ? head->data : 0;
    }    

    return 0;
} //пусть возвращает элемент
//наверное не элемент, а его данные, раз у нас стоит int 

void list_print(ListNode* head) {

    ListNode *bufer=head->next;
    while (bufer->next != NULL)
    {
        //потому что, head у нас NULL, мы голову должны пропустить
        printf("The node %p has data: %d\n", bufer, bufer->data);
        bufer=bufer->next;
    } 
        printf("The node %p has data: %d\n", bufer, bufer->data);
}

int main () {
    ListNode* head = list_new();    
    ListNode* first = list_add(head, 1);
    ListNode* second = list_add(first, 5);
    ListNode* third = list_add(second, 6);    

    //list_print(head); // 1 5 6 

    ListNode* new_second = list_add(first, 3);

    list_print(head); // 1 3 5 6

    printf("Deleted %d\n", list_delete(head, head)); //должно быть 6
    
    list_print(head); // 1 5 7

    list_free(head);
    head = NULL;

    return 0;
}