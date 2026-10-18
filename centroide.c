#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void alocar_pontos(int quantia_de_pontos, int dimensoes, double***pontos){

    *pontos = malloc(sizeof(double*) * quantia_de_pontos);

    for(int i = 0; i < quantia_de_pontos; i++){
        (*pontos)[i] = malloc(sizeof(double) * dimensoes);
    }
}

void ler_pontos(int quantia_de_pontos, int dimensoes, double **pontos){
    for(int i = 0; i < quantia_de_pontos; i++){
        printf("Forneca as dimencoes do ponto %d: ", i+1);
        for(int j = 0; j < dimensoes; j++){
            scanf("%lf", &pontos[i][j]);
        }
    }
}

void calcular_centroide(int quantia_de_pontos, int dimensoes, double **pontos, double* centroide){
    
    for(int i = 0; i < dimensoes; i++){
        double media_da_dimensao = 0;
        for(int j = 0; j < quantia_de_pontos; j++){
            media_da_dimensao += pontos[j][i];
        }
        media_da_dimensao /= quantia_de_pontos;
        centroide[i] = media_da_dimensao;   
    }

}

double calcular_distancia(int quantia_de_pontos, int dimensoes, double **pontos, double* centroide, int ponto_atual){
    double distancia_quadrado = 0;
    
    for(int i = 0; i < dimensoes; i++){
        distancia_quadrado += (centroide[i] - pontos[ponto_atual][i]) * (centroide[i] - pontos[ponto_atual][i]);
    }

    return sqrt(distancia_quadrado);
}

void calcular_distancias(int quantia_de_pontos, int dimensoes, double **pontos, double* centroide, double* distancias){

    for(int i = 0; i < quantia_de_pontos; i++){
        distancias[i] = calcular_distancia(quantia_de_pontos, dimensoes, pontos, centroide, i);
    }
}

void imprimir(int quantia_de_pontos, int dimensoes, double **pontos, double* centroide, double* distancias){
    double soma_das_distancias = 0;
   
    //imprimir centroide:
    printf("O centroide dos pontos eh:\n(");
    for(int i = 0; i < dimensoes; i++){
        if(i == 0){
            printf("%.2lf", centroide[i]);

        }
        else{ 
            printf(", %.2lf", centroide[i]);
        }
    }
    printf(")\n\n");

    //imprimir pontos e distancias
    printf("Os pontos e suas respectivas distancias sao:\n");
    for(int i  = 0; i < quantia_de_pontos; i++){
        printf("ponto %d: (", i);
        for(int j = 0; j < dimensoes; j++){
            if(j == 0){
                printf("%.2lf", pontos[i][j]);

            }
            else{ 
                printf(", %.2lf", pontos[i][j]);
            }
        }
        printf(")\n");
        printf("distancia: %.2lf\n\n", distancias[i]);
        soma_das_distancias += distancias[i];
    }
    printf("soma das distancias: %.2lf\n", soma_das_distancias);
}

int main(){
    int dimensoes, quantia_de_pontos;

    scanf("%d %d", &dimensoes, &quantia_de_pontos);

    double **pontos, *centroide;
    double *distancias;
    centroide = malloc(sizeof(double) * dimensoes);
    distancias = malloc(sizeof(double) * quantia_de_pontos);
    
    alocar_pontos(quantia_de_pontos, dimensoes, &pontos);
    
    ler_pontos(quantia_de_pontos, dimensoes, pontos);

    calcular_centroide(quantia_de_pontos, dimensoes, pontos, centroide);

    calcular_distancias(quantia_de_pontos, dimensoes, pontos, centroide, distancias);

    imprimir(quantia_de_pontos, dimensoes, pontos, centroide, distancias);
    
    for(int i = 0; i < quantia_de_pontos; i++)
        free(pontos[i]);
    
    free(pontos);
    free(centroide);
    free(distancias);

    return 0;
}