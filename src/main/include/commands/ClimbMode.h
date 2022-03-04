// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/Climb.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ClimbMode
    : public frc2::CommandHelper<frc2::CommandBase, ClimbMode> {
  public:
    ClimbMode(Climb * climb, std::function<double()> leftSpeed, std::function<double()> rightSpeed);

    void Initialize() override;

    void Execute() override;

    void End(bool interrupted) override;

    bool IsFinished() override;
  private:

    Climb * m_climb;
    std::function<double()> m_leftSpeed;
    std::function<double()> m_rightSpeed;
};
