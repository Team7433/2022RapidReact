// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RunShooter.h"


using namespace ShooterConstants;
RunShooter::RunShooter(Shooter* shooter, double targetVelocity, double velocityRamp) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(shooter);
  m_shooter = shooter;
  m_targetVel = targetVelocity;
  m_velocityRamp = velocityRamp;
  
}

// Called when the command is initially scheduled.
void RunShooter::Initialize() {
  m_direction = -(m_shooter->getTargetVelocity()-m_targetVel)/fabs(m_shooter->getTargetVelocity()-m_targetVel);
  // m_direction = 
}

// Called repeatedly when this Command is scheduled to run
void RunShooter::Execute() {
  
  currentVel = m_shooter->getTargetVelocity(); // 2000
  velError = m_targetVel - currentVel;

  if (sqrt(pow(velError, 2)) < velError) {
    m_shooter->setVelocity(m_targetVel);
    m_done = true;
  }
  else {
    m_shooter->setVelocity(currentVel+m_velocityRamp*m_direction);
  }
  

  // currentVel = m_shooter->getTargetVelocity();

  // if (currentVel*m_direction > m_targetVel) {
  //   m_shooter->setVelocity(m_targetVel);
  //   m_done = true;
  // } else {
  //   m_shooter->setVelocity((currentVel+(m_velocityRamp*m_direction)));
  // }



  frc::SmartDashboard::PutNumber("shooter/target vel", m_targetVel);
  frc::SmartDashboard::PutNumber("shooter/future vel", futureVel);
  frc::SmartDashboard::PutNumber("shooter/vel error", velError);

}

// Called once the command ends or is interrupted.
void RunShooter::End(bool interrupted) {
  m_done=false;
}

// Returns true when the command should end.
bool RunShooter::IsFinished() {
  return m_done;
}
