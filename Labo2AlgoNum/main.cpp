//*
//  Summary :   Ce programme définit les points d'intersections
//              d'une fonction avec l'axe des "X"
//              (appellés "Zeros" de la fonctions).
//  Author :    Burri Bastien
//              Schaffo Raphaël
//              Joël Rittiner
//              Vulliemin Kevin
//  Receiver :  Gobron Stéphane
//  Date :      17.03.15
//*

//*--------------------*//
//      Librairies      //
//*--------------------*//
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <math.h>

using namespace std;

//*--------------------*//
//      Définition      //
//*--------------------*//
int askInput(std::string message, int value);
void findIntersects(float a, float b, float eps);
float bissection(float a, float b, float eps);
float fun(float x);

//val 1 pour la première fonction et val 2 pour la 2ème
#define val 1
#define error -99999

//*--------------------*//
//   Prog. Principale   //
//*--------------------*//
int main()
{
    //Valeurs par défaut
    float a = -100;         //Valeurs d'intervalles
    float b = 100;
    float eps = 0.0001;     //Précision
    bool again = false;     //Bouclage

    //Accueil et demandes utilisateurs
    cout << "Bonjour, ce programme propose a l'utilisateur de trouver" << endl <<
            "les points d'intersections d'une fonction avec l'axe des x.\n" << endl;
    do
    {
        if(again)
            system("CLS");

        a = askInput("Veuillez entrer le debut de l'intervalle", -100);
        b = askInput("Veuiller entrer la fin de l'intervalle", 100);

        cout << endl;

        //Résolution
        findIntersects(a, b, eps);

        cout << endl;

        again = askInput("Voulez-vous recommencer (1 Oui, 0 Non)?", 0);
    }while(again);

    return 0;
}

//*--------------------*//
//      Fonctions       //
//*--------------------*//
int askInput(std::string message, int value)
{
    cout << message << " (" << value << " par defaut) : " << endl;
    std::string input;
    std::getline( std::cin, input );

    if ( !input.empty() ) {
        std::istringstream stream( input );
        stream >> value;
    }

    return value;
}

void findIntersects(float a, float b, float eps)
{
    float range;            //Valeur d'intervalle
    float rangeSize = 1;
    int i = 0;              //Compteur de solutions

    for(range = a; range < b; range+=rangeSize+eps)
    {
        float answer = bissection(range, range+rangeSize, eps);

        //Solutions trouvés
        if(answer != error)
        {
            cout.precision(4);
            cout << "Recherche de la " << ++i << " solution(s) :" << endl << answer << endl;
        }
    }

    //Pas de solutions
    if(i == 0) cout << "Pas de solution pour cette intervale" << endl;
}

float bissection(float x1, float x2, float eps)
{
    //Initialisation
    float mNew, mOld;           //Moyennes
    float fm, fa;               //y des valeurs relatives

    fa = fun(x1);               //y du debut de l'intervalle
    mNew = x1 + x2;
    //mOld = 2*mNew;            //Pas utile

    //Recherche
    while(fabs(mNew - mOld) > eps)
    {
        mOld = mNew;            //on sauvegarde l'ancienne moyenne
        mNew = (x1 + x2)/2;     //on effectue la nouvelle moyenne

        fm = fun(mNew);         //y de la moyenne

        if(fm*fa > 0)           //Si on est au DESSUS de la courbe
        {
            x1 = mNew;
            fa = fm;
        }
        else                    //Si on est en DESSOUS de la courbe
        {
            x2 = mNew;
        }
    }

    //Réponse
    mNew = (x1 + x2)/2;
    fm = fun(mNew);         //Dernier y de la reponse pour controle ~=0

    if(fabs(fm) < 10*eps)      //Tend vers 0
        return mNew;
    else                    //Ne tend pas vers 0
        return error;
}

float fun(float x)
{
     switch(val)
     {
     case 1:
        {
        return sin(x) - x / 13;
        }
     case 2:
        {
        return x / (1 - pow(x, 2.0));
        }
     case 3:
        {
        return 9 - pow(x, 2.0);
        }
     case 4:
        {
        return x + 1;
        }
     default:
        {
        cout << "Val must be 1 or 2" << endl;
        }
     }
}


    //On change l'intervalle pour trouver toutes les solutions
    /*tempa = a;

    while(tempa<b)
    {
        //On travail par tranche de 10*precision pour
        //trouver toutes les solutions de l'intervalle
        tempb = tempa+10*eps;

        //Fonction de bissection
        fa = fun(tempa);
        fb = fun(tempb);

        while(fabs(tempb-tempa) > eps)  //Tant que la valeur absolu de la différence
        {
            m = (tempa+tempb) / 2;      //moyenne = a + b / 2
            fm = fun(m);                //my = f(mx)

            if(fm*fa<=0)                //Si on est en DESSOUS de l'axe, on redéfinit l'intervalle sur B
            {                           //!! Commentaire à vérifier !!
                tempb=m;
                fb=fm;
            }
            else                        //Si on est en DESSUS de l'axe, on redéfinit l'intervalle sur A
            {
                tempa=m;
                fa=fm;
            }

            //cout m << endl;        //Si on désire afficher les étapes de résolutions
        }

        tempa=tempb;

        //Solutions trouvés
        if(fabs(fm)<eps)
        {
            cout << "Recherche de la "<< ++i <<" solution(s) :" << endl << m << endl;
        }
    }
    */
