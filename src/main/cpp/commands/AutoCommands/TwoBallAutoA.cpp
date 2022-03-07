// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoCommands/TwoBallAutoA.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
TwoBallAutoA::TwoBallAutoA(Intake* intake, Magazine* magazine, Shooter* shooter, HoodedShooter* hoodedShooter, Gyro* gyro, Vision* vision, SwerveDriveTrain* swerveDrive) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());

  // AddCommands(
  //   frc2::ParallelRaceGroup(BallAutoIntake(magazine, intake), MotionProfile(swerveDrive, gyro, coordinate{0.0_m, 0.0_m, 0.0_deg})),
  //   frc2::ParallelDeadlineGroup(frc2::FunctionalCommand([]{}, []{}, [](bool){}, [vision]{return vision->getTargetOffsetX()>1_deg ;}, {}), ControlShooter(shooter, hoodedShooter, &m_rampTarget, &m_rampSpeed, &m_hoodTarget), TurnToTarget(swerveDrive, gyro, vision))
  // );
}
