// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ClimbMode.h"

ClimbMode::ClimbMode(Climb * climb, std::function<double()> leftSpeed, std::function<double()> rightSpeed) {
  AddRequirements({climb});
  m_climb = climb;
  m_leftSpeed = leftSpeed;
  m_rightSpeed = rightSpeed;
}

// Called when the command is initially scheduled.
void ClimbMode::Initialize() {
  m_climb->SetClimbReleased(true);
}

// Called repeatedly when this Command is scheduled to run
void ClimbMode::Execute() {
  m_climb->SetMotors(m_leftSpeed(), m_rightSpeed());
}

// Called once the command ends or is interrupted.
void ClimbMode::End(bool interrupted) {
  m_climb->SetClimbReleased(false);
}

// Returns true when the command should end.
bool ClimbMode::IsFinished() {
  return false;
}
