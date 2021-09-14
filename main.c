#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME 256 /* tamanho maximo para nome de arquivo */
#define vrca 1020 /* tamanho maximo para as matrizes e, consequentemente, para a figura, em pixels)*/

int **oldimage;
int **newimage;
int nthreads;
int linhas;
int colunas;
int tamanho; //se a divisao nao for inteira aqui vai o mais 1
int sobra; //resto da divisao que vamos distribuir

void tratamento_normal(int li, int lf){
//    p3rintf("tratamento normal");
    int r,g,b;
    int l;
    int c;
    for(l = li; l <= lf; l++){
        for(c = 1; c < colunas - 1; c++){
            r = c*3;
            g = r+1;
            b = r+2;
            newimage[l][r] = (             //R
                      oldimage[l-1][r]     //l - 1, c
                    + oldimage[l][r]       //l    , c
                    + oldimage[l+1][r]     //l + 1, c
                    + oldimage[l-1][r-3]   //l - 1, c - 1
                    + oldimage[l][r-3]     //l    , c - 1
                    + oldimage[l+1][r-3]   //l + 1, c - 1
                    + oldimage[l-1][r+3]   //l - 1, c + 1
                    + oldimage[l][r+3]     //l    , c + 1
                    + oldimage[l+1][r+3]   //l + 1, c + 1
                    ) / 9;
            
            newimage[l][g] = (             //G
                      oldimage[l-1][g]     //l - 1, c
                    + oldimage[l][g]       //l    , c
                    + oldimage[l+1][g]     //l + 1, c
                    + oldimage[l-1][g-3]   //l - 1, c - 1
                    + oldimage[l][g-3]     //l    , c - 1
                    + oldimage[l+1][g-3]   //l + 1, c - 1
                    + oldimage[l-1][g+3]   //l - 1, c + 1
                    + oldimage[l][g+3]     //l    , c + 1
                    + oldimage[l+1][g+3]   //l + 1, c + 1
                    ) / 9;
            
            newimage[l][b] = (             //B
                      oldimage[l-1][b]     //l - 1, c
                    + oldimage[l][b]       //l    , c
                    + oldimage[l+1][b]     //l + 1, c
                    + oldimage[l-1][b-3]   //l - 1, c - 1
                    + oldimage[l][b-3]     //l    , c - 1
                    + oldimage[l+1][b-3]   //l + 1, c - 1
                    + oldimage[l-1][b+3]   //l - 1, c + 1
                    + oldimage[l][b+3]     //l    , c + 1
                    + oldimage[l+1][b+3]   //l + 1, c + 1
                    ) / 9;
        }
    }
}

void tratamento_plinha(){
//    printf("tratamento plinha");
    int r, g, b;
    int c;
    //primeira linha e primeira coluna
    r = 0;
    g = 1;
    b = 2;
    newimage[0][r] = (          //R
              oldimage[0][r]    //l     , c
            + oldimage[1][r]    //l + 1 , c
            + oldimage[0][r+3]  //l     , c + 1
            + oldimage[1][r+3]  //l + 1 , c + 1
            ) / 4;
    
    newimage[0][g] = (          //G
              oldimage[0][g]    //l     , c
            + oldimage[1][g]    //l + 1 , c
            + oldimage[0][g+3]  //l     , c + 1
            + oldimage[1][g+3]  //l + 1 , c + 1
            ) / 4;
    
    newimage[0][b] = (          //B
              oldimage[0][b]    //l     , c
            + oldimage[1][b]    //l + 1 , c
            + oldimage[0][b+3]  //l     , c + 1
            + oldimage[1][b+3]  //l + 1 , c + 1
            ) / 4;
    
    //primeira linha e ultima coluna
    r = (colunas * 3) - 3;
    g = r+1;
    b = r+2;
    newimage[0][r] = (          //R
              oldimage[0][r]    //l     , c
            + oldimage[1][r]    //l + 1 , c
            + oldimage[0][r-3]  //l     , c - 1
            + oldimage[1][r-3]  //l + 1 , c - 1
            ) / 4;
    
    newimage[0][g] = (          //G
              oldimage[0][g]    //l     , c
            + oldimage[1][g]    //l + 1 , c
            + oldimage[0][g-3]  //l     , c - 1
            + oldimage[1][g-3]  //l + 1 , c - 1
            ) / 4;
    
    newimage[0][b] = (          //B
              oldimage[0][b]    //l     , c
            + oldimage[1][b]    //l + 1 , c
            + oldimage[0][b-3]  //l     , c - 1
            + oldimage[1][b-3]  //l + 1 , c - 1
            ) / 4;
    
    for(c = 1; c < colunas - 1; c++){
        r = c*3;
        g = r+1;
        b = r+2;
        newimage[0][r] = (          //R
                  oldimage[0][r]    //l     , c
                + oldimage[1][r]    //l + 1 , c
                + oldimage[0][r-3]  //l     , c - 1
                + oldimage[1][r-3]  //l + 1 , c - 1
                + oldimage[0][r+3]  //l     , c + 1
                + oldimage[1][r+3]  //l + 1 , c + 1
                ) / 6;

        newimage[0][g] = (          //G
                  oldimage[0][g]    //l     , c
                + oldimage[1][g]    //l + 1 , c
                + oldimage[0][g-3]  //l     , c - 1
                + oldimage[1][g-3]  //l + 1 , c - 1
                + oldimage[0][g+3]  //l     , c + 1
                + oldimage[1][g+3]  //l + 1 , c + 1
                ) / 6;

        newimage[0][b] = (          //B
                  oldimage[0][b]    //l     , c
                + oldimage[1][b]    //l + 1 , c
                + oldimage[0][b-3]  //l     , c - 1
                + oldimage[1][b-3]  //l + 1 , c - 1
                + oldimage[0][b+3]  //l     , c + 1
                + oldimage[1][b+3]  //l + 1 , c + 1
                ) / 6;
    }
}

