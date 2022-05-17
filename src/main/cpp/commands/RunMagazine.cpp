// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RunMagazine.h"

RunMagazine::RunMagazine(Magazine* magazine, double output, std::function<bool()> shooterUpToSpeed) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({magazine});
  m_magazine = magazine;
  m_output = output;
  m_shooterUpToSpeed = shooterUpToSpeed;
}

// Called when the command is initially scheduled.
void RunMagazine::Initialize() {
  std::cout << "RunMagazine\n";
}

// Called repeatedly when this Command is scheduled to run
void RunMagazine::Execute() {

  if (true) {
    m_magazine->setPercentageOutput(m_output);
  } else {
    m_magazine->setPercentageOutput(0.0);
  }

}

// Called once the command ends or is interrupted.
void RunMagazine::End(bool interrupted) {
  m_magazine->setPercentageOutput(0.0);
}

// Returns true when the command should end.
bool RunMagazine::IsFinished() {
  return false;
}
