// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/DigitalOutput.h>
#include <ctre/Phoenix.h>

#include "Constants.h"

class Climb : public frc2::SubsystemBase {
 public:
  Climb();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void SetMotors(double leftSpeed, double rightSpeed);
  void SetClimbReleased(bool released);

 private:
  TalonSRX * m_leftClimb = new TalonSRX{ClimbConstants::kLeftClimbMotorId};
  TalonSRX * m_rightClimb = new TalonSRX{ClimbConstants::kRightClimbMotorId};

  frc::DigitalOutput m_releaseSolenoidRight{ClimbConstants::kClimbReleaseRightSoloniodId};
  frc::DigitalOutput m_releaseSolenoidLeft{ClimbConstants::kClimbReleaseLeftSoloniodId};
};
