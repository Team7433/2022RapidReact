// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <subsystems/SwerveDriveTrain.h>
#include <subsystems/Gyro.h>

#include <utils/MotionProfile.h>

#include <units/length.h>
#include <units/math.h>
#include <cmath>

#include <iostream>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class MotionProfile
    : public frc2::CommandHelper<frc2::CommandBase, MotionProfile> {
 public:
  MotionProfile(SwerveDriveTrain* driveTrain, Gyro* gyro, coordinate);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;


 private:
  SwerveDriveTrain* m_driveTrain;
  Gyro* m_gyro;

  coordinate m_targetCoord;
  units::meters_per_second_t m_maxVelocity{1_mps};
  units::meters_per_second_squared_t m_maxAcceleration{2_mps_sq};
  units::meters_per_second_t m_endVelocity{0.0_mps};
  units::meter_t m_distanceLeft{0.0_m};

  int m_Xdirection{1};
  int m_Ydirection{1};

  units::meters_per_second_t m_newXVelocity{0.0_mps};
  units::meters_per_second_t m_newYVelocity{0.0_mps};

  units::meters_per_second_t m_currentXVelocity{0.0_mps};
  units::meters_per_second_t m_currentYVelocity{0.0_mps};

  const double kPi {3.14159265359};

  double m_maxDegAccel{14.0};

  double m_newAngleOutput{0.0};
  units::degree_t m_angleDistance{0.0_deg};
  int m_angleDirection{1};
  double m_angleDistanceTravelled{0.0};
  double m_angleOutput{0.0};
  double m_angleMaxVel{0.0};
  double m_rotateKP{0.02};



};