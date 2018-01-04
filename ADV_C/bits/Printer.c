#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef union
{
    struct
    {
        unsigned char ink       : 4;
        unsigned char           : 1;
        unsigned char paperJam  : 1;
        unsigned char empty     : 1;
        unsigned char standby   : 1;
    };
    unsigned char status;
} printerStatus;



int main()  
{
    printerStatus ps;
    int i;
    char row[5];
    char* colors[] = {"", "b", "y", "b y", "m", "b m", "y m", "b y m", "c", "b c", "y c","b y c", "m c", "b m c", "y m c", "b y m c"};
    FILE* fp;
    srand((unsigned int)time(NULL));
    
    if((fp = fopen("printer_status.txt", "w")) == NULL)
    {
        printf("problem with the file\n");
        return -1;
    }
    
    for(i = 0; i < 10; ++i)
    {
        fprintf(fp, "%d\n",rand() % 255);
    }
    fclose(fp);
if((fp = fopen("printer_status.txt", "r")) == NULL)
    {
        printf("problem with the file\n");
        return -1;
    }
        
    while(1)
    {
        fgets(row, 5, fp);
        if(feof(fp))
		{
		    break;
	    }
        ps.status = (unsigned char)atoi(row);
        
   /*     printf("ps.status = %d\n", ps.status);*/
        
        if(ps.ink)
        {
            printf("missing: %s\n", colors[ps.ink]);
        }
        if(ps.paperJam)
        {
            printf("Paper jam\n");
        }
        if(ps.empty)
        {
            printf("empty\n");
        }
        if(ps.standby)
        {
            printf("standby\n");
        }
        printf("\n");
        ftell(fp);
        sleep(1);
    }
    fclose(fp);
    return 0;
}
