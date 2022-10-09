#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// declaração das funções
float **alocaMatriz(int n);
void preencheMatriz(float **mat, int n);
float determinante(float **mat, int n);
float **matrizInversa(float **mat_inv, float **mat, float det, int n);
void matrizMudancaDeBase(float **mat1, float **mat2, float **mat3, int n);
void imprimeMatriz(float **mat, int n);

int main(void){
    float **mat_a, **mat_b, **inv_a, **inv_b, **mb_ab, **mb_ba, det_a, det_b;
    int n;

    printf("Informe a dimensão da matriz: ");
    scanf("%d",&n);

    // alocação dinâmica das matrizes
    mat_a = alocaMatriz(n);
    mat_b = alocaMatriz(n);
    inv_a = alocaMatriz(n);
    inv_b = alocaMatriz(n);
    mb_ab = alocaMatriz(n);
    mb_ba = alocaMatriz(n);

    // leitura das matrizes A e B
    puts("Matriz A");
    preencheMatriz(mat_a, n);
    puts("Matriz B");
    preencheMatriz(mat_b, n);

    // determinante das matrizes A e B
    det_a = determinante(mat_a, n);
    det_b = determinante(mat_b, n);

    // verifica se são bases para calcular matriz inversa
    if(det_a && det_b){
        inv_a = matrizInversa(inv_a, mat_a, det_a, n);
        inv_b = matrizInversa(inv_b, mat_b, det_b, n);
    }else{
        if(!det_a && !det_b)
            puts("Nenhuma delas são uma base!");
        else if(!det_a)
            puts("A matriz A não é uma base!");
        else if(!det_b)
            puts("A matriz B não é uma base!");
        puts("Obs.: uma matriz é uma base quando é Linearmente Independente, ou seja, quando tem Determinante ≠ 0");
        return 0;
    }
    
    // calcula as matrizes de mudança de base
    matrizMudancaDeBase(inv_b, mat_a, mb_ab, n);
    matrizMudancaDeBase(inv_a, mat_b, mb_ba, n);

    // saída de dados
    puts("Matriz A");
    imprimeMatriz(mat_a, n);
    puts("Matriz B");
    imprimeMatriz(mat_b, n);
    printf("Determinante da matriz A = %.1f\n\n", det_a);
    printf("Determinante da matriz B = %.1f\n\n", det_b);
    puts("Matriz inversa de A");
    imprimeMatriz(inv_a, n);
    puts("Matriz inversa de B");
    imprimeMatriz(inv_b, n);
    puts("Matriz de mudança de base de A para B");
    imprimeMatriz(mb_ab, n);
    puts("Matriz de mudança de base de B para A");
    imprimeMatriz(mb_ba, n);

    return 0;
} // fim do programa

// funções utilizadas
float **alocaMatriz(int n){
    float **mat;
    mat = calloc(n, sizeof(float*));
    for(int i = 0; i < n; i++)
        mat[i] = calloc(n, sizeof(float));
    return mat;
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
    return mat_inv;
}

void matrizMudancaDeBase(float **mat1, float **mat2, float **mat3, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                mat3[i][j] += (mat1[i][k] * mat2[k][j]);
            }
        }
    }
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