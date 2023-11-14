#ifndef Tetris_h
#define Tetris_h

#define forn(i, n) for(int i = 0; i < int(n); i++)

class Tetris
{
public:
    int N_tetris, M_tetris;
    bool pieza[4][4];
    vector<vector<bool>> p;
    Tetris(int N_tetris, int M_tetris){
        this->N_tetris = N_tetris;
        this->M_tetris = M_tetris;
        forn(i, 4) forn(j, 4) pieza[i][j]=false;
        vector<bool> basura(M_tetris, false);
        p.resize(N_tetris, basura);
    }
    void recursion(int i, int j, int lqll){
        if(lqll == 0) return;
        pieza[i][j] = true;
        int ti=10, tj = 10;
        while(!(ti < 4 && tj < 4 && ti >= 0 && tj >= 0 && !pieza[ti][tj])){
            int d = rand()%4;
            ti = i + di[d];
            tj = j + dj[d];
        }
        recursion(ti, tj, lqll-1);
        return;
    }

    void genera_pieza(){
        for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) pieza[i][j] = false;
        recursion(rand()%4,rand()%4, 4);
    }

    int colocar_pieza(int posicion, bool t){
        int i = N_tetris;
        bool z = true;
        while(z){
            for(int k = 0; k < 4; k++) for(int h = 0; h < 4; h++)
                if(pieza[k][h] && ( (i-k)-1 < 0 ||  p[(i-k)-1][posicion + h])){
                    z=false;
                }
            if(!z) break;
            i--;
        }
        if(t) return i;
        for(int k = 0; k < 4; k++) for(int h = 0; h < 4; h++)
            if(pieza[k][h]){
                if(i-k<0 || i-k>=N_tetris) return -2;
                p[i-k][h+posicion] = true;
            }
        return -1;
    }


    bool genera_matriz(int &cnt, int pos){
        cout<<"\n";
        for(int k = 0; k < 4; k++, cout<<"\n") for(int i = 0; i < M_tetris; i++){
            int ti = i - pos;
            if(ti >= 0 && ti < 4 && pieza[k][ti]){
                cout<<"#";
            }else cout<<" ";
        }
        vector<int> filas_borradas(N_tetris, 0);
        bool pierde = false;
        for(int i = N_tetris-1; i >= 0; i--){
            bool z = true;
            for(int j = 0; j < M_tetris; j++){
                if(p[i][j]) {
                    if(i==N_tetris-1) pierde = true;
                }
                else{
                    z = false;
                }
            }
            if(z) {
                filas_borradas[i]=1;
                cnt++;
                for(int j = 0; j < M_tetris; j++) p[i][j] = false;
            }
        }

        if(pierde) return false;
        for(int i = 1; i < N_tetris; i++){
            filas_borradas[i] += filas_borradas[i-1];
            for(int j = 0; j < M_tetris; j++){
                if(p[i][j]){
                    p[i][j]=false;
                    if(i-filas_borradas[i]>=0) p[i-filas_borradas[i]][j] = true;
                }
            }
        }
        int g = colocar_pieza(pos, true);
        for(int i = N_tetris-1; i >= 0; i--){
            for(int j = 0; j < M_tetris; j++){
                if(g-i>=0 && g-i<=3 && j-pos>=0 && j-pos<=3  && pieza[g-i][j-pos]) cout<<"o";
                else if(p[i][j])cout<<"#";
                else cout<<".";
            }
            cout<<"\n";
        }
        return true;
    }
    void mueve(int &posicion, short direccion){
        for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) 
            if(pieza[i][j] && ( j + posicion + direccion < 0 || j + posicion + direccion >= M_tetris)) return;
        posicion += direccion;
        return;
    }
    void girar_pieza(){
        bool resultado[4][4];
        for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++){
            if(i==0){
                resultado[j][3] = pieza[i][j];
            }else if(j==3){
                resultado[3][3-i] = pieza[i][j];
            }else if(i==3){
                resultado[j][0] = pieza[i][j];
            }else if(j==0){
                resultado[0][3-i] = pieza[i][j];
            }
        }
        resultado[1][1] = pieza[2][1];
        resultado[1][2] = pieza[1][1];
        resultado[2][2] = pieza[1][2];
        resultado[2][1] = pieza[2][2];
        for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++){
            pieza[i][j] = resultado[i][j];
        }
        return;
    }

};
#endif