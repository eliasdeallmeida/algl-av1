#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// declaração das funções
void limpaTela();
float **alocaMatriz(int);
void liberaMatriz(float**, int);
void preencheMatriz(float**, int);
float determinante(float**, int);
float **matrizInversa(float**, float**, float, int);
float **matrizMudancaDeBase(float**, float**, int);
void imprimeMatriz(float**, int);

int main(void){
    float **mat_a, **mat_b, **mat_inv, **mat_mb, det_a, det_b;
    int n, opcao, controle = 0;
    
    do{
        if(!controle){
            limpaTela();
            // recebe tamanho NxN
            printf("Informe o tamanho da matriz [NxN]: ");
            scanf("%d",&n);
            // aloca dinamicamente a memória
            mat_a = alocaMatriz(n);
            mat_b = alocaMatriz(n);
            mat_inv = alocaMatriz(n);
            mat_mb = alocaMatriz(n);
            // recebe as matrizes A e B
            puts("\nMatriz A");
            preencheMatriz(mat_a, n);
            puts("Matriz B");
            preencheMatriz(mat_b, n);
            controle++;
        }
        printf("Pressione ENTER para continuar...");
        setbuf(stdin, NULL);
        getchar();
        limpaTela();
        // mostra as matrizes na tela
        puts("Matriz A");
        imprimeMatriz(mat_a, n);
        puts("Matriz B");
        imprimeMatriz(mat_b, n);
        // exibe menu de opções
        printf("=-=-=-=-=-=-=-= MENU =-=-=-=-=-=-=-=\n");
        puts("(1) determinante de A");
        puts("(2) determinante de B");
        puts("(3) matriz inversa de A");
        puts("(4) matriz inversa de B");
        puts("(5) matriz de mudaça de base A->B");
        puts("(6) matriz de mudaça de base B->A");
        puts("(7) reescrever matrizes");
        puts("(8) alterar tamanho das matrizes");
        puts("(9) sair");
        printf(">>> Sua opção: ");
        scanf("%d", &opcao);
        // executa os comandos para cada caso
        switch(opcao){
            case 1:
                det_a = determinante(mat_a, n);
                printf("\nDeterminante de A = %.1f\n\n", det_a);
                break;
            case 2:
                det_b = determinante(mat_b, n);
                printf("\nDeterminante de B = %.1f\n\n", det_b);
                break;
            case 3:
                det_a = determinante(mat_a, n);
                if(det_a){
                    mat_inv = matrizInversa(mat_inv, mat_a, det_a, n);
                    puts("\nMatriz inversa de A");
                    imprimeMatriz(mat_inv, n);
                }else{
                    printf("\nMatriz A não é uma base!\n\n");
                }
                break;
            case 4:
                det_b = determinante(mat_b, n);
                if(det_b){
                    mat_inv = matrizInversa(mat_inv, mat_b, det_b, n);
                    puts("\nMatriz inversa de B");
                    imprimeMatriz(mat_inv, n);
                }else{
                    printf("\nMatriz B não é uma base!\n\n");
                }
                break;
            case 5:
                det_a = determinante(mat_a, n);
                det_b = determinante(mat_b, n);
                if(det_a && det_b){
                    mat_inv = matrizInversa(mat_inv, mat_b, det_b, n);
                    mat_mb = matrizMudancaDeBase(mat_inv, mat_a, n);
                    puts("\nMatriz de mudança de base A->B");
                    imprimeMatriz(mat_mb, n);
                }else if(!det_a && !det_b){
                    printf("\nNenhuma delas são bases!\n\n");
                }else if(!det_a){
                    printf("\nMatriz A não é uma base!\n\n");
                }else if(!det_b){
                    printf("\nMatriz B não é uma base!\n\n");
                }
                break;
            case 6:
                det_a = determinante(mat_a, n);
                det_b = determinante(mat_b, n);
                if(det_a && det_b){
                    mat_inv = matrizInversa(mat_inv, mat_a, det_a, n);
                    mat_mb = matrizMudancaDeBase(mat_inv, mat_b, n);
                    puts("\nMatriz de mudança de base B->A");
                    imprimeMatriz(mat_mb, n);
                }else if(!det_a && !det_b){
                    printf("\nNenhuma delas são bases!\n\n");
                }else if(!det_a){
                    printf("\nMatriz A não é uma base!\n\n");
                }else if(!det_b){
                    printf("\nMatriz B não é uma base!\n\n");
                }
                break;
            case 7:
                limpaTela();
                puts("Matriz A");
                preencheMatriz(mat_a, n);
                puts("Matriz B");
                preencheMatriz(mat_b, n);
                break;
            case 8:
                controle = 0;
                break;
            case 9:
                limpaTela();
                puts("Programa encerrado.");
                break;
            default:
                printf("\nOpção inválida!\n\n");
        }
    }while(opcao != 9);

    // libera memória alocada
    liberaMatriz(mat_a, n);
    liberaMatriz(mat_b, n);
    liberaMatriz(mat_inv, n);
    liberaMatriz(mat_mb, n);

    return 0;
} // fim do programa

