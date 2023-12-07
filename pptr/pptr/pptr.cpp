#include <stdio.h>

struct point
{
	int xpos;
	int ypos;
};

int main()
{
	struct point pos1 = { 1, 2 };
	struct point pos2 = { 100, 200 };
	struct point* pptr = &pos1;
	(*pptr).xpos += 4;
	(*pptr).ypos += 5;
	printf("[%d, %d] \n" , pptr->xpos, pptr->ypos); 
		
	pptr = &pos2;
	pptr->xpos += 1; // = (*pptr).xpos=10;
	pptr->ypos += 2; // = (*pptr).ypos=20;
	printf("[%d, %d] \n", (*pptr).xpos, (*pptr).ypos);
	return 0;
}