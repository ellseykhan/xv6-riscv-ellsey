#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define N 10
#define A {{1,2,3,4,5,6,7,8,9,10},{11,12,13,14,15,16,17,18,19,20},{21,22,23,24,25,26,27,28,29,30},{31,32,33,34,35,36,37,38,39,40},{41,42,43,44,45,46,47,48,49,50},{51,52,53,54,55,56,57,58,59,60},{61,62,63,64,65,66,67,68,69,70},{71,72,73,74,75,76,77,78,79,80},{81,82,83,84,85,86,87,88,89,90},{91,92,93,94,95,96,97,98,99,100}}

#define B {{0,1,2,3,4,5,6,7,8,9},{0,1,2,3,4,5,6,7,8,9},{0,1,2,3,4,5,6,7,8,9},{0,1,2,3,4,5,6,7,8,9},{0,1,2,3,4,5,6,7,8,9},{0,1,2,3,4,5,6,7,8,9},{0,1,2,3,4,5,6,7,8,9},{0,1,2,3,4,5,6,7,8,9},{0,1,2,3,4,5,6,7,8,9},{0,1,2,3,4,5,6,7,8,9}}

void dispmatrix(int mat[N][N]);

int main(int argc, char *argv[]){
    int matrixa[N][N]=A;
    int matrixb[N][N]=B;
    int result[N][N]={0};
    printf("Matrix A: \n");
    dispmatrix(matrixa);
    printf("Matrix B: \n");
    dispmatrix(matrixb);
    for (int i=0;i<N;i++){
        int p[2];
        pipe(p);
        int ps[N]={0}; //partial sum   
        if(fork()==0){
            close(p[0]);
            for (int j=0;j<N;j++){
                for(int k=0;k<N;k++){
                    ps[j]+=matrixa[i][k]*matrixb[k][j];
                }
            }
            write(p[1],ps,N*sizeof(int));
            close(p[1]);
            exit(0);}
        else{
            close(p[1]);
            wait((int*)0);
            read(p[0],ps,N* sizeof(int));
            close(p[0]);
            for(int m=0;m<N;m++){
                result[i][m]=ps[m];
            }
        }
        
    }
    printf("Result: \n");
    dispmatrix(result);
    return 0;
};

void dispmatrix(int mat[N][N]){
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
        printf("%d ", mat[i][j]);
    }
    printf("\n");
}
}
