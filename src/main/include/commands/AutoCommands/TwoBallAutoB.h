// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ConditionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <frc2/command/ParallelRaceGroup.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <frc2/command/ParallelDeadlineGroup.h>

#include <frc/Timer.h>


#include "subsystems/Intake.h"
#include "subsystems/Magazine.h"
#include "subsystems/Shooter.h"
#include "subsystems/HoodedShooter.h"
#include "subsystems/Gyro.h"
#include "subsystems/Vision.h"
#include "subsystems/SwerveDriveTrain.h"

#include "commands/TurnToTarget.h"
#include "commands/BallAutoIntake.h"
#include "commands/MotionProfile.h"
#include "commands/RunMagazine.h"
#include "commands/ControlShooter.h"
#include "commands/MoveTo.h"





class TwoBallAutoB
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 TwoBallAutoB> {
 public:
  TwoBallAutoB(Intake*, Magazine*, Shooter*, HoodedShooter*, Gyro*, Vision*, SwerveDriveTrain*);
  std::function<double()> m_rampTarget{[]{return 16500;}};
  std::function<double()> m_rampSpeed{[]{return 400.0;}};
  std::function<double()> m_hoodTarget{[]{return 0.0;}};
};
