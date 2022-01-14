// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <frc/XboxController.h>
#include <frc/Joystick.h>

#include "subsystems/SwerveDriveTrain.h"
#include "subsystems/Gyro.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class DriveWithJoystick
    : public frc2::CommandHelper<frc2::CommandBase, DriveWithJoystick> {
 public:
  DriveWithJoystick(SwerveDriveTrain* swerveDrivetrain, Gyro* gyro, frc::XboxController* controller, frc::Joystick* joystick);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  frc::XboxController* m_controller;
  frc::Joystick* m_joystick;
  SwerveDriveTrain* m_swerveDriveTrain;
  Gyro* m_gyro;

};
