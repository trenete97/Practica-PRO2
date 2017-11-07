#include "Frase.hh"

bool Frase::iguals(string p1, string p2) {
    //Funció auxiliar que permet comparar dos paraules
    //sense tenir en compte els signes de puntuacio.
    if (!isalnum(p1[p1.size() - 1])) {
	//Si l'últim caracter no és alfanumèric copia el caracter 
	//i compara les dos paraules afegint-lo a ka que no el té. 
	char last = p1[p1.size() - 1];
	p2 = p2 + last;
    }
    return p1 == p2;
}

Frase::Frase() {
    //La frase buida no té cap paraula.
    paraules = vector<string> (0);
}

void Frase::afegir_paraula(string par) {
    paraules.push_back(par);
}

int Frase::substituir_paraula (string p1, string p2) {
  int num = 0; //Contador de les paraules canviades.
  for(int i = 0; i < paraules.size(); ++i){
    //Per cada paraula del vector si es igual a la que es vol substituir
    //la canvia per l'altra.
    if(paraules[i] == p1){
      paraules[i] = p2;
      num++;
    }
    //Si la paraula acaba amb signe de puntuació fa la substitució afegint-lo.
    else if(paraules[i] == p1+'.' or paraules[i] == p1+'!' or paraules[i] == p1+'?'
      or paraules[i] == p1+':' or paraules[i] == p1+',' or paraules[i] == p1+';'){
      char last = paraules[i][paraules[i].size()-1];
      paraules[i] = p2+last;
      num++;
     }
   }
   return num;
}

bool Frase::buscar_paraula(string paraula) const {
   int p=paraules.size();
   //Per cada paraula de la frase busca la paraula.
   for(int i = 0; i < p; i++) {
      if(iguals(paraules[i],paraula)) return true; 
   }
   return false;     
 
}

void Frase::escriu_frase() const {
  //Escriu la frase.
  cout<<paraules[0]; //Primera paraula sense espai.
  for (int i = 1; i < paraules.size(); i++) {
    //La resta amb un espai de separació.
    if (paraules[i] == "." or paraules[i] == "!" or paraules[i] == "?" or paraules[i] == ":"
     or paraules[i] == "," or paraules[i] == ";") cout << paraules[i];
    else cout << ' ' << paraules[i];
  }
}



bool Frase::buscar_seq(string seq) const {
  string paraula;
  for (int i = 0; i < paraules.size(); ++i) {
    //Busca la seqüència a partir de cada paraula.
    string aux = seq;
    istringstream iss(aux);
    bool trobat = true;
    int j = i;
    while (iss >> paraula) {
      if (j < paraules.size()) {
	if (!iguals(paraules[j], paraula)) trobat = false; 
	//Compara cada paraula de la sequencia amb la següent de la frase.
	++j;
      }
      else return false;
    }
    if (trobat) return true;
  }
  return false;
}

bool Frase::analitzar_exp(string exp) const {
  int longitud = exp.size();
  int pos;
  bool operador = false;
  //Si l'expresio comença amb claus:
  if (exp[0] == '{') {
    //Si acaba amb claus:
    if (exp[longitud - 1] == '}') {
      for (int p=0; p < longitud; ++p) {
	//Busca si hi ha un operador en mig de la frase.
        if (exp[p] == '|' or exp[p] == '&'){
	  operador = true; 
	  pos = p;
          break;
        }
      }
      //Si troba operador:
      if (operador) { 
	//Divideix l'expresio a dreta i esquerra
	string esq = exp.substr(0, pos - 1);
        string drt = exp.substr(pos + 2);
	//Fa una crida recursiva a les dues bandes tenint en compte si es & o |.
	if (exp[pos] == '|') return (analitzar_exp(esq) or analitzar_exp(drt));
	return (analitzar_exp(esq) and analitzar_exp(drt));
      }
      else {
	//Si no hi ha operador elimina les claus i busca les paraules.
	exp=exp.substr(1,longitud-2);
        istringstream iss(exp);
        string paraula;
	//Si ja no en troba una retorna fals.
        while(iss>>paraula) if(!buscar_paraula(paraula))return false;
        return true;
      }
    }
    //Acaba en parèntesis:
    else { 
      for (int p=0; p < longitud; ++p) {
	 pos=p;
	 if (exp[p] == '|' or exp[p] == '&')  break; //Hi ha operador segur.
      }
      //Divideix l'expresio i fa la crida recursiva.
      string esq = exp.substr(0, pos - 1);
      string drt = exp.substr(pos + 2); 

      if (exp[pos] == '|') return (analitzar_exp(esq) or analitzar_exp(drt));
      return (analitzar_exp(esq) and analitzar_exp(drt));
    }
  }
  //Si comença amb parèntesis:
  else if (exp[0] == '(') {
    //Si acaba amb parèntesis els elimina i es queda amb l'expresió central.
    if (exp[longitud - 1] == ')') {
      exp=exp.substr(1,longitud-2);
      longitud = exp.size();          
    }
    //Busca l'oerador que no es troba dins d'altres expresions.
    int num_par, num_clau;
    num_par=num_clau = 0;
    for (int p=0; p < longitud; ++p) {
      if(exp[p]=='(') ++num_par;
      else if(exp[p] == ')') --num_par;
      else if(exp[p] == '}') --num_clau;
      else if(exp[p] == '{') ++num_clau;
      if (num_par==0 and num_clau==0 and (exp[p] == '|' or exp[p] == '&')){
	//Ha trobat un operador que noi es trobava entre parentesis o claus.
	operador = true;
	pos = p;
	break;
      }
    }
    //Si no troba operador analitza l'expresio tal com està.
    if(!operador) return analitzar_exp(exp);
    //Fa la partició i retorna en funció de l'operador.
    string esq = exp.substr(0, pos - 1);
    string drt = exp.substr(pos + 2, longitud-1);
    if (exp[pos] == '|') return (analitzar_exp(esq) or analitzar_exp(drt));
    return (analitzar_exp(esq) and analitzar_exp(drt));       
  }
   //En el cas impossible que s'arrives al final retorna fals; el p2++ obliga a fer un return. 
   return false;
}
