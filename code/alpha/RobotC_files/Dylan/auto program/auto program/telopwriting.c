#include <stdio.h>
#include <stdlib.h>
#include "myflush.c"
#include "mypause.c"
#include "write.c"
#include "pragamwrite.c"
#include "pragamwriteE.c"
#include "pramaset.c"
#include "int.h"
//char m1[20],m2[20],m3[20],m4[20],m5[20],m6[20],m7[20],m8[20],E1[20],E2[20],E3[20],E4[20],E5[20],E6[20],E7[20],E8[20];
//char rightmotor[20], leftmotor[20], backright[20], backleft[20];
//int motorcount, encodertest, encoderN, pramavalue, controler1, port1, controler2, port2, controler3, port3, controler4, port4, pramavalue1, pramavalue2, pramavalue3, pramavalue4, pramavalue9;
//char name[20], stop;
int main()
{
    printf("what do you want to name your auto:");
    scanf("%s", &name);
    strcat(name,".c");
    printf("\nhow many motors are used in your drive (2 or 4): ");
    scanf("%d", &motorcount);
    printf("\ndo you have encoders install on your bot (1=yes 0=no): ");
    scanf("%d", &encodertest);
    if(motorcount == 2 && encodertest == 0)
    {

        pragamwrite(1);
        pramaset(pramavalue1, rightmotor);

        pragamwrite(2);
        pramaset(pramavalue2, leftmotor);
        write();

    }
    else if(motorcount == 4 && encodertest==0)
    {
        pragamwrite(3);
        pramaset(pramavalue1, rightmotor);

        pragamwrite(4);
        pramaset(pramavalue2, leftmotor);

        pragamwrite(5);
        pramaset(pramavalue3, backright);

        pragamwrite(6);
        pramaset(pramavalue4, backleft);
        write();


    }
    else if(motorcount == 2 && encodertest==1)
    {
        pragamwrite(1);
        pramaset(pramavalue1, rightmotor);

        pragamwrite(2);
        pramaset(pramavalue2, leftmotor);
        write();
    }
    else if(motorcount == 4 && encodertest==1)
    {
        pragamwrite(3);
        pramaset(pramavalue1, rightmotor);
        if (encoderN=1)
        {

        }
        pragamwrite(4);
        pramaset(pramavalue2, leftmotor);
        if (encoderN=1)
        {

        }
        pragamwrite(5);
        pramaset(pramavalue3, backright);
        if (encoderN=1)
        {

        }
        pragamwrite(6);
        pramaset(pramavalue4, backleft);
        if (encoderN=1)
        {

        }

    }





    myflush ( stdin );
    mypause();
    return 0;
}
