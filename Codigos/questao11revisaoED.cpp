#include <iostream>
#include <cmath>

using namespace std;
    
    
int main(){
    for(int i=0;i<5;i++){
        char letra;
        cin >> letra;
        if(letra=='C'){
            float r;
            cin >> r;
            cout <<  <<" "<< <<" "<<  << endl;
        }else if(letra=='T'){
            float l1,l2,l3;
            cin >> l1 >> l2 >> l3;
            cout <<  <<" "<<  <<" "<< sqrt((p/2)*((p/2)-l1)*((p/2)-l2)*((p/2)-l3))<< endl;
        }else if(letra=='R'){
            float lado1,lado2;
            cin >> lado1 >> lado2;
            float s=2*(lado1)+2*(lado2);
            cout << "Retangulo"<<" "<< s <<" "<< lado1*lado2 << endl;
        }
    }
    return 0;
}
