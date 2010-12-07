#define MOTORS OUT_AC
#define LMOTOR OUT_C
#define RMOTOR OUT_A
#define LIGHTS S1
#define TOUCHS S2
#define SOUNDS S3
#define USS    S4
#define ARM OUT_B
#define R180 570
#define LROT -100
#define RROT 100
#define NATACENI 360
#define VZDALENOST 40

bool hajzljetu = false;

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

task destroy()
{
  while(true)
  {
    if(hajzljetu==true)
    {
      //Stop(search);

OnFwd(MOTORS,100);
      
    }
  }
}

task search()
{
  int smer = 1;
   while(hajzljetu==false)
   {
      
      
      if(smer==1)
      {
	RotateMotorMy(100,NATACENI,true);
	smer=0;
	Wait(1);

      }
       if(smer==0)
       {
 	RotateMotorMy(-100,NATACENI,true);
 	smer=1;
	Wait(1);

       }
      
    }
  }


task cmuchac()
{
  while(true)
  {
    if(SensorUS(USS)<VZDALENOST)
      hajzljetu=true;
    else
      hajzljetu=false;
  }
}

task cara()
{
  while(true)
  {
  //OnFwd(MOTORS,100);
  
  until(Sensor(LIGHTS)<40);
  OnRev(MOTORS,100);
  Wait(1000);
  Off(MOTORS);
  RotateMotorMy(100,R180,true);
  Wait(1);
  }
  
}

sub _init()
{     /*
     for(int i=0;i<4;i++)
     {
          PlayTone(10000,100);
          Wait(990);
     } */
     PlayTone(2000,100);
     Wait(100);
     SetSensorType(LIGHTS, SENSOR_TYPE_LIGHT_ACTIVE);
     SetSensorMode(LIGHTS, SENSOR_MODE_PERCENT);
     SetSensorType(TOUCHS, SENSOR_TYPE_TOUCH);
     SetSensorMode(TOUCHS, SENSOR_MODE_BOOL);
     SetSensorType(USS, SENSOR_TYPE_LOWSPEED);



}

sub  _start()
{
  
     OnRev(MOTORS,100);
     Wait(500);
     Off(MOTORS); /*robot na vsech kolech*/
     RotateMotorMy(MOTORS,-100,R180);
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
     //_start();				//tralala2
     StartTask(search);
     StartTask(cmuchac);
     StartTask(destroy);
     
     StartTask(cara);
     
     
     //PlayTone(1000,100);
     //Wait(100);      
	 
}
