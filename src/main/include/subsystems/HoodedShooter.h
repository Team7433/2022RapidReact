// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>
#include <stdio.h>
#include <iostream>
#include "Constants.h"

#include <map>

using namespace HoodedShooterConstants;
class HoodedShooter : public frc2::SubsystemBase {
 public:
  HoodedShooter();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void ConfigPIDH(double, double, double);
  void setPercentageOutputHood(double output) {m_hoodmotor->Set(ControlMode::PercentOutput, output);}
  void setHoodPosition(double position);
  void resetEncoder() {m_hoodmotor->SetSelectedSensorPosition(0.0, 0, 10);}

  double getHoodEncoderPosition() {return m_hoodmotor->GetSelectedSensorPosition();}
  double getHoodTargetPosition() {return m_currentHoodPosition;}
  double getHoodPositionError() {return m_hoodmotor->GetClosedLoopError();}
  double getHoodPercentageOutput() {return m_hoodmotor->GetMotorOutputPercent();}  // hood functions
  double getHoodVelocity() {return m_hoodmotor->GetSelectedSensorVelocity();}
  bool hasHoodHitLimit() {return !m_hoodmotor->IsRevLimitSwitchClosed();}

  



 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonSRX* m_hoodmotor = new WPI_TalonSRX{kHoodMotorID};


  double static constexpr k_hoodMaxEncoder{kHoodEncoderMax}; //gotta find this value
  double m_currentHoodPosition{0.0};

  //PID values for hood
  std::map<std::string, double> k_PID_H{{"kP", kP}, {"kI", kI}, {"kD", kD}, {"kF", kF}};
};