void tratamento_ulinha(int l){
//    printf("tratamento ulinha");
    int r, g, b;
    int c;
    //ultima linha e primeira coluna
    r = 0;
    g = 1;
    b = 2;
    l = linhas - 1;
    newimage[l][r] = (          //R
              oldimage[l][r]    //l     , c
            + oldimage[l-1][r]  //l - 1 , c
            + oldimage[l][r+3]  //l     , c + 1
            + oldimage[l-1][r+3]//l - 1 , c + 1
            ) / 4;
    
    newimage[l][g] = (          //G
              oldimage[l][g]    //l     , c
            + oldimage[l-1][g]  //l - 1 , c
            + oldimage[l][g+3]  //l     , c + 1
            + oldimage[l-1][g+3]//l - 1 , c + 1
            ) / 4;
    
    newimage[l][b] = (          //B
              oldimage[l][b]    //l     , c
            + oldimage[l-1][b]  //l - 1 , c
            + oldimage[l][b+3]  //l     , c + 1
            + oldimage[l-1][b+3]//l - 1 , c + 1
            ) / 4;
    
    //ultima linha e ultima coluna
    r = (colunas * 3) - 3;
    g = r+1;
    b = r+2;
    newimage[l][r] = (          //R
              oldimage[l][r]    //l     , c
            + oldimage[l-1][r]  //l - 1 , c
            + oldimage[l][r-3]  //l     , c - 1
            + oldimage[l-1][r-3]//l - 1 , c - 1
            ) / 4;
    
    newimage[l][g] = (          //G
              oldimage[l][g]    //l     , c
            + oldimage[l-1][g]  //l - 1 , c
            + oldimage[l][g-3]  //l     , c - 1
            + oldimage[l-1][g-3]//l - 1 , c - 1
            ) / 4;
    
    newimage[l][b] = (          //b
              oldimage[l][b]    //l     , c
            + oldimage[l-1][b]  //l - 1 , c
            + oldimage[l][b-3]  //l     , c - 1
            + oldimage[l-1][b-3]//l - 1 , c - 1
            ) / 4;
    
    for(c = 1; c < colunas - 1; c++){
        r = c*3;
        g = r+1;
        b = r+2;
        newimage[l][r] = (          //R
                  oldimage[l][r]    //l     , c
                + oldimage[l-1][r]  //l - 1 , c
                + oldimage[l][r-3]  //l     , c - 1
                + oldimage[l-1][r-3]//l - 1 , c - 1
                + oldimage[l][r+3]  //l     , c + 1
                + oldimage[l-1][r+3]//l - 1 , c + 1
                ) / 6;

        newimage[l][g] = (          //G
                  oldimage[l][g]    //l     , c
                + oldimage[l-1][g]  //l - 1 , c
                + oldimage[l][g-3]  //l     , c - 1
                + oldimage[l-1][g-3]//l - 1 , c - 1
                + oldimage[l][g+3]  //l     , c + 1
                + oldimage[l-1][g+3]//l - 1 , c + 1
                ) / 6;

        newimage[l][b] = (          //B
                  oldimage[l][b]    //l     , c
                + oldimage[l-1][b]  //l - 1 , c
                + oldimage[l][b-3]  //l     , c - 1
                + oldimage[l-1][b-3]//l - 1 , c - 1
                + oldimage[l][b+3]  //l     , c + 1
                + oldimage[l-1][b+3]//l - 1 , c + 1
                ) / 6;
    }    
}

