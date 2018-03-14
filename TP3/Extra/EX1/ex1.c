#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415

typedef struct _ComplexRect
{
	float real;
    float imaginaria;
} ComplexRect;

typedef struct _ComplexAng
{
	float modulo;
    float angulo;
} ComplexAng;

float toDegrees(float radians) {
    // PI -> 180
    // RAD -> X

    return (radians * 180) / PI;
}

ComplexAng toAngular(ComplexRect rect) {
    ComplexAng output;

    output.modulo = sqrt(rect.real * rect.real + rect.imaginaria * rect.imaginaria);
    output.angulo = atan(rect.imaginaria / rect.real);

    // Se o angulo for 0 e a parte real for menor que 0, o angulo tem de ser 180
    if(rect.imaginaria == 0 && rect.real < 0) {
        output.angulo += PI;
    }

    return output;
}

ComplexRect toRectangular(ComplexAng ang) {
    ComplexRect output;

    output.real = ang.modulo * cos(ang.angulo);
    output.imaginaria = ang.modulo * sin(ang.angulo);

    return output;
}

int main() {
    int amount;
    printf("Quantidade de complexos a converter: ");
    scanf("%d", &amount);

    ComplexRect *lista = malloc(amount * sizeof(ComplexRect));

    int i;
    for(i = 0; i < amount; i++) {
        printf("Insira os coeficientes do %dº numero (real imaginaria): ", (i + 1));

        ComplexRect complex;
        scanf("%f %f", &(complex.real), &(complex.imaginaria));

        lista[i] = complex;
    }

    printf("As respetivas representaçoes polares sao:\n");
    for(i = 0; i < amount; i++) {
        ComplexRect rect = lista[i];
        ComplexAng ang = toAngular(rect);

        printf("#%d: Mod=%.2f Ang=%.2f\n", i + 1, ang.modulo, toDegrees(ang.angulo));
    }

    return 0;
}