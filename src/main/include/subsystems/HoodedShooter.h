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

  double getHoodEncoderPosition() {return m_hoodmotor->GetSelectedSensorPosition();}
  double getHoodTargetPosition() {return m_currentHoodPosition;}
  double getHoodPositionError() {return m_hoodmotor->GetClosedLoopError();}
  double getHoodPercentageOutput() {return m_hoodmotor->GetMotorOutputPercent();}  // hood functions
  double getHoodVelocity() {return m_hoodmotor->GetSelectedSensorVelocity();}
  bool hasHoodHitLimit() {return m_hoodlimit.Get();}

  



 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonSRX* m_hoodmotor = new WPI_TalonSRX{7};
  frc::DigitalInput m_hoodlimit{8};

  double static constexpr k_hoodMaxEncoder{0.0}; //gotta find this value
  double m_currentHoodPosition{0.0};

  //PID values for hood
  std::map<std::string, double> k_PID_H{{"kP", 0.18}, {"kI", 00000000000001}, {"kD", 0.0}, {"kF", 0.0}};
};
