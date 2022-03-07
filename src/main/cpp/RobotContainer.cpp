// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() : m_swerveDriveTrain{&m_gyro} {
  // Initialize all of your commands and subsystems here
  m_swerveDriveTrain.SetDefaultCommand(DriveWithJoystick(&m_swerveDriveTrain, &m_gyro, &m_controller, &m_joystick));
  m_shooter.SetDefaultCommand(ControlShooter(&m_shooter, &m_hoodedShooter, &m_rampTarget, &m_rampSpeed, &m_hoodTarget));
  
  // m_shooter.SetDefaultCommand(RunShooter(&m_shooter, 10))


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

  frc2::JoystickButton(&m_controller, 1).WhenReleased(frc2::InstantCommand([this] {m_controller.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 0);}));
  // frc2::JoystickButton(&m_controller, 2).WhenPressed(
  //   frc2::InstantCommand([this] {m_swerveDriveTrain.ResetOdometry();})
  // );

  // frc2::JoystickButton(&m_controller, 3).WhenPressed(MotionProfile(&m_swerveDriveTrain, &m_gyro, coordinate{0.0_m, 0.0_m, 0.0_deg}));



  // frc2::JoystickButton(&m_controller, 5).WhenPressed(frc2::ConditionalCommand(
  //   frc2::ParallelCommandGroup(RunShooter(&m_shooter, 0, 400), frc2::InstantCommand([this]{m_isShooting =false;})),
  //   frc2::ParallelCommandGroup(RunShooter(&m_shooter, 19000, 400), frc2::InstantCommand([this]{m_isShooting =true;})),
  //   [this] {return m_isShooting;}

  // ));


  frc2::JoystickButton(&m_controller, 5).WhenPressed(frc2::InstantCommand([this]{

    if (m_rampTarget() == 0.0) {
      m_rampTarget = [this]{return (1304.347826* m_vision.getTargetDistance().to<double>()) + 12469.56522;};
      m_hoodTarget = [this]{return (17.95652* m_vision.getTargetDistance().to<double>()) - 43.09565;};
    } else {
      m_rampTarget = []{return 0.0;};
      m_hoodTarget = []{return 0.0;};
    }

  }));
  


  frc2::JoystickButton(&m_controller, 6).WhileHeld(BallAutoIntake(&m_magazine, &m_intake));



  frc2::JoystickButton(&m_joystick, 4).WhenPressed(frc2::InstantCommand([this] {
    m_counter = m_counter + 200;
    m_rampTarget = [this]{return m_counter;};
  }));

  frc2::JoystickButton(&m_joystick, 6).WhenPressed(frc2::InstantCommand([this] {
    m_counter = m_counter - 200;
    if (m_counter < 200) {
      m_counter = 0;
    }
    m_rampTarget = [this]{return m_counter;};
  }));

  frc2::JoystickButton(&m_controller, 7).ToggleWhenPressed(ClimbMode(&m_climb, [this] {return m_controller.GetLeftY(); }, [this] {return m_controller.GetRightY(); } ) );





  frc2::JoystickButton(&m_joystick, 1).ToggleWhenPressed(AutoTarget(&m_swerveDriveTrain, &m_gyro, &m_vision, &m_joystick, &m_controller));
  frc2::JoystickButton(&m_joystick, 2).WhileHeld(RunMagazine(&m_magazine, 0.6, [this]{return m_shooter.getPercentOutput()!=0.0;}));

  // frc2::JoystickButton(&m_joystick, 2).WhenPressed(frc2::InstantCommand([this]{
  //   m_controller.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 1);
  //   m_controller.SetRumble(frc::GenericHID::RumbleType::kRightRumble, 1);
  // }));

  // frc2::JoystickButton(&m_joystick, 2).WhenReleased(frc2::InstantCommand([this]{
  //   m_controller.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 0);
  //   m_controller.SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0);
  // }));

  frc2::TriggerButton(&m_controller, frc::XboxTriggers::L_trig).WhenPressed(frc2::InstantCommand([this]{m_hoodedShooter.setPercentageOutputHood(0.5);}));
  frc2::TriggerButton(&m_controller, frc::XboxTriggers::L_trig).WhenReleased(frc2::InstantCommand([this]{m_hoodedShooter.setPercentageOutputHood(0.0);}));
  frc2::TriggerButton(&m_controller, frc::XboxTriggers::R_trig).WhenPressed(frc2::InstantCommand([this]{m_hoodedShooter.setPercentageOutputHood(-0.5);}));
  frc2::TriggerButton(&m_controller, frc::XboxTriggers::R_trig).WhenReleased(frc2::InstantCommand([this]{m_hoodedShooter.setPercentageOutputHood(0);}));



  frc2::JoystickButton(&m_joystick, 3).WhenPressed(frc2::SequentialCommandGroup(frc2::SequentialCommandGroup(RunShooter(&m_shooter, 4000, 300), EjectOneBall(&m_magazine, &m_shooter)), RunShooter(&m_shooter, 0, 300)));
  
  frc2::POVButton(&m_controller, 180).WhileHeld(ReverseIntake(&m_intake));

}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return nullptr;
}
