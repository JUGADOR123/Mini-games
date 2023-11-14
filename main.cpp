#include<iostream>
#include<string>
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<vector>
#include<istream>
#include<iomanip>
#include<Jugador.h>
#include<Ahorcado.h>
#include<Buscaminas.h>
#include<SaltoContraComputadora.h>
#include<Tetris.h>
#include<TypeSong.h>

using namespace std;

#define seg 1000
#define forn(i, n) for(int i = 0; i < int(n); i++)
#define pb  push_back

const int N_juegos = 5;
string juego[N_juegos] = {
    "TypeSong", "Ahorcado", "Saltos", "Buscaminas", "Tetris"
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
    cout<<"...Iniciando...";

    jugadores.pb({});
    do{
        Sleep(3*seg);
        system("cls");
        cout<<"-------------Hola!---------------\nIntroduce tu nombre de usuario (sin espacios)\n";
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

        cout<<nombre_de_usuario<<", que quieres hacer?\n"<<
        "[1]. Jugar TypeSong\n"<<
        "[2]. Jugar Ahorcado\n"<<
        "[3]. Jugar Saltos contra la computadora\n"<<
        "[4]. Jugar Buscaminas\n"<<
        "[5]. Jugar Tetris\n"<<
        "[6]. Estadisticas\n"<<
        "[7]. Datos por jugador\n"<<
        "[8]. salir\n";
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
            cout<<"Escoge la cancion\n";
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
            cout << "  Liste ? \n Escribir el texto de la cancion lo mas parecido posible\n"<<
                    "Para indicar que terminaste, escribe '$' y un enter\n";

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
            cout<<"Comenzamos!"<< TS.canciones[cancion_escogida] << ":\n" <<TS.letra[cancion_escogida]<<"\n";
            cout<<"\n";
            getline(cin, letra_usuario, '$');

            system("cls");
            r = TS.parecido(TS.letra[cancion_escogida], letra_usuario);
            cout<<"Puntos conseguidos: ";
            cout<< fixed << setprecision(2) << r;
            cout<<"\n";

            player.juegos_jugados[0]=true;
            player.mejor_puntuacion = max(player.mejor_puntuacion, r);
            player.peor_puntuacion = min(player.peor_puntuacion, r);
            if(r < 40) cout<<"Para que juegas si no sabes escribir?\n";
            else if(r < 60) cout<<"Que malo eres!\n";
            else if(r < 80) cout<<"Lo podrias hacer mejor\n";
            else if(r<99) cout<<"Nice\n";
            else{
                cout<<"Perfecto! Deberias probar escribir con mayor regularidad\n";
                player.juegos_ganados[0]=true;
            }
            break;

}
            case '2':{
            Ahorcado ahorcado; 
            cout<<"Escoge la dificultad\n1.Facil\n2.Medio\n3.Dificil\n";
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
                cout<<"La respuesta era: "<<ahorcado.palabras[dificultad][palabra]
                    <<"\nERES PESIMO EN LAS PALABRAS, LEE MAS POR FAVOR!\n";
            }else{
                puntaje = 100 - (errores * (100.0/7.0));
                cout<<"Ganaste, bien hecho\nTu puntaje es de: "<< fixed << setprecision(2) << puntaje <<"\n";
                player.juegos_ganados[1] = true;
            }
            player.mejor_puntuacion = max(player.mejor_puntuacion, puntaje);
            player.peor_puntuacion = min(player.peor_puntuacion, puntaje);

}
            break;




            case '3':
{
            cout<<"El juego trata de lo siguiente (vas a jugar contra la computadora). \n"<<
            "Saltaras una cantidad menor a M pasos, luego la computadora, luego tu y asi sucesivamente. Gana quien logre llegar mas alla del final, que sera una recta de N espacios\n" <<
            "Si escoges en el salto un valor mayor que M o menor que 1, pierdes automaticamente\n"<<
            "Para darte chance, tu escogeras el valor de la N y de la M\n";
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
                    cout<<"PIERDES por TRAMPOSO!\n";
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
                cout<<"La computadora salta: "<< h <<"\n";
                posicion += h;
                saltoContraComputadora.salto(posicion);
                Sleep(2 * seg);
            }
            player.juegos_jugados[2] = true;
            if(!gana){
                cout<<"JAJAJAJAJA te gano un codigo de una mecatronica! Piensa un poco mas la proxima\n";
                player.peor_puntuacion = 0;
            }
            else{
                cout<<"Has ganado!! Muy listo\n";
                player.juegos_ganados[2] = true;
                player.mejor_puntuacion = 100;
            }
            break;

}
            // Buscaminas
            case '4':{

            cout<<"BIENVENIDO A BUSCAMINAS \n";
            cout<<"Elije la dificultad \n";
            cout<<"1.-Nivel facil \n"<<"2.-Nivel medio\n"<<"3.-Nivel avanzado\n";
            

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
                cout<<"Si quiere indicar que hay una bomba, escriba [q].\nDe lo contrario escriba [e]\nEscoja la coordenada (x, y)\n";
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

            if(bombas_descubiertas<buscaminas.minas) {cout<<"Perdiste!\nConseguiste descubrir "<<bombas_descubiertas<<" bombas";}
            else {
                cout<<"Ganaste!\nFelicidades";
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

            cout << "Jugaras Tetris version Chyaru!\n"<<
                    "Se te mostrara la pieza, y debes decidir si cambiar de pieza\n" <<
                    "y con las flechitas moverlo de izquierda a derecha.\n"<<
                    "Tambien puedes decidir el tamano del espacio de Juego, con N y M (con valores menores a 50)\n";
            Sleep(7 * seg);
            cout << "Con la tecla 'w' cambias de pieza (no puedes hacer mas de 2 cambios seguidos)\n"<<
                    "Con la tecla 'a' mueves la pieza a la izquierda\n" <<
                    "Con la tecla 'd' mueves la pieza a la derecha\n" <<
                    "Con la tecla 'q' giras la pieza\n"<<
                    "Con la tecla 's' confirmas, la pieza se acomodara\n";
            Sleep(5 * seg);
            int N, M;
            while(true){
                cout<<"\n\nIntroduce N y M (menores que 50 y mayores que 5)";
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
            cout<<"El juego ha acabado!\nCompletaste "<<filas_completadas<<" filas\n";
            player.juegos_jugados[4] = true;
            player.mejor_puntuacion = max(player.mejor_puntuacion, (double)(filas_completadas));
            player.peor_puntuacion = min(player.peor_puntuacion, (double)(filas_completadas));
            if(filas_completadas==100){
                cout<<"Ganaste\n!Felicidades";
                player.juegos_ganados[4] = true;
            }
}
            break;

        // Estadisticas
        case '6':{

        for(int i = 0; i < jugadores.size(); i++){
            cout<<"Jugador "<<jugadores[i].Nickname<<"\n";
            vector<string> ganados, jugados;
            for(int j = 0; j < N_juegos; j++){
                if(jugadores[i].juegos_jugados[j]) jugados.push_back(juego[j]);
                if(jugadores[i].juegos_ganados[j]) ganados.push_back(juego[j]);
            }
            if(jugados.size()==0){
                cout<<"Sin juegos\n";
            }else{
                cout<<"Los juegos jugados son:\n";
                for(int j = 0; j < jugados.size(); j++, cout<<"\n")
                    cout<<jugados[j];
            }
            if(ganados.size()==0){
                cout<<"No ha ganado ningun juego\n";
            }else{
                cout<<"Los juegos ganados son:\n";
                for(int j = 0; j < ganados.size(); j++, cout<<"\n")
                    cout<<ganados[j];
            }
            if(jugados.size()) cout<< "Mejor puntaje: "<<jugadores[i].mejor_puntuacion<<"\n" << "Peor puntaje: "<<jugadores[i].peor_puntuacion<<"\n";
            cout<<"\n\n\n";
        }
        Sleep(10*seg);
}
        break;

        // Datos por jugador
        case '7':{

        cout<<"Ingrese el nombre de quien desea ver las estadisticas\n";
        string jugador_buscado; cin>>jugador_buscado;
        int g = index_de_jugador(jugador_buscado);
        if(g==-1){
            cout<<"No se encontró al jugador\n";
            break;
        }
        Jugador player = jugadores[g];
        vector<string> ganados, jugados;
        for(int j = 0; j < N_juegos; j++){
            if(player.juegos_jugados[j]) jugados.push_back(juego[j]);
            if(player.juegos_ganados[j]) ganados.push_back(juego[j]);
        }
        if(jugados.size()==0){
            cout<<"Sin juegos\n";
        }else{
            cout<<"Los juegos jugados son:\n";
            for(int j = 0; j < jugados.size(); j++, cout<<"\n")
                cout<<jugados[j];
        }
        if(ganados.size()==0){
            cout<<"No ha ganado ningun juego\n";
        }else{
            cout<<"Los juegos ganados son:\n";
            for(int j = 0; j < ganados.size(); j++, cout<<"\n")
                cout<<ganados[j];
        }
        if(jugados.size()) cout<< "Mejor puntaje: "<<player.mejor_puntuacion<<"\n" << "Peor puntaje: "<<player.peor_puntuacion<<"\n";
        cout<<"\n\n\n";
}
        break;
    }
    }while(eleccion!='8');
    cout<<"se cambia";
    return 0;
}
