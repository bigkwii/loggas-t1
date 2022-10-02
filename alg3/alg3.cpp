#include "gen.hpp"
#include "matrix.hpp"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//Variable globales dos arreglos.
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

    }
    return cuadricula[m][n];
    
}

int alg3(string str1, string str2, int x) {
    //veo si alcanzan a ser todos de tamano x o me van a quedar mas pequeños
    int n = max(str1.length(), str2.length()) ;
    if (n%x !=0 && n>=x) {
        return -1;
    }

    //caso entre perfect.
    //numero de elementos en cada submatriz
    int sub = n/x;
    //creo el espacio para ir guardando las fronteras
    //son x+1 filas/columnas de tamanno n+1 cada una.
    //int filas[x+1][n+1];
    //matriz con malloc
    int **filas=NULL; // double pointer matrix
    int s=0;
    filas= (int **)malloc((n+1) * sizeof(int*));
    while( s < (n+1))
    {
        filas[s]=(int *)malloc((n+1) * sizeof(int));
        s++;
    }

    //int columnas[x+1][n+1];
    int **columnas=NULL;
    s=0;
    columnas= (int **)malloc((n+1) * sizeof(int*));
    while( s < (n+1))
    {
        columnas[s]=(int *)malloc((n+1) * sizeof(int));
        s++;
    }

    //fronteras iniciales
    //lleno la primera coluna y la primera fila con valores de 0 a n.
    for(int i = 0; i <= n; i = i + 1) filas[0][i] = i; 
    for(int j = 0; j <= n; j = j + 1) columnas[0][j] = j; 
    
    //INICIALIZO FRONTERAS.
    //debo inicializar mis subfronteras note y sur.
    //Inicializo norte.
    int norte[sub+1];
    for (int l=0; l<=sub; l++) norte[l] = filas[0][l];

    //inicializo frontera oeste.
    int oeste[sub+1];
    for (int l=0; l<=sub; l++) oeste[l] = columnas[0][l];

    //LLENAR MATRIZ.

    //recorre de arriba a abajo. Se completa la columna (j+1)
    for (int j=0; j<x; j++) {
        //?????????????
        filas[j+1][0] = norte[sub];
        //para ir de izquierda a derecha. En este ciclo se completa la fila (i+1).
        for (int i=0; i<x; i++) {
            //muestro las fronteras iniciales.

            //recorto el string para la submatriz.
            string st1 = str1.substr(sub*i,sub);
            string st2 = str2.substr(sub*i,sub);

            for (int k=1; k<=sub; k++) {

                filas[j+1][k+sub*i] = editDist(st2.substr(0,k),st1, norte,oeste);
                //cout <<filas[j+1][k+sub*i]<< ";";
            }
            //Completo la frontera este.
    
            for (int k=0; k<=sub; k++) {
                if (k==0) {
                    columnas[i+1][k+sub*j] =norte[sub];


                }
                else {
 
                    columnas[i+1][k+sub*j] = editDist(st2, st1.substr(0,k),norte,oeste);
                }
            }

            //ACTUALIZO FRONTERAS NORTE Y OESTE
            //Norte
            for (int l=0; l<=sub; l++) {
                if(i==x-1) {
                    norte[l] = filas[j+1][l];
                }
                else {
                    norte[l] = filas[j][l+sub*(i+1)];
                }
            }
            //oeste
            for (int l=0; l<=sub; l++) {
                if (i==x-1) {
                    oeste[l] = columnas[0][l+(j+1)*sub];
                }
                else {
                    oeste[l] = columnas[i+1][l+j*sub];
                }   
            } 
            //cout <<  "\n \n ";   
        }
    }
    int res = filas[x][n];

    s = 0;
    while( s < (n+1)) {free(filas[s]);s++;}
    free(filas);
    s = 0;
    while( s < (n+1)) {free(columnas[s]);s++;}
    free(columnas);
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
    for (int j = 0; j<=2; j++){
        //Para guardar las sumas.
        double sum =0;
        //se hace un ciclo para las 50 comparaciones.
        for (int i = 0; i <=  n; ++i) {
            //genero string de forma aleatoria
            string str1 = crear(len);
            string str2 = crear(len);
            int x; // numero de subdivisiones
            x = len/64 > 0 ? len/64 : 1; //

            //marco el tiempo justo antes de ejecutar el algoritmo.
            auto inicio = chrono::steady_clock::now();
            //Se ejecuta algortmo.
            
            int a =alg3(str1, str2,x);
            //Se marca el tiempo después de ejecutado el algoritmo.
            auto fin = chrono::steady_clock::now();
            if (a==-1) {
                return 10;
            }
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