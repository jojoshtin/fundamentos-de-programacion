#include <stdio.h>
#include <stdbool.h>
#define suminicial 100000

/* Procedimiento que toma el ganador para cada juez y retorna
al ganador del round y el tipo de victoria */
void decision(int w,int b,int p,int *winner,int *dec);

//Función que toma el tipo de victoria y retorna lo que se le sumará al ganador en cada round
int calcpremio(int tipovic);

/* Procedimiento que toma las tarjetas y retorna el total de puntos de cada 
boxeador para cada tarjeta */
void pfinal(int tarjeta1[12][2],int tarjeta2[12][2],int tarjeta3[12][2],int *res1w,int *res1b,int *res1p,int *res2w,int *res2b,int *res2p);

/* Procedimiento que toma los puntos de cada luchador y decide quien es el ganador del
encuentro y retorna su tarjeta con más puntos y menos puntos usando el procedimiento
mayormenor */
void decision_definitiva(int *winner,int *tipovic,int *tarjetamayor,int *tarjetamenor,int puntosfloydw, int puntosfloydb, int puntosfloydp,int puntoscanelow,int puntoscanelob,int puntoscanelop);

/* Procedimiento que toma los puntos totales del ganador de cada tarjeta, las compara y retorna
el número de la mayor y de la menor */
void mayormenor(int num1,int num2,int num3,int *tarjetamayor,int *tarjetamenor);

/* Procedimiento que muestra por pantalla todos los resultados */
void imprimir(int winner,int rwinfloyd,int rwincanelo,int tipovic,int juez[],int mayortarjeta,int menortarjeta,int totalfloyd,int totalcanelo,int puntosfloyd1,int puntosfloyd2,int puntosfloyd3,int puntoscanelo1,int puntoscanelo2,int puntoscanelo3);

