// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TurnToTarget.h"
#include <iostream>


TurnToTarget::TurnToTarget(Vision * vision, SwerveDriveTrain * swerve) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({vision, swerve});
  m_vision = vision;
  m_swerve = swerve;
  
}

// Called when the command is initially scheduled.
void TurnToTarget::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TurnToTarget::Execute() {
  double P = 0.05; // sort of a PID loop, proportional control constant to map the error to an adjustment in the steering control
  minimum_command = 0.05; // the minimum amount to actually rotate the bot, so it doesnt freak out at very small offsets
  
  if (m_vision->getTargetOffsetX() != 0.0){
    x_error = m_vision->getTargetOffsetX();
    double rotate;

    
    rotate = x_error*P;
     std::cout<< "RUNNING " << rotate << std::endl; 

    m_swerve->Drive(0, 0, rotate);

  }

  


}

// Called once the command ends or is interrupted.
void TurnToTarget::End(bool interrupted) {}

// Returns true when the command should end.
bool TurnToTarget::IsFinished() {
 return fabs(x_error) < minimum_command;
}
