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

double promedio(double a[], int len) {
    double sumatoria = 0;
    for (int x = 0; x < len; x++) {
        sumatoria += a[x];
    }
    double promedio = sumatoria / len;
    return promedio;
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
//int main(){
//    string c_array[50];
//    string * strs =generador(50, 2,c_array );

//    cout << "array = [ ";
//    for (int i = 0; i < 50; ++i) {
//        cout << strs[i] << "   ";
//    }
//    cout << "]" << endl;
//}