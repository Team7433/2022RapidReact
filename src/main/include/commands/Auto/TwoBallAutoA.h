// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "commands/AutoShooter.h"
#include "commands/BallAutoIntake.h"
#include "commands/MotionProfile.h"
#include "commands/RunMagazine.h"
#include "commands/TurnToTarget.h"

#include "subsystems/Intake.h"
#include "subsystems/Magazine.h"
#include "subsystems/SwerveDriveTrain.h"
#include "subsystems/Gyro.h"
#include "subsystems/Vision.h"
#include "subsystems/DualShooter.h"

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/ParallelDeadlineGroup.h>
#include <frc2/command/ParallelRaceGroup.h>
#include <frc2/command/ConditionalCommand.h>
#include <frc2/command/InstantCommand.h>

class TwoBallAutoA
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 TwoBallAutoA> {
 public:
  TwoBallAutoA(Intake *, Magazine *, SwerveDriveTrain *, Gyro *, Vision *, DualShooter *);
};
