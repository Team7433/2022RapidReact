// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RunDualShooter.h"

RunDualShooter::RunDualShooter(DualShooter * dualshooter, double rollerTargetVel, double shooterTargetVel, double rampRes) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({dualshooter});
  m_dualshooter = dualshooter;
  m_shooterTargetVel = shooterTargetVel;
  m_shooterTargetVel = rollerTargetVel;
  m_rampResolution = rampRes;


}

// Called when the command is initially scheduled.
void RunDualShooter::Initialize() {
  m_shooterDir = fabs(m_shooterTargetVel - m_dualshooter->GetShooterVel()) / (m_shooterTargetVel - m_dualshooter->GetShooterVel());
  m_rollerDir = fabs(m_rollerTargetVel - m_dualshooter->GetRollerVel())/ (m_dualshooter->GetRollerVel() - m_rollerTargetVel);

  currentRollerVel = m_dualshooter->GetRollerVel(); // get the initial roller velocity
  currentShooterVel = m_dualshooter->GetShooterVel(); // get initial shooter velocity

  m_done = false;
  
}

// Called repeatedly when this Command is scheduled to run
void RunDualShooter::Execute() {
  currentShooterVel = m_dualshooter->GetShooterVel();
  currentRollerVel = m_dualshooter->GetRollerVel();
  frc::SmartDashboard::PutNumber("DualShooter/rollerVel", currentRollerVel);
  frc::SmartDashboard::PutNumber("DualShooter/shooterVel", currentShooterVel);

  if (fabs(m_shooterTargetVel - currentShooterVel) < m_rampResolution) { // if the difference is small enough set the shooter to the target velocity
    m_dualshooter->SetShooter(m_shooterTargetVel);
    m_done = true;
  }
  else {
    tempShooter = currentShooterVel + m_rampResolution * m_rollerDir;
    std::cout << tempShooter << std::endl;
    m_dualshooter->SetShooter(tempShooter);
  }


}

// Called once the command ends or is interrupted.
void RunDualShooter::End(bool interrupted) {}

// Returns true when the command should end.
bool RunDualShooter::IsFinished() {
  return false;
}
