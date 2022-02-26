// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Magazine.h"

Magazine::Magazine() = default;

// This method will be called once per scheduler run
void Magazine::Periodic() {
    frc::SmartDashboard::PutBoolean("magazine/sensor", isBall());
}
