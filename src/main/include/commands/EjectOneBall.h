// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "commands/RunShooter.h"

#include "subsystems/Shooter.h"
#include "subsystems/Magazine.h"

#include <frc/Timer.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class EjectOneBall
    : public frc2::CommandHelper<frc2::CommandBase, EjectOneBall> {
 public:
  EjectOneBall(Magazine*, Shooter*);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
  frc::Timer m_timer;
  Shooter m_shooter;
  Magazine m_magazine;



};