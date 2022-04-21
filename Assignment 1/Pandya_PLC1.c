#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int count = 0, i_Count = 0, k_Count = 0, n_Count = 0, o_Count = 0, c_Count = 0, s_Count = 0;


char keywords[32][10] = {
  "auto",
  "break",
  "case",
  "char",
  "const",
  "continue",
  "default",
  "do",
  "double",
  "else",
  "enum",
  "extern",
  "float",
  "for",
  "goto",
  "if",
  "int",
  "long",
  "register",
  "return",
  "short",
  "signed",
  "sizeof",
  "static",
  "struct",
  "switch",
  "typedef",
  "union",
  "unsigned",
  "void",
  "volatile",
  "while"
};

void check_Characters(char *ptr);

int main(int arg_Count, char * arg_Values[]) {
  char chr, str[25];
  char  seprators[15] = " \t\n,;(){}[]#\"<>", operators[] = "!%^&*+=~|.<>/?";
  int x;
  char *fileName = NULL;
  FILE *src;


	if(arg_Count != 2)
	{
		fprintf(stderr, "\\%s\\imp.txt\n",arg_Values[0]);
		fprintf(stderr, "   input.c  :  The name of a file to process.\n");
		exit(1);
	}
fileName=arg_Values[1];
	
//put input file's path
  src = fopen(fileName, "r");

  if (src == NULL) {
    printf("Input file not found!!!");
    exit(0);
  }

  while ((chr = fgetc(src)) != EOF) {
    for (x = 0; x <= 14; x++) {
      if (count == -1)
        break;

      if (chr == seprators[x]) {
		  
		if (chr == '"') {
          
		  printf("\nArgument : ");
          do {
            chr = fgetc(src);
            printf("%c", chr);
          } while (chr != '"');
          printf("\n");
          count = -1;
          break;
        }
		
        if (chr == '#') {
          while (chr != '<') {
            chr = fgetc(src);
          }
          printf("\nHeader : ");
          while (chr != 'h') {
            chr = fgetc(src);
            printf("%c", chr);
          }
          chr = fgetc(src);
          printf("\n");
          count = -1;
          break;
        }

        str[count] = '\0';
        check_Characters(str);

        if (chr != '\n' && chr != ' ') {
          printf("\nSeperator : %c\n", chr);
          s_Count++;
        }
      }
    }
	
	for (x = 0; x <= 14; x++) {
      if (chr == operators[x]) {
        printf("\nOperator : %c\n", chr);
        o_Count++;
        str[count] = '\0';
        check_Characters(str);
      }
    }
    if (count != -1) {
      str[count] = chr;
      count++;
    } else
      count = 0;
  }
  printf("------- Total Count --------");
  printf("\n Identifiers \t: %d", i_Count);
  printf("\n Keywords \t: %d", k_Count);
  printf("\n Separator \t: %d", s_Count);
  printf("\n Operators \t: %d", o_Count);
  printf("\n Numbers \t: %d", n_Count);
  printf("\n----------------------------");

  return 0;
}


void check_Characters(char * ptr) {
  int i, flag = 0;
  for (i = 0; i <= 31; i++) {
    if (strcmp(keywords[i], ptr) == 0) {
      printf("\nKeyword : %s\n", ptr);
      k_Count++;
      flag = 1;
      break;
    }
  }

  if (flag == 0) {
    if (isdigit(ptr[0])) {
		printf("\nNumber : %s", ptr);
		n_Count++;
    } else {
      if (strlen(ptr) > 1) {
        printf("\nIdentifier : %s", ptr);
        i_Count++;
      }
    }
  }
  count = -1;
}