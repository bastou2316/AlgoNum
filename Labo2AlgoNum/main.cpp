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
#include <sstream>
#include <math.h>

using namespace std;

//*--------------------*//
//      D�finition      //
//*--------------------*//
int askInput(std::string message, int value);
float fun(float x);
void bissection(float a, float b, float eps);

//val 1 pour la premi�re fonction et val 2 pour la 2�me
#define val 1

//*--------------------*//
//   Prog. Principale   //
//*--------------------*//
int main()
{
    //Valeurs par d�faut
    float a = -100;         //Valeurs d'intervalles
    float b = 100;
    float eps = 0.0001;     //Pr�cision

    //Accueil et demandes utilisateurs
    cout << "Bonjour, ce programme propose a l'utilisateur de trouver" << endl <<
            "les points d'intersections d'une fonction avec l'axe des x.\n" << endl;
    do
    {
        a = askInput("Veuillez entrer le debut de l'intervalle", -100);
        b = askInput("Veuiller entrer la fin de l'intervalle", 100);

        //R�solution
        bissection(a, b, eps);
    }while(false);

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

void bissection(float a, float b, float eps)
{
    float tempa, tempb;     //Valeurs d'intervalles
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
}
