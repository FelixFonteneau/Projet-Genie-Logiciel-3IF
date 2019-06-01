/*************************************************************************
 Algo  -  description
 -------------------
 début                : $DATE$
 copyright            : (C) $YEAR$ par $AUTHOR$
 e-mail               : $EMAIL$
 *************************************************************************/

//---------- Réalisation de la classe <Algo> (fichier Algo.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <cmath>
#include <float.h>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Algo.h"
#define PI  3.141592653589793238463
#define earthRadiusKm 6371.0
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

vector<double> Algo::Moyenne(vector<Moment> intervaleTemps, double radius, vector<double> coordonees, vector<Capteur*>* capteurs)
// Algorithme : Fait la moyenne des moyenne des capteurs.
{
  vector<double> somme;
  vector<double> nbValeurs;
  vector<double> moyenne;
  //initialisation des vecteurs moyenne et somme à 4 valeurs à 0
  for( unsigned i(0); i < 4; i++)
  {
    somme.push_back(0);
    nbValeurs.push_back(0);
  }

//on parcours tous les capteurs
  for(Capteur* capteur : capteurTerritoire(capteurs, radius, coordonees))
  {
    vector<double> moyenneCapt = moyenneCapteur(capteur, intervaleTemps);

    //pour toutes les valeurs (O3/NO2/SO2/PM10) donc 4
    for(unsigned i(0); i < 4; i++)
    {
        // si aucune valeur => -1
        if(moyenneCapt[i] > 0)
        {
          somme[i] += moyenneCapt[i];
          ++nbValeurs[i];
        }
    }
  }
  //calcul de moyenne
  for(unsigned i(0); i < 4; i++)
  {
      //on regarde si il y a eu des valeurs
      if(nbValeurs[i] > 0 )
      {
        moyenne[i] = somme[i]/nbValeurs[i];
      }
      //sinon on met la valeur à -1, pour aucune valeurs
      else
      {
        moyenne[i] = -1;
      }
  }
  return moyenne;
}


double Algo::QualiteAir(vector<Capteur*>* capteurs, double latitude, double longitude)
{
    double rayonMax = 90;
    int nbCapteur = 0;
    double distanceMini1 = DBL_MAX, distanceMini2 = DBL_MAX, distanceMini3 = DBL_MAX;

    vector<MesureSO2> *MesuresSO2Capt1, *MesuresSO2Capt2, *MesuresSO2Capt3;
    vector<MesureO3> *MesuresO3Capt1, *MesuresO3Capt2, *MesuresO3Capt3;
    vector<MesurePM10> *MesuresPM10Capt1, *MesuresPM10Capt2, *MesuresPM10Capt3;
    vector<MesureNO2> *MesuresNO2Capt1, *MesuresNO2Capt2, *MesuresNO2Capt3;

    for (Capteur* capteur : *capteurs)
    {
        vector<double> coordsCapteur = capteur->getCoords();
        double distanceCourante = obtenirDistance(coordsCapteur[0], coordsCapteur[1], latitude, longitude);
        if (distanceCourante < distanceMini1 && distanceCourante < rayonMax)
        {
            distanceMini1 = distanceCourante;
            nbCapteur++;
            MesuresSO2Capt1 = (*capteur).RecupererMesuresSO2();
            MesuresO3Capt1 = (*capteur).RecupererMesuresO3();
            MesuresPM10Capt1 = (*capteur).RecupererMesuresPM10();
            MesuresNO2Capt1 = (*capteur).RecupererMesuresNO2();
        }
        if (distanceMini1 < distanceCourante && distanceCourante < distanceMini2  && distanceCourante < rayonMax)
        {
            distanceMini2 = distanceCourante;
            nbCapteur++;
            MesuresSO2Capt2 = (*capteur).RecupererMesuresSO2();
            MesuresO3Capt2 = (*capteur).RecupererMesuresO3();
            MesuresPM10Capt2 = (*capteur).RecupererMesuresPM10();
            MesuresNO2Capt2 = (*capteur).RecupererMesuresNO2();
        }
        if (distanceMini2 < distanceCourante && distanceCourante < distanceMini3  && distanceCourante < rayonMax)
        {
            distanceMini3 = distanceCourante;
            nbCapteur++;
            MesuresSO2Capt3 = (*capteur).RecupererMesuresSO2();
            MesuresO3Capt3 = (*capteur).RecupererMesuresO3();
            MesuresPM10Capt3 = (*capteur).RecupererMesuresPM10();
            MesuresNO2Capt3 = (*capteur).RecupererMesuresNO2();
        }
    }

    int derniereMesureCapt1 = 0, derniereMesureCapt2 = 0, derniereMesureCapt3 = 0;
    double NO2Capt1 = 0, O3Capt1 = 0, PM10Capt1 = 0, SO2Capt1 = 0, NO2Capt2 = 0, O3Capt2 = 0, PM10Capt2 = 0, SO2Capt2 = 0, NO2Capt3 = 0, O3Capt3 = 0, PM10Capt3 = 0, SO2Capt3 = 0;

    if (nbCapteur >= 1) {
        derniereMesureCapt1 = (*MesuresSO2Capt1).size() - 1;
        NO2Capt1 = MesuresNO2Capt1->at(derniereMesureCapt1).Valeur();
        O3Capt1 = MesuresO3Capt1->at(derniereMesureCapt1).Valeur();
        PM10Capt1 = MesuresPM10Capt1->at(derniereMesureCapt1).Valeur();
        SO2Capt1 = MesuresSO2Capt1->at(derniereMesureCapt1).Valeur();
    }
    if (nbCapteur >= 2) {
        derniereMesureCapt2 = (*MesuresSO2Capt2).size() - 1;
        NO2Capt2 = MesuresNO2Capt2->at(derniereMesureCapt2).Valeur();
        O3Capt2 = MesuresO3Capt2->at(derniereMesureCapt2).Valeur();
        PM10Capt2 = MesuresPM10Capt2->at(derniereMesureCapt2).Valeur();
        SO2Capt2 = MesuresSO2Capt2->at(derniereMesureCapt2).Valeur();
    }
    if (nbCapteur == 3) {
        derniereMesureCapt3 = (*MesuresSO2Capt3).size() - 1;
        NO2Capt3 = MesuresNO2Capt3->at(derniereMesureCapt3).Valeur();
        O3Capt3 = MesuresO3Capt3->at(derniereMesureCapt3).Valeur();
        PM10Capt3 = MesuresPM10Capt3->at(derniereMesureCapt3).Valeur();
        SO2Capt3 = MesuresSO2Capt3->at(derniereMesureCapt3).Valeur();
    }

    int atmo = 0;

    atmo = calculAtmoPondere(NO2Capt1,
                                O3Capt1,
                                PM10Capt1,
                                SO2Capt1,

                                NO2Capt2,
                                O3Capt2,
                                PM10Capt2,
                                SO2Capt2,

                                NO2Capt3,
                                O3Capt3,
                                PM10Capt3,
                                SO2Capt3,

                                distanceMini1,
                                distanceMini2,
                                distanceMini3,

                                nbCapteur);

    return atmo;
}



