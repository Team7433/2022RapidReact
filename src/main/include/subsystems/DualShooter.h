// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include "Constants.h"
#include <map>
#include <string.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>

using namespace ShooterConstants;

class DualShooter : public frc2::SubsystemBase {
 public:
  DualShooter();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void SetRoller(double vel){m_rollerMotor->Set(ControlMode::Velocity, vel);}
  void SetShooter(double vel){m_shooterMotor->Set(ControlMode::Velocity, vel);}

  // void SetRollerPCGO(double pcgo){std::cout << "WorkingOne\n"; m_rollerMotor->Set(ControlMode::PercentOutput, pcgo);}
  // void SetShooterPCGO(double pcgo){std::cout << "workingTwo\n"; m_shooterMotor->Set(ControlMode::PercentOutput, pcgo);} // remove before flight

  void setDualRoller(double percentageOutput) { m_shooterMotor->Set(ControlMode::PercentOutput, percentageOutput); m_rollerMotor->Set(ControlMode::PercentOutput, percentageOutput);}
  double GetRollerVel(){return m_rollerMotor->GetSelectedSensorVelocity();}
  double GetShooterVel(){return m_shooterMotor->GetSelectedSensorVelocity();}

  void UpdateSD();
  void PIDInit();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonFX * m_shooterMotor = new WPI_TalonFX{kShooterMotorID};
  WPI_TalonFX * m_rollerMotor = new WPI_TalonFX{kRollerMotorID}; // rename this const
  std::map<std::string, double> m_pidRoller{{"kP", 0.001}, {"kI", 0}, {"kD", 0}};
  std::map<std::string, double> m_pidShooter{{"kP", 0.001}, {"kI", 0}, {"kD", 0}}; // bruh piss

  double m_maxShooterVel;
  double m_maxRollerVel;


};
