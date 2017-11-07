#include "Cjt_autors.hh"

/** @file main.cc
    @brief Programa principal de la <em>Pràctica de Pro2 - Primavera 2016</em>.
*/
int main(){
    /*Creem un conjunt d'autors buit sobre el qual efactuarem totes les operacions.*/
    Cjt_autors biblio;
    string linia = "";
    getline(cin,linia); //llegim instrucció
    while (linia != "sortir") { 
        istringstream iss(linia);
	string m;
 	iss >> m; //llegim la primera paraula de la instrucció
 	if (m != "") cout << linia << endl;
   	if (m == "afegir") {
      	    iss >> m;
	    if (m == "cita") {
		int x;
		iss >> x;
		int y;
		iss >> y;
		if (biblio.txt_triat() and x <= y and x > 0 and 
		    y <= biblio.consultar_autor().consultar_txt_t().consultar_num_frases()) {
		    string ref;
		    string autor = biblio.consultar_autor().consultar_aut();
		    istringstream iss(autor);
		    string inicials = "";
                    while (iss >> m) inicials += m[0]; //Guardem les inicials de l'autor.
                    int index = biblio.consultar_index(inicials); //Consultem nombre de cites amb les inicials.
                    ref = inicials + to_string(index + 1); //Creem la referencia de la cita a afegir.
                    Cita c;
		    c.omplir_cita(biblio.consultar_autor().consultar_txt_t(), x, y, ref);
                    if (!biblio.consultar_autor().existeix_cita(c)) {
		        biblio.afegir_ref(inicials);
		        biblio.afegir_cita(c);
		    }
		    else cout << "error" << endl;
		}
		
		else cout << "error" << endl;
	    }
			
	    else if (m == "text") {
		int n = linia.size() - 14;
		string titol = linia.substr(13, n); //titol sense cometes.
		getline(cin, linia);
		n = linia.size() - 8;
		string nom = linia.substr(7, n); //nom de l'autor sense cometes.
		Text text;
		text.omplir_text(titol, nom);
		Autor autor(text.consultar_autor());
		autor.afegir_txt(text);
		biblio.afegir_aut(autor);
	    }
	}
		
	else if (m == "triar") {
	    iss >> m; //llegir "text".
	    iss >> m; 
	    string exp = m; //inicialitzem la expresio amb la primera paraula i li afegim les altres.
	    while (iss >> m) exp += " " + m;
	    exp.erase(0, 1); //borrem claus del principi.
	    exp.erase(exp.size() - 1, 1); //borrem claus del final.
	    biblio.triar_txt(exp);
	}
		
	else if (m == "eliminar") {
      	    iss >> m;
	    if (m == "cita") {
	    iss >> m;
	    m.erase(0,1); //borrem primeres cometes de la referencia.
	    m.erase(m.size()-1,1); //borrem cometes del final de la referencia.
	    biblio.eliminar_cita(m);
     	    }
     		
	    else if (m == "text") {
	        if (biblio.txt_triat()) biblio.eliminar_txt();
	        else cout << "error" << endl;
	    }
        }
		
        else if (m == "substitueix") {
	    iss >> m;
	    string p1 = m;
	    p1.erase(0, 1); //borrem primeres cometes de la paraula.
	    p1.erase(p1.size() - 1, 1); //borrem cometes del final de la paraula.
	    iss >> m; //llegir "per"
	    iss >> m;
	    string p2 = m;
	    p2.erase(0, 1); //borrem primeres cometes de la paraula.
	    p2.erase(p2.size() - 1, 1); //borrem cometes del final de la paraula.
	    if (biblio.txt_triat()) biblio.substituir_paraula(p1, p2);
	    else cout << "error" << endl;
	}
		
	else if (m == "textos") {
	    iss >> m;
	    int n = linia.size() - 17;
	    string autor = linia.substr(14, n); //autor sense cometes i sense "?".
	    biblio.consultar_aut(autor).titols();
	}
		
	else if (m == "tots") {
	    iss >> m;
	    if (m == "textos") biblio.escriure_textos();
	    else if (m == "autors") biblio.autors();
	    iss >> m; //llegir "?".
	}
		
	else if (m == "info") {
	    iss >> m;
	    if (m == "?") {
		if (biblio.txt_triat()) biblio.consultar_autor().escriure_autor_t();
		else cout << "error" << endl;
	    }
			
	    else if (m == "cita") {
	        iss >> m;
	        m.erase(0, 1); //borrem primeres cometes de la referencia.
	        m.erase(m.size() - 1, 1); //borrem cometes del final de la referencia.
	        biblio.cita_ref(m);
	        iss >> m; //llegir "?".
	    }
	}
		
	else if (linia == "autor ?") {
            if (biblio.txt_triat()) cout << biblio.consultar_autor().consultar_aut() << endl;
            else cout << "error" << endl;
	}

	else if (linia == "contingut ?") {
            if (biblio.txt_triat()) biblio.consultar_autor().consultar_txt_t().escriu_frases(-1,-1);
            else cout << "error" << endl;
	}
		
	else if (m == "frases") {
	    iss >> m;
	    if ((m[0] >='0' and m[0] <= '9') or m[0] == '-') { //Si el primer caracter es un nombre
		int x = atoi(m.c_str()); //Convertim el string llegit a int
		iss >> m;
		int y = atoi(m.c_str()); //Convertim el string llegit a int
	        if (biblio.txt_triat() and x <= y and x > 0 and 
		    y <= biblio.consultar_autor().consultar_txt_t().consultar_num_frases()) {
		    biblio.consultar_autor().consultar_txt_t().escriu_frases(x, y);
		}
		else cout << "error" << endl;
            }
			
	    else if (m[0] == '"') {
		int n = linia.size() - 11;
		string seq = linia.substr(8, n); //llegim la sequencia sense les cometes
		if (biblio.txt_triat()) biblio.consultar_autor().consultar_txt_t().buscar_seq(seq);
		else cout << "error" << endl;
	    }	
			
	    else {
		int n = linia.size() - 9;
		string exp = linia.substr(7, n); //llegim la expressió amb les claus i parèntesis
		if (biblio.txt_triat()) biblio.exp_frases(exp);
		else cout << "error" << endl;
	    }
	}
		
	else if (m == "nombre") {
	    iss >> m; //llegir "de".
	    iss >> m;
	    if (m == "frases") {
		if (biblio.txt_triat()) 
		    cout << biblio.consultar_autor().consultar_txt_t().consultar_num_frases()<<endl;
		else cout << "error" << endl;
	    }
			
	    else if (m == "paraules") {
	        if (biblio.txt_triat()) 
		    cout << biblio.consultar_autor().consultar_txt_t().consultar_num_paraules()<<endl;
		else cout << "error" << endl;
	    }	
	    iss >> m; //llegir "?"
        }
		
	else if (linia == "taula de frequencies ?") {
	    if (biblio.txt_triat()) biblio.consultar_autor().consultar_txt_t().taula_freq();
	    else cout << "error" << endl; 
	}
		
	else if (m == "cites") {
            iss >> m;
	    if (m == "?") {
	        if (biblio.txt_triat()) biblio.consultar_autor().cites_triat();
                else cout << "error" << endl;
	    }
	 		
	    else if (m == "autor") {
                iss >> m;
	        int n = linia.size() - 16;
	        string autor = linia.substr(13,n); //autor sense cometes.
	        biblio.consultar_aut(autor).cites();
	    }
        }
	
	else if (linia == "totes cites ?") biblio.cites_conj();
	
	if (m != "") cout << endl; //final d'instrucció
	getline(cin,linia); //llegir seguent linia
    }	
}