/*Mesure* moyenne(Moment intervaleTemps[2], double radius, double coordonees[2], list<Capteur> capteurs) {
    Mesure mesures[4];
    sumNO2 = 0;
    sumCO2 = 0;
    sumNO4 = 0;
    sumH1N1 = 0;
    for(Moment m : capteurs.getMoment()) {
        //if(c.getMesure().getMoment()) {
            sumNO2 += c.getMesures[1].getValue;
            //...
        //}
    }

    return mesures
}


double qualiteAir(list<Capteur> capteurs, double coordonees[2]) {
    //à compléter
}*/


vector<Capteur*> Algo::capteurTerritoire(vector<Capteur*>* capteurs, double radius, vector<double> coordonees) {
    vector<Capteur*> captTerritoire;
    for(Capteur* c : *capteurs) {
		    vector<double> coords = c->getCoords();
        double dist = pow((coords[0]-coordonees[0]),2)+pow(coords[2]-coordonees[1], 2);
        if(dist < radius) {
            captTerritoire.push_back(c);
        }
    }
    return captTerritoire;
}
/*
list<Capteur> capteurDefaillants(list<Capteur> capteurs) {
    list<Capteur> captDefaillants;
    for(Capteur c : capteurs) {
        for(Mesure m : c.getMesures()[0]) {
            if(m.value < 0){
                captDefaillants.insert(captDefaillants.end(), c);
            }
        }
        for(Mesure m : c.getMesures()[1]) {
            if(m.value < 0){
                captDefaillants.insert(captDefaillants.end(), c);
            }
        }
        for(Mesure m : c.getMesures()[2]) {
            if(m.value < 0){
                captDefaillants.insert(captDefaillants.end(), c);
            }
        }
        for(Mesure m : c.getMesures()[3]) {
            if(m.value < 0){
                captDefaillants.insert(captDefaillants.end(), c);
            }
        }
    }
    return captDefaillants;
}*/


