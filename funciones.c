#include <stdio.h>
#include <string.h>
#include "funciones.h"

void createAlumno(char nombre[], int edad, int notas[]){
    FILE *fnombre = fopen("nombres.txt","a+");
    FILE *fdatos = fopen("datos.txt","a+");

    if (fnombre == NULL || fdatos==NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }
    fputs(nombre,fnombre);
    fprintf(fdatos,"%d %d %d %d\n",edad,notas[0],notas[1],notas[2]);
    fclose(fnombre);
    fclose(fdatos);
}

void readAlumnos(){
    char nombre[20];
    int edad, n1, n2, n3, i=1, len;
    FILE *fnombre = fopen("nombres.txt","r");
    FILE *fdatos = fopen("datos.txt","r");
    if (fnombre == NULL || fdatos==NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }
    printf("#\t\tNombre\t\tEdad\t\tNota1\t\tNota2\t\tNota3\n");
    while (!feof(fnombre))
    {
        fgets(nombre,20,fnombre);
        len = strlen(nombre) - 1;
        nombre[len]='\0';
        fscanf(fdatos,"%d %d %d %d\n",&edad,&n1,&n2,&n3);
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%d\t\t%d\n",i,nombre,edad,n1,n2,n3);
    }
    fclose(fnombre);
    fclose(fdatos);
}

void findAlumnoByNombre(char nombreBuscar[], int *posNombres, int *posDatos){
    char nombre[20];
    int edad, n1, n2, n3, i=1, len, f=0;
    FILE *fnombre = fopen("nombres.txt","r");
    FILE *fdatos = fopen("datos.txt","r");
    if (fnombre == NULL || fdatos==NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }
    
    while (!feof(fnombre))
    {
        fgets(nombre,20,fnombre);
        len = strlen(nombre) - 1;
        nombre[len]='\0';
        if (strcmp(nombre,nombreBuscar)==0)
        {
            f=1;
            printf("#\t\tNombre\t\tEdad\t\tNota1\t\tNota2\t\tNota3\n");
            fscanf(fdatos,"%d %d %d %d\n",&edad,&n1,&n2,&n3);
            printf("%d\t\t%s\t\t%d\t\t%d\t\t%d\t\t%d\n",i,nombre,edad,n1,n2,n3);
            break;
        }
        *posNombres=ftell(fnombre);
        *posDatos=ftell(fdatos);
    }
    if (f==0)
    {
        printf("No existe el alumno\n");
        *posDatos=-1;
        *posNombres=-1;
    }
    fclose(fnombre);
    fclose(fdatos);
}

void updateAlumno(char nombreActualizar[20]){
    char nombre[20];
    int edad, n1, n2, n3, posNombre, posDatos;
    findAlumnoByNombre(nombreActualizar,&posNombre,&posDatos);
    if (posDatos !=-1 && posNombre!=-1)
    {
        printf("Ingrese el nuevo nombre: ");
        fgets(nombre,20,stdin);
        printf("Ingrese la nueva edad: ");
        scanf("%d",&edad);
        printf("Ingrese la nueva nota 1: ");
        scanf("%d",&n1);
        printf("Ingrese la nueva nota 2: ");
        scanf("%d",&n2);
        printf("Ingrese la nueva nota 3: ");
        scanf("%d",&n3);
        FILE *fnombre = fopen("nombres.txt", "r+");
        FILE *fdatos = fopen("datos.txt", "r+");
        if (fnombre == NULL || fdatos == NULL)
        {
            printf("Error al abrir el archivo\n");
            return;
        }
        fseek(fnombre,posNombre,0);
        fputs(nombre,fnombre);
        fseek(fdatos,posDatos,0);
        fprintf(fdatos,"%d %d %d %d\n",edad,n1,n2,n3);
        fclose(fnombre);
        fclose(fdatos);
    }
}