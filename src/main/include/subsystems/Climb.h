// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "ctre/Phoenix.h"

#include "Constants.h"

class Climb : public frc2::SubsystemBase {
 public:
  Climb();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void setPercentageOutput(double pcgo){climbMotorOne->Set(ControlMode::PercentOutput, pcgo);}

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonFX * climbMotorOne = new WPI_TalonFX{2};
  WPI_TalonFX * climbMotorTwo = new WPI_TalonFX{4};


};
