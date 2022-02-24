// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoTarget.h"

AutoTarget::AutoTarget(SwerveDriveTrain* swerveDriveTrain, Gyro* gyro, Vision* vision, frc::Joystick* joystick) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({swerveDriveTrain});

  m_swerveDrive= swerveDriveTrain;
  m_gyro = gyro;
  m_vision = vision;
  m_joystick = joystick;

}

// Called when the command is initially scheduled.
void AutoTarget::Initialize() {

  if (m_vision->getTargetVisible())
  {
     m_gyroTarget = m_gyro->GetYaw() + m_vision->getTargetOffsetX();
  } else {
    m_done = true;
  }
  

}

// Called repeatedly when this Command is scheduled to run
void AutoTarget::Execute() {

  //sets new gyro target if the vision has been updated
  if(m_vision->getTargetVisible() && m_vision->getTXUpToDate()){
    m_gyroTarget = m_gyro->GetYaw() + m_vision->getTargetOffsetX();
  }

  //sets the error for rotation
  m_error = getCLosestError(m_gyroTarget);

  //KI controller Loop
  if (fabs(m_error.to<double>()) < m_izone) {
    m_accumulator += m_error.to<double>();
  } else {
    m_accumulator = 0.0;
  }
  if (m_accumulator >= m_maxAccumulator) {
    m_accumulator = m_maxAccumulator;
  }
  //rotate output variable
  double rotate{m_error.to<double>()*kPID["kP"] + m_accumulator*kPID["kI"] + kPID["kS"] };
  //driving forward variable
  double forward = m_joystick->GetRawAxis(1);
  if (fabs(forward) < kJoystickForwardDeadZone) {
    forward = 0;
  }
  //strafe variable
  double strafe = -m_joystick->GetRawAxis(0);
  if (fabs(strafe) < kJoystickStrafeDeadZone) {
    strafe = 0;
  }
  std::cout << "error: " << m_error.to<double>() << " output: " << rotate << std::endl;
  //telling swerveDrive Controller to drive with the above outputs
  m_swerveDrive->Drive(forward*kForwardMultiplier, strafe*kStrafeMultiplier, rotate, true, true, false);
}

// Called once the command ends or is interrupted.
void AutoTarget::End(bool interrupted) {
  m_done=false;
}

// Returns true when the command should end.
bool AutoTarget::IsFinished() {
  return m_done;
}

units::degree_t AutoTarget::getCLosestError(units::degree_t targetGyroAngle) {

  targetGyroAngle = getRemappedGyroAngle(targetGyroAngle);

  units::degree_t error{0_deg};
  if (units::math::fabs(targetGyroAngle - m_gyro->GetYaw()) <= 180_deg - units::math::fabs(m_gyro->GetYaw()) + 180_deg - units::math::fabs(targetGyroAngle)) {
    error = targetGyroAngle - m_gyro->GetYaw();

  } else {
    error =  units::math::fabs(180_deg - m_gyro->GetYaw()) + units::math::fabs(180_deg - targetGyroAngle);

  }

  return error;

}

units::degree_t AutoTarget::getRemappedGyroAngle(units::degree_t targetGyroAngle) {

  if (targetGyroAngle <= -180_deg) {
    targetGyroAngle = 180_deg-units::degree_t(remainderf(-(targetGyroAngle.to<double>()), 180));
  } else if (targetGyroAngle >= 180_deg) {
    targetGyroAngle = 180_deg-units::degree_t(remainderf((targetGyroAngle.to<double>()), 180));
  }
  return targetGyroAngle;

}