/* FUNCIÓN PRINCIPAL */
int main(){
    int juez[3]={1,2,3}; //Vector número de jueces
    char ans; //Variable para leer confirmaciones
    /* Ganador de cada round para cada juez, ganador definitivo del round,
    tipo de victoria, contadores de rounds ganados para cada boxeador, y
    sus premios totales: */
    int ganadorw,ganadorb,ganadorp,rwinner,tipovic,rwinfloyd=0,rwincanelo=0,premiototfloyd=suminicial,premiototcanelo=suminicial;
    /*Matrices para almacenar las tarjetas de los jueces y variables para la mayor y la menor*/
    int tarjetaw[12][2],tarjetab[12][2],tarjetap[12][2],tarjetamayor=3,tarjetamenor=3;
    /*Variable para el ganador, otra de confirmaciones y unas para los ciclos*/
    int winner,res,i,j;
    /*Puntos totales de cada boxeador para cada juez*/
    int ptotalfloydw=0,ptotalcanelow=0,ptotalfloydb=0,ptotalcanelob=0,ptotalfloydp=0,ptotalcanelop=0;
    
    //Ciclo principal para recorrer los rounds
    for (i=0;i<12;i++){
        //Ciclo para preguntar a cada juez el ganador y si hubo una caida de algun boxeador
        for(j=0;j<3;j++){
            printf("Ingrese el ganador del round para el juez %d, 1: Floyd, 2: Canelo o 3: Empate\n",juez[j]);
            if(j==0){
                //Mini ciclo para leer el ganador para el juez White y validar
                do{
                    scanf("%d",&ganadorw);
                    if((ganadorw<1)||(ganadorw>3)){
                        printf("Numero invalido, por favor ingrese de nuevo:\n");
                    }
                }while((ganadorw<1)||(ganadorw>3));
                /*Condicional para ir agregando la puntuacion dada por el juez
                a su respectiva tarjeta*/
                if(ganadorw==1){
                    tarjetaw[i][0]=10;
                    tarjetaw[i][1]=9;
                }else{
                    if(ganadorw==2){
                        tarjetaw[i][0]=9;
                        tarjetaw[i][1]=10;
                    }else{
                        tarjetaw[i][0]=10;
                        tarjetaw[i][1]=10;
                    }
                }
            }
            if(j==1){
                //Mini ciclo para leer el ganador para el juez Blue y validar
                do{
                    scanf("%d",&ganadorb);
                    if((ganadorb<1)||(ganadorb>3)){
                        printf("Numero invalido, por favor ingrese de nuevo:\n");
                    }
                }while((ganadorb<1)||(ganadorb>3));
                /*Condicional para ir agregando la puntuacion dada por el juez
                a su respectiva tarjeta*/
                if(ganadorb==1){
                    tarjetab[i][0]=10;
                    tarjetab[i][1]=9;
                }else{
                    if(ganadorb==2){
                        tarjetab[i][0]=9;
                        tarjetab[i][1]=10;
                    }else{
                        tarjetab[i][0]=10;
                        tarjetab[i][1]=10;
                    }
                }
            }
            if(j==2){
                //Mini ciclo para leer el ganador para el juez Pink y validar
                do{
                    scanf("%d",&ganadorp);
                    if((ganadorp<1)||(ganadorp>3)){
                        printf("Numero invalido, por favor ingrese de nuevo:\n");
                    }
                }while((ganadorp<1)||(ganadorp>3));
                /*Condicional para ir agregando la puntuacion dada por el juez
                a su respectiva tarjeta*/
                if(ganadorp==1){
                    tarjetap[i][0]=10;
                    tarjetap[i][1]=9;
                }else{
                    if(ganadorp==2){
                        tarjetap[i][0]=9;
                        tarjetap[i][1]=10;
                    }else{
                        tarjetap[i][0]=10;
                        tarjetap[i][1]=10;
                    }
                }
                //Ciclo para preguntar si hubo alguna caida y validar
                do{
                    printf("Hubo alguna caida o toque a la lona? Indique: y/n\n");
                    scanf(" %c",&ans);
                    if((ans!='y')&&(ans!='n')){
                        printf("Letra invalida, por favor ingrese de nuevo:\n");
                    }
                }while((ans!='y')&&(ans!='n'));
                //Ciclo en caso de que haya ocurrido una caida
                while((ans)=='y'){
                    //Ciclo para preguntar a cual boxeador y validar
                    do{
                        printf("De parte de cual boxeador? Floyd: 1, Canelo: 2\n");
                        scanf("%d",&res);
                        if((res!=1)&&(res!=2)){
                            printf("Numero invalido, por favor ingrese de nuevo:\n");
                        }
                    }while((res!=1)&&(res!=2));
                    /*Condicionales que restan 2 puntos al puntaje total del boxeador
                    que sufrio la caida*/
                    if(res==1){
                        ptotalfloydw+=(-2);
                        ptotalfloydb+=(-2);
                        ptotalfloydp+=(-2);
                    }
                    if(res==2){
                        ptotalcanelow+=(-2);
                        ptotalcanelob+=(-2);
                        ptotalcanelop+=(-2);
                    }
                    /*Ciclo para preguntar si ocurrio otra caida y dependiendo
                    la respuesta vuelva a ejecutar el ciclo de pregunta de caida*/
                    do{
                        printf("Hubo otra? Indique: y/n\n");
                        scanf(" %c",&ans);
                        if((ans!='y')&&(ans!='n')){
                        printf("Letra invalida, por favor ingrese de nuevo:\n");
                        }
                    }while((ans!='y')&&(ans!='n'));
                }
            }
        }
        //Procedimiento que retorna el ganador del round y el tipo de victoria
        decision(ganadorw,ganadorb,ganadorp,&rwinner,&tipovic);
        /*Condicional que aumenta el contador de rounds ganados al ganador y suma el debido
        porcentaje de dinero a su premio acumulado dependiendo el tipo de victoria*/
        if(rwinner==1){
            rwinfloyd++;
            premiototfloyd+=calcpremio(tipovic);
        }
        if(rwinner==2){
            rwincanelo++;
            premiototcanelo+=calcpremio(tipovic);
        }
    } //Fin de los 12 rounds

    //Procedimiento que retorna los puntos totales de cada tarjeta de cada luchador
    pfinal(tarjetaw,tarjetab,tarjetap,&ptotalfloydw,&ptotalfloydb,&ptotalfloydp,&ptotalcanelow,&ptotalcanelob,&ptotalcanelop);
    /*Procedimiento que retorna el ganador del encuentro, tipo de victoria, y la mayor
    y menor tarjeta dependiendo de las puntuaciones*/
    decision_definitiva(&winner,&tipovic,&tarjetamayor,&tarjetamenor,ptotalfloydw,ptotalfloydb,ptotalfloydp,ptotalcanelow,ptotalcanelob,ptotalcanelop);
    //Procedimiento que muestra por pantalla lo que pide el enunciado
    imprimir(winner,rwinfloyd,rwincanelo,tipovic,juez,tarjetamayor,tarjetamenor,premiototfloyd,premiototcanelo,ptotalfloydw,ptotalfloydb,ptotalfloydp,ptotalcanelow,ptotalcanelob,ptotalcanelop);
    return 0;
} //FIN FUNCION PRINCIPAL

