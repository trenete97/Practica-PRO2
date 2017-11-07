#include "Autor.hh"

Autor::Autor() {
  //L'autor creat és buit i per tant tots els seus paràmetres son nuls.
  autor="";
  num_textos = num_frases = num_paraules = 0;
  map_text = map<string, Text>();
  txt_triat = map<string, Text>::iterator();
  map_cita = map<string, Cita>();
  atriat=false;
}

Autor::Autor(string n) {
  //L'autor creat és buit i per tant tots els seus paràmetres son nuls.
  //A excepció del nom que l'hi és donat.
  autor=n;
  num_textos = num_frases = num_paraules = 0;
  map_text = map<string, Text>();
  txt_triat = map<string, Text>::iterator();
  map_cita = map<string, Cita>();
  atriat=false;
}

void Autor::afegir_txt(const Text& txt) {
  map_text.insert(make_pair(txt.consultar_titol(), txt));
  num_frases += txt.consultar_num_frases();	
  //S'incrementa el nombre de frases de l'autor amb les del text.
  num_paraules += txt.consultar_num_paraules();	
  //S'incrementa el nombre de paraules de l'autor amb les del text.
  ++num_textos;
  //S'incrementa en 1 el nombre de textos de l'autor.
}

void Autor::afegir_cita(const Cita& cta) {
  //S'afageix la cita en el map de cites, com a clau s'usa la seva referència.
  map_cita.insert(make_pair(cta.consultar_referencia(),cta));
}

void Autor::eliminar_txt() {
  num_frases-=txt_triat->second.consultar_num_frases();		
  //Es redueix el nombre de frases de l'autor amb les que pertanyen al text ha borrar.
  num_paraules-=txt_triat->second.consultar_num_paraules();	
  //Es redueix el nombre de paraules de l'autor amb les que pertanyen al text ha borrar.
  map_text.erase(txt_triat->first);
  //S'elimina el text del map
  --num_textos;
  //I es redueix en un el nombre de textos de l'autor
  txt_triat=map_text.end();
  //Es perd el valor del text triat .
  atriat=false;
  //Es declara que l'autor no té el text triat.
}

void Autor::eliminar_cita (string referencia) {
  map_cita.erase(referencia);
  //S'elimina del map la cita segons la referència.
}

void Autor::tria_text (int pos) {
  txt_triat=map_text.begin();
  //L'iterador de txt_triat es mou a l'inici del map.
  for(int i=0; i<pos; ++i) {
   //S'incrementa l'iterador fins que indica el text a la posició pos.
   ++txt_triat;
  }
  atriat=true;
  //Es declara que l'autor conté el text triat.
}

void Autor::substituir_paraula(string& p1,string& p2){
  txt_triat->second.substituir_paraula(p1,p2);
}

void Autor::autor_triat (bool b) {
  atriat=b;
}

int Autor::consultar_num_paraules() const {
  return num_paraules;
}
 
int Autor::consultar_num_frases() const {
  return num_frases;
}

int Autor::consultar_num_textos() const {
  return num_textos;
}

int Autor::consultar_num_cites() const {
  return map_cita.size();
}

string Autor::consultar_aut() const {
  return autor;
}

Text Autor::consultar_txt_t() const {
  return txt_triat->second;
}

Text Autor::cercar_txt(int pos) const {
  map<string, Text>::const_iterator it;
  //Es declara un iterador a l'inici del map de textos.
  it=map_text.begin();
  for(int i=0; i<pos; ++i) ++it;
  //S'incrementa l'iterador fins que aquest apunta el text a la posició pos.
  return it->second;
  //Retorna el text a la posició pos.
}


bool Autor::existeix_cita(const Cita& cta) const {
  string titol = cta.consultar_titol();
  int num=map_cita.size();
  map<string, Cita>::const_iterator it;
  //Es declara un iterador a l'inici del map de cites.
  it=map_cita.begin();
  for(int i=0; i<num; ++i){
    //Es busca en cada element del map:
    if(it->second.consultar_titol()==cta.consultar_titol()){
      //Si coincideix el titol, la x i la y existeix una cita igual.
      if(it->second.consultar_x()==cta.consultar_x()){
	if(it->second.consultar_y()==cta.consultar_y()) return true;
      }
    }
    ++it;
  }
  return false;
  //Altrament el map no conté la cita.
}
               
Cita Autor::cerca_cita(string ref) const { 
  map<string, Cita>::const_iterator it;
  //Es declara un iterador del map de cites a la posició que té per clau ref.
  it=map_cita.find(ref);
  if(it!= map_cita.end()) return it->second;
  //Si la posició és vàlida retorna la cita.
  else{
    Cita cta;
    //sinó crea i retorna una cita buida.
    return cta;
  }

}

void Autor::titols() const {
  map<string, Text>::const_iterator it;
  //Es declara un iterador a l'inici del map de textos.
  it=map_text.begin();
  for(int i=0; i<num_textos; ++i){
    //Per cada text s'escriu la seva clau en el map, és a dir, el seu títol.
    cout<<'"'<<it->first<<'"'<<endl;
    ++it;
  }
}

void Autor::cites() const {
  for(map<string, Cita>::const_iterator it = map_cita.begin(); it != map_cita.end(); ++it){
  //Per cada element en el map de cites:
  cout<<it->first<<endl;
  //Se'n escriu la clau, és a dir, la referència; 
  it->second.escriu_contingut();
  //el contingut i el titol del text.
  cout<<'"'<<it->second.consultar_titol()<<'"'<<endl;
  }
}

void Autor::cites_triat() const {
  int num=map_cita.size();
  map<string, Cita>::const_iterator it;
  //Es declara un iterador a l'inici del map de cites.
  it=map_cita.begin();
  for(int i=0; i<num; ++i){
      //Per cada cita que pertany al text triat se'n escriu la informació.
      if(it->second.consultar_titol()==txt_triat->first){
	cout<<it->first<<endl;
	it->second.escriu_contingut();
	cout<<autor<<' '<<'"'<<it->second.consultar_titol()<<'"'<<endl;
	++it;
      }
  }
}
void Autor::escriure_autor_t() const {
  //Escriu la informació del text triat.
  cout<<autor<<' '<<'"'<<txt_triat->first<<'"'<<' '<<txt_triat->second.consultar_num_frases();
  cout<<' '<<txt_triat->second.consultar_num_paraules()<<endl;
  cout<<"Cites Associades:"<<endl;
  int num=map_cita.size();
  //Escriu les cites del text triat. 
  map<string, Cita>::const_iterator it;
  it=map_cita.begin();
  for(int i=0; i<num; ++i){
    if(it->second.consultar_titol()==txt_triat->first){
      //Comprova que la cita és del text triat.
      cout<<it->first<<endl;
      it->second.escriu_contingut();
      ++it;
    }
  }
}