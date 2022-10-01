#include <iostream>

// A Naive recursive C++ program to find minimum number
// operations to convert str1 to str2
#include <bits/stdc++.h>
using namespace std;
 
// Utility function to find minimum of three numbers
int min(int x, int y, int z) {return std::min({x, y, z});}
 
int editDist(string str1, string str2) {
    // tamaño matriz
    int m = str1.length();
    int n = str2.length();

    //se crea la matriz
    int cuadricula[m+1] [n+1]; //m filas y n columnas 
    int cost;
    
    //lleno las m filas
    for(int i = 0; i <= m; i = i + 1) {
        cuadricula[i][0] = i;
    }
    //lleno las n columnas
    for(int j = 0; j <= n; j = j + 1) {
        cuadricula[0][j] =j;
    }

    //comienzo a llenar la tabla
    //recorro filas
    for (int i = 1; i <= m; i++) {
        //recorro columnas
        for (int j = 1; j <= n; j++) {
            //si son iguales, asigno valor 0. Si son distintas, valor 1.
            if (str1[i-1] == str2[j-1]) {
                cost = 0;
            } else {
                cost = 1;
            }
            //voy llenando la cuadricula en fila i, columna j.
            cuadricula[i][j] = min(cuadricula[i-1][j] +1, 
                                   cuadricula[i-1] [j-1] + cost, 
                                   cuadricula[i][j-1] +1);
        }
    }
    return cuadricula[m][n];
    
}
// Driver code
int main()
{
    // your code goes here
    string str1 = "banana";
    string str2 = "ananas";

    cout << editDist(str1, str2);
 
    return 0;
}
