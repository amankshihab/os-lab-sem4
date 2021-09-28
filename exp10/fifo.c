#include <stdio.h>
#include <stdbool.h>

int pageFrame_num; // holds the no . of frames

int frame[20]; // holds the pages taken as input from the user

int pages[20];

int iter_var = 0;

void init()
{

	for (int i = 0; i < pageFrame_num; i++)
	{

		frame[i] = -1;
	}
}

bool check(int page)
{

	for (int i = 0; i < pageFrame_num; i++)
	{

		if (frame[i] >= 0 && frame[i] == page)
			return true;
	}

	return false;
}

void replacePage(int frameReplace)
{

	frame[iter_var] = frameReplace;

	iter_var = (iter_var + 1) % pageFrame_num;
}

void display()
{

	printf("\n\nThe frame now is:\n");

	for (int i = 0; i < pageFrame_num; i++)
	{

		printf("%d ", frame[i]);
	}
}

int main()
{

	int hitCount = 0;
	int faultCount = 0;

	printf("\nEnter the no. of page frames:");
	scanf("%d", &pageFrame_num);

	printf("\nEnter the no. of pages:");
	int page_num;
	scanf("%d", &page_num);

	printf("\nEnter the pages:");

	for (int i = 0; i < page_num; i++)
	{

		scanf("%d", &pages[i]);
	}

	init(); // initializes the page frames to -1

	for (int i = 0; i < page_num; i++)
	{

		if (check(pages[i]))
		{

			hitCount += 1;
		}
		else
		{

			faultCount += 1;
			replacePage(pages[i]);
		}

		display();
	}

	printf("\n\nNo. of faults = %d\nNo. of hits = %d\n", faultCount, hitCount);
}
