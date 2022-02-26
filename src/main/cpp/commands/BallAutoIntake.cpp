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
void BallAutoIntake::Initialize() {
    m_intake->setPercentOutput(0.5);
    
    if (m_magazine->isBall() == false) {
      m_magazine->setPercentageOutput(0.4);
    }
    if (m_intake->getPercentOutput() != 0.0 || m_magazine->getPercentageOutput() !=0.0 ) {

      m_done = true;
    }
    
}

// Called repeatedly when this Command is scheduled to run
void BallAutoIntake::Execute() {
  if (m_magazine->isBall() == true) {
    m_magazine->setPercentageOutput(0.0);
    m_done = true;
  }

  
}

// Called once the command ends or is interrupted.
void BallAutoIntake::End(bool interrupted) {
  m_intake->setPercentOutput(0);
  m_magazine->setPercentageOutput(0);
  m_done = false;
}

// Returns true when the command should end.
bool BallAutoIntake::IsFinished() {
  return m_done;
}