void decision(int w,int b,int p,int *winner,int *dec){
    /*Toma como parametros la decision de cada juez (un numero del 1 al 3:
    1 Floyd, 2 Canelo, 3 empate) y por referencia el ganador y el tipo de victoria*/

    int winf=0,winc=0; //Contadores de cuantos jueces le dan la victoria a cada boxeador
    switch (w){ //Seleccion del ganador para el juez White, si un boxeador gana, su contador sube
        case 1:
            winf++;
            break;
        case 2:
            winc++;
            break;
        default:
            break;
    }
    switch (b){ //Seleccion del ganador para el juez Blue, si un boxeador gana, su contador sube
        case 1:
            winf++;
            break;
        case 2:
            winc++;
            break;
        default:
            break;
    }
    switch (p){ //Seleccion del ganador para el juez Pink, si un boxeador gana, su contador sube
        case 1:
            winf++;
            break;
        case 2:
            winc++;
            break;
        default:
            break;
    }
    /*2 Condicionales: si el ganador tiene 2 ventajas en puntos a su favor y el perdedor 1,
    retorna el numero correspondiente al ganador y la decision en este caso 1: Decision dividida*/
    if((winf==2)&&(winc==1)){
        *winner=1;
        *dec=1;
    }
    if((winc==2)&&(winf==1)){
        *winner=2;
        *dec=1;
    }
    /*2 Condicionales: si el ganador tiene las 3 ventajas en puntos a su favor retorna
    el numero correspondiente al ganador y la decision en este caso 2: Decision unanime*/
    if(winf==3){
        *winner=1;
        *dec=2;
    }
    if(winc==3){
        *winner=2;
        *dec=2;
    }
    /*2 Condicionales: si el ganador tiene 2 ventajas en puntos a su favor y el perdedor 0,
    es decir, que hubo un empate, retorna el numero correspondiente al ganador y la
    decision en este caso 3: Decision por mayoria*/
    if((winf==2)&&(winc==0)){
        *winner=1;
        *dec=3;
    }
    if((winc==2)&&(winf==0)){
        *winner=2;
        *dec=3;
    }
} //FIN PROCEDIMIENTO DECISION

int calcpremio(int tipovic){ //Toma el tipo de victoria de cada round
    int porcentaje;
    //Condicionales que dependiendo del tipo de victoria asigna a "porcentaje" lo que se sumara
    if(tipovic==1){
        porcentaje=((suminicial/100)*5);
    }
    if(tipovic==2){
        porcentaje=((suminicial/100)*10);
    }
    if(tipovic==3){
        porcentaje=((suminicial/100)*15);
    }
    return (porcentaje); //Retorna el porcentaje que se sumará en cada round al premio del ganador
} //FIN FUNCION CALCPREMIO

void pfinal(int tarjeta1[12][2],int tarjeta2[12][2],int tarjeta3[12][2],int *res1w,int *res1b,int *res1p,int *res2w,int *res2b,int *res2p){
    /*Ciclo "para" que va sumandole a 6 variables tomadas por referencia los puntos
    que cada juez le dio a cada boxeador en sus respectivas tarjetas*/
    for(int i=0;i<12;i++){
        *res1w+=tarjeta1[i][0]; //Puntos totales Floyd juez White
        *res1b+=tarjeta2[i][0]; //Puntos totales Floyd juez Blue
        *res1p+=tarjeta3[i][0]; //Puntos totales Floyd juez Pink
        *res2w+=tarjeta1[i][1]; //Puntos totales Canelo juez White
        *res2b+=tarjeta2[i][1]; //Puntos totales Canelo juez Blue
        *res2p+=tarjeta3[i][1]; //Puntos totales Canelo juez Pink
    }
} //FIN PROCEDIMIENTO PFINAL

