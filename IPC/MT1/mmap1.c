#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>




int main()
{
    char* str = "shalom";
    void* addr;
    int fd;
    
    fd = open("./fd.txt", O_RDWR);
    
    addr = mmap(NULL, 100, 0666, MAP_SHARED, fd, 0);
    
    strcpy((char*)addr, str);
    sleep(10);
    munmap(addr, sizeof(int));
    
    return 0;

}























/*
open file

addr = mmap(...)




munmap()
close file

exit()

*/
