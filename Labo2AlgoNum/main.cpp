#include <iostream>
#include <math.h>

using namespace std;
float fun(float x);

//val 1 pour la première fonction et fun 2 pour la 2ème
#define val 2

int main()
{

    float a,fa,eps,m,fm,b,fb;
    eps = 0.0001;
   // cin>>a>>b;
    a = -100;
    b = 100;
    fa=fun(a);
    fb=fun(b);
    while(fabs(b-a)>eps)
    {
       m=(a+b)/2;
       fm = fun(m);
       if(fm*fa<=0)
       {
           b=m;
           fb=fm;
       }
       else
       {
           a=m;
           fa=fm;
       }

       cout << m << endl;
    }


return 0;
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



