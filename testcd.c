#include <stdio.h> 
#include <string.h>
#include <errno.h>
// chdir function is declared 
// inside this header 
#include<unistd.h>  
int main() 
{    
    char s[100]; 
  
    // printing current working directory 
    //printf("%s\n", getcwd(s, 100)); 
  
    // using the command 
    //chdir("/Users/fedda/Desktop"); 
    if (chdir("/Users/fedda/Desktop") != 0)  
        printf("%s", strerror(errno));
    // printing current working directory 
    //printf("%s\n", getcwd(s, 100)); 
    
    // after chdir is executed 
    return 0; 
} 



/*
*   С помощью strerror(errno) выводим сообщение об ошибке для cd
*   chdir меняет директорию, принимает 1 параметр - путь
*   при неудаче возвращает -1 и устанавливает errno
*
*
*
*/