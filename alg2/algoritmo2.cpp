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
    for(auto const& value : col)
        cout << value << "; ";
        cout << endl;
    
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
        for(auto const& value : col)
        cout << value << "; ";
        cout << endl;
    }
    return col[n];
}

// Driver code
int main()
{
    // your code goes here
    string str1 = "banana";
    string str2 = "ananas";

    cout << columna(str1, str2);
 
    return 0;
}