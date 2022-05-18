// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoShooter.h"

using namespace DualShooterConstants;

AutoShooter::AutoShooter(Vision * vision) {
  // Use addRequirements() here to declare subsystem dependencies.
  m_vision = vision;
}

// Called when the command is initially scheduled.
void AutoShooter::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoShooter::Execute() {
  std::function<double()> m_shooterSpeed = [this]{
    return (4 / m_vision->getTargetDistance()) * kShooterDefaultSpeed;
  };

  std::function<double()> m_rollerSpeed = [this]{
    return kShooterToRoller * m_shooterSpeed(); // convert this to units
  };
}

// Called once the command ends or is interrupted.
void AutoShooter::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoShooter::IsFinished() {
  return false;
}
