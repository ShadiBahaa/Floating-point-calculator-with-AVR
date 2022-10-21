/****************************************************/
/******** Author     : Shadi Bahaa   ****************/
/******** File name  : STACK_D.h  ****************/
/******** Date       : 14/10/2022    ****************/
/******** Version    : V1            ****************/
/******** Desc       : ...           ****************/
/****************************************************/
#ifndef STACK_D_H_
#define STACK_D_H_
/* Data node */
typedef struct NodeD
{
    f64 data;
    struct NodeD* next;
} NodeD;
/* The head element */
NodeD* Res = NULL;
/* function to add an element at the beginning
 * options:
 * data : range[-1.7E-308 - 1.7E+308]
*/
void pushD(f64 data)
{
	/* No stack is created till now */
    if (Res==NULL)
    {
    	Res = (NodeD*)malloc(sizeof(NodeD));
    	Res->data = data;
    	Res->next = NULL;
    }
    /* There is at least one element */
    else
    {
    	NodeD *tmp = (NodeD*)malloc(sizeof(NodeD));
        tmp->data = data;
        tmp->next = Res;
        Res = tmp;
    }
}
/* function the deletes the first element */
void popD()
{
    if (Res)
    {
    	NodeD *tmp = Res->next;
        free(Res);
        Res = tmp;
    }
}
/* function the returns the first node data
 * result:
 * stack contains at least one element -> data of the head
 * otherwise                           -> zero
*/
f64 topD()
{
    if (Res)return Res->data;
    return 0;
}
#endif /* STACK_D_H_ */
