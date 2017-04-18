/* HUID: 90904116 */
#include<stdio.h>
#include<time.h>
#include<vector>
#include<math.h>
#include<iostream>
#include<valarray>

/* generate 'len' random binary numbers to simulate random S */
void jumble(int S[],int len){
    for(int i=0;i<len;i++){
        S[i] = drand48()>.5;
    }
}

/* generate 'len' random numbers to simulate random S */
void p_jumble(int P[],int len){
    for(int i=0;i<len;i++){
        P[i] = ceil(drand48()*100);
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

/* set the second array equal to the first before */
void v_set_equal(std::vector<long long> A,std::vector<long long> A2,int len){
    for(int i=0;i<len;i++){
        A2[i] = A[i];
    }
}

long long kk(std::vector<long long> v) 
{
    std::sort (v.begin(), v.end());
    int counter = 0;
    int len = v.end() - v.begin();
    while (counter < len-1) {

        long long diff = v[len - 1] - v[len - 2];

        // printf("index: %d, Diff: %d\n", counter,diff);
        v.erase(v.end()-1);
        v.erase(v.end()-1);
        v.insert(v.begin(),0);

        v.insert(std::upper_bound(v.begin() + counter, v.end(), diff), diff);
        // print_vec(v);

        counter ++;
    }
    return v[len-1];
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


long long arr_sum(std::vector<long long> A,int size){
    long long result = 0;
    for(int i=0;i<size;i++){
        result += A[i];
    }
    return result;
}

/* function to determine residue of list, given assignment S */
long long residue(std::vector<long long> A, int S[], long double sum, int size){
    long long result = 0;
    for(int j=0;j<size;j++){
        if(S[j]){
            result += A[j];
        }
    }
    long long final = 2*std::abs(sum/2-result);
    return final;
}

void partitionTransform(std::vector<long long> A, std::vector<long long> newA, int P[], int size) {
    for(int group=1; group<size+1; group++){
        bool searching = true;
        int first_index = -1;

        for(int i=0; i<size+1; i++){
            if (P[i] == group) {
                if (searching){
                    searching = false;
                    newA[i] = A[i];
                    first_index = i;
                }
                else {
                    newA[first_index] += A[i];
                    newA[i] = 0;
                }   
            }
        }
    }
}

long long repeated_random(std::vector<long long> A, int S[], int P[], long double sum, int size, int n_iter, bool use_P){
    long long current_best = sum;
    long long S_local[size];
    std::vector<long long> A2(size,0);
    /* first representation, then second one */
    if(use_P==0){
        for(int i=0;i<n_iter;i++){
            jumble(S,size);
            long long res = residue(A,S,sum,size);
            if(res < current_best){
                /*printf("res: %lli \n",res);*/
                current_best = res;
                *S_local = *S;
            }
        }
    }
        
    else{
        for(int i=0;i<n_iter;i++){
            p_jumble(P,size);
            partitionTransform(A,A2,P,size);
            long long res = kk(A2);
            if(res < current_best){
                /*printf("res: %lli \n",res);*/
                current_best = res;
                *S_local = *S;
            }
        }
    }
    return current_best;
}

long double T(int iter){
    double power = iter/300;
    return 300000000000*pow(.8,power);
}

long long hill_climbing(std::vector<long long> A,int S[], long double sum, int size, int n_iter){
    int place_holder[size];
    jumble(S,size);
    long long current_best = residue(A,S,sum,size);
    /*printf("initial residue: %lli \n",current_best);*/ 
    for(int k=0;k<n_iter;k++){
        random_move(S,place_holder,size);
        long long res = residue(A,place_holder,sum,size);
        if(res < current_best){
            set_equal(place_holder,S,size);
            printf("res: %lli \n",res); 
            current_best = res;
            // printf("current: %d \n",current_best);
        }
    }
    return current_best;
}

long long sim_annealing(std::vector<long long> A,int S[], long double sum, int size, int n_iter){
    int place_holder[size];
    int orig_place_holder[size];
    set_equal(S,orig_place_holder,size);

    jumble(S,size);
    long long S_res = residue(A,S,sum,size);
    long long S_res3 = S_res;
    int rand_count = 0;
    /*printf("initial residue: %lli \n",S_res);*/
    for(int k=0;k<n_iter;k++){
        random_move(S,place_holder,size);
        long long S_res2 = residue(A,place_holder,sum,size);
        if(S_res2 < S_res){
            set_equal(place_holder,S,size);
            S_res = S_res2;
            // printf("current: %d \n",S_res);
        }
        else{
            long double prob = (-S_res2 - S_res)/T(k);
            /*printf("before term: %LF \n",prob);*/
            prob = exp(prob);
            /*printf("prob: %LF \n", prob); */
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
    int size = 100;
    std::vector<long long> A(size,0);
    srand48((int)time(NULL));
    /* read integers into an array */
    FILE *fin = fopen("hi.txt","r");
    for(int k=0;k<size;k++){
        fscanf(fin,"%lli\n",&A[k]);
    }
    fclose(fin);
    long double total_sum = arr_sum(A,size);
    printf("sum: %Lf \n",total_sum);


    int S[size];
    int P[size];
    int a, b, c;
    long long scores[3] = {0,0,0};

    for(int i=0;i<1;i++){
        scores[0] += repeated_random(A,S,P,total_sum,size,25000,1);
        /*scores[1] += hill_climbing(A,S,total_sum,size,25000);
        scores[2] += sim_annealing(A,S,total_sum,size,25000);*/
        printf("hi \n");
    }
    
    long double scores_avg[3] = {scores[0],scores[1],scores[2]};
    /*scores_avg = {scores_avg[0]/100,scores_avg[1]/100,scores_avg[2]/100};*/

    printf("random score: %LF \n",scores_avg[0]);
    /*printf("hill score: %LF \n",scores_avg[1]/100);
    printf("sim_annealing score: %LF \n",scores_avg[2]/100);*/
    


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