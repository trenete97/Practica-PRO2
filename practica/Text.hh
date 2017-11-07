/** @file Text.hh
    @brief Especificació de la classe Text
*/

#ifndef _TEXT_HH_
#define _TEXT_HH_
#include <vector>
#include <algorithm>
#include "Frase.hh"


using namespace std;

/** @class Text
    @brief Representa un text que inclou: tí­tol, autor i contingut.  */
   
class Text
  {

public:
  //Constructores 

  /** @brief Creadora per defecte. 
      \pre <em>Cert</em>
      \post El resultat es un text buit.
  */  
  Text();
 
  //Modificadores

  /** @brief Defineix el text.
      \pre El paràmetre implícit està buit.
      \post El paràmetre implícit conté un títol tit i autor aut. També llegeix el contingut.
  */
  void omplir_text(string tit, string aut);

  /** @brief Substitueix totes les aparicions d'una paraula en el text per una altra.
      \pre <em>Cert</em>
      \post El paràmetre implicit ja no conté cap aparició de p1 en el contingut i en el seu lloc està p2. 
  */
  void substituir_paraula (string p1, string p2);

  // Consultores

  /** @brief Consultora del nom de l'autor.

      \pre <em>Cert</em>.
      \post El resultat es l'autor del text. 
  */
  string consultar_autor() const;
  

  /** @brief Consultora del títol del text.

      \pre  <em>Cert</em>.
      \post El resultat és el títol del text.
  */
  string consultar_titol() const;

  
  /** @brief Consultora del nombre de paraules del text.

      \pre  <em>Cert</em>.
      \post El resultat és el nombre de paraules del text. 
  */
  int consultar_num_paraules() const;
  
 
  /** @brief Consultora del nombre de frases del text.

      \pre  <em>Cert</em>.
      \post El resultat és el nombre de frases del text. 
  */
  int consultar_num_frases() const;
  
  /** @brief Consultora d'una frase del text.

      \pre El text té com a mínim num_frases frases.
      \post Retorna la frase amb numero num_frase. 
  */
  Frase consultar_frase(int num_frase) const;
  
  
  /** @brief Cercadora d'una paraula en una frase del text.

      \pre El text té com a mí­nim num_frases frases.
      \post Retorna true si la frase amb numero num_frase conté la paraula, altrament retorna false. 
  */
  bool buscar_paraula(string paraula, int num_frase) const;

  /** @brief Cercadora d'una paraula en el text.

      \pre <em>Cert</em>.
      \post Retorna la posició de la paraula en la taula de freqüències.
	    Si no existia retorna -1.
  */
  int buscar_par(string paraula) const;
  
 
  //Escriptura
  
  /** @brief Escriptora de frases del text.

      \pre Si es dòna l'interval x y, és valid.
      \post Escriu numerades de la x-èssima fins a la y-èssima frase del contingut. Si nop es donava interval escriu tot el text. 
  */  
  void escriu_frases(int x,int y);
  
  
  /** @brief Escriptora de la freqüència de les paraules del text.

      \pre  <em>Cert</em>.
      \post S'escriuen les paraules del text ordenades per frequencia i en cas d'empat creixentment (primer llargada i després alfabèticament). 
  */
  void taula_freq() const;
  
  
  /** @brief Cercadora d'una seqüència de paraules en les frases del text.
 
      \pre  <em>Cert</em>.
      \post S'escriuen les frases del text que contenen la seqüència seq de paraules. 
  */
  void buscar_seq(string seq) const;
 
  /** @brief Cercadora d'una expresio de paraules en les frases del text.
 
      \pre  <em>Cert</em>.
      \post S'escriuen les frases del text que contenen l'expresió exp de paraules. 
  */
  void exp_frases(string exp) const;
  
  /** @brief Representa una paraula, està formada per la cadena (l'string de la paraula) 
      i la freqüència en la que apareix en un text.  */
 
  struct Paraula{
    string cadena;
    int freq;
  };
 
  
private:
  /** @brief Indica el nom de l'autor del text. */
  string autor;
  /** @brief Indica el títol del text. */
  string titol;
  /** @brief Indica el nombre de paraules del text. */
  int num_paraules;
  /** @brief Indica el nombre de frases del text. */
  int num_frases;
  /** @brief Vector que conté les paraules del text, sense signes de puntuacio, amb la seva freqüència. */
  vector<Paraula> paraules;
  /** @brief Vector que conte les frases del text. */
  vector<Frase> frases;
  /** @brief Funció per ordenar el vector de paraules decreixentment en funcio de la frequencia i en cas d'empat alfabeticament.
    \pre  <em>Cert</em>..
    \post El resultat indica si el valor de la frequencia de p1 és més gran que el de p2, en cas d'empat els compara alfabeticament.
  */
  static bool ordre(const Paraula& p1, const Paraula& p2);
  /** @brief Arregla els espais addicionals d'un string i el retorna normalitzat.
      \pre  <em>Cert</em>.
      \post El string esta normalitzat, no conté espais addicionals.
  */
  static string treu_espais(string s);
};
#endif
