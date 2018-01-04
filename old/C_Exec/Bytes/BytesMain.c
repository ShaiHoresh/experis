#include <stdio.h>
#include "Bytes.h"

bitMap* CreateBitMap(unsigned int _nof);
int DestroyBitMap(bitMap* _bM);
void PrintBitMap(bitMap* _bM);
void PrintBitMap2(bitMap* _bM);


int main()
{
    unsigned int numOfFeat, feat;
    bitMap* bM;
    BitFuncs bitF[3] = {BitOn, BitOff, IsBitOn};
    int option, cont, flag;
    
    cont = 1;
    
    printf("Please enter the number of features:\n");
    scanf("%u", &numOfFeat);
    bM = CreateBitMap(numOfFeat);
    
	while(cont)
	{
		printf("Choose option:\n");
		printf("0: Turn bit on\n");
		printf("1: Turn bit off\n");
		printf("2: Check if bit is on\n");
		printf("3: Print the bitmap\n");
		printf("Enter any other number to exit.\n\n");
		
		scanf("%d", &option);
		if(option == 3)
		{
		    PrintBitMap(bM);
		    PrintBitMap2(bM);
		}
		else if(option > 3 || option < 0)
		{
		    cont = 0;
		    break;
	    }
	    else
	    {
		    printf("Please enter bit number:\n");
		    scanf("%u", &feat);
			flag = bitF[option](bM, feat);
			switch(option)
			{
			    case 0:
			        if(flag == 1)
			        {
			            printf("bit num %d turned on\n\n", feat);
			        }
			        else
			        {
			            printf("out of range\n\n");
			        }
			    break;
		        case 1:
			        if(flag == 1)
			        {
			            printf("bit num %d turned off\n\n", feat);
			        }
			        else
			        {
			            printf("out of range\n\n");
			        }
			    break;
		        case 2:
			        if(flag == 1)
			        {
			            printf("bit num %d is on\n\n", feat);
			        }
			        else if (flag == 0)
			        {
			            printf("bit num %d is off\n\n", feat);
			        }
			        else
			        {
			            printf("out of range\n\n");
			        }
			    break;
			    default: break;
			}
		}
	}
    
    
    
    DestroyBitMap(bM);
    return 0;
}




