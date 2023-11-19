#ifndef Ahorcado_h
#define Ahorcado_h


class Ahorcado
{
    public:
    const int N_palabras = 10;
    const int errores_ahorcado = 7;
    Ahorcado(){}
    string palabras[3][10] = {
        // facil
        "person", "extend", "lookout", "eloquent", "cellular",
        "bat", "pimp", "yo-yo", "literal", "game",
        // medio
        "not permitted", "rights do not exist", "mexcican politics", "no longer being sold", "people have to work",
        "I need medicine", "I have the flu", "I have a sore throat", "I'm not getting out of this", "I have faith",
        // dificil
        "I don't want to hear any more excuses", "you told me you loved me", "but they were all lies", "to sweeten my ears", "to sweeten my ears",
        "but they were all lies", "sweeten my ears",
        "enlighten me and tell me," "what was I really to you,"
        "a simple distraction," "someone with an expensive car,"
        "I don't care to know", "I'm fine on my own", "I'm fine on my own", "I'm not interested in knowing"
    };
    string ahorcado[7] = {
        "-------------\n|           |\n|\n|\n|\n|\n|\n|\n",//0
        "-------------\n|           |\n|           O\n|\n|\n|\n|\n|\n",//1
        "-------------\n|           |\n|           O\n|           |\n|\n|\n|\n|\n",//2
        "-------------\n|           |\n|           O\n|           |\n|          / \n|\n|\n|\n", //3
        "-------------\n|           |\n|           O\n|           |\n|          / (\n|\n|\n|\n", //4
        "-------------\n|           |\n|           O\n|          -|\n|          / (\n|\n|\n|\n", // 5
        "-------------\n|           |\n|           O\n|          -|-\n|          / (\n|\n|\n|    PERDISTE!!\n" //6
    };
    friend short ronda_ahorcado(string, vector<bool>, char);
    ~Ahorcado()
    {
        cout << "Minigame ended";
    }
};


short ronda_ahorcado(string &a, vector<bool> &intentos, char letra_del_turno){
    vector<char> s(a.size(), '_');
    string letras_fallidas="";
    bool Z = true;
    for(int i = 0; i < intentos.size(); i++) if(intentos[i]){
        bool z = false;
        for(int j = 0; j < a.size(); j++){
            if(a[j]==' ') s[j] = ' ';
            else if(a[j]==i+'a'){
                s[j] = a[j];
                z = true;
            }
        }
        if(!z){
            letras_fallidas+=char(i+'a');
            if(i+'a'==letra_del_turno) Z = false;
        }
    }
    cout<<"\n\n";
    for(int i = 0; i < s.size(); i++) cout<<s[i];
    cout<<"\n\n";
    cout<<letras_fallidas<<"\n";
    if(!Z) return 1;
    for(int i=0; i < s.size(); i++){
        if(s[i]=='_'){
            return 0;
        }
    }
    return -1;
}



#endif