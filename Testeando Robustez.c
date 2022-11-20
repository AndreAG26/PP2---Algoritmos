#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void validar(char []);


void validar(char num[]){
	int i;
    for (i = 0; i < strlen(num); i++)
    {
        if(!isdigit(num[i]) ) {
            printf("Ingrese un numero valido");
            break;
        }
    }
}

int main() {
    char a[256];
    scanf("%s", a);
    validar(a);
    printf("\nblabla");
}
