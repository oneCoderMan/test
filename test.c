#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFSIZE 1024

void vuln(){
  char buf[20];
  gets(buf);
  puts(buf);
  fflush(stdout);
}

int main(void)
{
    char login[32];
    char passwd[32];
    
    printf("Login: ");
    gets(login);
    printf("Password: ");
    gets(passwd);
    
    if (strcmp(login, "root") == 0) {
        if (strcmp(passwd, "12345678") == 0) {
            printf("Access Granted.\n");
            
            // Set the gid to the effective gid
              // this prevents /bin/sh from dropping the privileges
              printf("Database Search: ");
              gid_t gid = getegid();
              setresgid(gid, gid, gid);

              vuln();
              return 0;
        }
    }
    
    printf("Access Denied.\n");
    return 1;
}