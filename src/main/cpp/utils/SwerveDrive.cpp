#include <utils/SwerveDrive.h>
#include <iostream>
using namespace Iona;


void SwerveDrive::Drive(double forward, double strafe, double rotate, units::degree_t gyroAngle, bool invertHeading, bool invertRotation, bool squaredInputs, bool velocityMode, bool squareRotation) {
    //invert heading and rotation logic
    // forward = invertHeading ? -forward : forward;
    // strafe = invertHeading ? -strafe : strafe;
    // rotate = invertRotation ? -rotate : rotate;
    
    //convert inputs to squared if defined
    if (squaredInputs) {
        forward = std::copysign(pow(forward, 2.0), forward);
        strafe = std::copysign(pow(strafe, 2.0), strafe);
    }
    if (squareRotation) {
        rotate = std::copysign(pow(rotate, 2.0), rotate);
    }

    //getting chasis angle from the gyro
    currentRobotAngle = gyroAngle;
    // std::cout << gyroAngle.to<double>() << std::endl;

    //converting joystick field centric inputs to field centric values for the bot depending on the chasis angle
    FWD = forward*units::math::cos(currentRobotAngle) + (strafe*units::math::sin(currentRobotAngle));
    STR = strafe*units::math::cos(currentRobotAngle) - (forward*units::math::sin(currentRobotAngle));

    //setting variables for vector math later
    A = STR - (rotate * (kwheelBase/kradius));
    B = STR + (rotate * (kwheelBase/kradius));
    C = FWD - (rotate * (ktrackWidth/kradius));
    D = FWD + (rotate * (ktrackWidth/kradius));

    //setting output
    outputs["TopRight"] = sqrt(pow(B, 2) + pow(C, 2));
    outputs["TopLeft"] = sqrt(pow(B, 2) + pow(D, 2));
    outputs["BottomLeft"] = sqrt(pow(A, 2) + pow(D, 2));
    outputs["BottomRight"] = sqrt(pow(A, 2) + pow(C, 2));

    //find the max in the outputs if they are above 1
    double max{velocityMode ? maxVel : 1.0};
    for (auto output : outputs) {
        if(fabs(output.second) > max) {
            max = fabs(output.second);
        }
    }

    //sets the target angle for each swerve module
    angles["TopRight"] = units::math::atan2(units::centimeter_t(B), units::centimeter_t(C));
    angles["TopLeft"] = units::math::atan2(units::centimeter_t(B), units::centimeter_t(D));
    angles["BottomLeft"] = units::math::atan2(units::centimeter_t(A), units::centimeter_t(D));
    angles["BottomRight"] = units::math::atan2(units::centimeter_t(A), units::centimeter_t(C));

    //logic to convert - 180 through 180 to 0 through 360
    for (auto angle : angles) {
        if (units::math::fabs(angle.second).to<double>()/angle.second.to<double>() == -1.0) {
            angles[angle.first] = angle.second + 360_deg;
        }
    }

    //Set all swerve modules
    m_swerveModules["TopRight"]->setModule(angles["TopRight"], outputs["TopRight"], velocityMode);
    m_swerveModules["TopLeft"]->setModule(angles["TopLeft"], outputs["TopLeft"], velocityMode);
    m_swerveModules["BottomRight"]->setModule(angles["BottomRight"], outputs["BottomRight"], velocityMode);
    m_swerveModules["BottomLeft"]->setModule(angles["BottomLeft"], outputs["BottomLeft"], velocityMode);

    // m_topRightModule->setDriveOutput(outputs["TopRight"]);
    // m_topLeftModule->setDriveOutput(outputs["TopLeft"]);
    // m_bottomRightModule->setDriveOutput(outputs["BottomRight"]);
    // m_bottomLeftModule->setDriveOutput(outputs["BottomLeft"]);

    // m_topRightModule->setHeadingAngle(angles["TopRight"]);
    // m_topLeftModule->setHeadingAngle(angles["TopLeft"]);
    // m_bottomRightModule->setHeadingAngle(angles["BottomRight"]);
    // m_bottomLeftModule->setHeadingAngle(angles["BottomLeft"]);

}

void SwerveDrive::DisplayData() {

    // m_topRightModule->displayData();
    // m_topLeftModule->displayData();
    // m_bottomRightModule->displayData();
    // m_bottomLeftModule->displayData();

    m_swerveModules["TopRight"]->displayData();
    m_swerveModules["TopLeft"]->displayData();
    m_swerveModules["BottomRight"]->displayData();
    m_swerveModules["BottomLeft"]->displayData();

    frc::SmartDashboard::PutNumber("SwerveDrive/Forward", FWD);
    frc::SmartDashboard::PutNumber("SwerveDrive/Strafe", STR);
    
}

