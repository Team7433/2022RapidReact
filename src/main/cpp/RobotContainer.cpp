// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
// a commmit
// hi david if you see this in the future i am dead


#include "RobotContainer.h"


RobotContainer::RobotContainer() : m_swerveDriveTrain{&m_gyro} {
  // Initialize all of your commands and subsystems here
  m_swerveDriveTrain.SetDefaultCommand(DriveWithJoystick(&m_swerveDriveTrain, &m_gyro, &m_controller, &m_joystick));
  
  frc::SmartDashboard::PutData(&m_autoChooser);
  m_autoChooser.AddOption("NoAuto", 0);
  m_autoChooser.AddOption("AutoA2", 1);
  m_autoChooser.AddOption("AutoB2", 2);

  // Configure the button bindings
  ConfigureButtonBindings();
}
    
void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
    
  // frc2::JoystickButton(&m_controller, 1).WhileHeld(
  //   frc2::InstantCommand([this] {m_controller.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 1); m_swerveDriveTrain.ResetGyro();})
  // );
  frc2::JoystickButton(&m_controller, 1).WhenPressed(
    frc2::InstantCommand([this] {m_swerveDriveTrain.ResetGyro();})
  );
  frc2::JoystickButton(&m_joystick, 5).WhenPressed(
    frc2::InstantCommand([this] {m_swerveDriveTrain.ResetGyro();})
  );

  frc2::JoystickButton(&m_controller, 1).WhenReleased(frc2::InstantCommand([this] {m_controller.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 0);}));
  frc2::JoystickButton(&m_controller, 2).WhenPressed(
    frc2::InstantCommand([this] {m_swerveDriveTrain.ResetOdometry();})
  );

  // frc2::JoystickButton(&m_controller, 3).WhenPressed(MotionProfile(&m_swerveDriveTrain, &m_gyro, coordinate{0.0_m, 0.0_m, 0.0_deg}));



  


 //frc2::JoystickButton(&m_controller, 6).WhileHeld(BallAutoIntake(&m_magazine, &m_intake));



 //  frc2::JoystickButton(&m_controller, 6).WhenPressed(RunDualShooter(&m_dualshooter, 1000, 1000, 10)); // we can add ratios in the command or make instant command
  // to do the stuff for ratios and speed

  frc2::JoystickButton(&m_controller, 6).WhenPressed(frc2::InstantCommand([this]{
    m_dualshooter.setDualRoller(0.0);
  }));

  frc2::JoystickButton(&m_controller, 5).WhenPressed(frc2::InstantCommand([this]{
    m_dualshooter.setDualRoller(0.2);
  }));

  // frc2::JoystickButton(&m_controller, 7).ToggleWhenPressed(ClimbMode(&m_climb, [this] {return m_controller.GetLeftY(); }, [this] {return m_controller.GetRightY(); } ) );






  // frc2::JoystickButton(&m_joystick, 2).WhileHeld(RunMagazine(&m_magazine, 0.6);

  // frc2::JoystickButton(&m_joystick, 2).WhenPressed(frc2::InstantCommand([this]{
  //   m_controller.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 1);
  //   m_controller.SetRumble(frc::GenericHID::RumbleType::kRightRumble, 1);
  // }));

  // frc2::JoystickButton(&m_joystick, 2).WhenReleased(frc2::InstantCommand([this]{
  //   m_controller.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 0);
  //   m_controller.SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0);
  // }));
  
  frc2::POVButton(&m_controller, 180).WhileHeld(ReverseIntake(&m_intake));

}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous


  // switch (m_autoChooser.GetSelected()) {
  //   case 0: return nullptr;
  //   break;
  //   case 1: return new TwoBallAutoA(&m_intake, &m_magazine, &m_shooter, &m_hoodedShooter, &m_gyro, &m_vision, &m_swerveDriveTrain);
  //   break;
  //   case 2: return  new TwoBallAutoB(&m_intake, &m_magazine, &m_shooter, &m_hoodedShooter, &m_gyro, &m_vision, &m_swerveDriveTrain);
      
  // };
  return nullptr;
}
