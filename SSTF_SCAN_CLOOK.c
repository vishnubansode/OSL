#include<stdio.h>
#include<stdlib.h>
void sstf(int req[],int n,int head)
{
    int total_seek_time=0;
    int i,j,diff,min;
    int visited[100]={0};
    
    printf("sstf algo  :");
    
    for(i=0;i<n;i++)
    {
        min=1000;
        int ind=-1;
        
        for(j=0;j<n;j++)
        {
            if(!visited[j])
            {
                diff=abs(req[j]-head);
                if(diff<min)
                {
                    min=diff;
                    ind=j;
                }
            }
        }
        visited[ind]=1;
        total_seek_time+=abs(req[ind]-head);
        head=req[ind];
        printf("%d",head);
    }
    printf("\ntotal_seek_time is :%d",total_seek_time);
}
int main()
{
    int n,i,head;
    int req[100];
    
    printf("\nenter the no of request  :");
    scanf("%d",&n);
    
    printf("\nenter the head :");
    scanf("%d",&head);
    
    printf("\nenter the request string");
    for(i=0;i<n;i++)
    {
        scanf("%d",&req[i]);
    }
    
    sstf(req,n,head);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>

void scan(int req[], int n, int head, int direction, int disk_size) {
    int total_seek_time = 0;
    int i, j;

    // Sort requests
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (req[j] > req[j + 1]) {
                int temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    printf("SCAN algo: ");

    // If direction is 1, move towards larger values; if -1, towards smaller values
    if (direction == 1) {
        // Move to the right
        for (i = 0; i < n; i++) {
            if (req[i] >= head) {
                break;
            }
        }
        for (j = i; j < n; j++) {
            printf("%d ", req[j]);
            total_seek_time += abs(req[j] - head);
            head = req[j];
        }
        // Move to the end of disk
        if (head < disk_size - 1) {
            total_seek_time += abs(disk_size - 1 - head);
            head = disk_size - 1;
        }
        // Move to the left
        for (j = i - 1; j >= 0; j--) {
            printf("%d ", req[j]);
            total_seek_time += abs(req[j] - head);
            head = req[j];
        }
    } else {
        // Move to the left
        for (i = n - 1; i >= 0; i--) {
            if (req[i] <= head) {
                break;
            }
        }
        for (j = i; j >= 0; j--) {
            printf("%d ", req[j]);
            total_seek_time += abs(req[j] - head);
            head = req[j];
        }
        // Move to the start of disk
        if (head > 0) {
            total_seek_time += abs(head - 0);
            head = 0;
        }
        // Move to the right
        for (j = i + 1; j < n; j++) {
            printf("%d ", req[j]);
            total_seek_time += abs(req[j] - head);
            head = req[j];
        }
    }

    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main() {
    int n, head, direction, disk_size;
    int req[100];

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    printf("Enter direction (1 for up, -1 for down): ");
    scanf("%d", &direction);

    printf("Enter the request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    scan(req, n, head, direction, disk_size);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

void clook(int req[], int n, int head) {
    int total_seek_time = 0;
    int i, j;

    // Sort requests
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (req[j] > req[j + 1]) {
                int temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    printf("C-LOOK algo: ");

    // Move rightwards and then wrap to the start
    for (i = 0; i < n; i++) {
        if (req[i] >= head) {
            break;
        }
    }
    for (j = i; j < n; j++) {
        printf("%d ", req[j]);
        total_seek_time += abs(req[j] - head);
        head = req[j];
    }
    // Jump back to the beginning of the requests
    if (i > 0) {
        total_seek_time += abs(head - req[0]);
        head = req[0];
        for (j = 0; j < i; j++) {
            printf("%d ", req[j]);
            total_seek_time += abs(req[j] - head);
            head = req[j];
        }
    }

    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main() {
    int n, head;
    int req[100];

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    clook(req, n, head);

    return 0;
}

