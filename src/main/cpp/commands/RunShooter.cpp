// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RunShooter.h"


using namespace ShooterConstants;
RunShooter::RunShooter(Shooter* shooter, double targetVelocity, double velocityRamp, bool moveHood, std::function<double()> hoodPos) : RunShooter(shooter, [targetVelocity]{return targetVelocity;}, velocityRamp, moveHood, hoodPos) {}


RunShooter::RunShooter(Shooter* shooter, std::function<double()> targetVelocity, double velocityRamp, bool moveHood, std::function<double()> hoodPos) {

  AddRequirements({shooter});
  m_shooter = shooter;
  m_targetVel = targetVelocity;
  m_velocityRamp = velocityRamp;
  m_moveHood = moveHood;
  m_hoodPos = hoodPos;

  

}


// Called when the command is initially scheduled.
void RunShooter::Initialize() {
  std::cout << "runshooter: " << m_targetVel() << std::endl;

  
  m_shooter->m_rampTarget = m_targetVel();
  if (m_shooter->getTargetVelocity() != m_targetVel()) {
    m_direction = -(m_shooter->getTargetVelocity()-m_targetVel())/fabs(m_shooter->getTargetVelocity()-m_targetVel());
  } else {
    m_done = true;
  }

}

// Called repeatedly when this Command is scheduled to run
void RunShooter::Execute() {

  // if (m_moveHood) {
  //   m_shooter->setHoodPosition(m_hoodPos());
  // }
  if(m_shooter->getTargetVelocity() != m_targetVel()) {
    currentVel = m_shooter->getTargetVelocity();

    if (currentVel*m_direction > m_targetVel()*m_direction && m_done == false) {
      m_shooter->setVelocity(m_targetVel());
      m_done=true;
    } else {
      m_shooter->setVelocity((currentVel+(m_velocityRamp*m_direction)));
    }

  }


}

// Called once the command ends or is interrupted.
void RunShooter::End(bool interrupted) {
  m_shooter->setVelocity(m_targetVel());
  m_done=false;
}

// Returns true when the command should end.
bool RunShooter::IsFinished() {
  return m_done;
}
