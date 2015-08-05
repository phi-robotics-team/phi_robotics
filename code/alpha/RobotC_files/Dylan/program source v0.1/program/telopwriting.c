#include <stdio.h>
#include <stdlib.h>
#include "myflush.c"
#include "mypause.c"
#include "write.c"
#include "pragamwrite.c"
#include "pramaset.c"
#include "int.h"
/*char m1[10],m2[10],m3[10],m4[10],m5[10],m6[10],m7[10],m8[10];
char rightmotor[10], leftmotor[10], backright[10], backleft[10];
int motorcount, pramavalue, controler1, port1, controler2, port2, controler3, port3, controler4, port4, pramavalue1, pramavalue2, pramavalue3, pramavalue4;;
*/
int main()
{
   /*char m1[10],m2[10],m3[10],m4[10],m5[10],m6[10],m7[10],m8[10]
char rightmotor[10], leftmotor[10], backright[10], backleft[10];
int motorcount;*/

    printf("what do you want to name your telop:");
    scanf("%s", &name);
    strcat(name,".c");
    printf("\nhow many motors are used in your drive (2 or 4): ");
    scanf("%d", &motorcount);
    if(motorcount == 2)
    {

        pragamwrite(1);
        pramaset(pramavalue1, rightmotor);

        pragamwrite(2);
        pramaset(pramavalue2, leftmotor);
        write();

    }
    else if(motorcount == 4)
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
    else
    {
        write();
    }






    myflush ( stdin );
    mypause();
    return 0;
}
