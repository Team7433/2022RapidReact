// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
// a commmit
// hi david if you see this in the future i am dead


#include "RobotContainer.h"


RobotContainer::RobotContainer() : m_swerveDriveTrain{&m_gyro} {
  m_swerveDriveTrain.SetDefaultCommand(DriveWithJoystick(&m_swerveDriveTrain, &m_gyro, &m_controller, &m_joystick));
  
  frc::SmartDashboard::PutData(&m_autoChooser);
  m_autoChooser.AddOption("NoAuto", 0);
  m_autoChooser.AddOption("AutoA2", 1);
  m_autoChooser.AddOption("AutoB2", 2);

  ConfigureButtonBindings();
}
    
void RobotContainer::ConfigureButtonBindings() {

    // frc2::JoystickButton(&m_controller, 1).WhenReleased(frc2::InstantCommand([this] {m_controller.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 0);}));
    
    frc2::JoystickButton(&m_controller, 2).WhenPressed(
    frc2::InstantCommand([this] {m_swerveDriveTrain.ResetOdometry();}) // reset odometry
  );

  // frc2::JoystickButton(&m_controller, 4).WhenPressed(RunDualShooter(&m_dualshooter, []{return 10000;}, []{return 10000;}, 10)); // run the shooter
  // frc2::JoystickButton(&m_controller, 4).WhenReleased(RunDualShooter(&m_dualshooter, []{return 0;}, []{return 0;}, 10)); // stop shooter when button released


  frc2::JoystickButton(&m_controller, 4).WhenPressed(frc2::InstantCommand([this]{
    m_dualshooter.SetRoller(9000);
    m_dualshooter.SetShooter(8500);
  }));

  frc2::JoystickButton(&m_controller, 4).WhenReleased(frc2::InstantCommand([this]{
    m_dualshooter.setDualRoller(0.0);
  }));
  frc2::JoystickButton(&m_joystick, 5).WhenPressed(
    frc2::InstantCommand([this] {m_swerveDriveTrain.ResetGyro();}) // reset gyro for swerve
  );

  frc2::JoystickButton(&m_controller, 5).WhileHeld(RunMagazine(&m_magazine, 0.6, []{return true;})); // run magazine


 frc2::JoystickButton(&m_controller, 6).WhileHeld(BallAutoIntake(&m_magazine, &m_intake)); // intake balls



  



  // frc2::JoystickButton(&m_controller, 7).ToggleWhenPressed(ClimbMode(&m_climb, [this] {return m_controller.GetLeftY(); }, [this] {return m_controller.GetRightY(); } ) );
  // TODO climb



  
  frc2::POVButton(&m_controller, 180).WhileHeld(ReverseIntake(&m_intake)); // reverse the intake if stuck balls

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
