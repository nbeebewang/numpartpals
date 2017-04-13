/* HUID: 90904116 */
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<iostream>

/* script to generate 100 64-bit random numbers */
int main(){
	srand48((int)time(NULL));
	FILE *fout = fopen("rand_nums.out", "w");

	for(int k=0;k<100;k++){
		double rando = drand48()*1000000000000;
		long long rando2 = floor(rando);
		fprintf(fout,"%lli\n",rando2);
	}
}

