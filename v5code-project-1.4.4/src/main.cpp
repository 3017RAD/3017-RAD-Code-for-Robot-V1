// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RightDriveMotorA     motor         16              
// RightDriveMotorB     motor         17              
// LeftDriveMotorA      motor         9               
// LeftDriveMotorB      motor         10              
// FlyWheel             motor         5               
// Lift                 motor_group   11, 20          
// RADinertial          inertial      14              
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RightDriveMotorA     motor         16              
// RightDriveMotorB     motor         17              
// LeftDriveMotorA      motor         9               
// LeftDriveMotorB      motor         10              
// FlyWheel             motor         5               
// Lift                 motor_group   11, 20          
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

void calibrate(){
RADinertial.calibrate();
if(RADinertial.isCalibrating()){
Controller1.rumble(rumbleShort);
  };
}


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
/*
CATA LOGIC 
 cmd 
 P ~ Pull catapult to tennsioned position 
 l ~ Launches the cata pult 
 A ~ Runs Catapult in Autonomous 
*/
/*
*/
void autoncode ( char cmd, float dis, float delay, float speed ){ //Code that will run during auton driving 
  // cmd = direction, dis = distance/ andle, delay, how long code will run 
  RightDriveMotorA.setVelocity(speed,pct);
  RightDriveMotorB.setVelocity(speed,pct);
  LeftDriveMotorA.setVelocity(speed,pct);
  LeftDriveMotorB.setVelocity(speed,pct);
  switch (cmd){
  case 'f': {
  RightDriveMotorA.setReversed ( true ) ; 
  RightDriveMotorB.setReversed ( true );
  LeftDriveMotorA.setReversed ( false );
  LeftDriveMotorB.setReversed( false );
  motor_group drive = motor_group(LeftDriveMotorA, LeftDriveMotorB, RightDriveMotorA, RightDriveMotorB);
  drive.spinFor( dis ,rev);
  //wait( delay, sec );
  break;
  }
  case 't': {
  RightDriveMotorA.setReversed ( true ) ; 
  RightDriveMotorB.setReversed ( true );
  LeftDriveMotorA.setReversed ( true );
  LeftDriveMotorB.setReversed( true );
  motor_group drive = motor_group(LeftDriveMotorA, LeftDriveMotorB, RightDriveMotorA, RightDriveMotorB);
  drive.spinFor( dis ,rev);
  //wait( delay, sec );
  break;
  }
  }
}  
void autonomous(void) {
Lift.setVelocity(80,pct); 
autoncode('f',18.75,1,100);
autoncode('t',4,1,80);
Lift.spinFor(fwd,2,rev);
wait(.5,sec);
Lift.spinFor(fwd,-1.8,rev);
autoncode('f', 3, .75, 100);
autoncode('f', -3, .75, 100);
//autoncode('f', 3, 1, 50);
//autoncode('f', -2.8, 1, 50);
autoncode('t',3.6,.75,80);
autoncode('f',17,1,100);
autoncode('t',3.8,.75,80);
autoncode('f',9.95,1,100);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/



void usercontrol(void) {
  // User control code here, inside the loop
  RightDriveMotorA.setReversed ( true ) ; 
  RightDriveMotorB.setReversed ( true );
  LeftDriveMotorA.setReversed ( true );
  LeftDriveMotorB.setReversed( true );
//Bug fixer
Brain.Timer.reset();
  while (1) {
    int FlY_V = 100; //FlyWheel  Velocity 
    int Y = 1 ; // Defines Y Varible 
    int X = 1 ; // Defines X Varible 

     RightDriveMotorA.spin(fwd); // Starts spinning motor Forward 
     RightDriveMotorB.spin(fwd); // Starts spinning motor Forward 
     LeftDriveMotorA.spin(fwd); // Starts spinning motor Forward 
     LeftDriveMotorB.spin(fwd); // Starts spinning motor Forward 
     X = Controller1.Axis3.position(percent); // sets varibles to percentage of Controler axis
     Y = Controller1.Axis1.position(percent); // sets varibles to percentage of Controler axis
    RightDriveMotorA.setVelocity( Y   - X, pct) ; // Set motor speed to to difference of both axises 
    RightDriveMotorB.setVelocity( Y - X, pct) ; // Set motor speed to to difference of both axises 
    LeftDriveMotorB.setVelocity( Y + X , pct ); // Set motor speed to to sum of both axises 
    LeftDriveMotorA.setVelocity( Y + X , pct ); // Set motor speed to to sum of both axise
    //Lift 
    Lift.setStopping(hold);
      if (Controller1.ButtonR1.pressing())
        {FlyWheel.spin(fwd,FlY_V,pct);}
        else if (Controller1.ButtonR2.pressing()){
        FlyWheel.stop();
        }
      if (Controller1.ButtonL1.pressing()){
     Lift.spin(fwd,100,pct);}
     else if(Controller1.ButtonL2.pressing()){
       Lift.spin(reverse,100,pct);
     }
     else{
       Lift.stop();
     }
    //Time Controll
    if (Brain.Timer.time(seconds) == 75 ){
      Controller1.rumble(rumbleLong);
    };
    //Match Load Identifery 
    if (FlyWheel.velocity(pct) <= FlY_V -90 ) //Red Speed Identifyer Number
    {
       Brain.Screen.setFillColor( red );
       Brain.Screen.drawRectangle( 0, 0, 500, 700 );
    }
    else if(FlyWheel.velocity(pct) <= FlY_V -40) //Yellow Speed Identifyer Number
    {
       Brain.Screen.setFillColor( yellow );
       Brain.Screen.drawRectangle(  0, 0, 500, 700  );
    }
    else if(FlyWheel.velocity(pct) <= FlY_V ) //Green Speed Identifyer Number
    {
       Brain.Screen.setFillColor( green );
       Brain.Screen.drawRectangle( 0, 0, 500, 700 );
    }
    else if (FlyWheel.velocity(pct) <= FlY_V -10 )  {
      Brain.Screen.clearScreen( black );
    }
    //End Of Drive Control Code 
    wait(20, msec); // Sleep the task for a short amount of time to             // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
