// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/HoodedShooter.h"
#include "subsystems/Shooter.h"

#include <functional>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ControlShooter
    : public frc2::CommandHelper<frc2::CommandBase, ControlShooter> {
 public:
  ControlShooter(Shooter*, HoodedShooter*, std::function<double()>* rampTarget, std::function<double()>* rampSpeed, std::function<double()>* hoodTarget);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  double calculateDirection();

 private:
  Shooter* m_shooter;
  HoodedShooter* m_hoodedShooter;
  std::function<double()>* m_rampTarget;
  std::function<double()>* m_rampSpeed;
  std::function<double()>* m_hoodTarget;

  bool m_hasInit{false};

};
