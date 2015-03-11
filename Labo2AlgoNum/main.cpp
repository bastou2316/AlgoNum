#include <iostream>
#include <math.h>

using namespace std;
float fun(float x);
void bisection(float a, float b, float eps);

//val 1 pour la première fonction et val 2 pour la 2ème
#define val 1

int main()
{

    float a,b,eps,tempb,tempa,fm,fa,m,fb;
    eps = 0.0001;
    //cin>>a>>b;
    a=-100;
    b=100;
    int i = 0;
    //On change l'intervale pour trouver toutes les sols
    tempa = a;
    while(tempa<b)
    {
    //On part à du coté de l'intervalle a jusqu'à ce qu'on arrive a l'intervalle b
    //le +10*eps certifie qu'il n'y aura pas deux solutions dans l'intervalle
      tempb = tempa+10*eps;
      //Fonction de bissection
    fa=fun(tempa);
    fb=fun(tempb);
    while(fabs(tempb-tempa)>eps)
    {
       m=(tempa+tempb)/2;
       fm = fun(m);
       if(fm*fa<=0)
       {
           tempb=m;
           fb=fm;
       }
       else
       {
           tempa=m;
           fa=fm;
       }

     //   cout m << endl; //Si on désire afficher les étapes de résolutions
    }
      //ENDFUNCTION
      tempa=tempb;
      if(fabs(fm)<eps) //Solution trouvé
      {
        i++;
        cout << "Recherche de la "<< i <<" solution(s) :" << endl;
        cout<< m << endl;
      }

    }


    if(fm>eps) cout << "Pas de solution pour cette intervale" << endl;


return 0;
}

void bisection(float a, float b, float eps)
{

}

float fun(float x)
    {
     switch(val)
     {
     case 1:
        {
            float y;
            y=sin(x)-x/13;
            return y;
        }
     case 2:
        {
            float y;
            y=x/(1-pow(x,2.0));
            return y;
        }
     default:
        {
            cout << "Val must be 1 or 2" << endl;
        }
     }

    }



