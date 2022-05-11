// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "units/length.h"
#include "units/angle.h"
/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace ShooterConstants {
    static constexpr double kTimeOutMS = 10;
    static constexpr double maxVelocity = 23000; // max velocity of the motor (velocity at 100% output)
    static constexpr double kFCalc = 1023 / maxVelocity; //kF calculations for the shooter motor
    double constexpr static k_maxAccumulator{1.5};
    double constexpr static k_iZone{300};
    static constexpr int kShooterMotorID = 6;
    static constexpr int kRollerMotorID = 5;
    

}


namespace SwerveDriveConstants {

    static constexpr double kJoystickRotateDeadZone{0.25};
    static constexpr double kJoystickStrafeDeadZone{0.15};
    static constexpr double kJoystickForwardDeadZone{0.15};

    static constexpr double kStrafeMultiplier{1.85};
    static constexpr double kForwardMultiplier{1.85};
    static constexpr double kRotateMultiplier{1.25};


}

namespace HoodedShooterConstants {
    static constexpr double kTimeOutMS = 10;
    static constexpr int kHoodMotorID = 54;
    static constexpr double kHoodEncoderMax = 2886.0;
    static constexpr double kP = 30.0;
    static constexpr double kI = 0.0001;
    static constexpr double kD = 0.0;
    static constexpr double kF = (1023*0.5)/123;
}

namespace MagazineConstants {
    static constexpr int kMagazineMotorID = 52;
    static constexpr int kBallSensorID = 9;
}

namespace ClimbConstants {

    static constexpr int kLeftClimbMotorId = 1;
    static constexpr int kRightClimbMotorId = 2;
    static constexpr int kClimbReleaseLeftSoloniodId = 3;
    static constexpr int kClimbReleaseRightSoloniodId = 4;

}
namespace IntakeConstants {

    static constexpr int kIntakeMotorID{51};
    static constexpr int kSolenoidLockID{5};

}

namespace VisionConstants {
    constexpr units::meter_t kLimelightHeight = 51_cm;
    constexpr units::meter_t kTowerHeight = 264_cm;
    constexpr units::degree_t kLimelightOffsetAngle = 35_deg;


}