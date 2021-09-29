#include <stdio.h>

void main()
{
    int cyl[20], size, temp, head, head_index, trav[20], t = 0, seek_time;
    cyl[0] = 0;
    printf("Enter head value:");
    scanf("%d", &head);
    cyl[1] = head;
    printf("Enter no:of tracks:");
    scanf("%d", &size);
    printf("Enter tracks:");
    for (int i = 2; i < size + 2; i++)
    {
        scanf("%d", &cyl[i]);
    }
    cyl[size + 2] = 199;
    int full = size + 3;
    for (int i = 0; i < full - 1; i++)
    {
        for (int j = 0; j < full - i - 1; j++)
        {
            if (cyl[j] > cyl[j + 1])
            {
                temp = cyl[j];
                cyl[j] = cyl[j + 1];
                cyl[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < full; i++)
    {
        if (cyl[i] == head)
        {
            head_index = i;
            break;
        }
    }
    for (int i = head_index; i < full; i++)
    {
        trav[t++] = cyl[i];
    }
    for (int i = 0; i < head_index - 1; i++)
    {
        trav[t++] = cyl[i];
    }
    seek_time = (199 - head) + 199 + (199 - cyl[head_index - 1]);
    printf("Traversal order is:");
    for (int i = 0; i < t; i++)
    {
        printf("%d  ", trav[i]);
    }
    printf("\nSeek time is:%d\n", seek_time);
}