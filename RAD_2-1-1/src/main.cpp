/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Dylan                                                     */
/*    Created:      1/9/2024, 8:28:42 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

//Motor Definitions
controller Controller1 = controller(primary);
motor RightDriveMotorA = motor(PORT16, ratio6_1, false);
motor RightDriveMotorB = motor(PORT17, ratio6_1, false);
motor RightDriveMotorC = motor(PORT18, ratio6_1, false);
motor LeftDriveMotorA = motor(PORT9, ratio6_1, false);
motor LeftDriveMotorB = motor(PORT10, ratio6_1, false);
motor LeftDriveMotorC = motor(PORT12, ratio6_1, false);
motor CATAPULT = motor(PORT5, ratio18_1, false);
motor Intake = motor(PORT11, ratio18_1, false);
inertial RADinertial(PORT14);
rotation CATASENSE (PORT1);
optical TRIballDetect (PORT21);

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

  }
  case 't': {
  RightDriveMotorA.setReversed ( true ) ; 
  RightDriveMotorB.setReversed ( true );
  LeftDriveMotorA.setReversed ( true );
  LeftDriveMotorB.setReversed( true );
  motor_group drive = motor_group(LeftDriveMotorA, LeftDriveMotorB, RightDriveMotorA, RightDriveMotorB);
  drive.spinFor( dis ,rev);
  break;
  }
  }
}  

void pre_auton(void) {

}

void autonomous(void) {
  
}


void usercontrol(void) {
  //Once Run
  RightDriveMotorA.setReversed ( true ) ; 
  RightDriveMotorB.setReversed ( true );
  RightDriveMotorC.setReversed ( true );
  LeftDriveMotorA.setReversed ( true );
  LeftDriveMotorB.setReversed( true );
  LeftDriveMotorC.setReversed( true );
  int Y = 1 ; // Defines Y Varible 
  int X = 1 ; // Defines X Varible 
 // CATASENSE.resetPosition();
  //TRIballDetect.setLightPower(100,pct);
  while (1) {
    // Drive Train Code
    RightDriveMotorA.spin(fwd); // Starts spinning motor Forward 
    RightDriveMotorB.spin(fwd); // Starts spinning motor Forward 
    RightDriveMotorC.spin(fwd); // Starts spinning motor Forward 
    LeftDriveMotorA.spin(fwd); // Starts spinning motor Forward 
    LeftDriveMotorB.spin(fwd); // Starts spinning motor Forward 
    LeftDriveMotorC.spin(fwd); // Starts spinning motor Forward 
     X = Controller1.Axis3.position(percent); // sets varibles to percentage of Controler axis
     Y = Controller1.Axis1.position(percent); // sets varibles to percentage of Controler axis
     motor_group Ldrive = motor_group(LeftDriveMotorA, LeftDriveMotorB, LeftDriveMotorC);
     Ldrive.setVelocity( Y   + X, pct );
    motor_group Rdrive = motor_group(RightDriveMotorA, RightDriveMotorB, RightDriveMotorC);
     Rdrive.setVelocity( Y   - X, pct );
    //Intake Code
    if (Controller1.ButtonR1.pressing()){
      Intake.spin(fwd,100,pct); }
    else if(Controller1.ButtonR2.pressing()){
      Intake.spin(reverse,100,pct);}
    else {
      Intake.stop();};
   //CataPult PID + Controller + AutoLaunch 
 
    CATAPULT.spin(reverse);

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
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
