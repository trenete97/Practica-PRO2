#include "Cita.hh"

Cita::Cita(){
    //Al ser una cita buida els seus valors són nuls. 
    contingut = vector<Frase>(0);
    //referencia = "-1" indica que la cita es buida.
    referencia = "-1";
}

Cita::Cita(string referencia, string titol, int x, int y, vector<Frase> contingut) {
    //Crea una cita usant els valors donats.
    this->referencia = referencia;
    this->titol = titol;
    this->x = x;
    this->y = y;
    this->contingut = contingut;
}

void Cita::omplir_cita(const Text& txt, int x, int y, string ref) {
    //Omple una cita amb els valors que se li donen.
    referencia = ref;
    titol = txt.consultar_titol();
    this->x = x;
    this->y = y;
    int iaux = 0;
    contingut = vector<Frase>(y-x+1);
    for (int i = x; i <= y; ++i) {
        contingut[iaux] = txt.consultar_frase(i);
        ++iaux;
    }   
}

string Cita::consultar_titol() const {
    return (titol);
}

string Cita::consultar_referencia() const {
    return (referencia);
}

int Cita::consultar_x() const {
    return (x);
}

int Cita::consultar_y() const {
    return (y);
}

vector<Frase> Cita::consultar_contingut() {
    return (contingut);
}

void Cita::escriu_contingut() const{
    //Per cada frase del contingut escriu el seu nombre i la frase.
    for (int i = x; i <= y; ++i) {
        cout << i << " ";
        contingut[i-x].escriu_frase();
	cout << endl;
    }
}
