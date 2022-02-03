// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/DriveWithJoystick.h"

DriveWithJoystick::DriveWithJoystick(SwerveDriveTrain* swerveDrivetrain, Gyro* gyro, frc::XboxController* controller, frc::Joystick* joystick) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(swerveDrivetrain);
  m_swerveDriveTrain = swerveDrivetrain;
  m_controller = controller;
  m_joystick = joystick;
  m_gyro = gyro;
}

// Called when the command is initially scheduled.
void DriveWithJoystick::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {

  // double rotate = m_controller->GetX(frc::GenericHID::JoystickHand::kRightHand);
  // double rotate = m_controller->GetRightX();
  double rotate = m_joystick->GetRawAxis(2);

  if (fabs(rotate) < 0.15) {
    rotate = 0;
  }
  // double forward = -m_controller->GetY(frc::GenericHID::JoystickHand::kLeftHand);
  // double forward = -m_controller->GetLeftY();
  double forward = m_joystick->GetRawAxis(1);
  if (fabs(forward) < 0.15) {
    forward = 0;
  }
  // double strafe = m_controller->GetX(frc::GenericHID::JoystickHand::kLeftHand);
  // double strafe = m_controller->GetLeftX();
  double strafe = m_joystick->GetRawAxis(0);
  if (fabs(strafe) < 0.15) {
    strafe = 0;
  }

  m_swerveDriveTrain->Drive(forward*0.8, strafe*0.8, rotate*0.8, true, true);

}

// Called once the command ends or is interrupted.
void DriveWithJoystick::End(bool interrupted) {}

// Returns true when the command should end.
bool DriveWithJoystick::IsFinished() {
  return false;
}
