/** @file Frase.hh
    @brief Especificació de la classe Frase
*/

#ifndef _FRASE_HH_
#define _FRASE_HH_
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

/** @class Frase
    @brief Representa una frase.  */
   
class Frase
  {

public:
  //Constructores 

  /** @brief Creadora per defecte. 
      \pre <em>Cert</em>
      \post El resultat es una frase buida.
  */  
  Frase();
 
  //modificadores 

  /** @brief Afageix una paraula a la frase. 
      \pre <em>Cert</em>
      \post El paràmetre implícit conté la paraula par.
  */  
 void afegir_paraula(string par);

 /** @brief Substitueix totes les aparicions d'una paraula en la frase per una altra.
      \pre <em>Cert</em>
      \post El paràmetre implicit ja no conté cap aparició de p1, en el seu lloc està p2. 
	    Retorna el nombre de vegades que apareixia p1 en la frase original.
 */
 int substituir_paraula (string p1, string p2);

 //Consultores
 /** @brief Cercadora d'una paraula en una frase del text.

     \pre <em>Cert</em>.
     \post Retorna true si la frase conté la paraula, altrament retorna false. 
 */
 bool buscar_paraula(string paraula) const;
 
 /** @brief Cercadora d'una seqüència de paraules en la frase del text.
 
      \pre  <em>Cert</em>.
      \post Retorna true si la frase conté la seqüència seq de paraules. 
  */
  bool buscar_seq(string seq) const;
   
  /** @brief Cercadora d'una expresio de paraules en la frase del text.
 
      \pre  <em>Cert</em>.
      \post Retorna true si la frase conté la expresio exp. 
  */
  bool analitzar_exp(string exp) const;
  
  //Escriptores
  /** @brief Escriptora d'una frase del text.

     \pre <em>Cert</em>.
     \post S'escriu la frase pel canal de sortida. 
 */
 void escriu_frase() const;
 
 

private:
   /** @brief Vector que conte les parauls de la frase. */
  vector<string> paraules;

  /** @brief Funció que indica si dos paraules son iguals.
    \pre <em>Cert</em>.
    \post El resultat indica si els dos paraules son iguals.
	  Sense tenir en compte els signes de puntuació.
  */
  static bool iguals(string p1, string p2);
   
};
#endif
