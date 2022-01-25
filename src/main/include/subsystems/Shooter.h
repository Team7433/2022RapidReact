// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>


class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void setPercentOutput(double output) {m_motor->Set(ControlMode::PercentOutput, output);}
  void setVelocity(double velocity) {m_motor->Set(ControlMode::Velocity, velocity);}
  void ConfigPID(double P, double I, double D);
  double getPercentOutput() {return m_motor->GetMotorOutputPercent();}
  double getVelocity() {return m_motor->GetSelectedSensorVelocity();}
  double getTargetVelocity() {return m_motor->GetClosedLoopTarget();}
  

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonFX* m_motor = new WPI_TalonFX{6};
  WPI_TalonFX* m_motorS = new WPI_TalonFX{5};

};
