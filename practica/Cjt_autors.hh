/** @file Cjt_autors.hh
    @brief Especificació de la classe Cjt_autors
*/

#ifndef _CJT_AUTOR_HH_
#define _CJT_AUTOR_HH_
#include "Autor.hh"

/** @class Cjt_autors
    @brief Inclou tots els autors amb textos del programa.
   */
class Cjt_autors
  {

public:
   
  //Constructores 

  /** @brief Creadora per defecte. 
      
      \pre <em>Cert</em>
      \post El resultat es el conjunt buit.
  */  
  Cjt_autors();
  
 
  //Modificadores

  /** @brief Afegeix un text al conjunt.
      
      \pre  <em>Cert</em>
      \post Si ja existeix un text amb el mateix titol i autor dòna un missatge d'error. 
	    Altrament el paràmetre impí­cit conté un text amb titol tit, autor aut i contingut txt.
	    Si no existia l'autor, el paràmetre implí­cit ara l'inclou.
  */
  void afegir_aut(Autor& autor);
  
  /** @brief Afegeix una referència al parametre implicit.
  
      \pre Inicials es un parametre valid
      \post S'ha afegit la referència al paràmetre implícit.
    */
    void afegir_ref(string inicials);
    
   /** @brief Tria un text.

      \pre <em>Cert</em>.
      \post Si no hi ha un únic text que conté les paraules dòna un misatge d'error.
	    Altrament el conjunt té sel·leccionat el text amb les paraules. 
  */
  void triar_txt(string paraules);
  
  /** @brief Afegeix una cita al conjunt.
     
      \pre <em>Cert</em>.
      \post L'autor conte la cita cta.
  */
  void afegir_cita(const Cita& cta);
  
  /** @brief Elimina una cita del conjunt.
     
      \pre <em>Cert</em>.
      \post Si no existeix cap cita amb la referència indicada dòna un misatge d'error.
	    Altrament el paràmetre implícit ja no conté la cita.
  */
  void eliminar_cita (const string& referencia);

  /** @brief Esborra el <em>text triat</em> del parametre implicit.

    \pre Hi ha un text triat.
    \post El parametre implicit ja no conté el text triat.
  */
  void eliminar_txt();
  
  /** @brief Substitueix totes les aparicions del primer parametre al text pel segon parametre.

       \pre El text no és buit.
       \post El parametre conté el text modificat.
     */ 
    void substituir_paraula(string & p1, string & p2);
  
  // Consultores
  
  /** @brief Consultora d'un text triat del parametre implicit
      \pre <em>Cert.</em>
      \post Retorna true si hi ha un text triat, false altrament.
  */
    bool txt_triat() const;
    
   /** @brief Consultora del nom de l'autor.

      \pre <em>Cert</em>.
      \post Si no hi ha un text triat dòna un missatge d'error. 
	    Altrament el resultat es l'autor del text triat. 
  */
  Autor consultar_autor() const;
  
  /** @brief Retorna l'autor amb nom autor del parametre implicit
      \pre <em>Cert</em>.
      \post Si existia un autor amb nom autor el retorna. Retorna un autor buit altrament.
  */
  Autor consultar_aut(const string& autor);
  
   /** @brief Retorna els nombres de la referencia especificada
   
      \pre El parametre <em>inicials</em> és vàlid
      \post Retorna l'index de la referència especificada
   */
    int consultar_index(const string& inicials) const;
  
   //Escriptores

   /** @brief Escriptora dels textos del conjunt.

      \pre <em>Cert</em>.
      \post S'escriuen els titols i l'autor de tots els textos ordenats per autor i títol. 
  */
  void escriure_textos() const;
  
  /** @brief Escriptora dels autors del conjunt.

      \pre <em>Cert</em>.
      \post S'escriuen tots els autors indicant el nombre de textos de l'autor,i el nombre de frases i paraules dels textos. Ordenats alfabeticament.
  */
  void autors() const;
  
  /** @brief Escriptora de les frases que compleixen l'expressió.

      \pre <em>exp</em> conte l'expressio.
      \post S'escriuen les frases que compleixen l'expressio.
    */
    void exp_frases(string & exp);

  /** @brief Escriptora de totes les cites del conjunt.

      \pre <em>Cert</em>.
      \post S'escriuen totes les cites del parametre implicit. Se'n escriu:la referència, el contingut, l'autor i títol del text. Ordenades per referència.
  */
  void cites_conj() const;  

 /** @brief Escriptora d'una cita.

      \pre <em>Cert</em>.
      \post Si no hi ha cap cita amb referència ref dòna un missatge d'error.
	    Altrament s'escriu la cita amb referencia ref. Se'n escriu: l'autor, títol, numero de les frases inicial i final i el contingut.
  */
  void cita_ref(string ref) const; 

private:
  /** @brief Bolea que indica que hi ha un text triat. */
  bool ttriat;
  /** @brief Map que conté tots els autors. */
  map<string, Autor> map_autor;
  /** @brief Iterador del map d'autors que indica la posició de l'autor del text triat. */
  map<string, Autor>::iterator aut_triat;
  /** @brief Map amb la referència de les cites, la clau son les inicials de l'autor i el contingut el nombre de referències per aquelles inicials. */
  map<string, int> map_ref;
  /** @brief Retorna si una paraula es troba en un string.
      \pre <em>Cert.</em>
      \post Retorna true si s'ha trobat la paraula al string. Altrament, retorna fals.
  */
  static bool buscar_par(string paraula, string paraules);
  /** @brief Comprova si les inicials de l'autor on apunta l'iterador <em>aut</em> corresponen amb <em>inicials</em>.
      \pre <em>aut</em> es un iterador valid, igual que <em>inicials</em>.
      \post Retorna cert si les inicials de l'autor on apunta <em>aut</em> corresponen amb <em>inicials</em>. Altrament, retorna fals.
  */
  static bool mirar_inicials(const map<string, Autor>::const_iterator & aut, const string & inicials);
};
#endif
