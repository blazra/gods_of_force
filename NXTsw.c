#define MOTORS OUT_AC
#define LMOTOR OUT_C
#define RMOTOR OUT_A
#define LIGHTS S1
#define TOUCHS S2
#define SOUNDS S3
#define USS    S4
#define ARM OUT_B
#define R180 1000
#define NATACENI 500
#define VZDALENOST 100

int smer = 1;
bool nalozeno=false;
bool probehlo=false;
bool probehlo2=false;
int slum = 0;


sub RotateMotorMy(int pwr,int degrees,bool brk=true)
{

    OnFwd(LMOTOR,pwr);
    OnFwd(RMOTOR,0-pwr);
    until(abs(MotorTachoCount(OUT_A))>=abs(degrees));
    if(brk)
    Off(MOTORS);
    else
    Float(MOTORS);
    Wait(1);
}

task hever() //nadzvednuti soupere
{

    OnRev(ARM,70);
    Wait(800);
    Float(ARM);
    Wait(100);
    Off(ARM);
    while(true)
    {
       until(SensorUS(USS)<11);  //cekani nez se protivni priblizi na mene nez 11cm
       int zvedni=300;
       ResetTachoCount(ARM);
       if(Sensor(TOUCHS)==1)     //pokud je narazni stlacen hned zvedame
       {
         PlayTone(500,100);
         OnFwd(ARM,100);
         Wait(zvedni);
         Off(ARM);
         nalozeno=true;

       }
       else                     //jinak...
       {
         OnFwd(ARM,30);
         Wait(500);
         Off(ARM);
         if(MotorTachoCount(ARM)<100)//pokud naraznik stlacen, nabere silou,  jinak testuje o kolik se zmeni uhel za nejakou dobu a malou silu motoru, pokud malo, radlice je zatizena a zabere na plno, jinak ji vraci dolu
         {
             nalozeno=true;
             OnFwd(ARM,100);
             Wait(zvedni);
             Off(ARM);
         }
         else                       //navraceni zvedaku dolu
         {
             OnRev(ARM,50);
             Wait(100);
             Off(ARM);
             Float(ARM);
         }//konec podminky mereni sily
       }//konec podminky narazniku
    } //konec cyklu
}



task search()
{
  Wait(100);


      for(int i;i<3&&probehlo==false;i++)
      {

      while(smer==1)
      {
          OnFwd(LMOTOR,100);
          OnRev(RMOTOR,100);
          Wait(5);
          if(slum==NATACENI)
             smer=0;
          slum++;
      }
       while(smer==0)
       {
           OnFwd(RMOTOR,100);
           OnRev(LMOTOR,100);
           Wait(5);
           if(slum==2*NATACENI)
           {
              smer=1;
              slum=0;
           }
           slum++;
       }
       slum=0;
      } //konec foru
}


task cara()
{
  Wait(100);
  while(true)
  {
  //OnFwd(MOTORS,100);
     until(Sensor(LIGHTS)<40);
     smer=88;
     probehlo=true;
     RotateMotorEx(MOTORS,-100,500,0,false,true);
     if(nalozeno!=true)
        RotateMotorMy(100,R180-500,true);
     Wait(1);
     smer=1;

   if(nalozeno)
   {
     PlayTone(3000,900);
     OnRev(ARM,70);
     Wait(800);
     Float(ARM);
     Wait(100);
     Off(ARM);
     nalozeno=false;
   }
   probehlo2=false;
                        //StartTask(search);
  }

}

sub _init()
{                     //vypis textu v teto fci je jen informativni
     //ClearScreen();
     //TextOut(10,LCD_LINE2,"INIT started!!");
     SetSensorType(LIGHTS, SENSOR_TYPE_LIGHT_ACTIVE);
     SetSensorMode(LIGHTS, SENSOR_MODE_PERCENT);
     //TextOut(10,LCD_LINE3,"LIGHT S. OK");
     SetSensorType(TOUCHS, SENSOR_TYPE_TOUCH);
     SetSensorMode(TOUCHS, SENSOR_MODE_BOOL);
     //TextOut(10,LCD_LINE4,"TOUCH S. OK");
     SetSensorType(USS,    SENSOR_TYPE_LOWSPEED);
     //TextOut(10,LCD_LINE5,"US S. OK");

     for(int i=0;i<4;i++)
     {
          //TextOut(30+10*i,LCD_LINE6,"X");    //ukazuje prubeh cekani
          PlayTone(10000,100);
          Wait(990);
     }
     //ClearScreen();
     PlayTone(2000,100);
     Wait(100);
}

sub  _start()
{
     OnFwd(MOTORS,100);
     Wait(200);
     OnRev(MOTORS,100);
     Wait(300);
     OnFwd(LMOTOR,100);
     OnRev(RMOTOR,100);
     Wait(R180);
     Off(MOTORS);
}

task disp()         /*vypis na display + pri stisku oranzoveho tl. preruseni smycky*/
{
    while (!ButtonPressed(BTNCENTER,false))
    {
       ClearScreen();
       NumOut(50,LCD_LINE1,BatteryLevel());
       NumOut(50,LCD_LINE2,Sensor(LIGHTS));
       NumOut(50,LCD_LINE3,Sensor(TOUCHS));
       NumOut(50,LCD_LINE4,SensorUS(USS));
       NumOut(10,LCD_LINE5,smer);
       NumOut(50,LCD_LINE5,probehlo);
       NumOut(90,LCD_LINE5,probehlo2);
       TextOut(0,LCD_LINE6,"Orange to ABORT!!");
       Wait(100);
    }
    StopAllTasks();
}

task main()
{
     _init();                   //init senzoru a 5s cekani
     //StartTask(disp);           //debug vlakno
     _start();                  //nahozeni na kola
     StartTask(cara);           //ochane vlakno branici vyjeti z kruhu
     StartTask(search);
     StartTask(hever);
      while(true)
      {
         Wait(100);
         until(SensorUS(USS)<VZDALENOST)
         {
            if(probehlo&&!probehlo2&&smer!=88)
            {
                OnFwd(RMOTOR,100);
                OnRev(LMOTOR,100);
                probehlo2=true;
            }
         }
         StopTask(search);
         if(smer!=88)
            OnFwd(MOTORS,100);

      }

}
