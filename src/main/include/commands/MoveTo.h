// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.


#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <subsystems/SwerveDriveTrain.h>
#include <utils/MotionProfile.h>
#include <iostream>


#include <units/velocity.h>
#include <units/acceleration.h>
#include <units/length.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class MoveTo
    : public frc2::CommandHelper<frc2::CommandBase, MoveTo> {
 public:
  MoveTo(SwerveDriveTrain* DriveTrain, units::meter_t targetX, units::meter_t targetY, units::radian_t targetAngle);
  MoveTo(SwerveDriveTrain* DriveTrain, coordinate targetCoordinate) : MoveTo(DriveTrain, targetCoordinate.xCoordinate, targetCoordinate.yCoordinate, units::convert<units::deg, units::rad>(targetCoordinate.angle)) {}

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;



  private:

  SwerveDriveTrain* m_driveTrain;
  units::meter_t m_distanceToTarget{0.0_m};

  units::meters_per_second_t m_maxVel{1.25_mps};
  units::meters_per_second_t m_endVel{0_mps};
  units::meters_per_second_squared_t m_acceleration{0.5_mps_sq};

  units::radians_per_second_t m_maxRad{4_rad_per_s};
  units::radians_per_second_t m_endRad{4_rad_per_s};
  units::radians_per_second_squared_t m_radAcceleration{4_rad_per_s_sq};

  units::millisecond_t m_timestep{20_ms};

  bool invertDirectionX{false};
  bool invertDirectionY{false};

  units::meter_t m_targetX{0.0_m};
  units::meter_t m_targetY{0.0_m};

  units::radian_t m_angleTarget{0.0_rad};

  Iona::MotionProfile<units::meters_per_second_t, units::meters_per_second_squared_t, units::meter_t> x_profile{m_maxVel, m_endVel, m_acceleration, m_targetX, m_timestep, invertDirectionX};
  Iona::MotionProfile<units::meters_per_second_t, units::meters_per_second_squared_t, units::meter_t> y_profile{m_maxVel, m_endVel, m_acceleration, m_targetY, m_timestep, invertDirectionY};

  Iona::MotionProfile<units::radians_per_second_t, units::radians_per_second_squared_t, units::radian_t> angle_profile{m_maxRad, m_endRad, m_radAcceleration, m_angleTarget, m_timestep};

};
