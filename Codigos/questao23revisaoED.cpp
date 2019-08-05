#include <iostream>

using namespace std;

struct atomo{
    int C;
    int H;
};

int main(){
    atomo *dados = new atomo[1];
    for(int i=0;i<1;i++){
        cin >> dados[i].C >> dados[i].H;
    }
    int total=0;
    for(int i=0;i<1;i++){
        total+=(12*(dados[i].C)+(1*(dados[i].H)));
    }
    cout << total;
    delete[] dados;
    return 0;
}
    
