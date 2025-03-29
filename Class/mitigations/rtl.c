#include<stdio.h>
#include<unistd.h>

int main()
{
    char buf[40];
    
    printf("%p\n", buf);
    printf("%p\n", printf);
    read(0, buf, 100);

    return 0;
}