void decision_definitiva(int *winner,int *tipovic,int *tarjetamayor,int *tarjetamenor,int puntosfloydw, int puntosfloydb, int puntosfloydp,int puntoscanelow,int puntoscanelob,int puntoscanelop){
    /*Toma por referencia las variables: ganador, tipo de victoria y la tarjeta mayor y menor
    y toma por valor los puntos totales que cada juez le dio a cada boxeador */

    int winnerw,winnerb,winnerp; // 1 variable winner para cada ganador segun cada juez
    
    /*Se usan los siguientes condicionales para comparar el puntaje de los boxeadores y determinar
    cual tiene más puntos en cada tarjeta y asignar a sus respectivas variables
    el ganador de esa tarjeta (1: Floyd, 2: Canelo, 3: empate)*/

    if(puntosfloydw>puntoscanelow){ //Si el puntaje de Floyd es mayor al de Canelo
        winnerw=1; // Ganador: Floyd
    }else{ //Si no
        if(puntoscanelow>puntosfloydw){ //Si el puntaje de Canelo es mayor al de Floyd
            winnerw=2; //Ganador: Canelo
        }else{ // Si no
            winnerw=3; //Los puntajes son iguales, por lo tanto es empate
        }
    }
    if(puntosfloydb>puntoscanelob){ //Si el puntaje de Floyd es mayor al de Canelo
        winnerb=1; // Ganador: Floyd
    }else{ //Si no
        if(puntoscanelob>puntosfloydb){ //Si el puntaje de Canelo es mayor al de Floyd
            winnerb=2; //Ganador: Canelo
        }else{ // Si no
            winnerb=3; //Los puntajes son iguales, por lo tanto es empate
        }
    }
    if(puntosfloydp>puntoscanelop){ //Si el puntaje de Floyd es mayor al de Canelo
        winnerp=1; // Ganador: Floyd
    }else{ //Si no
        if(puntoscanelop>puntosfloydp){ //Si el puntaje de Canelo es mayor al de Floyd
            winnerp=2; //Ganador: Canelo
        }else{ // Si no
            winnerp=3; //Los puntajes son iguales, por lo tanto es empate
        }
    }
    /*Se usa el procedimiento "decision" para determinar el ganador
    del encuentro y el tipo de victoria */
    decision(winnerw,winnerb,winnerp,&*winner,&*tipovic);
    /*Se usa este condicional para usar el procedimiento
    mayormenor solo con los puntos del ganador*/
    if(*winner==1){
        /*El procedimiento mayormenor compara las puntaciones totales del ganador en
        las tarjetas y retorna dos variables, una de la tarjeta mayor y otra para la
        tarjeta menor con el numero para identificarlas, si no aplica ningun cambio
        a una o ambas variables significa que 2 o todas las puntuaciones son iguales*/
        mayormenor(puntosfloydw,puntosfloydb,puntosfloydp,&*tarjetamayor,&*tarjetamenor);
    }else{
        mayormenor(puntoscanelow,puntoscanelob,puntoscanelop,&*tarjetamayor,&*tarjetamenor);
    }
}

void mayormenor(int num1,int num2,int num3,int *tarjetamayor,int *tarjetamenor){
    /*Se usan 3 condicionales para comparar los puntajes finales del boxeador
    ingresado para determinar la tarjeta mayor (0: White, 1: Blue, 2: Pink).
    Si hay 2 puntajes iguales y mayores que el puntaje diferente simplemente no hace nada
    y la variable tarjeta mayor se queda en 3 como está asignada en el cuerpo principal,
    esto para identificar cuales son iguales y poder mostrarlas por pantalla*/
    if((num1>num2)&&(num1>num3)){
        *tarjetamayor=0;
    }
    if((num2>num1)&&(num2>num3)){
        *tarjetamayor=1;
    }
    if((num3>num1)&&(num3>num2)){
        *tarjetamayor=2;
    }
    /*Se usan 3 condicionales para comparar los puntajes finales del boxeador
    ingresado para determinar la tarjeta menor (0: White, 1: Blue, 2: Pink).
    Si hay 2 puntajes iguales y menores que el puntaje diferente simplemente no hace nada
    y la variable tarjeta menor se queda en 3 como está asignada en el cuerpo principal,
    esto para identificar cuales son iguales y poder mostrarlas por pantalla*/
    if((num1<num2)&&(num1<num3)){
        *tarjetamenor=0;
    }
    if((num2<num1)&&(num2<num3)){
        *tarjetamenor=1;
    }
    if((num3<num1)&&(num3<num2)){
        *tarjetamenor=2;
    }
} // FIN PROCEDIMIENTO MAYORMENOR

