#include "stack.h"

#include <stdio.h>
#include <string.h>

int CheckBrackets(char* eq);
int TakeCareOfPar(Stack* _bracketStack);
int TakeCareOfSqu(Stack* _bracketStack);
int TakeCareOfCur(Stack* _bracketStack);

void PrintTestResult(int isFlag);

int TestEmptyEq();
int TestNormalEq();
int TestCloseBeforeOpen();
int TestUnmatchedBrackets();
int TestEqualNumButMessBrackets();
int TestComplicatedEq();
int TestWOEnoughclosers();
int TestTooMuchclosers();

int main()
{

    TestEmptyEq();
    TestNormalEq();
    TestCloseBeforeOpen();
    TestUnmatchedBrackets();
    TestEqualNumButMessBrackets();
    TestComplicatedEq();
    TestWOEnoughclosers();
    TestTooMuchclosers();

return 0;
}

int CheckBrackets(char* eq)
{
    int length = 0, i = 0;
    int ascichar, isFlag = 0/*, rem*/;
	Stack* bracketStack;

	bracketStack = StackCreate(5, 2);
    length = strlen(eq);
	
	for(i = 0; i < length; ++i)
	{
        ascichar = eq[i];
        if(ascichar == '(' || ascichar == '[' || ascichar == '{')
        {
            StackPush(bracketStack, ascichar);
        }		
        if(ascichar == ')')
        {
        	isFlag = TakeCareOfPar(bracketStack);
        }
        if(ascichar == ']')
        {
        	isFlag = TakeCareOfSqu(bracketStack);
        }
        if(ascichar == '}')
        {
        	isFlag = TakeCareOfCur(bracketStack);
        }
        
        if(isFlag == 1)
        {
        	break;
        }
	}

    if(length == 0 || (StackIsEmpty(bracketStack) != 0 && isFlag == 0))
    {
        isFlag = 0;
    }
    return isFlag;
}	
	
	
	
int TakeCareOfPar(Stack* _bracketStack)
{
    int isFlag = 0, bracketCheck;
    StackTop(_bracketStack, &bracketCheck);
    
    if(bracketCheck == '(')
    {
        StackPop(_bracketStack, &bracketCheck);
    }
    else
    {
        isFlag = 1;
    }
    return isFlag;
}
        
int TakeCareOfSqu(Stack* _bracketStack)
{
    int isFlag = 0, bracketCheck;
    StackTop(_bracketStack, &bracketCheck);
    if(bracketCheck == '[')
    {
        StackPop(_bracketStack, &bracketCheck);
    }
     else
    {
        isFlag = 1;
    }
    return isFlag;
}
        
int TakeCareOfCur(Stack* _bracketStack)
{
    int isFlag = 0, bracketCheck;
    StackTop(_bracketStack, &bracketCheck);
    if(bracketCheck == '{')
    {
        StackPop(_bracketStack, &bracketCheck);
    }
    else
    {
        isFlag = 1;
    }
    return isFlag;
}        

void PrintTestResult(int isFlag)
{
    if(0 == isFlag)
    {
        printf("SUCCEEDED:  ");
    }
    else
    {
        printf("FAILED:     ");
    }
}

int TestEmptyEq()
{
	int isFlag = 0;
    isFlag = CheckBrackets("");
    PrintTestResult(isFlag);
    printf("test empty equation\n");
    return isFlag;
}

int TestNormalEq()
{
	int isFlag = 0;
    isFlag = CheckBrackets("{[(5+3)*4]+54}=86");
    PrintTestResult(isFlag);
    printf("test normal equation\n");
    return isFlag;
}

int TestCloseBeforeOpen()
{
	int isFlag = 0;
    isFlag = CheckBrackets("]45^2-23455[");
    PrintTestResult(!isFlag);
    printf("test close before open\n");
    return isFlag;
}

int TestUnmatchedBrackets()
{
	int isFlag = 0;
    isFlag = CheckBrackets("{234[234)243]234}");
    PrintTestResult(!isFlag);
    printf("test unmatched brackets\n");
    return isFlag;
}

int TestEqualNumButMessBrackets()
{
	int isFlag = 0;
    isFlag = CheckBrackets("{2(34[2342)43]234}");
    PrintTestResult(!isFlag);
    printf("test equal num but mess brackets\n");
    return isFlag;
}

int TestComplicatedEq()
{
	int isFlag = 0;
    isFlag = CheckBrackets("[14*{1234-[241*34]*(234^43)-23}*2]");
    PrintTestResult(isFlag);
    printf("test complicated Eq\n");
    return isFlag;
}

int TestWOEnoughclosers()
{
	int isFlag = 0;
    isFlag = CheckBrackets("(142(2341(256(5123)234)");
    PrintTestResult(!isFlag);
    printf("test not enough closers\n");
    return isFlag;
}

int TestTooMuchclosers()
{
	int isFlag = 0;
    isFlag = CheckBrackets("(142(2341(256(5123)234)243)234)2345)456)");
    PrintTestResult(!isFlag);
    printf("test too much closers\n");
    return isFlag;
}