bool Algo::similitude(vector<double> v1, vector<double> v2) {

	double ecartO3, ecartNO2,ecartSO2,ecartPM10;

	//On prend un dixieme de la médiane des valeurs comme seuil d'erreur
	const double seuilO3 = 240/2 * 0.1;
	const double seuilNO2 = 400/2 * 0.1;
	const double seuilSO2 = 500/2 * 0.1;
	const double seuilPM10 = 80/2 * 0.1;

	ecartO3 = abs(v1[0] - v2[0]);
	ecartNO2 = abs(v1[0] - v2[0]);
	ecartSO2 = abs(v1[0] - v2[0]);
	ecartPM10 = abs(v1[0] - v2[0]);

	if(ecartO3 <= seuilO3 && ecartNO2 <= seuilNO2 && ecartSO2 <= seuilSO2  && ecartPM10 <= seuilPM10){
		return true;
	}
	else {
		return false;
	}
}

/*
double ecartTypeRelatif(list<Mesure> mesures) {
    return 4;
}

list<Capteur> capteursProches(double latitude, double  longitude, list<Capteur> capteurs) {
    return nullptr;
}*/

//------------------------------------------------- Surcharge d'opérateurs
// Algo & Algo::operator = ( const Algo & unAlgo )
// Algorithme :
//
// {
// } //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Algo::Algo()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Algo>" << endl;
#endif
} //----- Fin de Algo


Algo::~Algo()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Algo>" << endl;
#endif
} //----- Fin de ~Algo


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
double Algo::enRadians(double latitude)
{
    return latitude * PI / 180;
}

