// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Auto/TwoBallAutoB.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
TwoBallAutoB::TwoBallAutoB(Intake * m_intake, Magazine * m_magazine, SwerveDriveTrain * m_swerve, Gyro * m_gyro, Vision * m_vision, DualShooter * m_dualshooter) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());

  frc::Timer* m_timer = new frc::Timer;

  AddCommands(
    frc2::InstantCommand([m_swerve] {m_swerve->ResetOdometry();}),
    MotionProfile(m_swerve, m_gyro, coordinate{1.314_m, 0.008_m, -14.70_deg}),
    frc2::InstantCommand([m_intake] {m_intake->setPercentOutput(0.6);}),
    frc2::ParallelRaceGroup(MotionProfile(m_swerve, m_gyro, coordinate{-2.085_m, -0.0101_m, -14.6_deg})),
    frc2::ParallelDeadlineGroup(frc2::FunctionalCommand([m_timer]{m_timer->Start();}, []{}, [m_timer](bool){m_timer->Stop(); m_timer->Reset();} , [m_vision, m_timer]{return units::math::fabs(m_vision->getTargetOffsetX())<1_deg && m_timer->HasElapsed(3_s);}, {}), RunDualShooter(m_dualshooter, [m_vision]{return m_vision->findVelocity() * kShooterToRoller;}, [m_vision]{return m_vision->findVelocity();}, 300), TurnToTarget(m_swerve, m_gyro, m_vision)),
    frc2::ParallelDeadlineGroup(frc2::FunctionalCommand([m_timer]{m_timer->Start();}, []{}, [m_timer](bool){m_timer->Stop(); m_timer->Reset();}, [m_timer]{return m_timer->HasElapsed(2_s);}, {}), frc2::InstantCommand([m_magazine] {m_magazine->setPercentageOutput(0.5);})),
    frc2::InstantCommand([m_magazine]{m_magazine->setPercentageOutput(0.0);}),
    frc2::InstantCommand([m_intake]{m_intake->setPercentOutput(0.0);}),
    frc2::InstantCommand([m_dualshooter]{m_dualshooter->setDualRoller(0.0);}),
    frc2::InstantCommand([]{std::cout << "TwoBallAutoB Finished\n";})
  );
}
