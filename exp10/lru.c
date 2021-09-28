#include <stdio.h>
#include <stdbool.h>

struct Page
{

	int page;
	int index;
};
struct Page pages[20], frame[20];

int frameNum;

int pageNum;

int iter_var = 0;

int hitCount = 0, faultCount = 0;

void init()
{

	for (int i = 0; i < frameNum; i++)
	{

		frame[i].page = -1;
		frame[i].index = -1;
	}
}

bool check(struct Page pages)
{

	for (int i = 0; i < pageNum; i++)
	{

		if (frame[i].page == pages.page)
		{

			return true;
		}
	}

	return false;
}

void display()
{

	printf("\nThe frame now is:\n");

	for (int i = 0; i < frameNum; i++)
	{

		printf("%d ", frame[i].index);
	}
}

int lessIndex()
{

	int min = 0;

	for (int i = 0; i < frameNum; i++)
	{

		if (frame[i].index <= min)
		{

			min = i;
		}
	}
}

void replaceByLRU(struct Page pages)
{

	if (frame[iter_var].page == -1)
	{

		frame[iter_var].page = pages.page;
		iter_var = (iter_var + 1) % frameNum;
	}
	else
	{

		if (check(pages))
		{

			hitCount += 1;
			pages.index += 1;
		}
		else
		{

			int index = lessIndex();

			frame[index] = pages;
		}
	}
}

int main()
{

	printf("\nEnter the no. of frames:");
	scanf("%d", &frameNum);

	init();

	printf("\nEnter the no. of pages:");
	scanf("%d", &pageNum);

	printf("\nEnter the pages:");
	for (int i = 0; i < pageNum; i++)
	{

		scanf("%d", &pages[i].page);

		pages[i].index = 0;
	}

	for (int i = 0; i < pageNum; i++)
	{

		replaceByLRU(pages[i]);

		display();
	}

	return 0;
}
