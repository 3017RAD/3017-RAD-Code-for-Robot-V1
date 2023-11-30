using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor RightDriveMotorA;
extern motor RightDriveMotorB;
extern motor LeftDriveMotorA;
extern motor LeftDriveMotorB;
extern motor CATA;
extern limit CATA_LIMIT;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );