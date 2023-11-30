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
void CATALOGIC (char cmd, float speed) {
  switch(cmd){
    case 'p':{
      CATA.spin(fwd,speed,pct);

      if (CATA_LIMIT.pressing() ) {
        CATA.stop();
      }
     // if (CATA.velocity(pct) < 40 ){
      //  CATA.stop();
      //}
      break;
    }
    case 'l':{
      CATA.spinFor(fwd, 3 , degrees );
      break;
    }
    case 'a':{
      CATA.spin(fwd,speed,pct);
      if (CATA_LIMIT.pressing()){
        CATA.stop();
        CATA.setStopping(brake);
        wait(1,sec);
        CATA.spin(fwd,speed,pct);
        
      }
      break;
    }
  }

}
*/
void autoncode ( char cmd, float dis, float delay, float speed ){ 
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
  wait( delay, sec );
  break;
  }
  case 't': {
  RightDriveMotorA.setReversed ( true ) ; 
  RightDriveMotorB.setReversed ( true );
  LeftDriveMotorA.setReversed ( true );
  LeftDriveMotorB.setReversed( true );
  motor_group drive = motor_group(LeftDriveMotorA, LeftDriveMotorB, RightDriveMotorA, RightDriveMotorB);
  drive.spinFor( dis ,rev);
  wait( delay, sec );
  break;
  }
  }
} 
void autonomous(void) {
    
autoncode('f',3,1,50);
autoncode('t',3,1,50); 
autoncode('f',3,1,100);  



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
//Bug fixer
  while (1) {
    int FlY_V = 100; //CATA Velocity 
    

    int Y = 1 ; // Defines Y Varible 
    int X = 1 ; // Defines X Varible 

     RightDriveMotorA.spin(fwd); // Starts spinning motor Forward 
     RightDriveMotorB.spin(fwd); // Starts spinning motor Forward 
     LeftDriveMotorA.spin(fwd); // Starts spinning motor Forward 
     LeftDriveMotorB.spin(fwd); // Starts spinning motor Forward 
     X = Controller1.Axis3.position(percent); // sets varibles to percentage of Controler axis
     Y = Controller1.Axis1.position(percent); // sets varibles to percentage of Controler axis
    RightDriveMotorA.setVelocity( Y*-1  - X, pct) ; // Set motor speed to to difference of both axises 
    RightDriveMotorB.setVelocity( Y*-1 - X, pct) ; // Set motor speed to to difference of both axises 
    LeftDriveMotorB.setVelocity( Y*-1 + X , pct ); // Set motor speed to to sum of both axises 
    LeftDriveMotorA.setVelocity( Y*-1 + X , pct ); // Set motor speed to to sum of both axise
    //CATA 
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