void imprimir(int winner,int rwinfloyd,int rwincanelo,int tipovic,int juez[],int mayortarjeta,int menortarjeta,int totalfloyd,int totalcanelo,int puntosfloyd1,int puntosfloyd2,int puntosfloyd3,int puntoscanelo1,int puntoscanelo2,int puntoscanelo3){
    //Toma como parametros todos los valores a mostrar por pantalla
    
    /*Condicional que imprime por pantalla el ganador y hace que al premio del perdedor
    se le asigne un 40% menos de la bolsa inicial */ 
    if(winner==1){
        printf("Ganador: Floyd Mayweather\n");
        totalcanelo=((suminicial/100)*60);
    }else{
        printf("Ganador: Saul Canelo Alvarez\n");
        totalfloyd=((suminicial/100)*60);
    }
     /*Se muestra por pantalla los puntos de cada boxeador para cada juez y su total sumados*/
    printf("Puntuacion Final:\n");
    printf("Floyd:\n- White: %d / Blue: %d / Pink: %d // Total: %d\n",puntosfloyd1,puntosfloyd2,puntosfloyd3,puntosfloyd1+puntosfloyd2+puntosfloyd3);
    printf("Canelo:\n- White: %d / Blue: %d / Pink: %d // Total: %d\n",puntoscanelo1,puntoscanelo2,puntoscanelo3,puntoscanelo1+puntoscanelo2+puntoscanelo3);
    printf("Rounds ganados por Floyd: %d, perdidos: %d\n",rwinfloyd,rwincanelo);
    printf("Rounds ganados por Canelo: %d, perdidos: %d\n",rwincanelo,rwinfloyd);
    /*Se muestra por pantalla el tipo de victoria, si la variable tipovic es 1: Decision dividida,
    si es 2: Decision unanime y si es 3: Decision por mayoria*/
    switch(tipovic){
        case 1:
            printf("Tipo de victoria: Decision dividida\n");
            break;
        case 2:
            printf("Tipo de victoria: Decision unanime\n");
            break;
        case 3:
            printf("Tipo de victoria: Decision por mayoria\n");
            break;
        default:
            break;
    }

    /*Se usan estos condicionales para mostrar por pantalla (dependiendo de las variables
    mayortarjeta y menortarjeta) la tarjeta mayor y menor, la tarjeta mayor y las tarjetas
    menores si hay 2 menores e iguales o la tarjeta menor y las tarjetas mayores si hay 2
    mayores e iguales*/
    if((mayortarjeta==3)||(menortarjeta==3)){
        if(mayortarjeta!=3){
            printf("La tarjeta del ganador con mayor puntuacion fue la del juez: %d y las otras dos tarjetas son menores e iguales\n",juez[mayortarjeta]);
        }
        if(menortarjeta!=3){
            printf("La tarjeta del ganador con menor puntuacion fue la del juez: %d y las otras dos tarjetas son mayores e iguales\n",juez[mayortarjeta]);
        }
        if(mayortarjeta==menortarjeta){
            printf("Las tres tarjetas del ganador tienen la misma puntuacion\n");
        }
    }else{
        printf("La tarjeta del ganador con mayor puntuacion fue la del juez: %d y la de menor puntuacion la del juez: %d\n",juez[mayortarjeta],juez[menortarjeta]);
    }
    //Muestra por pantalla el premio de cada boxeador
    printf("Premio Floyd: $%d\n",totalfloyd);
    printf("Premio Canelo: $%d\n",totalcanelo);
} //FIN PROCEDIMIENTO IMPRIMIR