#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RightDriveMotorA = motor(PORT1, ratio6_1, false);
motor RightDriveMotorB = motor(PORT2, ratio6_1, false);
motor LeftDriveMotorA = motor(PORT9, ratio6_1, false);
motor LeftDriveMotorB = motor(PORT10, ratio6_1, false);
motor CATA = motor(PORT5, ratio18_1, true);
limit CATA_LIMIT = limit(Brain.ThreeWirePort.A);

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