/*
    Codeur de float sur n bits par:
    Bastien Burri
    Raphael Schaffo
    Joel Rittiner
*/
#ifndef FLOATX_H
#define FLOATX_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

class FloatX
{
    public:
        /** Construct from number */
        FloatX(int nbBits);
        /** Construct from bits array */
        FloatX(string sig, string expo, string mant);
        /** Default destructor */
        virtual ~FloatX();

        int GetnbBitTot() { return this->nbBitTot; }

        int GetnbBitE() { return this->nbBitE; }

        int GetnbBitM() { return this->nbBitM; }

        int Gete() { return this->e; }

        long double Getnumber() { return this->number; }

        string Getsign() { return this->sign; }
        string Getmantisse() { return this->mantisse; }
        string Getexponant() { return this->exponant; }


        void Setnumber(long double val);

        void changeSign() { this->sign = (this->sign.at(0)=='0'?"1":"0"); }

        long double* Getlimits() { return this->limits; }

        int Getdecal() { return this->decal; }

        //Methodes
        void getDonneeEncodage();
        FloatX* add(FloatX* toAdd);
        FloatX* subtract(FloatX* toSub);
        string complementADeux(string str);

        long double binaryToNumber();


        long double* limits; //!< Member variable "limits"

    protected:
    private:
        //Methods
        void setNbBitsE();
        void setDecal();
        void setNbBitsM();
        void setLimits();

        void setExponant();
        void setMantisse();
        void setSign();

        string addMantisse(string mantisse1, string mantisse2, string retenue);
        string adapteMantisse(string mantisse, int delta);
        // Add 1 to a fixed length bite array
        string addOneToBiteArray(string biteArray);

        //Attributes
        int nbBitTot; //!< Member variable "nbBitTot"
        int nbBitE; //!< Member variable "nbBitE"
        int nbBitM; //!< Member variable "nbBitM"
        long double number; //!< Member variable "number"
        long double value; //!< Member variable "value"

        int decal; //!< Member variable "decal"

        string sign;
        string mantisse;
        string exponant;
        int e;
};

#endif // FLOATX_H
