// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/MoveTo.h"

MoveTo::MoveTo(SwerveDriveTrain* DriveTrain, units::meter_t targetX, units::meter_t targetY, units::radian_t targetAngle) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_driveTrain);

  m_driveTrain = DriveTrain;
  
  y_profile.SetTargetDistance(targetY);
  x_profile.SetTargetDistance(targetX);
  angle_profile.SetTargetDistance(targetAngle);


}

// Called when the command is initially scheduled.
void MoveTo::Initialize() {
  std::cout << "Move To Running\n";
  m_distanceToTarget = units::meter_t(sqrt(pow(m_targetX() - m_driveTrain->getCoordinate().xCoordinate(), 2) + pow(m_targetY() - m_driveTrain->getCoordinate().yCoordinate(), 2)));
}

// Called repeatedly when this Command is scheduled to run
void MoveTo::Execute() {

  m_driveTrain->Drive(x_profile.Update(m_driveTrain->getCoordinate().xCoordinate).to<double>(), y_profile.Update(m_driveTrain->getCoordinate().yCoordinate).to<double>(), angle_profile.Update(units::convert<units::deg, units::rad>(m_driveTrain->getCoordinate().angle)).to<double>(), false, true);

}

// Called once the command ends or is interrupted.
void MoveTo::End(bool interrupted) {
  std::cout << "moveTo Ended\n";
}
// Returns true when the command should end.
bool MoveTo::IsFinished() {
  return m_distanceToTarget < 1_cm and units::math::fabs(m_angleTarget - m_driveTrain->getCoordinate().angle) < 1_deg;
}
