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
 
  
  double getPercentOutput() {return m_motor->GetMotorOutputPercent();}
  double getVelocity() {return m_motor->GetSelectedSensorVelocity();} // shooter functions
  double getTargetVelocity() {return (m_motor->GetControlMode() == ControlMode::Velocity) ? m_motor->GetClosedLoopTarget() : 0.0;}

  

  bool rampHasReachedSpeed() {return m_rampTarget == getTargetVelocity();}

  ControlMode getControlMode() {return m_motor->GetControlMode();}
  
  double m_rampTarget{0.0};

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonFX* m_motor = new WPI_TalonFX{6};
  WPI_TalonFX* m_motorS = new WPI_TalonFX{5};
  


  //KI settings for shooter
  double constexpr static k_maxAccumulator{1.5};
  double constexpr static k_iZone{300};

  //PID values for shooter
  std::map<std::string, double> k_PID_S{{"kP", 0.18}, {"kI", 00000000000001}, {"kD", 0.0}};
  

  




};
