// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DigitalInput.h>

#include <map>
#include <string.h>


class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void setPercentOutput(double output) {m_motor->Set(ControlMode::PercentOutput, output);}
  void setVelocity(double velocity) {(velocity ==0)? m_motor->Set(ControlMode::PercentOutput, 0) : m_motor->Set(ControlMode::Velocity, velocity);}
  void ConfigPID(double P, double I, double D); // PID, and one-time initialisation stuffs
  void ConfigPIDH(double, double, double);
  void setPercentageOutputHood(double output) {m_hoodmotor->Set(ControlMode::PercentOutput, output);}
  void setHoodPosition(double position);

  
  double getPercentOutput() {return m_motor->GetMotorOutputPercent();}
  double getVelocity() {return m_motor->GetSelectedSensorVelocity();} // shooter functions
  double getTargetVelocity() {return (m_motor->GetControlMode() == ControlMode::Velocity) ? m_motor->GetClosedLoopTarget() : 0.0;}

  double getHoodEncoderPosition() {return m_hoodmotor->GetSelectedSensorPosition();}
  double getHoodTargetPosition() {return m_currentHoodPosition;}
  double getHoodPositionError() {return m_hoodmotor->GetClosedLoopError();}
  double getHoodPercentageOutput() {return m_hoodmotor->GetMotorOutputPercent();}  // hood functions
  double getHoodVelocity() {return m_hoodmotor->GetSelectedSensorVelocity();}
  bool hasHoodHitLimit() {return m_hoodlimit.Get();}

  bool rampHasReachedSpeed() {return m_rampTarget == getTargetVelocity();}

  ControlMode getControlMode() {return m_motor->GetControlMode();}
  
  double m_rampTarget{0.0};

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonFX* m_motor = new WPI_TalonFX{6};
  WPI_TalonFX* m_motorS = new WPI_TalonFX{5};
  WPI_TalonSRX* m_hoodmotor = new WPI_TalonSRX{7};
  frc::DigitalInput m_hoodlimit{8};


  //KI settings for shooter
  double constexpr static k_maxAccumulator{1.5};
  double constexpr static k_iZone{300};

  //PID values for shooter
  std::map<std::string, double> k_PID_S{{"kP", 0.18}, {"kI", 00000000000001}, {"kD", 0.0}};
  //PID values for hood
  std::map<std::string, double> k_PID_H{{"kP", 0.18}, {"kI", 00000000000001}, {"kD", 0.0}, {"kF", 0.0}};

  double static constexpr k_hoodMaxEncoder{0.0}; //gotta find this value
  double m_currentHoodPosition{0.0};




};
