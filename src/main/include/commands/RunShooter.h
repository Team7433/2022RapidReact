// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "Constants.h"
#include "subsystems/Shooter.h"
#include <functional>

#include <iostream>


/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class RunShooter
    : public frc2::CommandHelper<frc2::CommandBase, RunShooter> {
 public:
  RunShooter(Shooter* shooter, double targetVelocity, double velocityRamp, bool moveHood=false, std::function<double()> = [](){return 0.0;});
  RunShooter(Shooter*, std::function<double()>, double, bool=false, std::function<double()> = [](){return 0.0;});
  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  Shooter* m_shooter;
  std::function<double()> m_targetVel;
  double m_velocityRamp{0.0};
  double currentVel{0.0};
  double m_direction{0.0};
  bool m_done{false};


  bool m_moveHood;
  std::function<double()> m_hoodPos;

};
