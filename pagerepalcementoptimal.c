#include <stdio.h>
#include <stdlib.h>

int main()
{
    int ref_string[30], frames[30], no, n, i, j, k, pos, max, avail;
    int fcount = 0, hcount = 0;
    int temp[30];

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the number of frames: ");
    scanf("%d", &no);

    printf("Enter the reference string: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &ref_string[i]);
    }

    printf("\nReference_String   \tPage_Frames \tHit/Faults\n");

    for (i = 0; i < n; i++)
    {
        printf("\t%d\t    ", ref_string[i]);
        avail = 0;
        // Check if the page is already in a frame
        for (j = 0; j < no; j++)
        {
            if (frames[j] == ref_string[i])
            {
                hcount++;
                avail = 1; // Page is already in a frame
                for (k = 0; k < no; k++)
                {
                    printf(" %d\t", frames[k]);
                }
                printf("H");
            }
        }

        if (avail == 0)
        {
            fcount++;
            // Find a frame to replace
            if (i < no)
            {
                frames[i] = ref_string[i];
            }
            else
            {
                for (j = 0; j < no; j++)
                {
                    temp[j] = -1;
                    for (k = i + 1; k < n; k++)
                    {
                        if (frames[j] == ref_string[k])
                        {
                            temp[j] = k;
                            break;
                        }
                    }
                }

                avail = 0;
                for (j = 0; j < no; j++)
                {
                    if (temp[j] == -1)
                    {
                        pos = j;
                        avail = 1;
                    }
                }

                if (avail == 0)
                {
                    max = temp[0];
                    pos = 0;

                    for (j = 1; j < no; j++)
                    {
                        if (temp[j] > max)
                        {
                            max = temp[j];
                            pos = j;
                        }
                    }
                }
                frames[pos] = ref_string[i];
                for (k = 0; k < no; k++)
                {
                    printf(" %d\t", frames[k]);
                }
                printf("F");
            }
        }
        printf("\n");
    }

    printf("Number of page faults: %d\n", fcount);
    printf("Number of Hit Counts are %d", hcount);

    return 0;
}