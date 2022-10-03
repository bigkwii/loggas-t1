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
            frontera[k+i][l*m + m] = mat[i][m+1];
            frontera[k*m + m][l+j] = mat[m+1][j];
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
   //definimos n como la cantidad de pruebas a realizar. Se generarán 2n strings para estas.
    int n= 50;
    //Len corresponde al largo de los string. Se inicializa con el valor mínimo, siendo 8.
    int len = 8;
    //Se crea un arreglo para guardar los promedios para cada uno de los largos, siendo 13 
    //largos posibles.
    double prom[13];

    //se hace un ciclo para iterar sobre cada largo.
    for (int j = 0; j<=12; j++){
        //Para guardar las sumas.
        double sum =0;
        //se hace un ciclo para las 50 comparaciones.
        for (int i = 0; i <=  n; ++i) {
            //genero string de forma aleatoria
            string str1 = crear(len);
            string str2 = crear(len);
            int x; // numero de subdivisiones
            x = len/32 > 0 ? len/4 : 1; //

            //marco el tiempo justo antes de ejecutar el algoritmo.
            auto inicio = chrono::steady_clock::now();
            //Se ejecuta algortmo.
            
            editDist(str1, str2,x);
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
        cout << "Se terminó con str's de largo: " << len << " = 2^" << j+3 << "tiempo: " << sum/n <<endl;
        len=len*2;
    }
    cout << "promedios:       ";
    for(auto const& value : prom)
        cout << value << "; ";
        cout << endl;
    return 0;

}

