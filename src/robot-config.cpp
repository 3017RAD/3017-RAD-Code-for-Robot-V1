#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RightDriveMotorA = motor(PORT16, ratio6_1, false);
motor RightDriveMotorB = motor(PORT17, ratio6_1, false);
motor LeftDriveMotorA = motor(PORT9, ratio6_1, false);
motor LeftDriveMotorB = motor(PORT10, ratio6_1, false);
motor FlyWheel = motor(PORT5, ratio18_1, false);
motor LiftMotorA = motor(PORT11, ratio18_1, false);
motor LiftMotorB = motor(PORT20, ratio18_1, true);
motor_group Lift = motor_group(LiftMotorA, LiftMotorB);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}