#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

//genera un string aleatoreo de largo leng.
string crear(int leng) {
    char a;
    string b;
    for (int i=0; i<leng; i++) {
        a= 97+rand() %(122-97);
        b += a;
    }
    return b;
}

//se genera cant strings de largo leng
string * generador(int cant, int leng, string arr[]) {
    for (int j=0; j<cant; j++) {
        string str = crear(leng);
        arr[j] = str;
    }
    return arr;
}

//ejemplo de uso.
int main(){
    string c_array[5];
    string * strs =generador(5, 10,c_array );

    cout << "array = [ ";
    for (int i = 0; i < 5; ++i) {
        cout << strs[i] << "   ";
    }
    cout << "]" << endl;
}