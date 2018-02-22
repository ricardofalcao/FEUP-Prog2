#include <stdio.h>

int main() {
  int numA = 0, numO = 0, numC = 0;

  FILE *file;
  file = fopen("lusiadas-utf8.txt", "r");

  int c = getc(file);
  while(c > 0) {
    int c2 = c;
    c = getc(file);

    if (c > 0) {
      if (c2 == 0xC3) {
        if(c == 0x83 || c == 0xA3) {
          numA++;
        } else if(c == 0x95 || c == 0xB5) {
          numO++;
        } else if(c == 0x87 || c == 0xA7) {
          numC++;
        }
      }
    }
  }

  printf("Letra A com til = %d\n", numA);
  printf("Letra O com til = %d\n", numO);
  printf("Letra C com cedilha = %d\n", numC);

  return 0;
}