void tratamento_pcoluna(int li, int lf){
//    printf("tratamento pcoluna");
    int r, g, b;
    int l;
    for(l = li; l <= lf; l++){
        r = 0;
        g = 1;
        b = 2;
        newimage[l][r] = (          //R
                  oldimage[l][r]    //l     , c
                + oldimage[l-1][r]  //l - 1 , c
                + oldimage[l+1][r]  //l + 1 , c
                + oldimage[l][r+3]  //l     , c + 1
                + oldimage[l-l][r+3]//l - 1 , c + 1
                + oldimage[l+1][r+3]//l + 1 , c + 1
                ) / 6;

        newimage[l][g] = (          //G
                  oldimage[l][g]    //l     , c
                + oldimage[l-1][g]  //l - 1 , c
                + oldimage[l+1][g]  //l + 1 , c
                + oldimage[l][g+3]  //l     , c + 1
                + oldimage[l-l][g+3]//l - 1 , c + 1
                + oldimage[l+1][g+3]//l + 1 , c + 1
                ) / 6;
        
        newimage[l][b] = (          //B
                  oldimage[l][b]    //l     , c
                + oldimage[l-1][b]  //l - 1 , c
                + oldimage[l+1][b]  //l + 1 , c
                + oldimage[l][b+3]  //l     , c + 1
                + oldimage[l-l][b+3]//l - 1 , c + 1
                + oldimage[l+1][b+3]//l + 1 , c + 1
                ) / 6;
    }
}

void tratamento_ucoluna(int li, int lf){
//    printf("tratamento ucoluna");
    int r, g, b;
    int l;
    for(l = li; l <= lf; l++){
        r = (colunas * 3) - 3;
        g = r + 1;
        b = r + 2;
        newimage[l][r] = (          //R
                  oldimage[l][r]    //l     , c
                + oldimage[l-1][r]  //l - 1 , c
                + oldimage[l+1][r]  //l + 1 , c
                + oldimage[l][r-3]  //l     , c - 1
                + oldimage[l-l][r-3]//l - 1 , c - 1
                + oldimage[l+1][r-3]//l + 1 , c - 1
                ) / 6;

        newimage[l][g] = (          //G
                  oldimage[l][g]    //l     , c
                + oldimage[l-1][g]  //l - 1 , c
                + oldimage[l+1][g]  //l + 1 , c
                + oldimage[l][g-3]  //l     , c - 1
                + oldimage[l-l][g-3]//l - 1 , c - 1
                + oldimage[l+1][g-3]//l + 1 , c - 1
                ) / 6;
        
        newimage[l][b] = (          //B
                  oldimage[l][b]    //l     , c
                + oldimage[l-1][b]  //l - 1 , c
                + oldimage[l+1][b]  //l + 1 , c
                + oldimage[l][b-3]  //l     , c - 1
                + oldimage[l-l][b-3]//l - 1 , c - 1
                + oldimage[l+1][b-3]//l + 1 , c - 1
                ) / 6;
    }
}

void *filtra(int id){
    int linhai, linhaf, deslocamento, meutam;
    //printf("id = %d e inc = %d", id, incremento);
    meutam = tamanho;
    deslocamento = 0;
    if(sobra > 0){
        if(id < sobra){
            meutam++;
        } else {
            deslocamento = sobra;
        }
    }
    linhai = (meutam) * id + deslocamento;
    if(id == nthreads -1){
        linhaf = linhas - 1;
    } else {
        linhaf = (meutam) + linhai - 1;
    }
    printf("Eu sou a thread %d fico com: linha %d a %d\n", id, linhai, linhaf);
    
    if(id == 0){ //se essa thread pega a primeira parte
        tratamento_plinha(linhai);
        linhai++;
    } 
    if (id == (nthreads - 1)){ //se essa thread pega a última parte
        tratamento_ulinha(linhaf);
        linhaf--;
    }
    if(linhai <= linhaf){
        tratamento_pcoluna(linhai, linhaf);
        tratamento_ucoluna(linhai, linhaf);        
        if (colunas > 2){
            tratamento_normal(linhai, linhaf);
        }
    }
}

int **AlocaMatriz (int lin, int col){
    int **mat;  /* ponteiro para a matriz */
    int i;    /* variavel auxiliar      */
    if (lin < 1 || col < 1) { /* verifica parametros recebidos */
        printf("** Erro: Parametro invalido **\n");
        return(NULL);
    }
    /* aloca as linhas da matriz */
    mat = (int **) calloc (lin, sizeof(int *));
    if (mat == NULL) {
        printf("** Erro: Memoria Insuficiente **");
        return(NULL);
    }
    /* aloca as colunas da matriz */
    for (i = 0; i < lin; i++){
        mat[i] = (int*) calloc (col, sizeof(int));
        if (mat[i] == NULL) {
            printf("** Erro: Memoria Insuficiente **");
            return(NULL);
        }
    }
    return(mat); /* retorna o ponteiro para a matriz */
}

