#include "matrix.hpp"
#include <iostream>
#include "gen.hpp"

// A Naive recursive C++ program to find minimum number
// operations to convert str1 to str2
#include <bits/stdc++.h>
using namespace std;
 
// Utility function to find minimum of three numbers
int min_3(int x, int y, int z) {return std::min({x, y, z});}


int editDist(string str1, string str2,int m1[], int m2[]) {
    // tamaño matriz
    int m = str1.length();
    int n = str2.length();

    //se crea la matriz
    int cuadricula[m+1][n+1] ;//m filas y n columnas 
    int cost;
    
    //lleno las m filas
    for(int i = 0; i <= m; i = i + 1) {
        cuadricula[i][0] = m1[i];
    }
    //lleno las n columnas
    for(int j = 0; j <= n; j = j + 1) {
        cuadricula[0][j]=m2[j]; 
    }

    //comienzo a llenar la tabla
    //recorro filas
    for(auto const& value : cuadricula[0])
                cout << value << "; ";
                cout << endl;
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
            cuadricula[i][j]= min_3(cuadricula[i-1][j]+1,
                                cuadricula[i-1][j-1]+cost,
                                cuadricula[i][j-1]+1);
            //cout << " fi="<<cuadricula[i-1][j]+1<<" b=" << cuadricula[i-1][j-1]+cost <<" c="<<cuadricula[i][j-1]+1<<" \n";
            //cout << " cuadricula2="<<cuadricula[i][j]<<" \n";

        }
        //cout << " cuadricula2="<<cuadricula[0][0]<<" \n";
        
        for(auto const& value : cuadricula[i])
                cout << value << "; ";
                cout << endl;
    }
    return cuadricula[m][n];
    
}

// Driver code
int main()
{
    string str1="traspo";
    string str2="yartax";
    int a[25];
    for (int i=0;i<=24;i++){
        a[i]=i;
    }
    int c1[]={6,7,8,9,10,11,12};
    int c2[]={6,5,5,5,5,5,5};

    cout << editDist(str2,str1,c1,c2);
}