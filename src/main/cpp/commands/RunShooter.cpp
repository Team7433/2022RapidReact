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
  
}

// Called repeatedly when this Command is scheduled to run
void RunShooter::Execute() {
  // double currentVel = m_shooter->getVelocity();
  // double currentVelError = m_targetVel - currentVel;

  // double temp = currentVelError / m_velocityRamp;

  // double futureVel = currentVel + temp;

  

  currentVel = m_shooter->getTargetVelocity();

  velError = m_targetVel - currentVel;

  if (velError <= m_velocityRamp) {
    futureVel = m_targetVel;
    frc::SmartDashboard::PutNumber("shooter/if ", 1);

  }
  else {
     futureVel = currentVel + m_velocityRamp;
     frc::SmartDashboard::PutNumber("shooter/else ", 1);
  }

  futureVel = futureVel + kFCalc * futureVel;
  
  m_shooter->setVelocity(futureVel);

  
  frc::SmartDashboard::PutNumber("shooter/target vel", m_targetVel);
  frc::SmartDashboard::PutNumber("shooter/future vel", futureVel);
  frc::SmartDashboard::PutNumber("shooter/vel error", velError);

}

// Called once the command ends or is interrupted.
void RunShooter::End(bool interrupted) {}

// Returns true when the command should end.
bool RunShooter::IsFinished() {
  return false;
}
