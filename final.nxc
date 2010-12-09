#define MOTORS OUT_AC
#define LMOTOR OUT_C
#define RMOTOR OUT_A
#define LIGHTS S1
#define TOUCHS S2
#define SOUNDS S3
#define USS    S4
#define ARM OUT_B
#define R180 1000
#define LROT -100
#define RROT 100
#define NATACENI 500
#define VZDALENOST 100

bool acquired = false;
int smer = 1;
bool kraj = false;
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
    until(SensorUS(USS)<11);
    nalozeno=false;
    int zvedni=300;
    ResetTachoCount(ARM);
    if(Sensor(TOUCHS)==1)
    {
         PlayTone(500,100);
         OnFwd(ARM,100);
         Wait(zvedni);
         Off(ARM);
         nalozeno=true;

    }
    else
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
         else
         {
             OnRev(ARM,50);
             Wait(100);
             Off(ARM);
             Float(ARM);
         }
    }
    }
}



task search()
{
  Wait(100);


      for(int i;i<2&&probehlo==false;i++)
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
      }
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
{
     SetSensorType(LIGHTS, SENSOR_TYPE_LIGHT_ACTIVE);
     SetSensorMode(LIGHTS, SENSOR_MODE_PERCENT);
     SetSensorType(TOUCHS, SENSOR_TYPE_TOUCH);
     SetSensorMode(TOUCHS, SENSOR_MODE_BOOL);
     SetSensorType(USS, SENSOR_TYPE_LOWSPEED);
     for(int i=0;i<4;i++)
     {
          PlayTone(10000,100);
          Wait(990);
     }
     PlayTone(2000,100);
     Wait(100);
}

sub  _start()
{
     OnFwd(MOTORS,100);
     Wait(250);
     OnRev(MOTORS,100);
     Wait(250);
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
    TextOut(10,LCD_LINE5,"Press CENTER");
    TextOut(20,LCD_LINE6,"To ABORT!!");
    Wait(100);
    }
    StopAllTasks();
}

task main()
{
     _init();
     StartTask(disp);
     _start();
     StartTask(search);
     StartTask(hever);
     StartTask(cara);
      while(true)
      {
      Wait(100);
      until(SensorUS(USS)<VZDALENOST)
      {
       if(probehlo==true&&probehlo2==false&&smer!=88)
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
     //PlayTone(1000,100);
     //Wait(100);

}
