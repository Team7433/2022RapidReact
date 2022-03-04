// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Climb.h"

Climb::Climb() = default;

// This method will be called once per scheduler run
void Climb::Periodic() {}



void Climb::SetMotors(double left, double right) {
    m_leftClimb->Set(ControlMode::PercentOutput, left);
    m_rightClimb->Set(ControlMode::PercentOutput, right);
}

void Climb::SetClimbReleased(bool release) {
    m_releaseSolenoid.Set(release);
}