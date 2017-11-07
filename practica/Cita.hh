/** @file Cita.hh
    @brief Especificació de la classe Cita
*/

#ifndef _CITA_HH_
#define _CITA_HH_

#include "Frase.hh"
#include "Text.hh"

using namespace std;

/** @class Cita
    @brief Representa una cita que inclou: títol, referencia, contingut, la frase on comença i la frase on acaba.
  */
class Cita
  {

public:
  //Constructores 

  /** @brief Creadora per defecte. 
      \pre <em>Cert</em>
      \post El resultat es una cita buida.
  */  
  Cita();
  
  /** @brief Creadora d'una cita amb els parametres inicialitzats.
      \pre Els parametres son valids.
      \post El resultat es una cita amb els parametres inicialitzats.
  */ 
  Cita(string referencia, string titol, int x, int y, vector<Frase> contingut);

  //Modificadores

  /** @brief Modificadora d'una cita.
      \pre L'interval x y es valid i no existeix una altre cita del mateix text amb el mateix contingut.
      \post El resultat es una cita amb titol, referencia, el nombre de les frases on comença i acaba i el seu contingut.
  */
  void omplir_cita(const Text& txt, int x, int y, string ref);

  //Consultores

  /** @brief Consultora del títol del text.

      \pre <em>Cert</em>.
      \post El resultat és el títol del text al qual està associada la cita.
  */
  string consultar_titol() const;

  /** @brief Consultora de la referencia de la cita.

      \pre <em>Cert</em>.
      \post El resultat és la referencia de la cita. 
  */
  string consultar_referencia() const;

  /** @brief Consultora de la frase del text on comença la cita.

      \pre <em>Cert</em>.
      \post El resultat és el numero de la frase on comença la cita.
  */
  int consultar_x() const;
  
  /** @brief Consultora de la frase del text on acaba la cita.

      \pre <em>Cert</em>.
      \post El resultat és el numero de la frase on acaba la cita.
  */
  int consultar_y() const;
  
  /** @brief Consultora del contingut de la cita.

      \pre La cita esta inicialitzada.
      \post Retorna el contingut del patrametre implicit.
  */
  vector<Frase> consultar_contingut();
  
  //Escriptores
  
  /** @brief Escriptora dels parametres identificadors del parametre implicit.
      \pre El parametre implicit no es buit.
      \post S'escriuen els parametres identificadors de la cita.
  */
  void escriu_contingut() const;
  
private:
  /** @brief Indica el títol del text al qual pertany la cita. */
  string titol;
  /** @brief Indica la referència d'una cita, si el seu valor es "-1" es considera que la cita és buida. */
  string referencia;
  /** @brief Vector que conté cada una de les frases de la cita. */
  vector<Frase> contingut;
  /** @brief Indica la frase del text on comença la cita. */
  int x;
  /** @brief Indica la frase del text on acaba la cita. */
  int y;
};
#endif
