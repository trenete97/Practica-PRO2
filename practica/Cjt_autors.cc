#include "Cjt_autors.hh"

bool Cjt_autors::buscar_par(string paraula, string paraules) {
	//Funció auxiliar que permet saber si en un conjunt de paraules n'hi ha una en concret.
	istringstream iss(paraules);
	string m;
	while (iss >> m) {
		//Compara cada paraula del conjunt amb la paraula donada i retorna si són iguals encara que hi hagi signes de puntuació.
		if (m == paraula) return true;
		if (m == paraula + '.' or m == paraula + '?' or m == paraula + '!' or m == paraula + ',' or m == paraula + ':' or m == paraula + ';') return true;
	}
	return false;
}

bool Cjt_autors::mirar_inicials(const map<string, Autor>::const_iterator & aut, const string & inicials) {
	//Funció auxiliar que permet saber si unes inicials es corresponen amb un autor.
	istringstream iss(aut->first);
	string m;
	int i = 0;
	while (iss >> m) {
		//Compara la primera lletra de cada paraula que forma el nom de l'autor amb la inicial que li correspon.
		if (m[0] != inicials[i]) return false;
		++i;
	}
	return true;
}

Cjt_autors::Cjt_autors(){
    //Crea un autor buit i per tant els seus paràmetres són nuls.
    ttriat = false;
    map_autor = map<string, Autor>();
    aut_triat = map<string, Autor>::iterator();
    map_ref = map<string, int>();
}

void Cjt_autors::afegir_aut(Autor& autor) {
    //Busca si ja existeix una autor amb el mateix nom que el que es vol afegir, en cas contrari l'afegeix.
    map<string, Autor>::iterator it = map_autor.find(autor.consultar_aut());
    if (it == map_autor.end()) map_autor.insert(make_pair(autor.consultar_aut(), autor));
    else {
	//Si ja existia un autor comprova que el text que volem afegir no existeixi anteriorment.
        int tam = it->second.consultar_num_textos();
        for (int i = 0; i < tam; ++i) {
            string tit = autor.cercar_txt(0).consultar_titol();		//Com que volem afegir un autor sabem que només té un text.
            //Si ja hi ha un text amb el mateix titol es produeix error.
            if (it->second.cercar_txt(i).consultar_titol() == tit) {
                cout << "error" << endl;
                return;
            }
        }
        //Sinó afegeix el text a l'autor que ja es trobava en el map.
        it->second.afegir_txt(autor.cercar_txt(0));
    }
}

void Cjt_autors::afegir_ref(string inicials) {
    //Si ja exitien les inicials s'incrementa el nombre de cites associades. Sinó les afegeix amb el valor 1.
    ++map_ref[inicials];
}

void Cjt_autors::triar_txt(string paraules){
	if (paraules == "") {			//Les paraules no es un string buit.
		ttriat = false;
		cout << "error" << endl;
	}
	else {
	    map<string, Autor>::iterator it = map_autor.begin();
	    string aux = paraules;
	    //Cont indica el nombre de textos trobats que contenen les paraules.
	    int cont = 0;
	    while (cont < 2 and it != map_autor.end()) {	//Mentre no trobi dos texts amb les paraules i hi hagi més autors on buscar:
           	Text t;
	        int n = it->second.consultar_num_textos();
	        for (int i = 0; i < n; ++i) {
	            aux=paraules;
	            int trobades = 0;
	            t = it->second.cercar_txt(i);		//Busca a cada text de l'autor.
	            istringstream iss(aux);
	            string m;
	            int num_paraules=0;
	            while (iss >> m) {
			//Fa un recompte del nombre total de paraules ha buscar.
			++num_paraules;
			//busca les paraules en el títol, en l'autor i en el contingut del text.
		        if (buscar_par(m, t.consultar_titol()) or buscar_par(m, it->first) or t.buscar_par(m) != -1) ++trobades;
	            }
		    //Si el nombre de paraules trobades és igual al total:
	            if (trobades == num_paraules){
		      //Incrementa el contador alhora que sel·lecciona el text.
		      ++cont;
		            if (cont < 2) {
		                this->aut_triat = it;
		                this->aut_triat->second.autor_triat(true);
		                this->aut_triat->second.tria_text(i);
		            }
	            } 
	        }
            ++it;
        }
	//Si només ha trobat un text verifica que hi ha un text triat.
        if (cont == 1) this->ttriat = true;
	//Sinó dòna un misatge d'error i anul·la el text triat.
	else {
			this->ttriat = false;
			cout << "error" << endl;
		}
    }
}

void Cjt_autors::afegir_cita(const Cita& cta){
    aut_triat->second.afegir_cita(cta);
}

