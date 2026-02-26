#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define F 7
#define C 40
char laberinto[F][C];
typedef struct {int f,  c;} fila_columna;
int inicio_programa, fin_programa;

void random(int _[], int __){
    inicio_programa= clock();
    for (int i = 0; i < __; i++) {
        int mov_aleatorio = rand() % __;
        int movi_temporal = _[i];
        _[i] = _[mov_aleatorio];
        _[mov_aleatorio] = movi_temporal;
    }
}

void matriz(){
    for(int i=0; i<F; i++){
        for(int j=0; j<C;j++){
             printf("%c", laberinto[i][j]);
        }
        printf("\n");
    }
}

void dfs_crear_laberinto(int f, int c){
    fila_columna pos= {f,c};
    int romper_direcciones[]= {0,1,2,3};
    random(romper_direcciones, 4);

    for(int m=0; m<4; m++){
        int destino_f = pos.f; 
        int destino_c = pos.c;
        int romper_f = pos.f; 
        int romper_c = pos.c;

        if (romper_direcciones[m]==0) // Arriba
        {
            destino_f = pos.f - 2;
            romper_f =  pos.f - 1;
        }
        else if(romper_direcciones[m]==1) // Abajo
        {
            destino_f = pos.f + 2;
            romper_f = pos.f + 1;
        }
        else if(romper_direcciones[m]==2) // Izquierda
        {
            destino_c = pos.c - 2;
            romper_c = pos.c - 1; 
        }
        else if(romper_direcciones[m]==3) //  Derecha
        {
            destino_c = pos.c + 2;
            romper_c = pos.c + 1; 
        }

        // Validación de límites y tallado
        if(destino_f > 0 && destino_f < F-1 && destino_c > 0 && destino_c < C-1 )
        {
            if(laberinto[destino_f][destino_c]=='#')
            {
                laberinto[romper_f][romper_c]=' ';
                laberinto[destino_f][destino_c]=' ';
                dfs_crear_laberinto(destino_f, destino_c);
            }
        }
    }
}


int encontrar_salida(int f, int c) {
    // 1. Si es la salida, retornamos éxito inmediatamente
    if (laberinto[f][c] == '}') {
        matriz();
        printf("\n¡SALIDA ENCONTRADA!\n");
        return 1; 
    }

    // 2. Si no es un espacio en blanco, no podemos caminar por aquí
    // (Importante: 'l' ya no es ' ', por eso no vuelve atrás)
    if (laberinto[f][c] != ' ') return 0; 

    // 3. Marcamos el rastro
    laberinto[f][c] = 'l'; 

    matriz();        
    Sleep(100); // Un poco más rápido para que no sea eterno

    // 5. Intentamos las 4 direcciones
    if (encontrar_salida(f, c + 1) || encontrar_salida(f + 1, c) || 
        encontrar_salida(f, c - 1) || encontrar_salida(f - 1, c)) {
        return 1;
    }

   
    return 0;
}

int main(){
    srand(time(NULL));
    for(int i=0; i<F; i++){
        for(int j=0; j<C;j++){
            laberinto[i][j]='#';
        }
    }
    
    // Marcar el inicio como vacío para que el DFS pueda empezar
    laberinto[1][1]=' '; 
    
    dfs_crear_laberinto(1,1);
   

    laberinto[F-2][C-2]=' ';
    laberinto[1][0]='[';
    laberinto[F-2][C-1]='}';
    matriz();
     if(encontrar_salida(1,1)) {
        printf("\n¡CAMINO ENCONTRADO CON EXITO!\n");
    }
    fin_programa=clock();
    float tiempo=((double) (fin_programa-inicio_programa))/ CLOCKS_PER_SEC;
    printf("el tiempo trans currido fue %f", tiempo);    
    return 0;
}