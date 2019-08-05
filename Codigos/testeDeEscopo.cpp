#include <iostream>

using namespace std;


int foo() {
    static int y = 0;
    y++;
    return y;
}

int main() {
    int x; 
    foo();
    foo();
    x = foo();
    cout << x << endl;
    return 0;
}
