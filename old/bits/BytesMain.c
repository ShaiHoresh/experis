#include <stdio.h>
#include "Bytes.h"

int main()
{
    unsigned char ch = 0, ch2 = 0;
    int dec, rot, cont = 1,option = 1, dec2, copy, place, from, to, value;
    unsigned int bigNum;

    while(cont)
    {
        printf("\nPlease choose option:\n1: invert\n2: rotate\n3: set bits\n4: set tons of bits\n");
        scanf("%d", &option);
        switch(option)
        {
            case 1:
                printf("Please enter a number from 0 to 255\n");
                scanf("%d", &dec);
                ch = (unsigned char)dec;
                PrintBinChar(ch);
                printf("\nNow It's inverted:\n");
                invert(ch);
            break;
            case 2:
                printf("Please enter a number from 0 to 255\n");
                scanf("%d", &dec);
                ch = (unsigned char)dec;
                PrintBinChar(ch);
                printf("How many rotations do you want?\n");
                scanf("%d", &rot);
                rotate(ch, rot);
            break;
            case 3:
                printf("Please enter a number from 0 to 255\n");
                scanf("%d", &dec);
                ch = (unsigned char)dec;
                PrintBinChar(ch);
                printf("Please enter the second number (between 0-255):\n");
                scanf("%d", &dec2);
                ch2 = (unsigned char)dec2; 
                PrintBinChar(ch2);
                printf("How many numbers do you want to copy?\n");
                scanf("%d", &copy);
                printf("Where do you want to push them?\n");
                scanf("%d", &place);
                ch = SetBit(ch, place, copy, ch2);
                PrintBinChar(ch);
            break;
            case 4:
                printf("Please enter a number from 0 to 2^31 (-;\n");
                scanf("%u", &bigNum);
                printf("Please enter the limits (smaller first)\n");
                scanf("%d%d", &from, &to);
                printf("Please enter the value you want to put (0 or 1)\n");
                scanf("%d", &value);
                PrintBinInt(bigNum);
                bigNum = SetBits(bigNum, from, to, value);
                PrintBinInt(bigNum);
            break;
            default:
                cont = 0;
            break;
        }
    }
    return 0;
}

