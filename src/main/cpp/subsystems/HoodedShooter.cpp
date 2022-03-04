// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/HoodedShooter.h"

using namespace ShooterConstants;
HoodedShooter::HoodedShooter(){
    m_hoodmotor->ConfigFactoryDefault();

    ConfigPIDH(k_PID_H["kP"], k_PID_H["kI"], k_PID_H["kD"]);

    m_hoodmotor->Config_kF(0 ,k_PID_H["kF"], kTimeOutMS);
    m_hoodmotor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, kTimeOutMS);
}

// This method will be called once per scheduler run
void HoodedShooter::Periodic() {
    if (m_hoodmotor->GetControlMode() == ControlMode::Position) {

        frc::SmartDashboard::PutString("hood/controlMode", "position");
        frc::SmartDashboard::PutNumber("hood/targetPosition", getHoodTargetPosition());
        frc::SmartDashboard::PutNumber("hood/targetEncoderPos", getHoodEncoderPosition());
    } else {
        frc::SmartDashboard::PutString("hood/controlMode", "not position");
    }
    frc::SmartDashboard::PutNumber("hood/percentageOutput", getHoodPercentageOutput());
}

void HoodedShooter::setHoodPosition(double position) {
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


void HoodedShooter::ConfigPIDH(double P, double I, double D) {
    m_hoodmotor->Config_kP(0, P, kTimeOutMS);
    m_hoodmotor->Config_kI(0, I, kTimeOutMS);
    m_hoodmotor->Config_kD(0, D, kTimeOutMS);
}
