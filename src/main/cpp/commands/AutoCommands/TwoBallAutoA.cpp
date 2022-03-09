// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoCommands/TwoBallAutoA.h"
#include <units/math.h>

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
TwoBallAutoA::TwoBallAutoA(Intake* intake, Magazine* magazine, Shooter* shooter, HoodedShooter* hoodedShooter, Gyro* gyro, Vision* vision, SwerveDriveTrain* swerveDrive) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  frc::Timer* m_timer = new frc::Timer;

  AddCommands(
    frc2::InstantCommand([swerveDrive] {swerveDrive->ResetOdometry();}),
    frc2::ParallelRaceGroup(BallAutoIntake(magazine, intake), MotionProfile(swerveDrive, gyro, coordinate{1_m, 0.0_m, 0.0_deg})),
    // frc2::ParallelDeadlineGroup(frc2::FunctionalCommand([m_timer]{m_timer->Start();}, []{}, [m_timer](bool){m_timer->Stop(); m_timer->Reset();}, [vision, m_timer]{return units::math::fabs(vision->getTargetOffsetX())>1_deg && m_timer->HasElapsed(2_s);}, {}), ControlShooter(shooter, hoodedShooter, &m_rampTarget, &m_rampSpeed, &m_hoodTarget), TurnToTarget(swerveDrive, gyro, vision)),
    // frc2::ParallelDeadlineGroup(frc2::FunctionalCommand([m_timer]{m_timer->Start();}, []{}, [m_timer](bool){m_timer->Stop(); m_timer->Reset();}, [m_timer]{return m_timer->HasElapsed(2_s);}, {}), RunMagazine(magazine, 0.6, []{return true;})),
    // frc2::InstantCommand([magazine]{magazine->setPercentageOutput(0.0);})
    frc2::InstantCommand([]{std::cout << "TwoBallAutoFinished\n";})
  );
}
