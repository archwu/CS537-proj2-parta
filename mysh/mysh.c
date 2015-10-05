#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int lsh_cd(char **args);
int lsh_exit(char **args);

char *builtin_str[]{
"cd","exit"

}

#define BUFFSIZE 1024
char *mysh_read_line(void){
  int buffsize = BUFFSIZE;
  int position = 0;
  char*buffer = malloc(sizeof(char)*buffsize);
  int c;
  if(!buffer){
    fprintf(stderr, "mysh: allocation error\n");
    exit(EXIT_FAILURE);
  }
  while(1){
    c = getchar();
    if(c == EOF || c == '\n'){
      buffer[position] = '\0';
      return buffer;
    }
    else{
      buffer[position] = c;
    }
    position++;

    if (position>= buffsize) {
      buffsize += BUFFSIZE;
      buffer = realloc(buffer,buffsize);
      if (!buffer) {
        fprintf(stderr, "mysh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}


void mysh_loop(void){
  char* line;
  char** args;
  int status;

  do{
    printf("mysh #");
    line = mysh_read_line();
    args = mysh_split_line(line);
    status = mysh_execute(args);
  }while(status);
}

int main(int argc, char** argv){
  mysh_loop();
  return EXIT_SUCCESS;
}
