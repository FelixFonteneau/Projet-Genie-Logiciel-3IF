 /*************************************************************************
                           Mesure  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Mesure> (fichier Mesure.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel

#include "Mesure.h"
#include "Moment.h"
#include "Capteur.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
double Mesure::Valeur () const
{
  return value;
}

string Mesure::Capteur() const
{
  return capteurid;
}

string Mesure::type () const
{
	return "noType";
}





//------------------------------------------------- Surcharge d'opérateurs
ostream& operator <<(ostream& out, const Mesure& uneMesure)
{
    out << "Le " << uneMesure.date << " : " << uneMesure.value << " " << uneMesure.unite
    << " " << uneMesure.type() << "; capteur : " << uneMesure.capteurid/*<< typeid(uneMesure).name()*/;
    return out; // N'oubliez pas de renvoyer le flux, afin de pouvoir chaîner les appels
}



//-------------------------------------------- Constructeurs - destructeur
Mesure::Mesure(){}

Mesure::Mesure ( const Mesure & uneMesure ) : value(uneMesure.value), date(uneMesure.date),
        description(uneMesure.description),
        unite(uneMesure.unite), capteurid(uneMesure.capteurid)

// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Mesure>" << endl;
#endif

} //----- Fin de Mesure (constructeur de copie)


Mesure::Mesure (double uneValue, Moment& uneDate, string uneDescription,
   string uneUnite, string unCapteurid) :
       value(uneValue), date(uneDate), description(uneDescription), unite(uneUnite), capteurid(unCapteurid)
{
  #ifdef MAP
      cout << "Appel au constructeur de <Mesure>" << endl;
  #endif
}



Mesure::~Mesure ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Mesure>" << endl;
#endif
} //----- Fin de ~Mesure


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
