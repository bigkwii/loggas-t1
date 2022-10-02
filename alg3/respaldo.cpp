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
    if (n%x !=0) {
        return 0;
    }

    //caso entre perfect.
    //numero de elementos en cada submatriz
    int sub = n/x;
    //creo el espacio para ir guardando las fronteras
    //son x+1 filas/columnas de tamanno n+1 cada una.
    int filas[x+1][n+1];
    int columnas[x+1][n+1];

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
            //--------------------------------------
            cout << "j="<<j<< " i="<<i;
            cout << "norte ";
            for(auto const& value : norte)
                cout << value << "; ";
                cout << endl;
            //--------------------------------------

            //--------------------------------------
            cout << "oeste ";
            for(auto const& value : oeste)
                cout << value << "; ";
                cout << endl;
            //--------------------------------------

            //recorto el string para la submatriz.
            string st1 = str1.substr(sub*i,sub);
            string st2 = str2.substr(sub*i,sub);


            //para mostrar substring.
            //--------------------------------------
            //cout << " s1 "<<st1<< " s2 "<<st2<< " \n";
            //--------------------------------------

            //LLENAR FRONTERAS.

            //Se llena la frontera sur:

            //--------------------------------------
            //cout << "sur: \n";
            //--------------------------------------

            cout <<"sur \n";
            cout <<filas[j+1][sub*i]<< ";";
            for (int k=1; k<=sub; k++) {

                //mostrar strings comparandose.
                //--------------------------------------
                cout<< " st2.substr(0,k)="<< st2.substr(0,k)<<" st1="<<st1<<" ;\n";
                //--------------------------------------
                
                filas[j+1][k+sub*i] = editDist(st2.substr(0,k),st1, norte,oeste);
                cout <<filas[j+1][k+sub*i]<< ";";
            }
            //Completo la frontera este.
    
            //--------------------------------------
            //cout << "\n este \n";
            //--------------------------------------
            cout <<" \neste \n";
            for (int k=0; k<=sub; k++) {
                if (k==0) {
                    columnas[i+1][k+sub*j] =norte[sub];

                    //--------------------------------------
                    //cout <<columnas[i+1][0]<< ";";
                    //--------------------------------------
                }
                else {
                    //--------------------------------------
                    //cout<< " st1.substr(0,k)="<< st1.substr(0,k)<<" st2="<<st2<<" ;\n";
                    //--------------------------------------
                    
                    columnas[i+1][k+sub*j] = editDist(st2, st1.substr(0,k),norte,oeste);
                    
                    //--------------------------------------
                    //cout <<columnas[i+1][k+sub*j]<< " ;";
                    //--------------------------------------
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
            cout <<  "\n \n ";   
        }
    }
    return filas[x][n];
}

int main() {
        //Para guardar las sumas.
        string str1="abcdefghijklmnopqrstuvwn";
        string str2="abcbefghijklmnopqrstuvwo";

        cout << alg3(str1,str2,4);

}
