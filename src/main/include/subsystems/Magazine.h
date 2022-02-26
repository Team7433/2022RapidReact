// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>

class Magazine : public frc2::SubsystemBase {
 public:
  Magazine();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void setPercentageOutput(double output){m_motor->Set(ControlMode::PercentOutput, output);}
  double getPercentageOutput() {return m_motor->GetMotorOutputPercent();}
  bool isBall() {return !(m_ballsensor.Get());}

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonFX* m_motor = new WPI_TalonFX{52};
  frc::DigitalInput m_ballsensor{9};

};
