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
        "persona", "extender", "mirador", "elocuente", "celular",
        "murcielago", "proxeneta", "yoyo", "literal", "juego",
        // medio
        "no lo permito", "no existe el bajon", "politica mexicana", "los negros ya no se venden", "las mujeres tienen derechos",
        "necesito medicina", "tengo gripe", "me duele la garganta", "de esta no salgo", "tengo fe",
        // dificil
        "ya no quiero escuchar mas excusas", "me dijiste que me amabas",
        "pero fueron todas mentiras", "endulzarme el oido",
        "ilustrame y dime", "que fui yo para ti en realidad",
        "una simple distraccion", "alguien con un carro costoso",
        "no me interesa saber", "yo ya estoy bien asi sola"
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