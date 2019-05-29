/*************************************************************************
                           Capteur  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Capteur> (fichier Capteur.h) ----------------
#if ! defined ( CAPTEUR_H )
#define CAPTEUR_H

//--------------------------------------------------- Interfaces utilisées
#include "Mesure.h"
#include "MesureNO2.h"
#include "MesureO2.h"
#include "MesureSO2.h"
#include "MesurePM10.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
#include <vector>
//------------------------------------------------------------------------
// Rôle de la classe <Capteur>
//
//
//------------------------------------------------------------------------

class Capteur
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    void addMesureO2(int jour, int mois, int annee, int heure, int minute, int seconde, double valeur, string typeMesure);

    /*vector<Mesure> getMesuresNO2()
    {
        return mesuresNO2;
    }
    vector<Mesure> getMesuresSO2()
    {
        return mesuresSO2;
    }
    vector<Mesure> getMesuresPM10()
    {
        return mesuresPM10;
    }*/

//------------------------------------------------- Surcharge d'opérateurs
    // Capteur & operator = ( const Capteur & unCapteur );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Capteur (const string idCapt, const double lat, const double lon, const string description);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Capteur ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    vector<Mesure> mesuresO2;
    vector<Mesure> mesuresNO2;
    vector<Mesure> mesuresSO2;
    vector<Mesure> mesuresPM10;
	const string idCapteur;
	double latitude;
	double longitude;
	string description;
};

//-------------------------------- Autres définitions dépendantes de <Capteur>

#endif // CAPTEUR_H
