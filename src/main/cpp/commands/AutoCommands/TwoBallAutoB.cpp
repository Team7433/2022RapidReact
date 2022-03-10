// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoCommands/TwoBallAutoB.h"
#include <units/math.h>

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
TwoBallAutoB::TwoBallAutoB(Intake* intake, Magazine* magazine, Shooter* shooter, HoodedShooter* hoodedShooter, Gyro* gyro, Vision* vision, SwerveDriveTrain* swerveDrive) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  frc::Timer* m_timer = new frc::Timer;

  AddCommands(
    frc2::InstantCommand([swerveDrive] {swerveDrive->ResetOdometry();}),
    MotionProfile(swerveDrive, gyro, coordinate{1.0_m, -0.6_m, -16.0_deg}),
    frc2::InstantCommand([intake] {intake->setPercentOutput(0.6);}),
    frc2::ParallelRaceGroup(MotionProfile(swerveDrive, gyro, coordinate{1.7_m, -1.1_m, -16.0_deg})),
    frc2::ParallelDeadlineGroup(frc2::FunctionalCommand([m_timer]{m_timer->Start();}, []{}, [m_timer](bool){m_timer->Stop(); m_timer->Reset();} , [vision, m_timer]{return units::math::fabs(vision->getTargetOffsetX())<1_deg && m_timer->HasElapsed(1_s);}, {}), ControlShooter(shooter, hoodedShooter, &m_rampTarget, &m_rampSpeed, &m_hoodTarget), TurnToTarget(swerveDrive, gyro, vision)),
    frc2::ParallelDeadlineGroup(frc2::FunctionalCommand([m_timer]{m_timer->Start();}, []{}, [m_timer](bool){m_timer->Stop(); m_timer->Reset();}, [m_timer]{return m_timer->HasElapsed(2_s);}, {}), frc2::InstantCommand([magazine] {magazine->setPercentageOutput(0.3);})),
    frc2::InstantCommand([magazine]{magazine->setPercentageOutput(0.0);}),
    MotionProfile(swerveDrive, gyro, coordinate{1.7_m, 1.5_m, 67.0_deg}),
    MotionProfile(swerveDrive, gyro, coordinate{1.7_m, 1.5_m, 15.0_deg}),
    frc2::ParallelDeadlineGroup(frc2::FunctionalCommand([m_timer]{m_timer->Start();}, []{}, [m_timer](bool){m_timer->Stop(); m_timer->Reset();} , [vision, m_timer]{return m_timer->HasElapsed(1_s);}, {}), ControlShooter(shooter, hoodedShooter, &m_rampTarget, &m_rampSpeed, &m_hoodTarget), TurnToTarget(swerveDrive, gyro, vision)),
    frc2::ParallelDeadlineGroup(frc2::FunctionalCommand([m_timer]{m_timer->Start();}, []{}, [m_timer](bool){m_timer->Stop(); m_timer->Reset();}, [m_timer]{return m_timer->HasElapsed(2_s);}, {}), frc2::InstantCommand([magazine] {magazine->setPercentageOutput(0.3);})),
    frc2::InstantCommand([intake]{intake->setPercentOutput(0.0);}),
    frc2::InstantCommand([magazine]{magazine->setPercentageOutput(0.0);}),
    frc2::InstantCommand([]{std::cout << "TwoBallAutoBFinished\n";})
  );
}
// 