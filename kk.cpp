#include <iostream>
#include <vector>
#include <fstream>

std::vector<int> gen_random_vec(int len) {
    std::vector<int> v; 
    for(int i = 0; i < len; ++i) {
        v.push_back(rand());
    }
    return v;
} 


 
void print_vec(const std::vector<int>& vec)
{
    for(int i=0; i<vec.size(); ++i) std::cout << vec[i] << ' ';
    std::cout << '\n';
}


int kk(std::vector<int> v) 
{
    std::sort (v.begin(), v.end());
    // print_vec(v);


    int counter = 0;
    int len = v.end() - v.begin();
    while (counter < len-1) {

        int diff = v[len - 1] - v[len - 2];

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

    if ((argc != 2) && (argc != 3)) {
        printf("Usage ./kk inputfile\n");
        return -1;
    }

    char* input = argv[1];


    // READING IN FILE & PUSHING EACH NUMBER TO A VECTOR V
    std::vector<int> v;

    std::fstream myfile(input, std::ios_base::in);

    int a;
    while (myfile >> a)
    {
        v.push_back(a);
    }

    // print_vec(v);

    printf("%d\n", kk(v));


    
}