// funções utilizadas
void limpaTela(){
    #ifdef _WIN32
        system("cls");
    #elif _WIN64
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}

float **alocaMatriz(int n){
    float **mat;
    mat = calloc(n, sizeof(float*));
    if(mat == NULL){
        puts("Memória insuficiente!");
        exit(1);
    }
    for(int i = 0; i < n; i++){
        mat[i] = calloc(n, sizeof(float));
        if(mat[i] == NULL){
            puts("Memória insuficiente!");
            exit(1);
        }
    }
    return mat;
}

void liberaMatriz(float **mat, int n){
    for(int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

void preencheMatriz(float **mat, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("e[%d][%d] = ", i+1, j+1);
            scanf("%f", &mat[i][j]);
        }
    }
    printf("\n");
}

float determinante(float **mat, int n){
    float **m = alocaMatriz(n-1);
    float det = 0;
    int x, y, sinal = 1;
    if(n == 1)
        return mat[0][0];
    for(int i = 0; i < n; i++){
        x = y = 0;
        for(int k = 1; k < n; k++){
            for(int j = 0; j < n; j++){
                if(i != j){
                    m[x][y] = mat[k][j];
                    y++;
                }
            }
            x++;
            y = 0;
        }
        det += sinal * mat[0][i] * determinante(m, n-1);
        sinal *= -1;
    }
    liberaMatriz(m, n);
    return det;
}

float **matrizInversa(float **mat_inv, float **mat, float det, int n){
    float **mat_cof = alocaMatriz(n);
    float **m = alocaMatriz(n);
    int x, y;
    if(n == 1){
        **mat_inv = 1/det;
        return mat_inv;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
        x = y = 0;
        for(int k = 0; k < n; k++){
            for(int l = 0; l < n; l++){
                if(k != i && l != j){
                    m[x][y] = mat[k][l];
                    if(y < n-2){
                        y++;
                    }else{
                        x++;
                        y = 0;
                    }
                }
            }
        }
        mat_cof[i][j] = pow(-1, i+j) * determinante(m, n-1);
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            mat_inv[i][j] = mat_cof[j][i] / det;
        }
    }
    liberaMatriz(mat_cof, n);
    liberaMatriz(m, n);
    return mat_inv;
}

float **matrizMudancaDeBase(float **mat_inv, float **mat_ini, int n){
    float **mat_mb = alocaMatriz(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                mat_mb[i][j] += (mat_inv[i][k] * mat_ini[k][j]);
            }
        }
    }
    return mat_mb;
}

void imprimeMatriz(float **mat, int n){
    for(int i = 0; i < n; i++){
        printf("|");
        for(int j = 0; j < n; j++){
            printf(" %6.2f ", mat[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}