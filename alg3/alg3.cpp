#include "gen.hpp"
#include "matrix.hpp"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Utility function to find minimum of three numbers
int min(int x, int y, int z) {return std::min({x, y, z});}
 
int editDist(string str1, string str2) {
    // tamaño matriz
    int m = str1.length();
    int n = str2.length();

    //se crea la matriz
    MatrixI cuadricula = MatrixI(m+1, n+1, 0); //m filas y n columnas 
    int cost;
    
    //lleno las m filas
    for(int i = 0; i <= m; i = i + 1) {
        cuadricula.set(i,0, i);
    }
    //lleno las n columnas
    for(int j = 0; j <= n; j = j + 1) {
        cuadricula.set(0,j,j);
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
            cuadricula.set(i, j, min(cuadricula.get(i-1,j)+1, cuadricula.get(i-1,j-1)+cost, cuadricula.get(i,j-1)+1));
        }
    }
    return cuadricula.get(m,n);
    
}





int alg3(string str1, string str2, int x) {
    //veo si alcanzan a ser todos de tamano x o me van a quedar mas pequeños
    int n = max(str1.length(), str2.length()) ;
    
    if (n%x !=0) {
        return 0;
    }

    //caso entre perfect.
    //creo las primeras dos cosas.
    int fila1[n+1];
    int columna1[n+1];

    //recorremos de izquierda a derecha.
    int sub = n/x;
    //para ir de arriba a abajo
    for (int j=0; j<=1; j++) {
        //para ir de izquierda a derecha
        for (int i=0; i<=x; i++) {
            //genero la submatriz para esta iteración, que sería.[sub*i, sub*(i+1)]
            
            int k;
            //saco los substring en este caso.
            string st1 = str1.substr(0,sub);
            string st2 = str2.substr(0,sub);
            //donde guardaré mi frontera.
            int fron_fil[sub];
            int fron_col[1][sub];

            //ahora lleno la frontera. primero la frontera de la derecha:
            //Para lo que debo usar el primer algoritmo sobre el str1 completo e ir recorriendo el segundo str2.
            for (int k=1; k<=sub; k++) {
                fron_fil[k-1] = editDist(st2.substr(0,k),st1);
            }
            //for(auto const& value : fron_fil)
            //    cout << value << "; ";
            //    cout << endl;
             
            //ahora lleno la frontera de abajo.
            for (int k=1; k<=sub; k++) {
                fron_col[1][k-1] = editDist(st2,st1.substr(0,k));
            }

            //for(auto const& value : fron_fil[1])
            //    cout << value << "; ";
            //    cout << endl;

            
    }
    
}
return 0;
}

int main() {
        //Para guardar las sumas.
        string str1="banana bananabananabanana";
        string str2="ananas ananasananasananas";
        cout << alg3(str1,str2,4);

}
