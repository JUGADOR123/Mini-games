#ifndef Jugador_h
#define Jugador_h

class Jugador
{
public:
    string Nickname;
    vector<bool> juegos_jugados,juegos_ganados;
    double mejor_puntuacion, peor_puntuacion;
    Jugador(){
        mejor_puntuacion = 0;
        peor_puntuacion = 100;
        juegos_jugados.resize(5, false);
        juegos_ganados.resize(5, false);
    }

    friend int index_de_jugador(string);
    ~Jugador()
    {
        cout << "Player object deleted";
    }

};
#endif