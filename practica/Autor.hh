/** @file Autor.hh
    @brief Especificació de la classe Autor
*/

#ifndef _AUTOR_HH_
#define _AUTOR_HH_
#include "Text.hh"
#include "Cita.hh"
#include <map>

/** @class Autor
    @brief Representa un autor amb els seus textos, les seves cites associades i el nombre de frases i paraules dels seus textos.
   */
class Autor
  {

public:
  //Constructores 

  /** @brief Creadora per defecte. 
      \pre <em>Cert</em>
      \post El resultat és un autor buit.
  */  
  Autor();
  
  /** @brief Crea un autor amb nom. 
      \pre <em>Cert</em>
      \post El resultat es un autor buit amb nom n.
  */  
  Autor(string n);

  //Modificadores
  
  /** @brief Afegeix un text donat a l'autor.
      
      \pre <em>Cert</em>
      \post El parametre implí­cit conté el text txt.
  */
  void afegir_txt(const Text& txt);
  
  /** @brief Elimina un text de l'autor.
  
      \pre Existeix un text triat.
      \post El paràmetre implí­cit ja no conté el text triat.
  */
  void eliminar_txt();
  
   /** @brief Afegeix una cita de l'autor.
      
      \pre  Cta és una cita vàlida.
      \post S'ha afegit la cita cta a l'autor.   
  */
  void afegir_cita(const Cita& cta);
  
  /** @brief Elimina una cita de l'autor.
     
      \pre Existeix una cita amb la referència indicada.
      \post L'autor ja no conté la cita.
  */
  void eliminar_cita (string referencia);
  
  /** @brief Substitueix totes les aparicions d'una paraula en el text triat per una altra.
      \pre <em>Cert</em>
      \post El text triat ja no conté cap aparició de p1 en el contingut i en el seu lloc està p2. 
  */
  void substituir_paraula (string& p1, string& p2);
  
  /** @brief Tria un text de l'autor.
     
      \pre L'autor té almenys pos textos.
      \post El text triat passa a ser el numero pos de l'autor.
  */
  void tria_text (int pos);
  
   /** @brief Especifica si el text triat pertany o no a l'autor.
     
      \pre <em>Cert</em>.
      \post Si b és true el text triat és de l'autor. Si b és false el text triat no és de l'autor.
  */
  void autor_triat (bool b);

  
  //Consultores
  
  /** @brief Consultora del nombre de textos de l'autor.

      \pre  <em>Cert</em>.
      \post El resultat és el nombre de textos de l'autor. 
  */
  int consultar_num_textos() const;

  /** @brief Consultora del nombre de frases dels textos de l'autor.

      \pre  <em>Cert</em>.
      \post El resultat és el nombre de frases dels textos de l'autor. 
  */
  int consultar_num_frases() const;  
  
  /** @brief Consultora del nombre de paraules dels textos de l'autor.

      \pre  <em>Cert</em>.
      \post El resultat és el nombre de paraules dels textos de l'autor. 
  */
  int consultar_num_paraules() const;

   /** @brief Consultora del nombre de cites dels textos de l'autor.

      \pre  <em>Cert</em>.
      \post El resultat és el nombre de cites dels textos de l'autor. 
  */
  int consultar_num_cites() const;
 
  /** @brief Consultora del nom de l'autor.

      \pre  <em>Cert</em>.
      \post El resultat és el nom de l'autor. 
  */
  string consultar_aut() const;
  
  /** @brief Cercadora d'un text de l'autor.

      \pre  <em>Cert</em>.
      \post El resultat és el text numero pos de l'autor. 
  */
  Text cercar_txt(int pos) const;
  
  /** @brief Consultora del text triat.

      \pre  <em>Cert</em>.
      \post El resultat és el text triat. 
  */
  Text consultar_txt_t() const;
  
   /** @brief Indicadora de l'existencia d'una cita.

      \pre  <em>Cert</em>.
      \post El resultat indica si el paràmetre implícit conté la cita cta. 
  */
  bool existeix_cita(const Cita& cta) const;
  
  /** @brief Consultora d'una cita.

      \pre  <em>Cert</em>.
      \post El resultat és la cita amb referència ref. Si no existia la cita retorna una buida.
  */
  Cita cerca_cita(string ref) const;
  
  //Escriptores
  
  /** @brief Escriptora dels títols dels textos de l'autor.

      \pre  <em>Cert</em>.
      \post S'escriuen els tí­tols dels textos de l'autor. 
  */
  void titols() const;
  
  /** @brief Escriptora de les cites de l'autor.

      \pre  <em>Cert</em>.
      \post S'escriuen les referències, el contingut i el títol del text de les cites associades. 
  */
  void cites() const;
   
  /** @brief Escriptora de les cites del text triat.

      \pre  <em>Cert</em>.
      \post S'escriuen les referències, el contingut, el nom de l'autor i el títol del text de les cites del text triat. 
  */
  void cites_triat() const;
  
  /** @brief Escriptora de la informació del text triat.

      \pre  <em>Cert</em>.
      \post S'escriu el nom de l'autor, el titol del text triat, el numero de frases i paraules del text i les cites associades. 
  */
  void escriure_autor_t() const;
private:
   /** @brief Indica el nom de l'autor. */
  string autor;
  /** @brief Indica el nombre de textos de l'autor. */
  int num_textos; 
  /** @brief Indica el nombre de frases en els textos de l'autor. */
  int num_frases;
  /** @brief Indica el nombre de paraules en els textos de l'autor. */
  int num_paraules;
  /** @brief Map que conté els textos de l'autor. Els títols dels textos són les claus del map. */
  map<string, Text> map_text;
  /** @brief Map que conté les cites de textos de l'autor. Les referències de les cites són les claus del map. */
  map<string, Cita> map_cita;
  /** @brief Iterador del map de textos que indica quin és el text triat. */
  map<string, Text>::iterator txt_triat;
  /** @brief Bolea que indica si el text triat és de l'autor. */
  bool atriat;
};
#endif
