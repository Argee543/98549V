#include "main.h"

// motor
pros::Motor rightFront(4, pros::E_MOTOR_GEARSET_06, false);
pros::Motor rightMiddle(13, pros::E_MOTOR_GEARSET_06, false);
pros::Motor rightBack(20, pros::E_MOTOR_GEARSET_06, false);
pros::Motor leftFront(18, pros::E_MOTOR_GEARSET_06, true);
pros::Motor leftMiddle(10, pros::E_MOTOR_GEARSET_06, true);
pros::Motor leftBack(15, pros::E_MOTOR_GEARSET_06, true);
pros::Motor Cata(8, pros::E_MOTOR_GEARSET_18, false);
pros::Motor Cata2(9, pros::E_MOTOR_GEARSET_18, true);
pros::Motor intake(11, pros::E_MOTOR_GEARSET_18, true);
pros::ADIDigitalOut frontWings(1);
pros::ADIDigitalOut backleftWing(2);
pros::ADIDigitalOut backrightWing(3);

// motor_group
pros::MotorGroup left_side_motors({leftFront,leftMiddle,leftBack});
pros::MotorGroup right_side_motors({rightFront,rightMiddle,rightBack});

// drivetrain
lemlib::Drivetrain_t drivetrain {
    &left_side_motors, // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    11.75, // track width
    3.25, // wheel diameter
    360 // wheel rpm
};

//sensors
pros::Rotation rotCata(16, false);
pros::Rotation rotTrackVertical(5, false);
pros::Rotation rotTrackHorizontal(12,false);
pros::Imu inertial(14);
lemlib::TrackingWheel right_tracking_wheel(&rotTrackVertical, 2.75, 0.125);
lemlib::TrackingWheel back_tracking_wheel(&rotTrackHorizontal, 2.75, -2.625);

//odom
lemlib::OdomSensors_t odomSensors {
    nullptr, // vertical tracking wheel 1
    &right_tracking_wheel, // vertical tracking wheel 2
    &back_tracking_wheel, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial // inertial sensor
};

// forward/backward PID
lemlib::ChassisController_t lateralController {
    10.125, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    8, // kP
    80, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, odomSensors);

