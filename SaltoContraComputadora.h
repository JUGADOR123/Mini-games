class SaltoContraComputadora
{
    public:    
    int N, M;
    SaltoContraComputadora(int N, int M){
        this->N = N;
        this->M = M;
    }
    void salto(int posicion){
        for(int i = 1; i <= this->N; i++) if(i==posicion) cout<<"X"; else cout<<".";
        cout<<"\n";
        return;
    }

    int salto_computadora(int posicion){
        int r = (this->N-((int)(((this->N-posicion)+1)/(this->M+1))*(this->M+1)))+1;
        if(r==posicion) return posicion + 1;
        return r;
    }
     ~SaltoContraComputadora()
    {
        cout << "Minigame Ended";
    }
};