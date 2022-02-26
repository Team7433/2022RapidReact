// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>

#include <frc2/command/button/JoystickButton.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <frc2/command/InstantCommand.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ConditionalCommand.h>
#include <frc2/command/ScheduleCommand.h>

#include "utils/TriggerButton.h"

#include "subsystems/SwerveDriveTrain.h"
#include "subsystems/Gyro.h"
#include "subsystems/Shooter.h"
#include "subsystems/Vision.h"
#include "subsystems/Magazine.h"
#include "subsystems/HoodedShooter.h"
#include "subsystems/Intake.h"


#include "commands/DriveWithJoystick.h"
#include "commands/MoveTo.h"
#include "commands/MotionProfile.h"
#include "commands/RunShooter.h"
#include "commands/AutoTarget.h"
#include "commands/BallAutoIntake.h"

#include <frc/XboxController.h>
#include <frc/Joystick.h>



/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();

 private:
  // The robot's subsystems and commands are defined here...
  SwerveDriveTrain m_swerveDriveTrain;

  Gyro m_gyro;
  Shooter m_shooter;
  Magazine m_magazine;
  Intake m_intake;
  HoodedShooter m_hood;
  Vision m_vision;

  void ConfigureButtonBindings();

  frc::XboxController m_controller{0};
  frc::Joystick m_joystick{1};

  int m_counter = 0;

};
