/*************************************************************************
 MesureO3  -  description
 -------------------
 début                : $DATE$
 copyright            : (C) $YEAR$ par $AUTHOR$
 e-mail               : $EMAIL$
 *************************************************************************/

//---------- Réalisation de la classe <MesureO3> (fichier MesureO3.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "MesureO3.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void MesureO3::ajout( vector<MesureO3>* mesuresO3, vector<MesureNO2>* mesuresNO2, vector<MesureSO2>* mesuresSO2, vector<MesurePM10>* mesuresPM10){
	mesuresO3->push_back(*this);
}

string MesureO3::type() const{
	return "O3";
}
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

MesureO3::MesureO3 ( double uneValue, Moment& uneDate, string uneDescription, string uneUnite, string unCapteurid ) :
Mesure(uneValue, uneDate, uneDescription, uneUnite, unCapteurid)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <MesureO3>" << endl;
#endif
} //----- Fin de MesureO3




/* MesureO3::~MesureO3 ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <MesureO3>" << endl;
#endif
} //----- Fin de ~MesureO3 */


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
