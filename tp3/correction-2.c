#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE_MAX 1024


int *p;
 
void push(int x)
{
        *p=x;
	p++;
}
 
int pop()
{
	p--;
        return *p;
}
 
int main(int argc, const char **argv)
{
	p=(int*)malloc(STACK_SIZE_MAX*sizeof(int));

	int n1,n2;

	for(int i = 1; i < argc; i++){ 
                switch(*argv[i])
                {
                        case '+':
                        {
 				n1 = pop();
                		n2 = pop();
				push(n1+n2);
            			break;
                        }
                        case '-':
                        {
				n1 = pop();
                		n2 = pop();
                                push(n2-n1);
                                break;
                        }
                        case '*':
                        {
				n1 = pop();
                		n2 = pop();
                                push(n1*n2);
                                break;
                        }
                        case '/':
                        {
				n1 = pop();
                		n2 = pop();
                                push(n2/n1);
                                break;
                        }
			default:
				push(atoi(argv[i]));
                }
              
	}
        printf("\nThe result is %d\n\n",pop());
        return 0;


}
