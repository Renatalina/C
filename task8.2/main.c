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
    
    if(head->next != NULL) {            
            ListNode *remove_elem = where->next; 
            int return_data = remove_elem->data;

            if(remove_elem->next != NULL) {
                where->next = remove_elem->next;
            } else {
                where->next = NULL;
            }
            free(remove_elem);
            return return_data;        

    } else {
        return 0;
    }    

    return 0;
} //пусть возвращает элемент

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

    printf("Deleted %d\n", list_delete(head, second)); //должно быть 6
    
    list_print(head); // 1 5 7

    list_free(head);
    head = NULL;

    return 0;
}