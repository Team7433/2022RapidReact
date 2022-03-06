// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/InitHood.h"

InitHood::InitHood(HoodedShooter* hoodedShooter) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({hoodedShooter});

  m_hood = hoodedShooter;

}

// Called when the command is initially scheduled.
void InitHood::Initialize() {

  if(!m_hood->hasHoodHitLimit()){
    m_hood->setPercentageOutputHood(-0.5);
  }
  std::cout << m_hood->hasHoodHitLimit() << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void InitHood::Execute() {
}
// Called once the command ends or is interrupted.
void InitHood::End(bool interrupted) {
  m_hood->setPercentageOutputHood(0.0);
  m_hood->resetEncoder();
}

// Returns true when the command should end.
bool InitHood::IsFinished() {
  return m_hood->hasHoodHitLimit();
}
