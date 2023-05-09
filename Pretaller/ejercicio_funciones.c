#include <stdio.h>
#define n 10
int vector[10];
int i;
int mayorlocal;
int mayor();
void read();
void imprimir();
float prom();
float promlocal;
float suma=0;

void read()
{
    for (i=0;i<10;i++){
        printf("Ingrese el digito #%d\n",i+1);
        scanf("%d",&vector[i]);
    }
}
int mayor(int vector[])
{
    mayorlocal=0;
    for (i=0;i<10;i++){
        if(mayorlocal<vector[i]){
            mayorlocal=vector[i];
        }
    }
    return(mayorlocal);
}
float prom(int vector[])
{
    for (i=0;i<10;i++){
        suma+=vector[i];
    }
    promlocal=suma/n;
    return(promlocal);
}
void imprimir()
{
    for (i=0;i<n;i++){
        printf("El numero en la posicion %d es: %d\n",i+1,vector[i]);
    }
    printf("El promedio de todos los valores es: %f\n", promlocal);
    printf("El mayor de los valores es: %d\n", mayorlocal);
}
int main()
{
    read(vector);
    prom(vector);
    mayor(vector);
    imprimir();
    return(0);
}