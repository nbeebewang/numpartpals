#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>

std::vector<long long> gen_random_vec(int len) {
    std::vector<long long> v; 
    for(int i = 0; i < len; ++i) {
        v.push_back(rand());
    }
    return v;
} 


 
void print_vec(const std::vector<long long>& vec)
{
    for(int i=0; i<vec.size(); ++i) std::cout << vec[i] << ' ';
    std::cout << '\n';
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
 
int main(int argc, char** argv) {

    int N = 100;

    if ((argc != 2) && (argc != 3)) {
        printf("Usage ./kk inputfile\n");
        return -1;
    }

    char* input = argv[1];


    // READING IN FILE & PUSHING EACH NUMBER TO A VECTOR V
    std::vector<long long> v(100);

    std::fstream myfile(input, std::ios_base::in);

    // int a;
    // while (myfile >> a)
    // {
    //     printf("%lli\n\n", a);
    //     v.push_back(a);
    // }

    FILE *fin = fopen(input,"r");
    for(int k=0;k<N;k++){
        fscanf(fin,"%lli\n",&v[k]);
    }
    fclose(fin);




    double s = clock();

    printf("%lli, ", kk(v));

    double time = clock() - s;

    printf("%f\n", ((float)time)/CLOCKS_PER_SEC);



}