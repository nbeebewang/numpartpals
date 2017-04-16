/* HUID: 90904116 */
#include<stdio.h>
#include<time.h>
#include<vector>
#include<math.h>
#include<iostream>
#include<valarray>


/* generate 'len' random numbers to simulate random S */
void jumble(int S[],int len){
    for(int i=0;i<len;i++){
        S[i] = drand48()>.5;
    }
}

/* generate two random indices that do not overlap */
void gen_rand_ind(int r[2], int len){
    r[0] = floor(drand48()*len);
    r[1] = r[0];
    while(r[0]==r[1]){
        r[1] = floor(drand48()*len);
    }
}

/* set the second array equal to the first before */
void set_equal(int S[],int S2[],int len){
    for(int i=0;i<len;i++){
        S2[i] = S[i];
    }
}

/* a random move of one or two elements; alters S2 and leaves S unchanged */
void random_move(int S[],int S2[],int len){
    set_equal(S,S2,len);
    int rand_indices[2];
    gen_rand_ind(rand_indices,len);
    /*printf(" r_indices: %d %d \n",rand_indices[0],rand_indices[1]);*/
    S2[rand_indices[0]] = 1-S[rand_indices[0]];
    if(drand48() > .5){
        /*printf("yes \n");*/
        S2[rand_indices[1]] = 1 - S[rand_indices[1]];
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
    int S_local[size];
    for(int i=0;i<n_iter;i++){
        jumble(S,size);
        int res = residue(A,S,sum,size);
        if(res < current_best){
            printf("res: %d \n",res);
            current_best = res;
            *S_local = *S;
        }
    }
    return current_best;
}

double T(int iter){
    double power = iter/300;
    return 10000*pow(.8,power);
}

int hill_climbing(int A[],int S[], double sum, int size, int n_iter){
    int place_holder[size];
    jumble(S,size);
    int current_best = residue(A,S,sum,size);
    printf("initial residue: %d \n",current_best);
    for(int k=0;k<n_iter;k++){
        random_move(S,place_holder,size);
        int res = residue(A,place_holder,sum,size);
        if(res < current_best){
            set_equal(place_holder,S,size);
            current_best = res;
            // printf("current: %d \n",current_best);
        }
    }
    return current_best;
}

int sim_annealing(int A[],int S[], double sum, int size, int n_iter){
    int place_holder[size];
    int orig_place_holder[size];
    set_equal(S,orig_place_holder,size);

    jumble(S,size);
    int S_res = residue(A,S,sum,size);
    int S_res3 = S_res;
    int rand_count = 0;
    printf("initial residue: %d \n",S_res);
    for(int k=0;k<n_iter;k++){
        random_move(S,place_holder,size);
        int S_res2 = residue(A,place_holder,sum,size);
        if(S_res2 < S_res){
            set_equal(place_holder,S,size);
            S_res = S_res2;
            // printf("current: %d \n",S_res);
        }
        else{
            double prob = (-S_res2 - S_res)/T(k);
            prob = exp(prob);
            if(drand48() < prob){
                rand_count += 1;
                set_equal(place_holder,S,size);
                S_res = S_res2;
            }

        }
        if(S_res < S_res3){
            S_res3 = S_res;
            set_equal(S,orig_place_holder,size);
        }
    }
    printf("random move count: %d \n",rand_count);
    return S_res3;
}

int main(){
    int size = 20;
    int A[size];
    srand48((int)time(NULL));
    /* read integers into an array */
    FILE *fin = fopen("file.in2","r");
    for(int k=0;k<size;k++){
        fscanf(fin,"%d\n",&A[k]);
    }
    fclose(fin);
    double total_sum = arr_sum(A,size);

    int S[size];
    jumble(S,size);
    int S2[size];

    int score = hill_climbing(A,S,total_sum,size,2500000);
    printf("hill score: %d \n",score);

    int score2 = repeated_random(A,S,total_sum,size,25000);
    printf("random score: %d \n",score2);

    int score3 = sim_annealing(A,S,total_sum,size,25000);
    printf("sim_annealing score: %d \n",score3);


}

/*     for(int i=0;i<size;i++){
        printf("%d %d\n",i,S[i]);
    }
    printf("res: %d \n",res); */

    /*
    int S[size];
    jumble(S,size);
    for(int i=0;i<size;i++){
        printf("%d %d\n",i,S[i]);
    }

    int S2[size];
    random_move(S,S2,size);
    for(int i=0;i<size;i++){
        printf("%d %d\n",i,S2[i]);
    }*/