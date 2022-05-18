// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "Constants.h"
#include "subsystems/DualShooter.h"
#include "frc/smartdashboard/SmartDashboard.h"

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
  RunDualShooter(DualShooter * dualshooter, std::function<double()> rollerTargetVel, std::function<double()> shooterTargetVel, double rampRes);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
 private:
  DualShooter * m_dualshooter;
  std::function<double()> m_rollerTargetVelFunc;
  std::function<double()> m_shooterTargetVelFunc; // lambda function for the final speed
  
  double m_rollerTargetVel;
  double m_shooterTargetVel;

  double m_rampResolution; // the step of ramping for each iteration

  double currentRollerVel; // vars to track the current velocities
  double currentShooterVel;

  bool m_done = false; // track if cmd is done

  double m_rollerDir; // gets the direction to speed up or down
  double m_shooterDir;

  double tempShooter; // temporary variables to store the speed that the shooters are being set to
  double tempRoller;



};
