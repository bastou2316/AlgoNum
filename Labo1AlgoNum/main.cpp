/*
    Codeur de float sur n bits par:
    Bastien Burri
    Raphael Schaffo
    Joel Rittiner
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <FloatX.h>

using namespace std;

//Coder un nombre
void coder(int mini, int maxi)
{

    int nbBitTot;
    do
    {
        cout << "Entrez le nombre de bits pour l'encodage souhaite (entre " << mini <<" et " << maxi << ") : ";
        cin >> nbBitTot;
    }while(nbBitTot < mini || nbBitTot > maxi);

    FloatX* float1 = new FloatX(nbBitTot);

    cout << endl << "Pour un encodage sur " << float1->GetnbBitTot() << " bits:" << endl;
    cout << "Il y a 1 bit de signe, " << float1->GetnbBitE() << " bits d'exposant et " << float1->GetnbBitM() <<" bits de mantisse." << endl;
    cout << "Le decalage vaut " << float1->Getdecal() << "." << endl << endl;

    long double* limites = float1->Getlimits();
    long double nombre;

    cout << "Valeures les plus eloignees de 0: +/- " << limites[0] << endl;
    cout << "Valeures non-nulles les plus proches de 0: +/- " << limites[1] << endl << endl;
    nombre = NULL;
    do
    {
        cout << "Entrez un float a convertir : ";
        cin >> nombre;
    }while((nombre < -1.0*limites[0]) || (nombre > limites[0]) || ((nombre<limites[1]) && (nombre > -1.0*limites[1]) && (nombre != 0.)));

    float1->Setnumber(nombre);

    cout << "s: " << float1->Getsign() << endl;
    cout << "e: " << float1->Getexponant() << endl;
    cout << "m: " << float1->Getmantisse() << endl;
}

//Décoder un nombre
void decoder()
{
    string s, e, m;
    do
    {
        cout << "Entrez la valeur pour s (1 caractere binaire) : ";
        cin >> s;
    }while(s.length() != 1);
    cout << "Entrez la valeur pour e (suite de caracteres binaires) : ";
    cin >> e;
    cout << "Entrez la valeur pour m (suite de caracteres binaires) : ";
    cin >> m;
//    try
//    {
        FloatX* float1 = new FloatX(s, e, m);
        cout << endl << "Nombre entré: " << float1->Getnumber();
//    }
//    catch (int e)
//    {
//        cout << "Wrong input" << e;
//    }
}

//Addition / soustration
void additionSoustraction(int mini, int maxi, int sens)
{

    int nbBitTot;
    do
    {
        cout << "Entrez le nombre de bits pour l'encodage souhaite (entre " << mini <<" et " << maxi << ") : ";
        cin >> nbBitTot;
    }while(nbBitTot < mini || nbBitTot > maxi);

    FloatX* float1 = new FloatX(nbBitTot);
    FloatX* float2 = new FloatX(nbBitTot);

    cout << endl << "Pour un encodage sur " << float1->GetnbBitTot() << " bits:" << endl;
    cout << "Il y a 1 bit de signe, " << float1->GetnbBitE() << " bits d'exposant et " << float1->GetnbBitM() <<" bits de mantisse." << endl;
    cout << "Le decalage vaut " << float1->Getdecal() << "." << endl << endl;

    long double* limites = float1->Getlimits();
    long double nombre1;
    long double nombre2;

    cout << "Valeures les plus eloignees de 0: +/- " << limites[0] << endl;
    cout << "Valeures non-nulles les plus proches de 0: +/- " << limites[1] << endl << endl;
    nombre1 = NULL;
    nombre2 = NULL;
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
    FloatX* result;
    long double verification;
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

int main()
{

    int mini = 12;
    int maxi = 64;

    int choice;
    int continuer;

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
            coder(mini, maxi);
            break;
        case 2:
            decoder();
            break;
        case 3:
            additionSoustraction(mini, maxi, 0);
            break;
        case 4:
            additionSoustraction(mini, maxi, 1);
            break;
        case 5:
            break;
        default:
            break;
        }

        cout << endl << "Voulez-vous continuer (1 pour continuer, 0 pour arreter): ";
        cin >> continuer;
        cout << endl << endl << endl << endl;
    }while(continuer == 1);

//    while(true)
//    {
//        string s2;
//        string e2;
//        string m2;
//
//        cout << endl;
//        do
//        {
//            cout << "Entrer la valeur pour s (1 caractère binaire) : ";
//            cin >> s2;
//        }while(s2.length() != 1);
//
//        do
//        {
//            cout << "Entrer la valeur pour e (5 caractère binaire) : ";
//            cin >> e2;
//        }while(e2.length() != 5);
//
//        do
//        {
//            cout << "Entrer la valeur pour m (11 caractère binaire) : ";
//            cin >> m2;
//        }while(m2.length() != 11);
//
//        int signe = (-2*(s2.at(0)-48)) + 1;
//        int exposant = eToDec(e2);
//        double mantice = mToDec(m2);
//        double grandM = mantice/pow(2,12);
//
//        double res = signe*grandM*pow(2,exposant-15);
//        cout << endl;
//        cout << "La valeur numérique est " << res << endl;
//        cout << endl;
//
//        system("pause");
//        system("cls");
//    }
    system("pause");
    system("cls");
}
