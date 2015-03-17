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
#include <math.h>

using namespace std;

//*--------------------*//
//      Définition      //
//*--------------------*//
float fun(float x);
void bisection(float a, float b, float eps);

//val 1 pour la première fonction et val 2 pour la 2ème
#define val 1

//*--------------------*//
//   Prog. Principale   //
//*--------------------*//
int main()
{
    float tempa, a = -100;  //Valeurs d'intervalles
    float tempb, b = 100;
    float eps = 0.0001;     //Précision
    float m;                //Moyenne
    float fm, fa, fb;       //Y des valeurs relatives
    int i = 0;              //Compteur de solutions

    //On change l'intervalle pour trouver toutes les solutions
    tempa = a;

    while(tempa<b)
    {
        //On part à du coté de l'intervalle a jusqu'à ce qu'on arrive a l'intervalle b
        //le +10*eps certifie qu'il n'y aura pas deux solutions dans l'intervalle
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

    //Pas de solutions
    if(fm > eps) cout << "Pas de solution pour cette intervale" << endl;

    return 0;
}

//*--------------------*//
//      Fonctions       //
//*--------------------*//
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
     default:
        {
        cout << "Val must be 1 or 2" << endl;
        }
     }
}
