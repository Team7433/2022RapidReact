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
    m_hoodmotor->ConfigFactoryDefault();
    m_motorS->SetInverted(true);
    m_motorS->Follow(*m_motor, ctre::phoenix::motorcontrol::FollowerType::FollowerType_PercentOutput);

    m_motor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, kTimeOutMS);



    ConfigPID(k_PID_S["kP"], k_PID_S["kI"], k_PID_S["kD"]);
    ConfigPIDH(k_PID_H["kP"], k_PID_H["kI"], k_PID_H["kD"]);
    m_hoodmotor->Config_kF(0 ,k_PID_H["kF"], kTimeOutMS);



    m_motor->Config_kF(0, kFCalc, kTimeOutMS);
    m_motor->ConfigMaxIntegralAccumulator(0, k_maxAccumulator, kTimeOutMS);
    m_motor->Config_IntegralZone(0, k_iZone, kTimeOutMS);
}

// This method will be called once per scheduler run
void Shooter::Periodic() {
    if (m_motor->GetControlMode() == ControlMode::Velocity) {
        frc::SmartDashboard::PutString("shooter/controlmode", "velocity");
        frc::SmartDashboard::PutNumber("shooter/vel", getVelocity());
        frc::SmartDashboard::PutNumber("shooter/targetVel", getTargetVelocity());
        
    } else {
        frc::SmartDashboard::PutString("shooter/controlmode", "not vel");

    }
    if (m_hoodmotor->GetControlMode() == ControlMode::Position) {

        frc::SmartDashboard::PutString("hood/controlMode", "position");
        frc::SmartDashboard::PutNumber("hood/targetPosition", getHoodTargetPosition());
        frc::SmartDashboard::PutNumber("hood/targetEncoderPos", getHoodEncoderPosition());
    } else {
        frc::SmartDashboard::PutString("hood/controlMode", "not position");
    }
    frc::SmartDashboard::PutNumber("hood/percentageOutput", getPercentOutput());
    if (getHoodVelocity() > frc::SmartDashboard::GetNumber("hood/maxVel", 0.0)) {
        frc::SmartDashboard::PutNumber("hood/maxVel", getHoodVelocity());
    }
}

void Shooter::ConfigPID(double P, double I, double D) {
    m_motor->Config_kP(0, P, kTimeOutMS);
    m_motor->Config_kI(0, I, kTimeOutMS);
    m_motor->Config_kD(0, D, kTimeOutMS);
}

void Shooter::ConfigPIDH(double P, double I, double D) {
    m_hoodmotor->Config_kP(0, P, kTimeOutMS);
    m_hoodmotor->Config_kI(0, I, kTimeOutMS);
    m_hoodmotor->Config_kD(0, D, kTimeOutMS);
}

void Shooter::setHoodPosition(double position) {
    //saftey so position is never over 100 or below 0
    position = (position > 100) ? 100 : position;
    position = (position < 0) ? 0 : position;
    m_currentHoodPosition = position;
    //sets target encoder position
    double encoderPosition{(k_hoodMaxEncoder/100)*position};
    //saftey so position is never set to over max encoder;
    if (encoderPosition < 100 && encoderPosition > 0) {
        m_hoodmotor->Set(ControlMode::Position, encoderPosition);
    }
}