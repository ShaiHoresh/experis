#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>




int main()
{
    void* addr;
    int fd;
    int i;
    
    fd = open("./fd.txt", O_RDWR);
    
    addr = mmap(NULL, 100, 0666, MAP_SHARED, fd, 0);
    
  /*  i = *(int*)addr;*/
    
    printf("%s\n", (char*)addr);


    munmap(addr, sizeof(int));
    
    return 0;

}
