#include "Text.hh"

//Extres

bool Text::ordre(const Text::Paraula& p1, const Text::Paraula& p2) {
	if (p1.freq == p2.freq) {
		if (p1.cadena.size() == p2.cadena.size()) return p1.cadena < p2.cadena;
		return p1.cadena.size() < p2.cadena.size();
	}
	return p1.freq > p2.freq;
}

string Text::treu_espais(string s) {
	istringstream iss(s);
	string sfinal = "";
	iss >> s;
	sfinal += s;
	while (iss >> s) {
		if (!isalnum(s[0])) sfinal += s;
		else sfinal += " " + s;
	}
	return sfinal;
}

//Creadora
Text::Text() {
    num_paraules = 0;
    num_frases = 0;
    frases = vector<Frase>(0);
    paraules = vector<Paraula>(0);
}

//Modificadores
void Text::omplir_text(string tit, string aut) {
    titol = treu_espais(tit);
    autor = treu_espais(aut);
    string paraula;
    string par = "";
    Frase f;
    cin >> paraula;
    while (paraula != "****") {
        int mida = paraula.size();
        if (paraula[mida-1] == '.' or paraula[mida-1] == '!' or paraula[mida-1] == '?') {
            //Ultima paraula de la frase
	    f.afegir_paraula(paraula); //afegim paraula a la frase
            frases.push_back(f); //afegim la frase al text
            ++num_frases;
            Frase buit;
            f=buit; //Resetejem frase
        }
        else f.afegir_paraula(paraula); //afegim paraula a la frase

        //filtratge per taula de frequencies
        if (isalnum(paraula[0])) {
            num_paraules++;
            if (!isalnum(paraula[mida - 1])) {
                paraula.erase(paraula.size() - 1, 1); //borrem el signe enganxat per darrera a la paraula
            }
            par = paraula;
            int i = buscar_par(par);
            if (i > -1) paraules[i].freq++; //si esta la paraula
            else {
                Paraula p; //creem paraula
                p.cadena = par; 
                p.freq = 1;
                paraules.push_back(p);
            }
        }
        cin >> paraula;
    }
    sort(paraules.begin(),paraules.end(),ordre);
}

void Text::substituir_paraula (string p1, string p2) {
    int x = 0;
    for (int i = 0; i < num_frases; i++) x += frases[i].substituir_paraula(p1,p2);
    int pos = buscar_par(p2);
    int pos1 = buscar_par(p1);
    if (pos1 != -1) { //si esta la primera paraula
        if (pos == -1) paraules[pos1].cadena = p2; //si la segona no hi es
        else { //si la segona paraula hi es
            paraules[pos1].freq = 0; //Posem a zero la frequencia de la paraula que s'ha tret.
            paraules[pos].freq += x; //Augmentem la frequencia de la paraula afegida 
                                     //tantes vegades com ha aparegut
        }
    }
    sort(paraules.begin(), paraules.end(), ordre); //Ordenem vector de paraules
}

//Consultores
string Text::consultar_autor() const {
    return autor;
}
     
string Text::consultar_titol() const {
    return titol;
}

int Text::consultar_num_paraules() const {
    return num_paraules;
}

int Text::consultar_num_frases() const {
    return num_frases;
}

Frase Text::consultar_frase(int num_frase) const {
    return frases[num_frase - 1];
}

bool Text::buscar_paraula(string paraula, int num_frase) const {
    return frases[num_frase - 1].buscar_paraula(paraula);
  
}

int Text::buscar_par(string par) const {
	int i = 0;
	bool trobat = false;
	while (!trobat and i < paraules.size()) {
		if (paraules[i].cadena == par) return i;
		++i;
	}
	return -1;
}

//Escriptores
void Text::escriu_frases(int x = -1, int y = -1) {
    if (x == -1 and y == -1) { //s'escriu tot el text
        for (int i = 1; i <= num_frases; i++) {
            cout << i << ' ';
            frases[i - 1].escriu_frase();
            cout << endl;
        }
    }
    else {
        for(int i = x; i <= y; i++){
            cout << i <<' ';
            frases[i - 1].escriu_frase();
            cout << endl;
        }
    }
}
 
void Text::taula_freq() const {
    for (int i = 0; i < paraules.size(); ++i) {
        if (paraules[i].freq > 0) cout << paraules[i].cadena 
	    << ' ' << paraules[i].freq << endl;
    }
}

void Text::exp_frases(string exp) const {
    istringstream iss(exp);
    string paraula;
    string exp2 = "";
    iss >> paraula;
    exp2 += paraula;
    while (iss >> paraula) exp2 += ' ' + paraula;
    for (int i = 0; i < num_frases; ++i) {
        if (frases[i].analitzar_exp(exp2)) { //Si es compleix l'expressió
            cout << i + 1 << ' ';
            frases[i].escriu_frase();
            cout << endl;
        }
    } 
}
        
    
void Text::buscar_seq(string seq) const {
    for(int i = 0; i < num_frases; ++i) {
        if(frases[i].buscar_seq(seq)) { //Si la seqüència esta a la frase
            cout << i + 1 << ' ';
            frases[i].escriu_frase();
            cout << endl;
        }
    }
}
     
