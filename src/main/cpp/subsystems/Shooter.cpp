// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Shooter.h"
#include <iostream>
#include "Constants.h"

using namespace ShooterConstants;
Shooter::Shooter() {
    m_motor->ConfigFactoryDefault();
    m_motorS->ConfigFactoryDefault();
    m_motorS->SetInverted(true);
    m_motorS->Follow(*m_motor, ctre::phoenix::motorcontrol::FollowerType::FollowerType_PercentOutput);

    ConfigPID(0.3, 0, 0.0);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {
    if (m_motor->GetControlMode() == ControlMode::Velocity) {
        frc::SmartDashboard::PutString("shooter/controlmode", "velocity");
        frc::SmartDashboard::PutNumber("shooter/vel", getVelocity());
        
    } else {
        frc::SmartDashboard::PutString("shooter/controlmode", "not vel");

    }

    
    
}

void Shooter::ConfigPID(double P, double I, double D) {
    m_motor->Config_kP(0, P, kTimeOutMS);
    m_motor->Config_kI(0, I, kTimeOutMS);
    m_motor->Config_kD(0, D, kTimeOutMS);

}

