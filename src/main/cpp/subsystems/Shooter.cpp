// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Shooter.h"
#include <iostream>

Shooter::Shooter() {
    m_motor->ConfigFactoryDefault();
    m_motorS->ConfigFactoryDefault();
    m_motorS->SetInverted(true);
    m_motorS->Follow(*m_motor, ctre::phoenix::motorcontrol::FollowerType::FollowerType_PercentOutput);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {
    std::cout << getPercentOutput() << std::endl;
}
