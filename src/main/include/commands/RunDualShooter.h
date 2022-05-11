// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "Constants.h"
#include "subsystems/DualShooter.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class RunDualShooter
    : public frc2::CommandHelper<frc2::CommandBase, RunDualShooter> {
 public:
  RunDualShooter(DualShooter * dualshooter, double rollerTargetVel, double shooterTargetVel, double rampRes);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
 private:
  DualShooter * m_dualshooter;
  double m_rollerTargetVel;
  double m_shooterTargetVel; // stuf

  double m_lastShooterVel;
  double m_lastRollerVel;

  double m_curShooterVel;
  double m_curRollerVel;

  int m_rollerDir;
  int m_shooterDir;

  double m_rampResolution; // what is this variable name

  bool m_done; // track if cmd is done

  double m_tempRollerTarget;
  double m_tempShooterTarget;

};
