/*
    Codeur de float sur n bits par:
    Bastien Burri
    Raphael Schaffo
    Joel Rittiner
*/
#include "FloatX.h"
#include "windows.h"

FloatX::FloatX(int nbBits)
{
    //ctor
    nbBitTot = nbBits;
    setNbBitsE();
    setNbBitsM();
    setDecal();
    setLimits();

    sign = "";
    mantisse = "";
    exponant = "";

}

FloatX::FloatX(string sig, string expo, string mant)
{
    int iExpo = expo.length();
    int iMant = mant.length();
    nbBitTot = iExpo + iMant + 1;
    setNbBitsE();
    setNbBitsM();
    setDecal();
    setLimits();

    if((nbBitE!=iExpo) || (nbBitM!=iMant))
    {
        cout << "Wrong input in constructor";
    }

    sign = sig;
    exponant = expo;
    mantisse = mant;

    number = binaryToNumber();
}

FloatX::~FloatX()
{
    //dtor
}

//Retourne le nombre de bit optimal de l'exposant. Attention, la formule utilisée est une approximation logaritmique, et ne fonctione pas dans les extrêmes
//(exemple: sur 8 bits, 3 bits d'exposant sont conseillés, cette formule n'en donne que 2, sur 128 bits, 15 bits d'exposant sont conseillé, la formule n'en donne que 14)
//La formule retourne cependant le bon nombre de bit entre 16 et 64
void FloatX::setNbBitsE()
{
    nbBitE = floor(4.3281*log(nbBitTot)-6.6);
}

void FloatX::setDecal()
{
    decal = (int)pow(2.0, nbBitE-1.0)-1.0;
}

void FloatX::setNbBitsM()
{
    nbBitM = nbBitTot - nbBitE - 1;
}

void FloatX::setLimits()
{
    long double maxi;
    long double plusPetitPos;

    int exposantMax = pow(2.0, nbBitE)-1;
    long double mantisseMax = 1;
    for(int i = 1; i<=nbBitM; i++)
    {
     mantisseMax += pow(2.0, -i);
    }

    maxi = pow(2.0, exposantMax - decal) * mantisseMax;
    plusPetitPos = pow(2.0, 1-decal)*1.0;
    limits = new long double[2];
    limits[0] = maxi;
    limits[1] = plusPetitPos;
}

void FloatX::Setnumber(long double val)
{
    if(!(((val < -1.0*limits[0]) || (val > limits[0]) || ((val<limits[1]) && (val > -1.0*limits[1]) && (val != 0.)))))
    {
        number = val;
        value = abs(val);
        setSign();
        setExponant();
        setMantisse();
    }
    else
    {
        cout << "Wrong input" <<endl;
    }

}

long double FloatX::binaryToNumber()
{
    long double resultMantisse = 1;
    for(int i = 0; i < nbBitM; i++)
    {
        if(mantisse.at(i)=='1')
        {
            resultMantisse += pow(2.0, (-1.0)*(i+1));
        }
    }
    cout << "resultat mantisse: " << resultMantisse << endl;
    e = 0;
    for(int i = 0; i<nbBitE; i++)
    {
        if(exponant.at(i) == '1')
        {
            e += pow(2.0, nbBitE-(i+1));
        }
    }
    if(e == 0)
        return 0;
    cout << "e from binary: " << e << endl;;
    cout << "e minus decal: " << (e-decal) << endl;

    long double valAbs = pow(2.0, e - decal) * resultMantisse;
    if(sign.at(0)=='1')
        return (-1.0)*valAbs;
    return valAbs;
}

void FloatX::setExponant()
{
    int expo = 0;

    if(value >= 1)
    {
        while(value >= 2)
        {
            value /= 2.0;
            expo++;
        }
        e = decal + expo;
    }
    else if(value != 0.)
    {
        while(value < 1.0)
        {
            value *= 2.0;
            expo--;
        }
        e = decal+expo;
    }
    else
    {
        e = 0;
    }
    int eTemp = e;
    for(int i = nbBitE-1; i >= 0; i--)
    {
        if((eTemp - pow(2,i)) >= 0)
        {
            exponant += "1";
            eTemp -= pow(2,i);
        }
        else
        {
            exponant += "0";
        }
    }
}
void FloatX::setMantisse()
{
    value -= 1;
    for(int i = 0; i < nbBitM; i++)
    {
        value *= 2.0;
        if(value >= 1)
        {
            mantisse += "1";
            value -= 1;
        }
        else
        {
            mantisse += "0";
        }
    }
}
void FloatX::setSign()
{
    if(number>0)
        sign='0';
    else
        sign='1';
}

