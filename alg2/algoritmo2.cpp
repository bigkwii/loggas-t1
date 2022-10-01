#include "gen.hpp"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int min(int x, int y, int z) {return std::min({x, y, z});}

int columna(string str1, string str2) {
    int n = max(str1.length(), str2.length());
    int diag;
    //Creo la columna de tamaño n
    int col[n+1];
    //lleno la columna de valores de 0 a n
    for(int i = 0; i <= n; i = i + 1) {
        col[i] = i;
    }
    //for(auto const& value : col)
    //    cout << value << "; ";
    //    cout << endl;
    
    //para el algoritmo, los siguientes pasos:
    //1. si col[0] = col[0] +1;
    //2. si no, guardo col[i], col [i-1]. 
    //3. col[i] = min(...)

    //debo hacer una iteracion por cada n
    
    for(int i = 0; i < n; i = i + 1) {
        //hago una copia del arreglo.
        int copy[n+1];
        for (int k=0; k<=n; k++) {
            copy[k] = col[k];
        }
        //comienzo a editar
        col[0] = col[0] +1;
        for(int j = 1; j <= n; j = j + 1) {
            int N = col[j];  //norte
            int NO= copy[j-1]; //NO

            //determino el valor de la diagonal comparando los string.
            if (str1[i] == str2[j-1]) {
                diag = 0;
            } else {
                diag = 1;
            }
            col[j] = min(col[j-1] +1, N+1 , NO + diag);       
        }
        //recorro la columna
        //for(auto const& value : col)
        //cout << value << "; ";
        //cout << endl;
    }
    return col[n];
}




// Acá se va a hacer los experimentos del algoritmo
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

            //marco el tiempo justo antes de ejecutar el algoritmo.
            auto inicio = chrono::steady_clock::now();
            //Se ejecuta algortmo.
            columna(str1, str2);
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
    }
    cout << "promedios:       ";
    for(auto const& value : prom)
        cout << value << "; ";
        cout << endl;
    return 0;
}