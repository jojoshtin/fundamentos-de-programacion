#include <stdio.h>

void leer(float *n1,float *n2);
float sum(float n1,float n2);
float rest(float n1,float n2);
float mul(float n1,float n2);
float div(float n1,float n2);

int main (){
    int op,answ;
    float num1,num2;
    do{
        printf("Que operacion desea realizar?\n");
        do{
            printf("Ingrese 1 para suma\nIngrese 2 para resta\nIngrese 3 para multiplicacion\nIngrese 4 para division\n");
            scanf("%d", &op);
            switch(op){
                case 1:
                    leer(&num1,&num2);
                    printf("El resultado de la suma es: %.2f\n",sum(num1,num2));
                    break;
                case 2:
                    leer(&num1,&num2);
                    printf("El resultado de la resta es: %.2f\n",rest(num1,num2));
                    break;
                case 3:
                    leer(&num1,&num2);
                    printf("El resultado de la multiplicacion es: %.2f\n",mul(num1,num2));
                    break;
                case 4:
                    leer(&num1,&num2);
                    if(num2!=0){
                        printf("El resultado de la division es %.2f\n",div(num1,num2));
                    }else{
                        printf("Syntax ERROR\n");
                    }
                    break;
                default: 
                    break;
            }
        }while(op<1||op>4);
        printf("Desea calcular otro numero?\n");
        printf("1 = Si\n");
        printf("0 = No\n");
        scanf("%d",&answ);
    }while(answ==1);
    printf("Fin del programa, por favor cierre\n");
    return 0;
}

float sum(float n1,float n2){
    float res;
    res=n1+n2;
    return (res);
}

float rest(float n1,float n2){
    float res;
    res=n1-n2;
    return (res);
}

float mul(float n1,float n2){
    float res;
    res=n1*n2;
    return (res);
}

float div(float n1,float n2){
    float res;
    res=n1/n2;
    return (res);
}

void leer(float *n1,float *n2){
    printf("Ingrese el numero 1\n");
    scanf("%f",&*n1);
    printf("Ingrese el numero 2\n");
    scanf("%f",&*n2);
}
