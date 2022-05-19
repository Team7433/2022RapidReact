// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Auto/TwoBallAutoA.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
TwoBallAutoA::TwoBallAutoA(Intake * m_intake, Magazine * m_magazine, SwerveDriveTrain * m_swerve, Gyro * m_gyro, Vision * m_vision, DualShooter * m_dualshooter) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());

  AddCommands(
    frc2::ParallelDeadlineGroup(
      MotionProfile(m_swerve, m_gyro, coordinate{0.0_m, 0.0_m, 0.0_deg}),
      RunMagazine(m_intake, m_magazine)
    )
  );

}
