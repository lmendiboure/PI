#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Element
{
    int value;
    struct Element *next;
} Element_t;

typedef struct List
{
    Element_t *head;
} List_t;

List_t *init()
{

    List_t *list = malloc(sizeof(*list));

    Element_t *element = malloc(sizeof(*element));

    element->value = 0;

    element->next = NULL;

    list->head = element;

    return list;

}

void push(List_t *list, int nb)
{

    Element_t *new = malloc(sizeof(*new));

    new->value = nb;

    new->next = list->head;

    list->head = new;

}

int pop(List_t *list)
{

	Element_t *toDelete = list->head;

	list->head = list->head->next;
	
	return toDelete->value;

}


int main(int argc, const char **argv)
{
	List_t *newList = init();

	int n1,n2;

	for(int i = 1; i < argc; i++){
                switch(*argv[i])
                {
                        case '+':
                        {
 				n1 = pop(newList);
                		n2 = pop(newList);
				push(newList,n1+n2);
            			break;
                        }
                        case '-':
                        {
				n1 = pop(newList);
                		n2 = pop(newList);
                                push(newList,n2-n1);
                                break;
                        }
                        case '*':
                        {
				n1 = pop(newList);
                		n2 = pop(newList);
                                push(newList,n1*n2);
                                break;
                        }
                        case '/':
                        {
				n1 = pop(newList);
                		n2 = pop(newList);
                                push(newList,n2/n1);
                                break;
                        }
			default:
				push(newList,atoi(argv[i]));
                }
	}
        printf("\nThe result is %d\n\n",pop(newList));
        return 0;

}
