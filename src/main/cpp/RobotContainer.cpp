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

  frc2::JoystickButton(&m_controller, 4).WhenPressed(RunDualShooter(&m_dualshooter, [this]{
    double setVel = m_vision.findVelocity() * kShooterToRoller;
    frc::SmartDashboard::PutNumber("Vision/AutoRollVel", setVel);
    frc::SmartDashboard::PutNumber("Vision/ActualRollVel", m_dualshooter.GetRollerVel());
    return setVel;
    
    }, [this]{
      double setVel = m_vision.findVelocity();
      frc::SmartDashboard::PutNumber("Vision/AutoShootVel", setVel);
      frc::SmartDashboard::PutNumber("Vision/ActualShootVel", m_dualshooter.GetShooterVel());
      return setVel;
      }, 300)); // run the shooter

  // frc2::JoystickButton(&m_controller, 4).WhenPressed(RunDualShooter(&m_dualshooter, []{return 12500;}, []{return 12500 * kShooterToRoller;}, 300));

  frc2::JoystickButton(&m_controller, 4).WhenReleased(frc2::InstantCommand([this]{
    m_dualshooter.setDualRoller(0.0);
  }));
  frc2::JoystickButton(&m_joystick, 5).WhenPressed(
    frc2::InstantCommand([this] {m_swerveDriveTrain.ResetGyro();}) // reset gyro for swerve
  );

  frc2::JoystickButton(&m_controller, 5).WhileHeld(RunMagazine(&m_magazine, 0.6, []{return true;})); // run magazine


//  frc2::JoystickButton(&m_controller, 6).WhileHeld(BallAutoIntake(&m_magazine, &m_intake)); // intake balls

frc2::JoystickButton(&m_controller, 6).WhenPressed(frc2::InstantCommand([this]{
  m_intake.setPercentOutput(0.6);
}));

frc2::JoystickButton(&m_controller, 6).WhenReleased(frc2::InstantCommand([this]{
  m_intake.setPercentOutput(0.0);
}));

// frc2::JoystickButton(&m_joystick, 1).WhenPressed(TurnToTarget(&m_swerveDriveTrain, &m_gyro, &m_vision));

frc2::JoystickButton(&m_joystick, 1).ToggleWhenPressed(AutoTarget(&m_swerveDriveTrain, &m_gyro, &m_vision, &m_joystick, &m_controller));



  // frc2::JoystickButton(&m_controller, 7).ToggleWhenPressed(ClimbMode(&m_climb, [this] {return m_controller.GetLeftY(); }, [this] {return m_controller.GetRightY(); } ) );
  // TODO climb
  
  frc2::POVButton(&m_controller, 270).WhenPressed(frc2::InstantCommand([this]{
    m_climb.setPercentageOutput(0.6);
  }));

  frc2::POVButton(&m_controller, 270).WhenReleased(frc2::InstantCommand([this]{
    m_climb.setPercentageOutput(0.0);
  }));

  frc2::POVButton(&m_controller, 0).WhenPressed(frc2::InstantCommand([this]{
    m_climb.setPercentageOutput(-0.4);
  }));

  frc2::POVButton(&m_controller, 0).WhenReleased(frc2::InstantCommand([this]{
    m_climb.setPercentageOutput(0.0);
  }));

  // frc2::POVButton(&m_controller, 180).WhenPressed(frc2::InstantCommand([this]{
  //   m_climb.setPercentageOutput(0.1);
  // }));

  // frc2::POVButton(&m_controller, 180).WhenReleased(frc2::InstantCommand([this]{
  //   m_climb.setPercentageOutput(0.0);
  // }));
  
  // frc2::POVButton(&m_controller, 180).WhileHeld(ReverseIntake(&m_intake)); // reverse the intake if stuck balls

  frc2::POVButton(&m_controller, 180).WhenPressed(frc2::InstantCommand([this]{
    m_climb.setRelease(1);
  }));



}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous


  switch (m_autoChooser.GetSelected()) {
    case 0: return nullptr;
    break;
    case 1: return new TwoBallAutoA(&m_intake, &m_magazine, &m_swerveDriveTrain, &m_gyro, &m_vision, &m_dualshooter);
    break;
    case 2: return new OneBallAutoA(&m_magazine, &m_swerveDriveTrain, &m_gyro, &m_vision, &m_dualshooter);
      
  };
  return nullptr;
}
