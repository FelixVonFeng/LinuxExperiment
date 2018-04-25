# include <unistd.h>
# include <stdio.h>
# include "my_malloc.h"
static Header base; /* empy list to get started */
static Header * free_list = NULL; /* start of free list */
/* Malloc: general-purpose storage allocator */
void * Malloc(unsigned int nbytes)
{
	Header *p, *prev;
	unsigned int nunits;
	nunits = (nbytes + sizeof(Header) -1) / sizeof(Header) + 1;
	if ( (prev = free_list) == NULL)
	{ /* no free list yet */
		base.s.next = free_list = prev = &base;
		base.s.size = 0;
	}
	for (p = prev -> s.next; ; prev = p, p = p -> s.next) 
	{
		if (p -> s.size >= nunits) 
		{ /* big enough */
			if (p -> s.size == nunits)
			{/* exactly */
				prev -> s.next = p -> s.next;
			}
			else {
				p -> s.size -= nunits;
				p += p -> s.size;
				p -> s.size = nunits;
			}
			free_list = prev;
			return (void *) (p + 1) ;
	}
	if (p == free_list) 
	{/* wrapped around Free list */
		if ( ( p = morecore(nunits) ) == NULL)
		{
			return NULL; /* none left */
		} /* endfor */
	
       }
   }
}
static Header * morecore(unsigned int nu)

{

	char *cp;

	Header * up;

	if (nu < NALLOC)

		nu = NALLOC;

	cp = sbrk(nu * sizeof(Header) ) ;
	if (cp == (char *) -1) /* no space at all */
	{
		perror("sbrk error");
		return NULL;
	}
	printf("sbrk: %X -- %X \n",cp,cp+nu*sizeof(Header) );
	up = (Header * ) cp;
	up -> s.size = nu;
	Free(up + 1) ;
	return free_list;

}
/* Free:put block ap in Free list */
void Free(void * ap)

{
	Header * bp, *p;
	bp = (Header * ) ap - 1; /* point to block header */
	for (p = free_list; !(bp > p && bp < p -> s.next) ; p = p -> s.next)
	{
		if ( p >=p->s.next && (bp > p || bp < p -> s.next ) )
			break; /* freed block at start or end of arena */
	}
	if (bp + bp -> s.size == p -> s.next )
	{ /* join to upper nbr */
		bp -> s.size += p -> s.next -> s.size;
		bp -> s.next = p -> s.next -> s.next;
	}
	else
		bp -> s.next = p -> s.next;
	if (p+ p -> s.size == bp)
	{ /* join to lower nbr */
		p -> s.size += bp -> s.size;
		p -> s.next = bp -> s.next;
	}
	else
		p -> s.next = bp;
}

void printlist(void)

{

	Header *p;
	printf("free_list:");
	p = base.s.next;
	do{
		printf("%X:%d-->",p,p->s.size);
		p=p->s.next;	
	}while(p!=&base);
	printf("\n");
}
