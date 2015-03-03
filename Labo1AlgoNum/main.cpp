/*
    Lesson : Algorithme numérique
    Project: Codeur de float sur n bits
    Author : Bastien Burri
             Raphael Schaffo
             Joel Rittiner
             Vulliemin Kevin
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <FloatX.h>

#define MIN 12
#define MAX 64

using namespace std;

void code();
void decode();
void addOrSub(int sens);

int main()
{
    int choice;
    bool stop;

    do
    {
        do
        {
            cout << "Menu (faites votre choix):" << endl;
            cout << "1: Coder un nombre;" << endl;
            cout << "2: Decoder un nombre;" << endl;
            cout << "3: Additionner 2 nombres;" << endl;
            cout << "4: Soustraire 2 nombres;" << endl;
            cout << "5: Recherche de PI (non implementées)." << endl;
            cin >> choice;
            cout << endl << endl;
        }while((choice < 1)&&(choice>5));

        switch(choice)
        {
        case 1:
            code();
            break;
        case 2:
            decode();
            break;
        case 3:
            addOrSub(0);
            break;
        case 4:
            addOrSub(1);
            break;
        case 5:
            break;
        default:
            break;
        }

        cout << endl << "Voulez-vous continuer (1 pour continuer, 0 pour arreter): ";
        cin >> stop;
        system("cls");
    }while(stop);

    //system("pause");
    //system("cls");
}

//Coder un nombre
void code()
{
    FloatX* float1;
    int nbBitTot;
    long double* limites;
    long double nombre;

    //Récupération du nombre de bit du float saisi par l'utilisateur
    do
    {
        cout << "Entrez le nombre de bits pour l'encodage souhaite (entre " << MIN <<" et " << MAX << ") : ";
        cin >> nbBitTot;
    }while(nbBitTot < MIN || nbBitTot > MAX);

    //Création de l'objet float en spécifiant la taille du float
    float1 = new FloatX(nbBitTot);
    limites = float1->Getlimits();

    cout << endl << "Pour un encodage sur " << float1->GetnbBitTot() << " bits:" << endl;
    cout << "Il y a 1 bit de signe, " << float1->GetnbBitE() << " bits d'exposant et " << float1->GetnbBitM() <<" bits de mantisse." << endl;
    cout << "Le decalage vaut " << float1->Getdecal() << "." << endl << endl;
    cout << "Valeures les plus eloignees de 0: +/- " << limites[0] << endl;
    cout << "Valeures non-nulles les plus proches de 0: +/- " << limites[1] << endl << endl;

    //Récupération du nombre à coder dans le float
    nombre = NULL;

    do
    {
        cout << "Entrez un float a convertir : ";
        cin >> nombre;
    }while((nombre < -1.0*limites[0]) || (nombre > limites[0]) || ((nombre<limites[1]) && (nombre > -1.0*limites[1]) && (nombre != 0.)));

    //Assignation au float
    float1->Setnumber(nombre);

    cout << "s: " << float1->Getsign() << endl;
    cout << "e: " << float1->Getexponant() << endl;
    cout << "m: " << float1->Getmantisse() << endl;
}

//Décoder un nombre
void decode()
{
    string s, e, m;

    //Récupération des nombre binaires qui forment un float
    do
    {
        cout << "Entrez la valeur pour s (1 caractere binaire) : ";
        cin >> s;
    }while(s.length() != 1);

    cout << "Entrez la valeur pour e (suite de caracteres binaires) : ";
    cin >> e;

    cout << "Entrez la valeur pour m (suite de caracteres binaires) : ";
    cin >> m;

    //Création d'un nombre Float à partir de la forme float binaire
    FloatX* float1 = new FloatX(s, e, m);
    cout << endl << "Nombre entré: " << float1->Getnumber();
}

//Addition / soustration
void addOrSub(int sens)
{
    FloatX* float1;
    FloatX* float2;
    FloatX* result;

    int nbBitTot;
    long double nombre1 = NULL;
    long double nombre2 = NULL;
    long double* limites;
    long double verification;

    do
    {
        cout << "Entrez le nombre de bits pour l'encodage souhaite (entre " << MIN <<" et " << MAX << ") : ";
        cin >> nbBitTot;
    }while(nbBitTot < MIN || nbBitTot > MAX);

    float1 = new FloatX(nbBitTot);
    float2 = new FloatX(nbBitTot);
    limites = float1->Getlimits();

    cout << endl << "Pour un encodage sur " << float1->GetnbBitTot() << " bits:" << endl;
    cout << "Il y a 1 bit de signe, " << float1->GetnbBitE() << " bits d'exposant et " << float1->GetnbBitM() <<" bits de mantisse." << endl;
    cout << "Le decalage vaut " << float1->Getdecal() << "." << endl << endl;
    cout << "Valeures les plus eloignees de 0: +/- " << limites[0] << endl;
    cout << "Valeures non-nulles les plus proches de 0: +/- " << limites[1] << endl << endl;

    do
    {
        cout << "Entrez le premier float : ";
        cin >> nombre1;
    }while((nombre1 < -1.0*limites[0]) || (nombre1 > limites[0]) || ((nombre1<limites[1]) && (nombre1 > -1.0*limites[1]) && (nombre1 != 0.)));
    do
    {
        cout << "Entrez le deuxieme float : ";
        cin >> nombre2;
    }while((nombre2 < -1.0*limites[0]) || (nombre2 > limites[0]) || ((nombre2<limites[1]) && (nombre2 > -1.0*limites[1]) && (nombre2 != 0.)));

    float1->Setnumber(nombre1);
    float2->Setnumber(nombre2);

    if(sens == 0)
    {
        cout << endl <<"Resultat de l'addition:" << endl;
        result = float1->add(float2);
        verification = nombre1 + nombre2;
    }
    else
    {
        cout << endl <<"Resultat de la soustraction:" << endl;
        result = float1->subtract(float2);
        verification = nombre1 - nombre2;
    }

    cout << "s: " << result->Getsign() << endl;
    cout << "e: " << result->Getexponant() << endl;
    cout << "m: " << result->Getmantisse() << endl;
    cout << "resultat:  " << result->Getnumber() <<endl;
    cout << "Verification: " << verification << endl << "(Des differences peuvent survenir suivant le nombre de bits choisis pour encoder)." << endl;
}
