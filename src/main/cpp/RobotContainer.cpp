// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() : m_swerveDriveTrain{&m_gyro} {
  // Initialize all of your commands and subsystems here
  m_swerveDriveTrain.SetDefaultCommand(DriveWithJoystick(&m_swerveDriveTrain, &m_gyro, &m_controller, &m_joystick));


  // Configure the button bindings
  ConfigureButtonBindings();
  
  frc2::JoystickButton(&m_controller, 1).WhileHeld(
    frc2::InstantCommand([this] {m_controller.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 1); m_swerveDriveTrain.ResetGyro();})
  );

  frc2::JoystickButton(&m_controller, 1).WhenReleased(frc2::InstantCommand([this] {m_controller.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 0);}));
  frc2::JoystickButton(&m_controller, 2).WhenPressed(
    frc2::InstantCommand([this] {m_swerveDriveTrain.ResetOdometry();})
  );

  frc2::JoystickButton(&m_controller, 3).WhenPressed(MotionProfile(&m_swerveDriveTrain, &m_gyro, coordinate{0.0_m, 0.0_m, 0.0_deg}));
  frc2::JoystickButton(&m_controller, 4).WhenPressed (frc2::InstantCommand([this] {
    std::cout << "buttonPressed" << std::endl;
    if(m_shooter.getPercentOutput() == 0.0) {
      std::cout << "Shooting" << std::endl;
      m_shooter.setPercentOutput(1);
    } else {
      std::cout << "Unshooting" << std::endl;
      m_shooter.setPercentOutput(0.0);
    }

  }));
  // frc2::JoystickButton(&m_controller, 4).WhenPressed(frc2::InstantCommand([this] {m_shooter.setPercentOutput(0.5);}));
}
void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return nullptr;
}
