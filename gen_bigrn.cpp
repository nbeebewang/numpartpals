/* HUID: 90904116 */
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<iostream>

/* script to generate 100 64-bit random numbers */
int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Usage ./gen_bigrn outfile\n");
        return -1;
    }

    char* outfile = argv[1];


	srand48((int)time(NULL));
	FILE *fout = fopen(outfile, "w");

	for(int k=0;k<100;k++){
		double rando = drand48()*1000000000000;
		long long rando2 = floor(rando);
		fprintf(fout,"%lli\n",rando2);
	}
}

