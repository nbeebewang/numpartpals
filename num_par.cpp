/* HUID: 90904116 */
#include<stdio.h>
#include<time.h>
#include<vector>
#include<math.h>
#include<iostream>
#include<valarray>


/* generate 100 random numbers to simulate random S */
void jumble(int S[],int n_iter){
    for(int i=0;i<n_iter;i++){
        S[i] = drand48()>.5;
    }
}

double arr_sum(int A[],int size){
    double result = 0;
    for(int i=0;i<size;i++){
        result += A[i];
    }
    return result;
}

/* function to determine residue of list, given assignment S */
int residue(int A[], int S[], double sum, int size){
    int result = 0;
    for(int j=0;j<size;j++){
        if(S[j]){
            result += A[j];
        }
    }
    return 2*std::abs(sum/2-result);
}

int repeated_random(int A[], int S[], double sum, int size, int n_iter){
    int current_best = sum;
    int orig_S[size];
    for(int i=0;i<n_iter;i++){
        jumble(S,size);
        int res = residue(A,S,sum,size);
        if(res < current_best){
            printf("res: %d \n",res);
            current_best = res;
            *orig_S = *S;
        }
    }
    return current_best;

}

int main(){
    int size = 20;
    int A[size];
    srand48((int)time(NULL));
    /* read integers into an array */
    FILE *fin = fopen("file.in","r");
    for(int k=0;k<size;k++){
        fscanf(fin,"%d\n",&A[k]);
    }
    fclose(fin);
    double total_sum = arr_sum(A,size);

    int S[size];
    jumble(S,size);
    int res = residue(A,S,total_sum,size);
    int score = repeated_random(A,S,total_sum,size,1000000);
    printf("final score: %d \n",score);

}

/*     for(int i=0;i<size;i++){
        printf("%d %d\n",i,S[i]);
    }
    printf("res: %d \n",res); */