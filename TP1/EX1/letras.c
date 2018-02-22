#include <stdio.h>

int letraNormal(caracter) {
  if ((65 <= caracter && caracter <= 90) || (97 <= caracter && caracter <= 122)) {
    return 1;
  }

  return 0;
}

int tirarAcentos(int caracter) {
  if(192 <= caracter && caracter <= 195) {
    return (int) 'A';
  }

  if(224 <= caracter && caracter <= 227) {
    return (int) 'a';
  }

  if(201 <= caracter && caracter <= 202) {
    return (int) 'E';
  }

  if(233 <= caracter && caracter <= 234) {
    return (int) 'e';
  }

  if(caracter == 205) {
    return (int) 'I';
  }

  if(caracter == 237) {
    return (int) 'i';
  }

  if(211 <= caracter && caracter <= 213) {
    return (int) 'O';
  }

  if(243 <= caracter && caracter <= 245) {
    return (int) 'o';
  }

  if(caracter == 218) {
    return (int) 'U';
  }

  if(caracter == 250) {
    return (int) 'u';
  }

  return caracter;
}

int tirarCedilhas(int caracter) {
  if(caracter == 199) {
    return 'C';
  }

  if(caracter == 231) {
    return 'c';
  }

  return caracter;
}

int tornarMinuscula(int caracter) {
  if (65 <= caracter && caracter <= 90) {
    return caracter + 32;
  }

  return caracter;
}

int tornarMaiuscula(int caracter) {
  if (97 <= caracter && caracter <= 122) {
    return caracter - 32;
  }

  return caracter;
}