int **LiberaMatriz(int lin, int col, int **mat){
    int i;  /* variavel auxiliar */
    if(mat == NULL) return(NULL);
    if(lin < 1 || col < 1){  /* verifica parametros recebidos */
        printf("** Erro: Parametro invalido **\n");
        return(mat);
    }
    for(i=0; i<lin; i++) free(mat[i]); /* libera as linhas da matriz */
    free(mat);      /* libera a matriz */
    return(NULL); /* retorna um ponteiro nulo */
}

int main() {
    FILE *arqin;
    FILE *arqout;
    char narqin[MAX_NAME] = "c:\\temp\\img.ppm";
    char narqout[MAX_NAME] = "c:\\temp\\img2.ppm";
    char key[128];
    int i, j, max, r, g, b;
    
    printf("Quantas threads?\n");
    scanf("%d", &nthreads);
    pthread_t threads[nthreads];
    
//    printf("E qual a imagem? (maximo %d caracteres)\n", MAX_NAME);
//    scanf("%s", &narqin);
    
//    printf("E o destino? (maximo %d caracteres)\n", MAX_NAME);
//    scanf("%s", &narqout);
    
    printf("Arquivo de entrada: %s\n", narqin);
    arqin = fopen(narqin, "r");
    
    if (arqin == NULL) {
        printf("Erro na abertura do arquivo %s\n", narqin);
        return 0;
    }
    
    printf("Arquivo de saida: %s\n", narqout);
    arqout = fopen(narqout, "w");
    
    if (arqout == NULL) {
        printf("Erro na abertura do arquivo %s\n", narqin);
        return 0;
    }
    
    fscanf(arqin, "%s", key);//leio cabeçalho
    fprintf(arqout, "%s\n", key);//já escrevo o cabeçalho no novo arquivo
    printf("Arquivo tipo: %s \n", key);    
    fscanf(arqin, "%d %d %d", &colunas, &linhas, &max);//leio mais dados do cabeçalho
    fprintf(arqout, "%d\n%d %d", colunas, linhas, max);//já escrevo esses dados no novo arquivo
    printf("Colunas = %d \nLinhas = %d \n", colunas, linhas);
    
    //vamos definir o tamanho para cada um
    tamanho = linhas / nthreads;
    if ((linhas % nthreads) > 0){
        sobra = linhas % nthreads;
    } else {
        sobra = 0;
    }
    
    printf("Tamanho %d\n", tamanho);
    
    //por enquanto nao vamos aceitar imagem com apenas uma linha
    if(linhas < nthreads){
        printf("Mais threads do que dados %s\n", narqin);
        return 0;
    }
            
    oldimage = AlocaMatriz(linhas, colunas*3);    
    newimage = AlocaMatriz(linhas, colunas*3);
    
    for (i = 0; i <= linhas - 1; i++)
        for (j = 0; j <= colunas - 1; j++) {
            fscanf(arqin, " %d %d %d ", &r, &g, &b);
//            printf("RGB: %d %d %d \n", r, g, b);
            oldimage[i][j*3] = r;
            oldimage[i][j*3+1] = g;
            oldimage[i][j*3+2] = b;
//            printf("oldimage: %d %d %d \n", oldimage[i][j*3], oldimage[i][j*3+1], oldimage[i][j*3+2]);
        }
    
    //vamos criar as threads    
    for(i = 0; i < nthreads; i++){
        pthread_create (&threads[i], NULL, filtra, i);
        printf("Thread %d iniciada.\n", i);
    }
        
    //vamos receber as threads
    for(i = 0; i < nthreads; i++){
        pthread_join(threads[i], NULL);
        printf("Thread %d terminada.\n", i);
    }
    
    //escrever novo arquivo
    for (i = 0; i <= linhas - 1; i++){
        fprintf(arqout, "\n");
        for (j = 0; j <= colunas - 1; j++) {
            fprintf(arqout, "%d %d %d ", newimage[i][j*3], newimage[i][j*3+1], newimage[i][j*3+2]);
        }
    }
    
//    for (i = 0; i <= linhas - 1; i++) for (j = 0; j <= colunas - 1; j++) printf("RGB: %d %d %d \n", newimage[i][j*3], newimage[i][j*3+1], newimage[i][j*3+2]);
    
    LiberaMatriz(linhas, colunas*3, oldimage);
    LiberaMatriz(linhas, colunas*3, newimage);
    
    fclose(arqin);
    fclose(arqout);
    return 0;
}