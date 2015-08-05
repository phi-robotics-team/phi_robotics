//char rightmotor[10], leftmotor[10], backright[10], backleft[10];
#include "int.h"
void pragamwrite ( pramavalue9)
{
   // int  controller1, port1, controller2, port2, controller3, port3, controller4, port4, pramavalue1, pramavalue2, pramavalue3, pramavalue4;

 if(pramavalue9 == 1)
    {

     printf("\nwhat motor controller is the right motor in:");
     scanf("%d", &controller1);
     //printf("the controller is %d\n", controller1);
     printf("\nwhat port is the right motor in(1 or 2):");
     scanf("%d", &port1);
    // printf("the port is %d\n", port1);

     pramavalue1 = (controller1*controller1) + port1;

     //printf("pramavalue %d\n", pramavalue1);



     printf("\nwhat is the name of the right motor: ");
     scanf("%s", &rightmotor);





    }
    else if(pramavalue9 == 2)
    {


     printf("\nwhat motor controller is the left motor in: ");
     scanf("%d", &controller2);
     printf("\nwhat port is the left motor in(1 or 2): ");
     scanf("%d", &port2);

     pramavalue2 = (controller2*controller2) + port2;

     //printf("pramavalue %d", pramavalue2);
    printf("\nwhat is the name of the left motor: ");
    scanf("%s", &leftmotor);




    }
    else if(pramavalue9 == 3)
    {
     printf("\nwhat motor controller is the front right motor in:");
     scanf("%d", &controller1);
     printf("\nwhat port is the front right motor in(1 or 2):");
     scanf("%d", &port1);

     pramavalue1 = (controller1*controller1) + port1;

     printf("\nwhat is the name of the front right motor: ");
     scanf("%s", &rightmotor);

    }
    else if(pramavalue9 == 4)
    {
     printf("\nwhat motor controller is the front left motor in:");
     scanf("%d", &controller2);
     printf("\nwhat port is the front left motor in(1 or 2):");
     scanf("%d", &port2);

     pramavalue2 = (controller2*controller2) + port2;

     printf("\nwhat is the name of front left motor: ");
     scanf("%s", &rightmotor);

    }
    else if(pramavalue9 == 5)
    {
     printf("\nwhat motor controller is the back right motor in:");
     scanf("%d", &controller3);
     printf("\nwhat port is the back right motor in(1 or 2):");
     scanf("%d", &port3);

     pramavalue3 = (controller3*controller3) + port3;

     printf("\nwhat is the name of the back right motor: ");
     scanf("%s", &backright);

    }
    else if(pramavalue9 == 6)
    {
     printf("\nwhat motor controller is the back left motor in:");
     scanf("%d", &controller4);
     printf("\nwhat port is the back left motor in(1 or 2):");
     scanf("%d", &port4);

     pramavalue4 = (controller4*controller4) + port4;

     printf("\nwhat is the name of the back left motor: ");
     scanf("%s", &backleft);

    }

}
