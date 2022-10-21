/****************************************************/
/******** Author     : Shadi Bahaa   ****************/
/******** File name  : STACK_CHAR.h  ****************/
/******** Date       : 14/10/2022    ****************/
/******** Version    : V1            ****************/
/******** Desc       : ...           ****************/
/****************************************************/
#ifndef STACK_CHAR_H_
#define STACK_CHAR_H_
/* Data node */
typedef struct Node
{
    u8 data;
    struct Node* next;
} Node;
/* The head element */
Node* head = NULL;
/* function to add an element at the beginning
 * options:
 * data : range[0-255]
*/
void push(u8 data)
{
	/* No stack is created till now */
    if (head==NULL)
    {
        head = (Node*)malloc(sizeof(Node));
        head->data = data;
        head->next = NULL;
    }
    /* There is at least one element */
    else
    {
        Node *tmp = (Node*)malloc(sizeof(Node));
        tmp->data = data;
        tmp->next = head;
        head = tmp;
    }
}
/* function the deletes the first element */
void pop()
{
    if (head)
    {
        Node *tmp = head->next;
        free(head);
        head = tmp;
    }
}
/* function the returns the first node data
 * result:
 * stack contains at least one element -> data of the head
 * otherwise                           -> zero
*/
u8 top()
{
    if (head)return head->data;
    return 0;
}
#endif /* STACK_CHAR_H_ */
