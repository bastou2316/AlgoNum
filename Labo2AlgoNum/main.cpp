//*
//  Summary :   Ce programme d�finit les points d'intersections
//              d'une fonction avec l'axe des "X"
//              (appell�s "Zeros" de la fonctions).
//  Author :    Burri Bastien
//              Schaffo Rapha�l
//              Jo�l Rittiner
//              Vulliemin Kevin
//  Receiver :  Gobron St�phane
//  Date :      17.03.15
//*

//*--------------------*//
//      Librairies      //
//*--------------------*//
#include <iostream>
#include <math.h>

using namespace std;

//*--------------------*//
//      D�finition      //
//*--------------------*//
float fun(float x);
void bisection(float a, float b, float eps);

//val 1 pour la premi�re fonction et val 2 pour la 2�me
#define val 1

//*--------------------*//
//   Prog. Principale   //
//*--------------------*//
int main()
{
    float tempa, a = -100;  //Valeurs d'intervalles
    float tempb, b = 100;
    float eps = 0.0001;     //Pr�cision
    float m;                //Moyenne
    float fm, fa, fb;       //Y des valeurs relatives
    int i = 0;              //Compteur de solutions

    //On change l'intervalle pour trouver toutes les solutions
    tempa = a;

    while(tempa<b)
    {
        //On part � du cot� de l'intervalle a jusqu'� ce qu'on arrive a l'intervalle b
        //le +10*eps certifie qu'il n'y aura pas deux solutions dans l'intervalle
        tempb = tempa+10*eps;

        //Fonction de bissection
        fa = fun(tempa);
        fb = fun(tempb);

        while(fabs(tempb-tempa) > eps)  //Tant que la valeur absolu de la diff�rence
        {
            m = (tempa+tempb) / 2;      //moyenne = a + b / 2
            fm = fun(m);                //my = f(mx)

            if(fm*fa<=0)                //Si on est en DESSOUS de l'axe, on red�finit l'intervalle sur B
            {                           //!! Commentaire � v�rifier !!
                tempb=m;
                fb=fm;
            }
            else                        //Si on est en DESSUS de l'axe, on red�finit l'intervalle sur A
            {
                tempa=m;
                fa=fm;
            }

            //cout m << endl;        //Si on d�sire afficher les �tapes de r�solutions
        }

        tempa=tempb;

        //Solutions trouv�s
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
