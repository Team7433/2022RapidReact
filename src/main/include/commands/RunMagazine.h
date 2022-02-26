// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>


#include "subsystems/Magazine.h"

#include <functional>
/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class RunMagazine
    : public frc2::CommandHelper<frc2::CommandBase, RunMagazine> {
 public:
  RunMagazine(Magazine*, double ouput, std::function<bool()> shooterUpToSpeed);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;


  private:
  Magazine* m_magazine;
  double m_output;
  std::function<bool()> m_shooterUpToSpeed;
};
