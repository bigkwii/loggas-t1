#include "gen.hpp"
#include "matrix.hpp"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//Variable globales dos arreglos.
int min_3(int x, int y, int z) {return std::min({x, y, z});}

int editDistSub(string str1, string str2, int k, int l, int m, int ** frontera) {
    cout << "submatrix at: " << k << " " << l << endl;
    int mat[m+2][m+2] = {0};
    int cost;
    //lleno las m filas
    for(int i = 0; i < m; i = i + 1) {
        cout << "Write " << frontera[k][l+i] << endl;
        mat[i][0] = frontera[k][l+i];
    }
    //lleno las n columnas
    for(int j = 0; j < m; j = j + 1) {
        mat[0][j] = frontera[k][l+j];
    }
    //comienzo a llenar la tabla
    //recorro filas
    for (int i = 1; i <= m+1; i++) {
        //recorro columnas
        for (int j = 1; j <= m+1; j++) {
            //si son iguales, asigno valor 0. Si son distintas, valor 1.
            if (str1[k*m+i-1] == str2[l*m+j-1]) {
                cost = 0;
            } else {
                cost = 1;
            }
            //voy llenando la cuadricula en fila i, columna j.
            mat[i][j] = min_3(mat[i-1][j] +1, 
                                   mat[i-1] [j-1] + cost, 
                                   mat[i][j-1] +1);
        }
    }
    for(int i = 0; i < m; i = i + 1) {
        for(int j = 0; j < m; j = j + 1) {
            frontera[k+i][m+1] = mat[i][m+1];
            frontera[m+1][l+j] = mat[m+1][j];
        }
    }
    return mat[m+1][m+1];

}

int editDist(string str1, string str2, int x) {
    int n = str1.length();
    int m = n/x;
    int ** frontera = NULL;
    int s = 0;
    frontera = (int **)malloc((n+1) * sizeof(int*));
    while( s < (n+1))
    {
        frontera[s]=(int *)malloc((n+1) * sizeof(int));
        s++;
    }
    for(int i = 0; i <= n; i = i + 1) {
        frontera[i][0] = i;
    }
    for(int j = 0; j <= n; j = j + 1) {
        frontera[0][j] =j;
    }
    for(int k=0; k<x; k++){
        for(int l=0; l<x; l++){
            editDistSub(str1, str2, k, l, m, frontera);
        }
    }
    int res = frontera[n][n];
    s = 0;
    while( s < (n+1))
    {
        free(frontera[s]);
        s++;
    }
    free(frontera);
    return res;
}
    

// Acá se va a hacer los experimentos del algoritmo. Se muere xd
int main()
{
    string str1="ananasananasananasananas";
    string str2="bananabananabananabanana";
    cout << editDist(str1,str2,4);
    return 0;
}

