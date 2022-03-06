// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>

#include <frc/DigitalOutput.h>

#include "Constants.h"

using namespace IntakeConstants;

class Intake : public frc2::SubsystemBase {
 public:
  Intake();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void setPercentOutput(double percentoutput) {m_motor->Set(ControlMode::PercentOutput, percentoutput);}
  double getPercentOutput() {return m_motor->GetMotorOutputPercent();}
  void setSolenoid(bool state) { m_solenoidLock.Set(!state);}
 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonSRX * m_motor = new WPI_TalonSRX{kIntakeMotorID};
  frc::DigitalOutput m_solenoidLock{kSolenoidLockID};
};
  
