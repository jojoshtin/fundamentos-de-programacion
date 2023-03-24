#include <stdio.h>
#include <stdbool.h>

void main(){
    /*Fecha actual*/
    const int d_actual=23;
    const int m_actual=03;
    const int a_actual=2023;
    /*Descuentos*/
    const float desc_fem=0.15;
    const float desc_mayor=0.3;

    /*Variables*/
    int n,i,edad,a_nac,m_nac,d_nac,mujeres=0,hombres=0,mayores=0,menores=0,edad_calc,ud,cedula,sexo;
    float costo,costo_total;
    bool validez=true;

    printf("Ingrese la cantidad de citas a procesar:\n");
    scanf("%i", &n);
    printf("Ingrese el costo general de la cita:\n");
    scanf("%f", &costo);

    for(i=1;i<=n;i++){
        do{
            printf("Ingrese el sexo del paciente (1=masculino; 2=femenino):\n");
            scanf("%i", &sexo);
        } while(sexo!=1 && sexo!=2);

        do{
        printf("Ingrese la cedula del paciente:\n");
        scanf("%i", &cedula);
        } while(cedula<0);

        /*Leer y validar edad y fecha de nacimiento*/
        do{
            validez=true;
            printf("Ingrese la edad del paciente:\n");
            scanf("%i", &edad);
            printf("Ingrese el año de nacimiento del paciente:\n");
            scanf("%i", &a_nac);
            printf("Ingrese el mes de nacimiento del paciente:\n");
            scanf("%i", &m_nac);
            printf("Ingrese el dia de nacimiento del paciente:\n");
            scanf("%i", &d_nac);

            /*VALIDAR DATOS DE LA FECHA DE NACIMIENTO*/
            if(a_nac>a_actual){
                printf("La fecha de nacimiento no es valida: --------------\n");
                validez=false;
            }
            else{
                if(a_actual==a_nac){
                    if(m_nac>m_actual){
                        validez=false;
                        printf("La fecha de nacimiento no es valida: --------------\n");
                    }
                    else{
                        if(m_nac==m_actual && d_nac>d_actual){
                            validez=false;
                            printf("La fecha de nacimiento no es valida: --------------\n");
                        }
                    }
                }
            }
            if(m_nac>12 || m_nac<1){
                printf("La fecha de nacimiento no es valida: --------------\n");
                validez=false;
            }
            else{
                if (m_nac==2){
                    if((a_nac%4==0 && a_nac%100!=0) || a_nac%400==0){
                        ud=29;
                    }
                    else{
                        ud=28;
                    }
                }else if(m_nac==4 || m_nac==6 || m_nac==9 || m_nac==11){
                    ud=30;
                }else{
                    ud=31;
                }

                if(d_nac>ud){
                    printf("La fecha de nacimiento no es valida: --------------\n");
                    validez=false;
                }
            }

            if (validez){
                /*Calcular edad con fecha actual*/
                edad_calc=a_actual-a_nac;
                if(m_actual<=m_nac){
                    edad_calc=edad_calc-1;
                    if(m_actual==m_nac && d_actual>=d_nac){
                        edad_calc++;
                    }
                }
                if(edad!=edad_calc){
                printf("La fecha de nacimiento y edad no concuerdan, ingreselos nuevamente: \n");
                    /*La fecha de nacimiento o la edad son inválidos*/
                    validez=false;
                }
            }
        } while(!validez);

        costo_total=costo;
        if(sexo==1){
            hombres++;
            if(edad>60){
                printf("El paciente cuenta con un descuento del 30%c:   ",'%');
                costo_total=costo-(costo*desc_mayor);
            }
        }
        else{
                if(sexo==2){
                    mujeres++;
                if(cedula%2==0){
                    printf("El paciente cuenta con un descuento del 15%c:   ",'%');
                    costo_total=costo-(costo*desc_fem);
                }
            }
        }
        if(edad>=18){
            mayores++;
        }
        else{
            menores++;
        }
        printf("El costo total de la cita es de %f \n", costo_total);
    }
    printf("Se procesaron %i mujeres, %i hombres, %i pacientes menores de edad, %i mayores de edad", mujeres,hombres,menores,mayores);
    
}