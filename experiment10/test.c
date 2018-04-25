#include "my_malloc.h"
#include <stdio.h>
void main(void)
{
/* print_list(); */
    char *p[200],*str;
    int i;
    printf("sizeof(Header)=%d\n\n",sizeof(Header));
    for (i = 0; i < 5; i++)
    {
        p[i] = (char *) Malloc(8) ;
        printf("\nMalloc %d,%X\n", i, p[i]);
    }
    printf("========================\n=======================\n");
    if((str = (char *)Malloc(8))==NULL)
    {
        printf("Malloc str error\n");
        exit(1);
    }
    for(i = 2;i>=1;i--)
    {
        Free(p[i]);
        printf("\nfree %d,%X\n",i,p[i]);
    }
    printlist();
    for (i = 0; i < 5; i++){
        p[i] = (char *)Malloc(8);
        printf("\nMalloc %d,%X\n" , i,p[i]);
    }
    printlist();
}
