// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ShooterBottomHoop.h"

ShooterBottomHoop::ShooterBottomHoop(DualShooter * dualshooter) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({dualshooter});
  m_dualshooter = dualshooter;
}

// Called when the command is initially scheduled.
void ShooterBottomHoop::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ShooterBottomHoop::Execute() {
  m_dualshooter->SetRoller(4000);
  m_dualshooter->SetShooter(4000);
}

// Called once the command ends or is interrupted.
void ShooterBottomHoop::End(bool interrupted) {
  m_dualshooter->setDualRoller(0.0); // hehe nice code bruh
  // thanks man
}

// Returns true when the command should end.
bool ShooterBottomHoop::IsFinished() {
  return false;
}
