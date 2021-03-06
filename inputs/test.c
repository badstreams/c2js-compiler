#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

typedef struct lval_S {
  char a;
  int b;
  char* c;
  int length; // test rename on name collision
} lval_T;

void foo(int* a, int *b) {
  if (a[0] > 1) {
    b[0] = 2;
  } else if (a[0] > 1) {
    b[0] = 3;
  }
}

void bar(float x, float y); // just a declaration

void bang(int* a, int v) {
    for (int i = 0; i < v; ++i) {
        i++;
        a[i] -= i;
        *(a + i) -= i;
    }
    int i;
    while (i < 10) {
      i++;
    }
    switch (i) {
      case 0:
        i--;
        break;
      case 1:
      case 2:
        i++;
        break;
      default:
        i++;
        break;
    }
}

void error(char* message) {
  puts(message);
}

char buffer[1000];

void easy() {
  int a = 2;
  a = 3;
  printf("a: 3 == %d\n", a);
}

void structs() {
  lval_T param;
  printf("lval_T: 0 == %d\n", param.b);
  param.b = 2;
  printf("lval_T: 2 == %d\n", param.b);
  printf("lval_T size: 4 == %d\n", sizeof(param));

  lval_T params[10];
  params[0] = param;
  printf("lval_T.b: 2 == %d\n", param.b);

  lval_T param2 = {0, 0, "helo"};
  printf("lval_T.c: helo == %s\n", param2.c);
}

void pointers() {
  char* u = "test";
  char** ptr = &u;
  printf("test == %s\n", u);
  *ptr = "blah";
  printf("blah == %s\n", u);

  char* v[2] = { "string1", "string2" };
  char** v2 = v;
  printf("string1 == %s\n", *v2);
  
  int x[2] = { 23, 32 };
  int* x2 = x;
  printf("23 == %d\n", *x2);
  printf("23 == %d\n", x2[0]);
  x[0] = 45;
  x[1] = 56;
  printf("45 == %d\n", *(x2++));
  printf("56 == %d\n", *x2);
  printf("56 == %d\n", x2[0]);

  char* nul1 = NULL;
  char* nul2 = 0;
  if (nul1 == NULL) {
    puts("null == null");
  }
  if (nul2 == NULL) {
    puts("null == null");
  }
  if (u == NULL) {
    puts("ERROR: u == null");
  }

  if (u == "test") {
    puts("ERROR: u == test");
  }

  if ("test" == "test") {
    puts("test == test");
  }
  if ("test" != "test") {
    puts("ERROR: test");
  }
  if (v[0] != "string1") {
    puts("ERROR: v[0] != string1");
  }
}

void functions() {
  lval_T param;
  memset(&param, 2, sizeof(param));
  printf("lval_T.b: %d\n", param.b);
  printf("lval_T.b: %d\n", (&param)->b);
  // error currently
  //printf("lval_T: %d\n", (*(&param)).b);
  
  time_t starttime;
  starttime = time(NULL);
  printf("starttime: %d\n", starttime);

  char* a = malloc(10);
  char* b = "hello";
  char* c = "world";
  puts(b);
  puts(c);
  strcpy(a, b);
  puts(a);
  strcpy(a, c);
  puts(a);
}

// varargs
void printargs(int arg1, ...)
{
  va_list ap;
  int i;
 
  va_start(ap, arg1); 
  for (i = arg1; i >= 0; i = va_arg(ap, int))
    printf("%d ", i);
  va_end(ap);
  puts("");
}

int main(int argc, char** argv) {
  easy();
  structs();
  pointers();
  functions();
  printargs(5, 2, 14, 84, 97, 15, -1, 48, -1);
  return 0;
}
