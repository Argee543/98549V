#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void screen() {
    // loop forever
    while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // print the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
        pros::delay(10);
    }
}
void initialize() {
	pros::lcd::initialize();
	chassis.calibrate();
     // X: 0, Y: 0, Heading: 0
	pros::lcd::register_btn1_cb(on_center_button);
	pros::Task screenTask(screen); // create a task to print the position to the screen

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
	//chassis.turnTo(90,53,1000);
	//chassis.moveTo(0,25,5000);
	chassis.setPose(0,0,0);
	chassis.moveTo(0, 0, 5000);
	chassis.moveTo(-6.458, 21.957, 5000);
	chassis.moveTo(-21.44, 19.632, 5000);
	chassis.turnTo(70.146,55.467,5000,true);
	Cata = 93;
	Cata2 = -93;
	pros::delay(25000);
	Cata = 0;
	Cata2 = 0;
	chassis.moveTo(27.123, 27.898, 5000);


    //chassis.setPose(-62.67588961038961, -39.601183982683985, 0);
    //Goes to middle bar and drives to other end of it
    //chassis.follow("bar_to_middle.txt",5000,15);
    //chassis.setPose(-8.003388888888889, 35.85933982683983, 0);
    //Lines up with under path
    //chassis.follow("mid_to_under.txt",5000,15);
    //chassis.setPose(-39.601183982683985, 59.765566378066374, 53.38180568945886);
    //Goes under and does side push
   // chassis.follow("under_to_push",5000,15);
    //chassis.setPose(57.06312337662337, 31.493854978354978, 47.399295511062434);
    //Goes from side push straight to the first mid push coming from the angle
   // chassis.follow("side_to_fir_mid_push",5000,15);
    //chassis.setPose(37.522381673881675, 9.250670274170274, 82.38864845115556);
   // chassis.follow("sec_push_set",5000,15);
    //chassis.setPose(10.082191197691197, -28.791411976911977, 68.70209854663739);
   // chassis.follow("sec_push",5000,15);
    //chassis.setPose(40.224824675324676, -9.666430735930735, 78.31268845252097);
   // chassis.follow("set_mid_push",5000,15);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2);

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_mtr = left;
		right_mtr = right;

		pros::delay(20);
	}
}
