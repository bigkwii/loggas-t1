#include <iostream>
#include "gen.hpp"

// A Naive recursive C++ program to find minimum number
// operations to convert str1 to str2
#include <bits/stdc++.h>
using namespace std;
 
// Utility function to find minimum of three numbers
int min(int x, int y, int z) {return std::min({x, y, z});}
 
int editDist(string str1, string str2) {
    // tamaño matriz
    int n = str1.length();
    int cost;

    //matriz con malloc
    int **mat=NULL; // double pointer matrix
    int s=0;
    mat= (int **)malloc((n+1) * sizeof(int*));
    while( s < (n+1))
    {
        mat[s]=(int *)malloc((n+1) * sizeof(int));
        s++;
    }
    
    //lleno las m filas
    for(int i = 0; i <= n; i = i + 1) {
        mat[i][0] = i;
    }
    //lleno las n columnas
    for(int j = 0; j <= n; j = j + 1) {
        mat[0][j] =j;
    }

    //comienzo a llenar la tabla
    //recorro filas
    for (int i = 1; i <= n; i++) {
        //recorro columnas
        for (int j = 1; j <= n; j++) {
            //si son iguales, asigno valor 0. Si son distintas, valor 1.
            if (str1[i-1] == str2[j-1]) {
                cost = 0;
            } else {
                cost = 1;
            }
            //voy llenando la cuadricula en fila i, columna j.
            mat[i][j] = min(mat[i-1][j] +1, 
                                   mat[i-1] [j-1] + cost, 
                                   mat[i][j-1] +1);
        }
    }
    int res = mat[n][n];
    while( s < (n+1))
    {
        free(mat[s]);
        s++;
    }
    free(mat);
    //cout  << res << endl;
    return res;
    
}
 

// Acá se va a hacer los experimentos del algoritmo. Se muere xd
int main()
{
    //definimos n como la cantidad de pruebas a realizar. Se generarán 2n strings para estas.
    int n= 50;
    //Len corresponde al largo de los string. Se inicializa con el valor mínimo, siendo 8.
    int len = 8;
    //Se crea un arreglo para guardar los promedios para cada uno de los largos, siendo 13 
    //largos posibles.
    double prom[13];

    //se hace un ciclo para iterar sobre cada largo.
    for (int j = 0; j<=10; j++){
        //Para guardar las sumas.
        double sum =0;
        //se hace un ciclo para las 50 comparaciones.
        for (int i = 0; i <=  n; ++i) {
            //genero string de forma aleatoria
            string str1 = crear(len);
            string str2 = crear(len);

            //marco el tiempo justo antes de ejecutar el algoritmo.
            auto inicio = chrono::steady_clock::now();
            //Se ejecuta algortmo.
            editDist(str1, str2);
            //Se marca el tiempo después de ejecutado el algoritmo.
            auto fin = chrono::steady_clock::now();

            //Se calcula la diferencia, en microsegundos, entre el final y el inicio.
            double duracion = chrono::duration_cast<chrono::microseconds>(fin-inicio).count();
            
            //se suma la duración a la variable sum.
            sum = +duracion;
        }
        //Se calcula el promedio de dur para el j en particular.
        prom[j] = sum/n;

        //Calculo el siguiente largo.
        len=len*2;
        cout << "Largo: " << len << " = 2^" << j+3 << endl;
    }
    cout << "promedios:       ";
    for(auto const& value : prom)
        cout << value << "; ";
        cout << endl;
    return 0;
}
