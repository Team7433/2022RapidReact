// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/HoodedShooter.h"

using namespace ShooterConstants;
HoodedShooter::HoodedShooter(){
    m_hoodmotor->ConfigFactoryDefault();

    ConfigPIDH(k_PID_H["kP"], k_PID_H["kI"], k_PID_H["kD"]);

    m_hoodmotor->Config_kF(0 ,k_PID_H["kF"], HoodedShooterConstants::kTimeOutMS);
    m_hoodmotor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, HoodedShooterConstants::kTimeOutMS);
    m_hoodmotor->ConfigReverseLimitSwitchSource(LimitSwitchSource::LimitSwitchSource_FeedbackConnector, LimitSwitchNormal::LimitSwitchNormal_NormallyClosed, HoodedShooterConstants::kTimeOutMS);

    m_hoodmotor->ConfigMaxIntegralAccumulator(0, k_maxAccumulator, HoodedShooterConstants::kTimeOutMS);
    m_hoodmotor->Config_IntegralZone(0, k_iZone, HoodedShooterConstants::kTimeOutMS);
    // m_hoodmotor->SetInverted(true);
}


// This method will be called once per scheduler run
void HoodedShooter::Periodic() {
    if (m_hoodmotor->GetControlMode() == ControlMode::Position) {

        frc::SmartDashboard::PutString("hood/controlMode", "position");
        frc::SmartDashboard::PutNumber("hood/targetPosition", getHoodTargetPosition());
        frc::SmartDashboard::PutNumber("hood/targetEncoderPos", m_hoodmotor->GetClosedLoopTarget());
        frc::SmartDashboard::PutNumber("hood/error", m_hoodmotor->GetClosedLoopError());
    } else {
        frc::SmartDashboard::PutString("hood/controlMode", "not position");
    }
    frc::SmartDashboard::PutNumber("hood/percentageOutput", getHoodPercentageOutput());
    if (getHoodVelocity() > frc::SmartDashboard::GetNumber("hood/maxVel", 0.0)) {
        frc::SmartDashboard::PutNumber("hood/maxVel", getHoodVelocity());
    }
    frc::SmartDashboard::PutNumber("hood/currentEncoderPos", m_hoodmotor->GetSelectedSensorPosition());
    frc::SmartDashboard::PutBoolean("hood/limitSwitch", hasHoodHitLimit());

    if (hasHoodHitLimit()) {
        resetEncoder();
    }

}

void HoodedShooter::setHoodPosition(double position) {
    //saftey so position is never over 100 or below 0
    position = (position > 100) ? 100 : position;
    position = (position < 0) ? 0 : position;
    m_currentHoodPosition = position;
    //sets target encoder position
    double encoderPosition{(k_hoodMaxEncoder/100)*position};
    std::cout << encoderPosition << std::endl;
    //saftey so position is never set to over max encoder;
    if (encoderPosition < k_hoodMaxEncoder && encoderPosition > 0) {
        m_hoodmotor->Set(ControlMode::Position, encoderPosition);
    }
}


void HoodedShooter::ConfigPIDH(double P, double I, double D) {
    m_hoodmotor->Config_kP(0, P, HoodedShooterConstants::kTimeOutMS);
    m_hoodmotor->Config_kI(0, I, HoodedShooterConstants::kTimeOutMS);
    m_hoodmotor->Config_kD(0, D, HoodedShooterConstants::kTimeOutMS);
}
