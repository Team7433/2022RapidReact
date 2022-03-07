// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ReverseIntake.h"

ReverseIntake::ReverseIntake(Intake * intake) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(intake);

  m_intake = intake;
}

// Called when the command is initially scheduled.
void ReverseIntake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ReverseIntake::Execute() {
  m_intake->setPercentOutput(-0.5);
}

// Called once the command ends or is interrupted.
void ReverseIntake::End(bool interrupted) {
  m_intake->setPercentOutput(0.0);
}

// Returns true when the command should end.
bool ReverseIntake::IsFinished() {
  return false;
}
