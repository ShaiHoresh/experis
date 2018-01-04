#include <stdio.h>
#include <string.h>

int BinarySearchRec(int* _array, unsigned int _size, int number);
void ReverseString(char* _string, unsigned int _length);
void HanoiTower(unsigned int _disc, unsigned int _from, unsigned int _to);

int main()
{
    int array[10] = {1 ,2 ,3 ,5 ,7 ,12 ,23 ,56 ,67 ,78};
    int index = 0;
    char string[] = "superkalietc";
    
    index = BinarySearchRec(array, 10, 7) + 1;
    printf("your number is waiting in cell munber %d.\n", index);
    index = BinarySearchRec(array, 10, 1) + 1;
    printf("your number is waiting in cell munber %d.\n", index);
    index = BinarySearchRec(array, 10, 35) + 1;
    printf("your number is waiting in cell munber %d.\n", index);
    index = BinarySearchRec(array, 10, 78) + 1;
    printf("your number is waiting in cell munber %d.\n", index);
    ReverseString(string, strlen(string));
    printf("%s\n", string);

    HanoiTower(20, 1, 3);
    return 0;

}

int BinarySearchRec(int* _array, unsigned int _size, int _number)
{
    int middle = _size / 2;
    if( NULL == _array || 0 == _size) return 0;
    if(_array[middle] != _number && _size < 2)
    {
        return 0;
    }
    if(_array[middle] == _number)
    {
        return middle;
    }
        
    if(_array[middle] > _number)
    {
        return BinarySearchRec(_array, _size - middle, _number);
    }
    else
    {
        return middle + BinarySearchRec(_array + middle, _size - middle, _number);
    }
}

void ReverseString(char* _string, unsigned int _length)
{
    char ch;

    if(_length < 1)
    {
        return; 
    }
    ReverseString(_string + 1, _length - 2);
    
    ch = _string[_length-1];
    _string[_length-1] = _string[0];
    _string[0] = ch;  

   
}

void HanoiTower(unsigned int _disc, unsigned int _from, unsigned int _to)
{
    unsigned int using = 6 - _from - _to;
    if(_disc == 0) return;
    if(_disc == 1)
    {
        printf("Take disc num 1 from %d to %d\n", _from, _to);
        return;
    }
    HanoiTower(_disc - 1, _from, using);
    printf("Take disc num %d from %d to %d\n", _disc, _from, _to);
    HanoiTower(_disc - 1, using, _to);    
}

























