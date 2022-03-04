// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ControlShooter.h"

ControlShooter::ControlShooter(Shooter* shooter, HoodedShooter* hoodedShooter, std::function<double()>* rampTarget, std::function<double()>* rampSpeed, std::function<double()>* hoodTarget) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({hoodedShooter, shooter});
  m_shooter = shooter;
  m_hoodedSooter = m_hoodedSooter;
  
  m_rampSpeed = rampSpeed;
  m_rampTarget = rampTarget;
  m_hoodTarget = hoodTarget;

}

// Called when the command is initially scheduled.
void ControlShooter::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ControlShooter::Execute() {

  m_hoodedSooter->setHoodPosition((*m_hoodTarget)()); // sets hoodedshooter to position

  //checks if adding the next rampspeed will go over or equal to the target, if so then just set it to the target
  if (m_shooter->getTargetVelocity()+(calculateDirection()*(*m_rampSpeed)()) >= (*m_rampTarget)()*calculateDirection()) {
    m_shooter->setVelocity((*m_rampTarget)());
  }
  //sets the shooter velocity to current plus ramp speed
  m_shooter->setVelocity(m_shooter->getTargetVelocity()+(calculateDirection()*(*m_rampSpeed)()));



}

// Called once the command ends or is interrupted.
void ControlShooter::End(bool interrupted) {}

// Returns true when the command should end.
bool ControlShooter::IsFinished() {
  return false;
}

double ControlShooter::calculateDirection() {
  //returns -1, 0 or 1, showing which way the ramp is going 0 means its on target
  return  ((*m_rampTarget)()-m_shooter->getTargetVelocity() !=0.0) ? ((*m_rampTarget)() - m_shooter->getTargetVelocity())/fabs((*m_rampTarget)()-m_shooter->getTargetVelocity()) : 0.0;

}