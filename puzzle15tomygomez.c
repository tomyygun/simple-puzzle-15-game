#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 4
#define NUM_MATRICES 10
#define MIN_MOVIMIENTOS 40
#define MAX_MOVIMIENTOS 200

void imprimirMatriz(int matriz[N][N]);
int comprobarGanador(int matriz[N][N], int matrizObjetivo[N][N]);

int main (){

    int matriz[N][N];
    int i,j,contadorMovimientos=0;
    char movimiento, enter;
    int x = 3, y=3;    //representan las filas y columnas
    
    // historial de apuestas
    int historialApuestas [10];
    int historialResultados[10];
    int numPartidas = 0;

    //puntajes y apuestas
    int puntaje = 0, apuesta, movimientos, puntajeObtenido;
    
    //matrices prediseñadas
    int MATRICES[NUM_MATRICES][N][N]={ 
        { {14,8,7,12}, {1,5,10,11}, {15,9,3,0}, {6,4,13,2}},
        { {6,15,12,2}, {5,3,14,4}, {13,7,10,0}, {9,11,8,1}},
        { {5,14,9,8}, {13,2,10,0}, {15,1,12,11}, {7,6,4,3}},
        { {13,9,4,0}, {5,10,2,1}, {6,8,11,12}, {14,15,7,3}},
        { {13,15,12,6}, {10,2,0,5}, {1,11,7,9}, {14,3,4,8}},
        { {15,9,12,3}, {5,7,14,4}, {2,10,13,0}, {6,1,11,8}},
        { {7,6,9,5}, {0,8,3,10}, {1,13,2,11}, {14,4,15,12}},
        { {8,6,14,7}, {3,4,13,5}, {2,15,11,0}, {9,1,10,12}},
        { {12,0,14,7}, {4,10,8,13}, {3,6,2,15}, {9,11,1,5}},
        { {15,0,3,4}, {14,7,11,9}, {1,8,2,10}, {12,5,13,6}}
    };
    
    
    
    
    //matriz objetivo
    int MATRIZOBJETIVO[N][N] = {
        {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,0}
    };
    
    

    srand(time(NULL));
    
    
    //bucle principal
    do{
        //elegir matriz aleatoria
        int indiceAleatorio = rand() % NUM_MATRICES;
        int matrizSeleccionada[N][N];


        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                matrizSeleccionada[i][j] = MATRICES[indiceAleatorio][i][j];
                if (matrizSeleccionada[i][j] == 0){
                    y = i;
                    x = j;
                }
            }
        };


        printf("--------^u^ PUZZLE 15 ^u^---------\n");
        imprimirMatriz(matrizSeleccionada);
        //iniciar apuesta
        do {
            
            printf("Ingrese su apuesta! (debe ser entre %d y %d movimientos): \n", MIN_MOVIMIENTOS, MAX_MOVIMIENTOS);
            scanf("%d", &apuesta);

            if (apuesta < MIN_MOVIMIENTOS || apuesta > MAX_MOVIMIENTOS) {
                printf("*ERROR* Apuesta invalida. Por favor ingrese un numero entre %d y %d. \n", MIN_MOVIMIENTOS, MAX_MOVIMIENTOS);
            }
        } while (apuesta < MIN_MOVIMIENTOS || apuesta > MAX_MOVIMIENTOS );
        
        //reset de movimientos y puntajes
        movimientos = 0;
        puntajeObtenido = 0;
        contadorMovimientos=0;

        printf("PRESIONE DOS VECES SOLO PARA COMENZAR: W(arriba),S(abajo),A(izquierda),D(derecha) para mover el numero! (O presione 0 para salir)\n");
    
        //movimientos
        do {
            movimiento = getchar();
            enter = getchar();
            switch(movimiento){
                case 'w': 
                    if(y < 3 ) {
                        matrizSeleccionada[y][x]= matrizSeleccionada[y+1][x];
                        matrizSeleccionada[y+1][x] = 0;
                        imprimirMatriz(matrizSeleccionada);
                        y++;    //arriba 
                        contadorMovimientos++;
                    } else {
                        printf("Error, no es posible mover en esa posicion :(\n");
                        imprimirMatriz(matrizSeleccionada);
                    }
                    break;
                case 's': 
                    if(y > 0){
                        matrizSeleccionada[y][x]= matrizSeleccionada[y-1][x];
                        matrizSeleccionada[y-1][x] = 0;
                        imprimirMatriz(matrizSeleccionada);
                        y--;    //abajo
                        contadorMovimientos++;
                    } else {
                        printf("Error, no es posible mover en esa posicion u_u\n");
                        imprimirMatriz(matrizSeleccionada);
                    }
                    break;
                case 'a': 
                    if(x < 3){
                        matrizSeleccionada[y][x]= matrizSeleccionada[y][x+1];
                        matrizSeleccionada[y][x+1] = 0;
                        imprimirMatriz(matrizSeleccionada);
                        x++;    //izquierda
                        contadorMovimientos++;
                    } else {
                        printf("Error, no es posible mover en esa posicion o_o\n");
                        imprimirMatriz(matrizSeleccionada);
                    }
                    break;
                case 'd': 
                    if(x > 0){
                        matrizSeleccionada[y][x]= matrizSeleccionada[y][x-1];
                        matrizSeleccionada[y][x-1] = 0;
                        imprimirMatriz(matrizSeleccionada);
                        x--;    //derecha
                        contadorMovimientos++;
                    } else {
                        printf("Error, no es posible mover en esa posicion D:\n");
                        imprimirMatriz(matrizSeleccionada);
                    }
                    break;
                case '0': 
                    printf("Hasta pronto! ^u^\n");
                    break; //abandonar
                default: 
                    printf(" PRESIONE: W(arriba),S(abajo),A(izquierda),D(derecha)\n");
                break;
            }
            //contador de movimientos
           
            printf("Movimientos: %d\n",contadorMovimientos);

            movimientos++;
            
            //puntuaciones
            if (comprobarGanador(matrizSeleccionada, MATRIZOBJETIVO)){
                printf(" ¡ENHORABUENA! ¡HAS GANADO! ^U^ \n");
                printf("Total de movimientos: %d\n", contadorMovimientos);
                
                if (contadorMovimientos == apuesta)
                    puntajeObtenido = 1000;
                else if (contadorMovimientos > apuesta - 10 && contadorMovimientos < apuesta)
                    puntajeObtenido = 1200;
                else if (contadorMovimientos > apuesta && contadorMovimientos <= apuesta + 10)
                    puntajeObtenido = 500;
                else if (contadorMovimientos < apuesta - 10)
                    puntajeObtenido = 1500;
                else
                    puntajeObtenido = 0;

                printf("Puntaje obtenido: %d puntos\n",puntajeObtenido);
            }
            
        } while (movimiento != '0' && !comprobarGanador(matrizSeleccionada,MATRIZOBJETIVO));

        //historial de partidas
        historialApuestas[numPartidas] = apuesta;
        historialResultados[numPartidas] = puntajeObtenido;
        numPartidas++;

        if (numPartidas >=10) {
            printf("Historial de apuestas y resultados: \n");
            for(i=0;i<10;i++){
                printf("Partida %d: apuesta: %d, puntaje: %d \n",i+1,historialApuestas[i],historialResultados[i]);
            }
            numPartidas = 0;
        }

        printf("Desea realizar otra partida en esta ronda? (s/n): \n");
        scanf(" %c", &movimiento);
        
        printf("HISTORIAL DE APUESTAS Y RESULTADOS DE LA RONDA: \n");
        for(i=0;i<numPartidas;i++){
        printf("Partida %d: apuesta: %d, puntaje: %d \n",i+1,historialApuestas[i],historialResultados[i]);
    }

    } while (movimiento == 's');

  

    return 0;

}

//mostrar matriz
void imprimirMatriz(int matriz[N][N]) {
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(matriz[i][j] != 0){
                printf("[%2d]",matriz[i][j]);
            } else {
                printf("[  ]");
            }
            
        };
        printf("\n");
    };

}
//comprobar ganador
int comprobarGanador(int matrizSeleccionada[N][N], int matrizObjetivo[N][N]) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (matrizSeleccionada[i][j] != matrizObjetivo[i][j]) {
                return 0; // No gano todavía
            }
        }
    }
    return 1; //gano
}
