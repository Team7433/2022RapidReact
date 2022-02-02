// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() : m_swerveDriveTrain{&m_gyro} {
  // Initialize all of your commands and subsystems here
  m_swerveDriveTrain.SetDefaultCommand(DriveWithJoystick(&m_swerveDriveTrain, &m_gyro, &m_controller, &m_joystick));
  // m_shooter.SetDefaultCommand(RunShooter(&m_shooter, 10))


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


  // frc2::JoystickButton(&m_controller, 4).WhenPressed(RunShooter(&m_shooter, 20000.0, 100));

  frc2::JoystickButton(&m_controller, 4).WhenPressed(frc2::InstantCommand([this] {

    if (m_shooter.getPercentOutput() == 0.0){
    m_shooter.setPercentOutput(1.0); // run the shooter
    }
    else {
      m_shooter.setPercentOutput(0.0);
    }
  }));

  frc2::JoystickButton(&m_controller, 5).WhenPressed(frc2::InstantCommand( [this] {
    if (m_intake.getPercentOutput() == 0.0){
      m_intake.setPercentOutput(-0.5);
    }
    else {                                    // run the intake
      m_intake.setPercentOutput(0);
    }
  }));

  // frc2::JoystickButton(&m_controller, 7).WhenPressed(frc2::InstantCommand([this] {m_shooter.setPercentOutput(0.0); }, {&m_shooter})); // stop the shooter
  
  frc2::JoystickButton(&m_controller, 6).WhenPressed(frc2::InstantCommand([this]{

    if (m_magazine.getPercentageOutput() == 0) {
      m_magazine.setPercentageOutput(-0.3);
    } 
    else {
      m_magazine.setPercentageOutput(0.0);
    }

  }));

};
    
void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return nullptr;
}
