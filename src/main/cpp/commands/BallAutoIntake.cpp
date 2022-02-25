// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/BallAutoIntake.h"

BallAutoIntake::BallAutoIntake(Magazine * magazine, Intake * intake) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({magazine, intake});

  m_intake = intake;
  m_magazine = magazine;
}

// Called when the command is initially scheduled.
void BallAutoIntake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void BallAutoIntake::Execute() {
  if (m_magazine->isBall() == true) {
    m_magazine->setPercentageOutput(0.0);

  }
  else {
    m_intake->setPercentOutput(0.5);
    m_magazine->setPercentageOutput(0.4);
  }
}

// Called once the command ends or is interrupted.
void BallAutoIntake::End(bool interrupted) {}

// Returns true when the command should end.
bool BallAutoIntake::IsFinished() {
  return false;
}
