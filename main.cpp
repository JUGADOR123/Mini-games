#include<iostream>
#include<string>
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<vector>
#include<istream>
#include<iomanip>
#include "Jugador.h"
#include "Ahorcado.h"
#include"Buscaminas.h"
#include "SaltoContraComputadora.h"
#include "Tetris.h"
#include "TypeSong.h"

using namespace std;

#define seg 1000
#define forn(i, n) for(int i = 0; i < int(n); i++)
#define pb  push_back

const int N_juegos = 5;
string juego[5] = {
    "TypeSong", "Hanging", "Jumping", "Minesweeper", "Tetris"
};

vector<Jugador> jugadores;

int index_de_jugador(string jugador_buscado){
    for(int i = 0; i < jugadores.size(); i++){
        if(jugadores[i].Nickname==jugador_buscado){
            return i;
        }
    }
    return -1;
}

int main(){
    char eleccion;
    cout<<"...Starting...";

    jugadores.pb({});
    do{
        Sleep(3*seg);
        system("cls");
        cout<<"-------------Hello!---------------\nChoose your username (no spaces)\n";
        string nombre_de_usuario;
        cin>>nombre_de_usuario;
        int g = index_de_jugador(nombre_de_usuario);
        if(g==-1){
            g = jugadores.size();
            Jugador abogado;
            abogado.Nickname = nombre_de_usuario;
            jugadores.push_back(abogado);
        }
        Jugador &player = jugadores[g];

        cout<<nombre_de_usuario<<", what are we doing today?\n"<<
        "[1]. Play TypeSong\n"<<
        "[2]. Play Hanging\n"<<
        "[3]. Play Jumping against the computer\n"<<
        "[4]. Play Minesweeper\n"<<
        "[5]. Play Tetris\n"<<
        "[6]. Statistics\n"<<
        "[7]. Player Data\n"<<
        "[8]. Exit\n";
        cin>>eleccion;
        system("cls");
        double r;
        string letra_usuario;
        int errores;
        vector<bool> intentos(('z'-'a')+1);
        int palabra;
        bool gana;
        int posicion;
        int nn;
        bool gameover;
        int bombas_descubiertas;
        double puntaje_b;
        switch (eleccion){


            case '1':{
            TypeSong TS = TypeSong();
            cout<<"Choose a song:\n";
            for(int i = 0; i < TS.N_canciones; i++){
                cout<< i+1 << ". " << TS.canciones[i] << "\n";
            }
            int cancion_escogida;
            cin>>cancion_escogida;
            if(cancion_escogida>TS.N_canciones){
                cout<<"error";
                break;
            }
            cancion_escogida--;
            system("cls");
            cout << "  Ready? \n Type the song's lyrics as close as possible\n"<<
                    "To indicate that you finished, type the symbol $ and press enter.\n";

            Sleep(seg * 3);
            system("cls");
            cout<<"3";

            Sleep(seg);
            system("cls");
            cout<<"2";

            Sleep(seg);
            system("cls");
            cout<<"1";

            Sleep(seg);
            system("cls");
            cout<<"Go!"<< TS.canciones[cancion_escogida] << ":\n" <<TS.letra[cancion_escogida]<<"\n";
            cout<<"\n";
            getline(cin, letra_usuario, '$');

            system("cls");
            r = TS.parecido(TS.letra[cancion_escogida], letra_usuario);
            cout<<"Score: ";
            cout<< fixed << setprecision(2) << r;
            cout<<"\n";

            player.juegos_jugados[0]=true;
            player.mejor_puntuacion = max(player.mejor_puntuacion, r);
            player.peor_puntuacion = min(player.peor_puntuacion, r);
            if(r < 40) cout<<"Wow you typed so badly, why even bother playing?\n";
            else if(r < 60) cout<<"You are not good!\n";
            else if(r < 80) cout<<"You can improve\n";
            else if(r<99) cout<<"Nice\n";
            else{
                cout<<"Perfect! You should play more often.\n";
                player.juegos_ganados[0]=true;
            }
            break;

}
            case '2':{
            Ahorcado ahorcado; 
            cout<<"Choose difficulty\n1.Easy\n2.Medium\n3.Hard\n";
            int dificultad;
            cin>>dificultad;
            dificultad--;
            system("cls");
            palabra = rand() % ahorcado.N_palabras;

            errores = 0;
            cout<<ahorcado.ahorcado[0]<<"\n";
            for(int i = 0; i < intentos.size(); i++) intentos[i]=false;
            while(errores < ahorcado.errores_ahorcado-1){
                char intento; cin>>intento;
                intentos[intento-'a'] = true;
                system("cls");
                short d = ronda_ahorcado(ahorcado.palabras[dificultad][palabra], intentos, intento);
                if(d==1) errores++;
                system("cls");
                cout<<ahorcado.ahorcado[errores]<<"\n";
                ronda_ahorcado(ahorcado.palabras[dificultad][palabra], intentos, intento);
                if(d==-1) break;
            }
            double puntaje = 0;
            player.juegos_jugados[1] = true;
            if(errores == ahorcado.errores_ahorcado-1){
                cout<<"The answer is: "<<ahorcado.palabras[dificultad][palabra]
                    <<"\nYou are so bad reading, take more time to focus!\n";
            }else{
                puntaje = 100 - (errores * (100.0/7.0));
                cout<<"YOu won!!\nYour score is: "<< fixed << setprecision(2) << puntaje <<"\n";
                player.juegos_ganados[1] = true;
            }
            player.mejor_puntuacion = max(player.mejor_puntuacion, puntaje);
            player.peor_puntuacion = min(player.peor_puntuacion, puntaje);

}
            break;




            case '3':
{
            cout<<"The game consists of the following: (you are playing against the computer). \n"<<
            "You will jump a number of less than M steps, then the computer, then you, and so on. The winner is the one who gets further than the end, which will be a line of N spaces.\n" <<
            "If you choose in the jump a value greater than M or less than 1, you lose automatically\n"<<
            "To give you a chance, you will choose the value of the N and the M\n";
            int N, M;
            cin>>N>>M;
            system("cls");
            posicion = 1;
            SaltoContraComputadora saltoContraComputadora = SaltoContraComputadora(N, M);
            saltoContraComputadora.salto(posicion);
            gana = false;
            while(posicion <= N){
                cout<<"Tu turno: \n";
                int saltos;
                cin>>saltos;
                system("cls");
                if(saltos > M){
                    cout<<"You loose for being a cheater!\n";
                    break;
                }
                posicion += saltos;
                if(posicion > N){
                    gana = true;
                    break;
                }
                saltoContraComputadora.salto(posicion);
                int h = saltoContraComputadora.salto_computadora(posicion) - posicion;
                Sleep(seg);
                cout<<"Computer jumps: "<< h <<"\n";
                posicion += h;
                saltoContraComputadora.salto(posicion);
                Sleep(2 * seg);
            }
            player.juegos_jugados[2] = true;
            if(!gana){
                cout<<"Computer wins!!\n";
                player.peor_puntuacion = 0;
            }
            else{
                cout<<"You won, so smart\n";
                player.juegos_ganados[2] = true;
                player.mejor_puntuacion = 100;
            }
            break;

}
            // Buscaminas
            case '4':{

            cout<<"Welcome to minesweeper \n";
            cout<<"Choose difficulty \n";
            cout<<"1.-Easy \n"<<"2.-Medium\n"<<"3.-Hard\n";
            

            cin>>nn;

            Buscaminas buscaminas = Buscaminas();

            switch (nn)
            {
                case facil:
                buscaminas = Buscaminas(8,8,10);
                break;

                case medio:
                buscaminas = Buscaminas(16,16,40);
                break;

                case avanzado:
                buscaminas = Buscaminas(16, 30, 99);
                break;

                default:
                buscaminas.filas = -1;
                cout<<"error";
                break;
            }
            if(buscaminas.filas==-1) break;
            buscaminas.colocar_minas();

            int Di[8]={0, 0,1,1, 1,-1,-1,-1};
            int Dj[8]={1,-1,1,0,-1, 1, 0,-1};
            for(int i = 0; i < buscaminas.filas; i++){
                for(int j = 0; j < buscaminas.columnas; j++) if(buscaminas.tablero[i][j]!=-1){
                    int &cnt = buscaminas.tablero[i][j];
                    for(int k = 0; k < 8; k++){
                        int temp_i = i + Di[k];
                        int temp_j = j + Dj[k];
                        if(temp_i>=0 && temp_j>=0 && temp_i<buscaminas.filas && temp_j<buscaminas.columnas && buscaminas.tablero[temp_i][temp_j]==-1) cnt++;
                    }
                }
            }
            bombas_descubiertas = 0;
            while(bombas_descubiertas<buscaminas.minas){
                system("cls");
                buscaminas.mostrar_tablero();
                cout<<"To indicate a bomb, press [q].\nOhterwise [e]\nChoose coordinate (x, y)\n";
                char intension; cin>>intension;
                int x_b, y_b; cin>>x_b>>y_b;
                if(buscaminas.tablero[x_b][y_b]==-2 || buscaminas.tablero[x_b][y_b]>9) continue;
                if(intension=='e' && buscaminas.tablero[x_b][y_b]==-1 || intension=='q' && buscaminas.tablero[x_b][y_b]!=-1){
                    break;
                }
                if(intension=='e') buscaminas.tablero[x_b][y_b] += 10;
                else {
                    buscaminas.tablero[x_b][y_b] = -2;
                    bombas_descubiertas++;
                }
                if(buscaminas.tablero[x_b][y_b]==10) buscaminas.expandir(x_b, y_b);
            }

            if(bombas_descubiertas<buscaminas.minas) {cout<<"You lost!\nYou found  "<<bombas_descubiertas<<" bombs";}
            else {
                cout<<"Congrats! you won!";
                player.juegos_ganados[3] = true;
            }
            player.juegos_jugados[3] = true;
            //guardar estadistica
            puntaje_b = (bombas_descubiertas * 100.0)/(double)(buscaminas.minas);
            player.mejor_puntuacion = max(player.mejor_puntuacion, puntaje_b);
            player.peor_puntuacion = min(player.peor_puntuacion, puntaje_b);
}
            break;

            // Tetris
            case '5':{

            cout << "You will play Tetris version Chyaru!\n"<<
                    "You will be shown the piece, and you must decide whether to change piece\n" <<
                    "and with the little arrows move it from left to right.\n"<<
                    "You can also decide the size of the game space, with N and M (with values less than 50)\n"<<
            Sleep(7 * seg);
            cout << "With the 'w' key you change the piece (you can't make more than 2 changes in a row\n"<<
                    "With the 'a' key you move the piece to the left\n" <<
                    "With the 'd' key you move the piece to the right\n" <<
                    "With the 'q' key you rotate the part\n"<<
                    "Press the 's' key to confirm, the workpiece will be aligned\n";
            Sleep(5 * seg);
            int N, M;
            while(true){
                cout<<"\n\nSelect M and N (below 50 and above 5)";
                cin>>N>>M;
                if(N<=50 && M<=50 && N>=5 && M>=5) break;
            }
            Tetris tetris = Tetris(N, M);
            system("cls");
            int filas_completadas = 0, cambios = 0;
            while(filas_completadas<100){
                Sleep(100); // ??
                system("cls");
                tetris.genera_pieza();
                int posicion = tetris.M_tetris/2;
                bool d = tetris.genera_matriz(filas_completadas, posicion);
                if(!d) break;
                char jugada='?';
                cambios = 0;
                while(jugada!='s'){
                    cin>>jugada;
                    if(jugada=='w' && cambios<2){
                        cambios++;
                        tetris.genera_pieza();
                        posicion = tetris.M_tetris/2;
                    }else if(jugada=='a'){
                        tetris.mueve(posicion, -1);
                    }else if(jugada=='d'){
                        tetris.mueve(posicion, 1);
                    }else if(jugada=='q'){
                        tetris.girar_pieza();
                    }
                    system("cls");
                    tetris.genera_matriz(filas_completadas, posicion);
                }
                if(tetris.colocar_pieza( posicion, false)==-2) break;
            }
            Sleep(seg);
            system("cls");
            cout<<"Game is over!\nYou completed "<<filas_completadas<<" rows\n";
            player.juegos_jugados[4] = true;
            player.mejor_puntuacion = max(player.mejor_puntuacion, (double)(filas_completadas));
            player.peor_puntuacion = min(player.peor_puntuacion, (double)(filas_completadas));
            if(filas_completadas==100){
                cout<<"You won\n!Congrats\n";
                player.juegos_ganados[4] = true;
            }
}
            break;

        // Estadisticas
        case '6':{

        for(int i = 0; i < jugadores.size(); i++){
            cout<<"Player "<<jugadores[i].Nickname<<"\n";
            vector<string> ganados, jugados;
            for(int j = 0; j < N_juegos; j++){
                if(jugadores[i].juegos_jugados[j]) jugados.push_back(juego[j]);
                if(jugadores[i].juegos_ganados[j]) ganados.push_back(juego[j]);
            }
            if(jugados.size()==0){
                cout<<"No games\n";
            }else{
                cout<<"Games played:\n";
                for(int j = 0; j < jugados.size(); j++, cout<<"\n")
                    cout<<jugados[j];
            }
            if(ganados.size()==0){
                cout<<"No games won\n";
            }else{
                cout<<"Games won:\n";
                for(int j = 0; j < ganados.size(); j++, cout<<"\n")
                    cout<<ganados[j];
            }
            if(jugados.size()) cout<< "Best score: "<<jugadores[i].mejor_puntuacion<<"\n" << "Worst Score: "<<jugadores[i].peor_puntuacion<<"\n";
            cout<<"\n\n\n";
        }
        Sleep(10*seg);
}
        break;

        // Datos por jugador
        case '7':{

        cout<<"Choose username you want to see the stats\n";
        string jugador_buscado; cin>>jugador_buscado;
        int g = index_de_jugador(jugador_buscado);
        if(g==-1){
            cout<<"No played found\n";
            break;
        }
        Jugador player = jugadores[g];
        vector<string> ganados, jugados;
        for(int j = 0; j < N_juegos; j++){
            if(player.juegos_jugados[j]) jugados.push_back(juego[j]);
            if(player.juegos_ganados[j]) ganados.push_back(juego[j]);
        }
        if(jugados.size()==0){
            cout<<"No games\n";
        }else{
            cout<<"Games played:\n";
            for(int j = 0; j < jugados.size(); j++, cout<<"\n")
                cout<<jugados[j];
        }
        if(ganados.size()==0){
            cout<<"No games won\n";
        }else{
            cout<<"Games won:\n";
            for(int j = 0; j < ganados.size(); j++, cout<<"\n")
                cout<<ganados[j];
        }
        if(jugados.size()) cout<< "Best Score: "<<player.mejor_puntuacion<<"\n" << "Worst score: "<<player.peor_puntuacion<<"\n";
        cout<<"\n\n\n";
}
        break;
    }
    }while(eleccion!='8');
    cout<<"something";
    return 0;
}
