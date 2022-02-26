// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/EjectOneBall.h"

EjectOneBall::EjectOneBall(Magazine* magazine, Shooter* shooter) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({magazine});

  m_magazine = magazine;
  m_shooter = shooter;
}

// Called when the command is initially scheduled.
void EjectOneBall::Initialize() {
  RunShooter(m_shooter, 4000.0, 300.0).Schedule();
}

// Called repeatedly when this Command is scheduled to run
void EjectOneBall::Execute() {

  if (m_shooter->rampHasReachedSpeed()) {
    m_timer.Start();
    m_magazine->setPercentageOutput(0.5);
  }
  if (m_timer.HasElapsed(3_s)) {
    m_done = true;
  }

  

}

// Called once the command ends or is interrupted.
void EjectOneBall::End(bool interrupted) {
  m_magazine->setPercentageOutput(0.0);
  m_timer.Stop();
  m_timer.Reset();
  m_done = false;
}

// Returns true when the command should end.
bool EjectOneBall::IsFinished() {
  return m_done;
}
