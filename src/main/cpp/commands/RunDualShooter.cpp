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
  m_shooterDir = (fabs(m_dualshooter->GetShooterVel() - m_shooterTargetVel)) / (m_dualshooter->GetShooterVel() - m_shooterTargetVel);
  m_rollerDir = (fabs(m_dualshooter->GetRollerVel() - m_rollerTargetVel)) / (m_dualshooter->GetRollerVel() - m_rollerTargetVel);
  // DAVID IF YOU ARE READING THIS, I LEGIT DIDNT LOOK AT YOUR CODE i know it looks sus but its mine lol
  // fabssssss

  m_curRollerVel = m_dualshooter->GetRollerVel();
  m_curShooterVel = m_dualshooter->GetShooterVel();

  m_lastRollerVel = m_curRollerVel;
  m_lastShooterVel = m_curShooterVel;

}

// Called repeatedly when this Command is scheduled to run
void RunDualShooter::Execute() {
  m_curRollerVel = m_dualshooter->GetRollerVel();
  m_curShooterVel = m_dualshooter->GetShooterVel(); // made vars so dont keep calling vel, and so velocity doesn't change through 1 loop iter

  if (fabs(m_curShooterVel - m_shooterTargetVel) <= m_rampResolution){
    m_dualshooter->SetShooter(m_shooterTargetVel);
    m_done = true;
  }
  else {
    m_tempShooterTarget = m_lastShooterVel += m_rampResolution;
    if (m_curShooterVel >= m_tempShooterTarget){ // check if 
      m_dualshooter->SetShooter(m_curShooterVel += m_shooterDir * m_rampResolution);
    }
  }

  if (fabs(m_curRollerVel - m_rollerTargetVel) <= m_rampResolution){
    m_dualshooter->SetRoller(m_rollerTargetVel);
    m_done = true;
  }
  else {
    m_tempRollerTarget = m_lastRollerVel += m_rampResolution;
    if (m_curRollerVel >= m_tempRollerTarget){ // check if 
      m_dualshooter->SetRoller(m_curRollerVel += m_rollerDir * m_rampResolution);
    }
  }


  m_lastRollerVel = m_curRollerVel;
  m_lastShooterVel = m_curShooterVel; // put this at the end so when the loop runs next this is the last value

}

// Called once the command ends or is interrupted.
void RunDualShooter::End(bool interrupted) {}

// Returns true when the command should end.
bool RunDualShooter::IsFinished() {
  return m_done;
}
