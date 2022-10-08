#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// declaração das funções
float **alocaMatriz(int n);
void preencheMatriz(float **mat, int n);
void imprimeMatriz(float **mat, int n);
float determinanteCofator(float **mat, int n);
float **cofator(float **mat, int n);
float **transposta(float **mat, float **cofator, int n);
float **multiplicaMatrizes(float **mat1, float **mat2, float **mat3, int n);

int main(void){
    float **mat_a, **mat_b, **mat_mb, **inv_b, det_a, det_b;
    int n;

    printf("Informe a dimensão da matriz: ");
    scanf("%d",&n);

    // alocação dinâmica das matrizes
    mat_a = alocaMatriz(n);
    mat_b = alocaMatriz(n);
    inv_b = alocaMatriz(n);
    mat_mb = alocaMatriz(n);

    // leitura das matrizes A e B
    puts("Matriz A");
    preencheMatriz(mat_a, n);
    puts("Matriz B");
    preencheMatriz(mat_b, n);

    // calcula determinante das matrizes A e B
    det_a = determinanteCofator(mat_a, n);
    det_b = determinanteCofator(mat_b, n);

    // verifica se são bases para calcular matriz inversa
    if(det_a && det_b){
        inv_b = cofator(mat_b, n);
    }
    else{
        if(det_a == 0 && det_b == 0){
            puts("Nenhuma delas são uma base!");
        }
        else if(det_a == 0){
            puts("A matriz A não é uma base!");
        }
        else if(det_b == 0){
            puts("A matriz B não é uma base!");
        }
        return 0;
    }
    
    // multiplica a matriz inversa de B pela matriz A para encontrar matriz de mudança de base
    mat_mb = multiplicaMatrizes(inv_b, mat_a, mat_mb, n);

    // saída de dados
    puts("Matriz A");
    imprimeMatriz(mat_a, n);
    puts("Matriz B");
    imprimeMatriz(mat_b, n);
    printf("Determinante da Matriz A = %.1f\n\n", det_a);
    printf("Determinante da Matriz B = %.1f\n\n", det_b);
    puts("Matriz inversa de B");
    imprimeMatriz(inv_b, n);
    puts("Matriz de mudança de base de A para B");
    imprimeMatriz(mat_mb, n);

    return 0;
} // fim do programa

// funções utilizadas
float **alocaMatriz(int n){
    float **mat;
    mat = calloc(n, sizeof(float*));
    for(int i = 0; i < n; i++){
        mat[i] = calloc(n, sizeof(float));
    }
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

void imprimeMatriz(float **mat, int n){
    for(int i = 0; i < n; i++){
        printf("|");
        for(int j = 0; j < n; j++){
            printf(" %5.1f ", mat[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

float determinanteCofator(float **mat, int n){
    float det = 0, sinal = 1, **b;
    int i, j, k, m, t;

    b = alocaMatriz(n);
    
    if(n == 1){
        return mat[0][0];
    }
    else{
        det = 0;
        //for para percorre toda as linhas da matriz
        for(i = 0; i < n; i++){
            // indice da matriz com a respectiva coluna e linha tirada
            m = 0;
            t = 0;
            // codigo para tirar linhas e colunas e armazenar numa outra matriz
            for(k = 0; k < n; k++){
                for(j = 0; j < n; j++){
                    //b[k][j] = 0;
                    if(k != 0 && j != i){
                        b[m][t] = mat[k][j];
                        // controle do tamanho da matriz utilizada para o calculo da determinante
                        if(t < (n - 2)){
                            t++;
                        }else{
                            t = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + sinal * (mat[0][i] * determinanteCofator(b, n-1));
            //mudança de sinal
            sinal *= -1;
        }
    }

    return (det);
}

float **cofator(float **mat, int n){
    float **cofator = alocaMatriz(n);
    float **b = alocaMatriz(n);
    int i, k, r, s, m, t;
    
    for(i = 0; i < n; i++){
        for(k = 0; k < n; k++){
            // indice da matriz com a respectiva coluna e linha tirada
            m = 0;
            t = 0;
            // codigo para tirar linhas e colunas e armazenar numa outra matriz
            for(r = 0; r < n; r++){
                for(s = 0; s < n; s++){
                    if(r != i && s != k){
                        b[m][t] = mat[r][s];
                        // controle do tamanho da matriz utilizada para o cofator
                        if(t < (n - 2))
                            t++;
                        else{
                            t = 0;
                            m++;
                        }
                    }
                }
            }
            // calculando cada cofator da Matriz de entrada
            cofator[i][k] = pow(-1, i + k) * determinanteCofator(b, n-1);
        }
    }
    
    cofator = transposta(mat, cofator, n);
    return cofator;
}

float **transposta(float **mat, float **cofator, int n){
    float **inversa = alocaMatriz(n);
    float **b = alocaMatriz(n);
    float det;

    for(int i = 0; i < n; i++){
        for(int k = 0; k < n; k++){
            b[i][k] = cofator[k][i];
        }
    }
    det = determinanteCofator(mat, n);
    for(int i = 0; i < n; i++){
        for(int k = 0; k < n; k++){
            inversa[i][k] = b[i][k] / det;
        }
    }
    return inversa;
}

float **multiplicaMatrizes(float **mat1, float **mat2, float **mat3, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                mat3[i][j] += (mat1[i][k] * mat2[k][j]);
            }
        }
    }
    return mat3;
}