void Cjt_autors::eliminar_cita(const string& referencia) {
    int tam = referencia.size();
    string index_aux = "";
    int cont = 0;
    //Mira caràcter per caràcter per trobar el nombre en la referència.
    for (int i = 0; i < tam; ++i) {
	if (referencia[i] >= '0' and referencia[i] <= '9') {
	    ++cont;
	    index_aux += referencia[i];
	}
    }
    //Extreu el nombre per quedar-se només amb les inicials.
    string inicials_ref = referencia.substr(0, tam - cont);
    int index_ref = atoi(index_aux.c_str());
    int index = consultar_index(inicials_ref);
    //Comprova si existeix una referència vàlida.
    if (index != 0 and index >= index_ref) {
        for (map<string, Autor>::iterator aut = map_autor.begin(); aut != map_autor.end(); ++aut) {
            if (mirar_inicials(aut, inicials_ref)) {
            	if (aut->second.cerca_cita(referencia).consultar_referencia() != "-1") {
            	    aut->second.eliminar_cita(referencia);
            	    return;
		    //Elimina la cita de l'autor.
		}
	    }
        }
    //Si no troba la cita dòna un misatge d'error.
        cout << "error" << endl;
        return;
    }
    else cout << "error" << endl;
}

void Cjt_autors::eliminar_txt() {
	aut_triat->second.eliminar_txt();
	//Elimina el text triat i per tant deixa d'haver un text triat.
	ttriat = false;
}

void Cjt_autors::substituir_paraula(string& p1, string& p2){
    aut_triat->second.substituir_paraula(p1, p2);
}

bool Cjt_autors::txt_triat() const {
    return ttriat;
}

Autor Cjt_autors::consultar_autor() const {
    return aut_triat->second;
}

Autor Cjt_autors::consultar_aut(const string& autor) {
    map<string, Autor>::iterator it = map_autor.find(autor);	//Busca la posició de l'autor en el map.
    if (it != map_autor.end()) return it->second;		//Si el troba el retorna.
    Autor buit;		//Sinó retorna un autor buit.
    return buit;
}

int Cjt_autors::consultar_index(const string& inicials) const {
    map<string, int>::const_iterator it = map_ref.find(inicials);	//Busca les inicials en el map de referències.
    if (it != map_ref.end()) return it->second;				//Si les troba retorna l'index.
    //Si no hi ha cap retorna 0.
    else return 0;
}

void Cjt_autors::escriure_textos() const {
    for (map<string, Autor>::const_iterator it = map_autor.begin(); it != map_autor.end(); ++it) {
        //Per cada autor en el map.
        int ntxt = it->second.consultar_num_textos();
        for (int i = 0; i < ntxt; ++i) {
	    //I per cada text de l'autor n'escriu la informació.
            cout << it->first << " " << '"' << it->second.cercar_txt(i).consultar_titol() << '"' << endl;
        }
    }
}

void Cjt_autors::autors() const {
    //Escriu la informació per cada autor del map que té al menys un text.
    for (map<string, Autor>::const_iterator it = map_autor.begin(); it != map_autor.end(); ++it) {
	if (it->second.consultar_num_textos() != 0) {
	  cout << it->first << " " << it->second.consultar_num_textos() << " "<< it->second.consultar_num_frases() << " " << it->second.consultar_num_paraules() << endl;
	}
    }
}

void Cjt_autors::exp_frases(string & exp) {
    aut_triat->second.consultar_txt_t().exp_frases(exp);
}

void Cjt_autors::cites_conj() const {
    for (map<string, int>::const_iterator it = map_ref.begin(); it != map_ref.end(); ++it) {
	int index = it->second;
	string inicials = it->first;
	for (int i = 1; i <= index; ++i) {
	    map<string, Autor>::const_iterator aut = map_autor.begin();
	    for (map<string, Autor>::const_iterator aut = map_autor.begin(); aut != map_autor.end(); ++aut) {
		//Per cada cita comprova quins autors són possibles. 
		if (mirar_inicials(aut, inicials)) {
		    string ref = inicials + to_string(i);
		    Cita c = aut->second.cerca_cita(ref);
		    //Si l'autor realment conté la cita n'escriu la informació.
		    if (c.consultar_referencia() != "-1") {
		    	cout << ref << endl;
		    	c.escriu_contingut();
		        cout << aut->first << " " << '"' << c.consultar_titol() << '"' << endl;
			}
		}
	    }
	}
    }
}
void Cjt_autors::cita_ref(string ref) const{
    int tam = ref.size();
    string index_aux = "";
    int cont = 0;
    //Agafa l'index de la referència.
    for (int i = 0; i < tam; ++i) {
	if (ref[i] >= '0' and ref[i] <= '9') {
	    ++cont;
	    index_aux += ref[i];
	}
    }
    string inicials_ref = ref.substr(0, tam - cont);
    int index_ref = stoi(index_aux);
    int index = consultar_index(inicials_ref);
    //Si l'index és vàlid comprova si cada autor pot contenir la cita.
    if (index != 0 and index >= index_ref) {
    	for (map<string, Autor>::const_iterator aut = map_autor.begin(); aut != map_autor.end(); ++aut) {
            if (mirar_inicials(aut, inicials_ref)) {
	      Cita c = aut->second.cerca_cita(ref);
	      //Si realment l'autor conté la cita n'escriu la informació.
	      if (c.consultar_referencia() != "-1") {
		  cout << aut->first << " " << '"' << c.consultar_titol() << '"' << endl;
		  cout << c.consultar_x() << "-" << c.consultar_y() << endl;
		  c.escriu_contingut();
		  return;
	      }
            }
	}
    }
    else cout << "error" << endl;
}


