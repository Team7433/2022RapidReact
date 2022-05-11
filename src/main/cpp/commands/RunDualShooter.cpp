// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RunDualShooter.h"

RunDualShooter::RunDualShooter(DualShooter * dualshooter, double rollerTargetVel, double shooterTargetVel) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({dualshooter});
  m_dualshooter = dualshooter;
  m_shooterTargetVel = shooterTargetVel;
  m_shooterTargetVel = rollerTargetVel;


}

// Called when the command is initially scheduled.
void RunDualShooter::Initialize() {
  m_shooterDir = (fabs(m_dualshooter->GetShooterVel() - m_shooterTargetVel)) / (m_dualshooter->GetShooterVel() - m_shooterTargetVel);
  m_rollerDir = (fabs(m_dualshooter->GetRollerVel() - m_rollerTargetVel)) / (m_dualshooter->GetRollerVel() - m_rollerTargetVel);
  // DAVID IF YOU ARE READING THIS, I LEGIT DIDNT LOOK AT YOUR CODE i know it looks sus but its mine lol
  // fabssssss

}

// Called repeatedly when this Command is scheduled to run
void RunDualShooter::Execute() {
  if (m_dualshooter->GetShooterVel() - m_shooterTargetVel <= rampResolution) {
    m_dualshooter->SetRoller(m_shooterTargetVel);
  }
  else {
    
  }

}

// Called once the command ends or is interrupted.
void RunDualShooter::End(bool interrupted) {}

// Returns true when the command should end.
bool RunDualShooter::IsFinished() {
  return m_done;
}