FloatX* FloatX::add(FloatX* toAdd)
{
    if(toAdd->GetnbBitTot() != this->nbBitTot)
    {
        return NULL;
    }
    string expo1 = this->exponant;
    string mantisse1 = "1" + this->mantisse;
    string sign1 = this->sign;
    string expo2 = toAdd->Getexponant();
    string mantisse2 = "1" + toAdd->Getmantisse();
    string sign2 = toAdd->Getsign();
    string expo3;
    string mantisse3;
    string sign3;
    int e1 = this->Gete();
    int e2 = toAdd->Gete();

    //Adapte les mantisses pour que les exposant soient identiques
    if(e1 > e2)
    {
        int delta = e1 - e2;
        expo2 = expo1;
        mantisse2 = adapteMantisse(mantisse2, delta);
    }
    else if(e1 < e2)
    {
        int delta = e2 - e1;
        expo1 = expo2;
        mantisse1 = adapteMantisse(mantisse1, delta);
    }
    else
    {
        //Gestion du 0
        if((sign1 != sign2) && (mantisse1.compare(mantisse2) == 0))
        {
            sign3 = "0";
            expo3 = "";
            for(int i=0; i<nbBitE; i++)
            {
                expo3 += "0";
            }
            mantisse3 = "";
            for(int i = 0; i<nbBitM; i++)
            {
                mantisse3 += "0";
            }

            return new FloatX(sign3, expo3, mantisse3);
        }
    }
    expo3 = expo1;

    string retenue = "0";
    sign3 = "0";
    if(sign1.compare(sign2)!=0)
    {
        retenue = "1";
        if(sign1.compare("1") == 0)
        {
            mantisse1 == complementADeux(mantisse1);
            if(abs(this->number)>abs(toAdd->number))
                sign3 = "1";
        }
        else
        {
            mantisse2 == complementADeux(mantisse2);
            if(abs(this->number)<abs(toAdd->number))
                sign3 = "1";
        }

    }

    //Addition des mantisses
    mantisse3 = addMantisse(mantisse1, mantisse2, retenue);

    if(mantisse3.length() > this->nbBitM + 1)
    {
        if(sign1.compare(sign2)!=0)
        {
            mantisse3 = mantisse3.substr(1);
        }
        else
        {
            expo3 = addOneToBiteArray(expo3);
        }
    }
    if(sign1.compare(sign2)!=0)
    {
        int c = 0;
        while(mantisse3.at(0) == '0')
        {
            mantisse3 = mantisse3.substr(1) + "0";
        }

    }
    else
    {
        mantisse3 = mantisse3.substr(1, nbBitM);
    }


    return new FloatX(sign3, expo3, mantisse3);
}

FloatX* FloatX::subtract(FloatX* toSub)
{
    FloatX* float1 = new FloatX(nbBitTot);
    FloatX* float2 = new FloatX(nbBitTot);

    long double nombre1;
    long double nombre2;

    float1->Setnumber(nombre1);
    float2->Setnumber(nombre2);

    FloatX* result = new FloatX(nbBitTot);
    result = float1->add(float2);

     FloatX* sol = new FloatX(sign,exponant,mantisse);

     FloatX* addUn = new FloatX(GetnbBitTot());
     addUn->Setnumber(1.0);
     sol->add(addUn);
     return sol;
}

string FloatX::complementADeux(string str)
{
    string result = "";
    for(int i=0; i < str.length(); i++)
    {
        if(str.at(i) == '0')
            result += "1";
        else
            result += "0";
    }
    return result;
}

string FloatX::addMantisse(string mantisse1, string mantisse2, string retenue)
{
    string mantisse3 = "";
    string str1, str2;
    int leng = mantisse1.length();

    for(int i = leng-1; i >= 0; i--)
    {
        str1 = mantisse1.at(i);
        str2 = mantisse2.at(i);
        if(str1.compare("1") == 0)
        {
            if(str2.compare("1") == 0)
            {
                if(retenue.compare("1") == 0)
                {
                    mantisse3 = "1" + mantisse3;
                    retenue = "1";
                }
                else
                {
                    mantisse3 = "0" + mantisse3;
                    retenue = "1";
                }
            }
            else
            {
                if(retenue.compare("1") == 0)
                {
                    mantisse3 = "0" + mantisse3;
                    retenue = "1";
                }
                else
                {
                    mantisse3 = "1" + mantisse3;
                    retenue = "0";
                }
            }
        }
        else
        {
            if(str2.compare("1") == 0)
            {
                if(retenue.compare("1") == 0)
                {
                    mantisse3 = "0" + mantisse3;
                    retenue = "1";
                }
                else
                {
                    mantisse3 = "1" + mantisse3;
                    retenue = "0";
                }
            }
            else
            {
                if(retenue.compare("1") == 0)
                {
                    mantisse3 = "1" + mantisse3;
                    retenue = "0";
                }
                else
                {
                    mantisse3 = "0" + mantisse3;
                    retenue = "0";
                }
            }
        }
    }
    if(retenue.compare("1") == 0)
    {
        mantisse3 = "1" + mantisse3;
    }
    return mantisse3;
}

string FloatX::adapteMantisse(string mantisse, int delta)
{
    mantisse = mantisse.substr(0,mantisse.length()-delta);
    string tempo = "";
    for(int i = 0; i < delta; i++)
    {
        tempo += "0";
    }
    mantisse = tempo + mantisse;
    return mantisse;
}

string FloatX::addOneToBiteArray(string biteArray)
{
    string ba2 = "";
    for(int i=0; i<biteArray.length(); i++)
    {
        ba2 += "0";
    }
    return addMantisse(biteArray, ba2, "1");
}