// retourne la distance en metres
double Algo::obtenirDistance(double lat1d, double lon1d, double lat2d, double lon2d)
{

    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = enRadians(lat1d);
    lon1r = enRadians(lon1d);
    lat2r = enRadians(lat2d);
    lon2r = enRadians(lon2d);
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

int Algo::calculAtmoPondere(double valeurNO2Capt1, double valeurO3Capt1, double valeurPM10Capt1, double valeurSO2Capt1,
                            double valeurNO2Capt2, double valeurO3Capt2, double valeurPM10Capt2, double valeurSO2Capt2,
                            double valeurNO2Capt3, double valeurO3Capt3, double valeurPM10Capt3, double valeurSO2Capt3,
                            double distanceMini1, double distanceMini2, double distanceMini3, int nbCapteur)
{
    double atmoNO2, atmoO3, atmoPM10, atmoSO2;
    double inv1 = pow(distanceMini1, -1), inv2 = pow(distanceMini2, -1), inv3 = pow(distanceMini3, -1);
    if (nbCapteur == 0) {
        inv1 = 0; inv2 = 0; inv3 = 0;
    } else if (nbCapteur == 1) {
        inv2 = 0; inv3 = 0;
    } else if (nbCapteur == 2) {
        inv3 = 0;
    }

    double somme = inv1 + inv2 + inv3;

    atmoNO2 = inv1*valeurNO2Capt1 + inv2*valeurNO2Capt2 + inv3*valeurNO2Capt3;
    atmoNO2 = calculAtmo(atmoNO2/somme,"NO2");

    atmoO3 = inv1*valeurO3Capt1 + inv2*valeurO3Capt2 + inv3*valeurO3Capt3;
    atmoO3 = calculAtmo(atmoO3/somme,"O3");

    atmoPM10 = inv1*valeurPM10Capt1 + inv2*valeurPM10Capt2 + inv3*valeurPM10Capt3;
    atmoPM10 = calculAtmo(atmoPM10/somme, "PM10");

    atmoSO2 = inv1*valeurSO2Capt1 + inv2*valeurSO2Capt2 + inv3*valeurSO2Capt3;
    atmoSO2 = calculAtmo(atmoSO2/somme, "SO2");

    return max(max(int(atmoNO2),int(atmoO3)), max(int(atmoPM10),int(atmoSO2)));

}

int Algo::calculAtmo(double valeur, string type)
{
    int result = 0;
    if (type.compare("NO2") == 0)
    {
        if (0 <= valeur && valeur <= 29) {
            result = 1;
        } else if (30 <= valeur && valeur <= 54) {
            result = 2;
        } else if (55 <= valeur && valeur <= 84) {
            result = 3;
        } else if (85 <= valeur && valeur <= 109) {
            result = 4;
        } else if (110 <= valeur && valeur <= 134) {
            result = 5;
        } else if (135 <= valeur && valeur <= 164) {
            result = 6;
        } else if (165 <= valeur && valeur <= 199) {
            result = 7;
        } else if (200 <= valeur && valeur <= 274) {
            result = 8;
        } else if (275 <= valeur && valeur <= 399) {
            result = 9;
        } else result = 10;
    }
    else if (type.compare("O3") == 0)
    {
        if (0 <= valeur && valeur <= 29) {
            result = 1;
        } else if (30 <= valeur && valeur <= 54) {
            result = 2;
        } else if (55 <= valeur && valeur <= 79) {
            result = 3;
        } else if (80 <= valeur && valeur <= 104) {
            result = 4;
        } else if (105 <= valeur && valeur <= 129) {
            result = 5;
        } else if (130 <= valeur && valeur <= 149) {
            result = 6;
        } else if (150 <= valeur && valeur <= 179) {
            result = 7;
        } else if (180 <= valeur && valeur <= 209) {
            result = 8;
        } else if (210 <= valeur && valeur <= 239) {
            result = 9;
        } else result = 10;
    }
    else if (type.compare("PM10") == 0)
    {
        if (0 <= valeur && valeur <= 6) {
            result = 1;
        } else if (7 <= valeur && valeur <= 13) {
            result = 2;
        } else if (14 <= valeur && valeur <= 20) {
            result = 3;
        } else if (21 <= valeur && valeur <= 27) {
            result = 4;
        } else if (28 <= valeur && valeur <= 34) {
            result = 5;
        } else if (35 <= valeur && valeur <= 41) {
            result = 6;
        } else if (42 <= valeur && valeur <= 49) {
            result = 7;
        } else if (50 <= valeur && valeur <= 64) {
            result = 8;
        } else if (65 <= valeur && valeur <= 79) {
            result = 9;
        } else result = 10;
    }
    else if (type.compare("SO2") == 0)
    {
        if (0 <= valeur && valeur <= 39) {
            result = 1;
        } else if (40 <= valeur && valeur <= 79) {
            result = 2;
        } else if (80 <= valeur && valeur <= 119) {
            result = 3;
        } else if (120 <= valeur && valeur <= 159) {
            result = 4;
        } else if (160 <= valeur && valeur <= 199) {
            result = 5;
        } else if (200 <= valeur && valeur <= 249) {
            result = 6;
        } else if (250 <= valeur && valeur <= 299) {
            result = 7;
        } else if (300 <= valeur && valeur <= 399) {
            result = 8;
        } else if (400 <= valeur && valeur <= 499) {
            result = 9;
        } else result = 10;
    }
    return result;
}

vector<double> Algo::moyenneCapteur(Capteur* capteur, vector<Moment> intervaleTemps)
{
  vector<double> resultatMoyenne;
  double moyO3, moyNO2, moySO2, moyPM10;
  double somme(0);
  double nbMesure(0);

// calcul moyenne O3
  for(MesureO3 mesure : *capteur->RecupererMesuresO3())
  {
    if(mesure.getDate() > intervaleTemps[0] && mesure.getDate() < intervaleTemps[1])
    {
      somme += mesure.Valeur();
      ++nbMesure;
    }
  }
  if(nbMesure > 0)
  {
    moyO3 = somme/nbMesure;
  }
  else
  {
    moyO3 = -1;
  }

// calcul moyenne NO2
  somme = 0;
  nbMesure = 0;
  for(MesureNO2 mesure : *capteur->RecupererMesuresNO2())
  {
    if(mesure.getDate() > intervaleTemps[0] && mesure.getDate() < intervaleTemps[1])
    {
      somme += mesure.Valeur();
      ++nbMesure;
    }
  }
  if(nbMesure > 0)
  {
    moyNO2 = somme/nbMesure;
  }
  else
  {
    moyNO2 = -1;
  }

  // calcul moyenne SO2
    somme = 0;
    nbMesure = 0;
    for(MesureSO2 mesure : *capteur->RecupererMesuresSO2())
    {
      if(mesure.getDate() > intervaleTemps[0] && mesure.getDate() < intervaleTemps[1])
      {
        somme += mesure.Valeur();
        ++nbMesure;
      }
    }
    if(nbMesure > 0)
    {
      moySO2 = somme/nbMesure;
    }
    else
    {
      moySO2 = -1;
    }

    // calcul moyenne SO2
    somme = 0;
    nbMesure = 0;
    for(MesurePM10 mesure : *capteur->RecupererMesuresPM10())
    {
      if(mesure.getDate() > intervaleTemps[0] && mesure.getDate() < intervaleTemps[1])
      {
        somme += mesure.Valeur();
        ++nbMesure;
      }
    }
    if(nbMesure > 0)
    {
      moyPM10 = somme/nbMesure;
    }
    else
    {
      moyPM10 = -1;
    }

    resultatMoyenne.push_back(moyO3);
    resultatMoyenne.push_back(moyNO2);
    resultatMoyenne.push_back(moySO2);
    resultatMoyenne.push_back(moyPM10);

    return resultatMoyenne;

}