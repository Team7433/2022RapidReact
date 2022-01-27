// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TurnToTarget.h"

TurnToTarget::TurnToTarget(Vision * vision) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(vision);
  m_vision = vision;
  
}

// Called when the command is initially scheduled.
void TurnToTarget::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TurnToTarget::Execute() {}

// Called once the command ends or is interrupted.
void TurnToTarget::End(bool interrupted) {}

// Returns true when the command should end.
bool TurnToTarget::IsFinished() {
  return false;
}
