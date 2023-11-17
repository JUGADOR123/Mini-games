#ifndef Buscaminas_h
#define Buscaminas_h

#define facil 1
#define medio 2
#define avanzado 3

const int di[4] = {1,0,-1,0};
const int dj[4] = {0,1,0,-1};

class Buscaminas
{
public:
    int filas, columnas, minas;
    vector<vector<int>> tablero;
    Buscaminas(){}
    Buscaminas(int filas, int columnas, int minas){
        this->filas = filas;
        this->columnas = columnas;
        this->minas = minas;
        vector<int> basura_(columnas, 0);
        tablero.resize(filas, basura_);
    }
    void colocar_minas(){
        int minas_colocadas=0;
        while(minas_colocadas<minas){
            int seleccion = rand()%(filas*columnas);
            int fila = seleccion / columnas;
            int columna = seleccion % filas;
            if(tablero[fila][columna]==-1) continue;
            tablero[fila][columna]=-1;
            minas_colocadas++;
        }
        return;
    }

    char mostrar(int casilla){
        if(casilla==10){
            return '.';
        }
        else if(casilla > 10){
            return (casilla-10) +'0';
        }
        else if(casilla == -2){
            return '*';
        }
        else{
            return '#';
        }
    }

    void mostrar_tablero(){
        cout<<"   ";
        for (int i=0; i<columnas;i++){
            cout<<i<<"  ";
            if(i<10) cout<<" ";
        }
        cout<<endl<<endl;

        for(int i=0; i<filas; i++){
            cout<<i<<" ";
            if(i<10) cout<<" ";
            for(int j=0; j<columnas; j++){
                cout<<mostrar(tablero[i][j])<<"   ";
            }
            cout<<endl;
        }

        return;
    }

    void expandir(int i, int j){
        for(int k = 0; k < 4; k++){
            int temp_i = i + di[k];
            int temp_j = j + dj[k];
            if(!(temp_i>=0 && temp_j>=0 && temp_i<filas && temp_j<columnas)) continue;
            if(tablero[temp_i][temp_j]==0){
                tablero[temp_i][temp_j]=10;
                expandir(temp_i,temp_j);
            }else if(tablero[temp_i][temp_j]<10 && tablero[temp_i][temp_j]>0){
                tablero[temp_i][temp_j] += 10;
            }
        }
        return;
    }
    ~Buscaminas()
    {
        cout << "Minigame Ended";
    }


};

#endif