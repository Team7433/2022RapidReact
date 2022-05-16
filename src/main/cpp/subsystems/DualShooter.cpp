// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/DualShooter.h"

// This method will be called once per scheduler run
void DualShooter::Periodic() {
    UpdateSD();
    if (m_shooterMotor->GetSelectedSensorVelocity() > m_maxShooterVel){
        m_maxShooterVel = m_shooterMotor->GetSelectedSensorVelocity();
    }
    if (m_rollerMotor->GetSelectedSensorVelocity() > m_maxRollerVel){ 
        m_maxRollerVel = m_rollerMotor->GetSelectedSensorVelocity();
    }

    frc::SmartDashboard::PutNumber("DualShooter/Shooter/MaxVel", m_maxShooterVel);
    frc::SmartDashboard::PutNumber("DualShooter/Roller/MaxVel", m_maxRollerVel);
    }

void DualShooter::PIDInit() {
    m_shooterMotor->Config_kP(0, m_pidShooter["kP"], kTimeOutMS);
    m_shooterMotor->Config_kI(0, m_pidShooter["kI"], kTimeOutMS);
    m_shooterMotor->Config_kD(0, m_pidShooter["kD"], kTimeOutMS);

    m_rollerMotor->Config_kP(0, m_pidRoller["kP"], kTimeOutMS);
    m_rollerMotor->Config_kI(0, m_pidRoller["kI"], kTimeOutMS);
    m_rollerMotor->Config_kD(0, m_pidRoller["kD"], kTimeOutMS); // cpp dictionary lmao

}


DualShooter::DualShooter() {

    m_shooterMotor->ConfigFactoryDefault();
    m_rollerMotor->ConfigFactoryDefault();

    m_shooterMotor->SetInverted(true);

    m_shooterMotor->ConfigSelectedFeedbackSensor(motorcontrol::FeedbackDevice::IntegratedSensor, 0, kTimeOutMS);
    m_rollerMotor->ConfigSelectedFeedbackSensor(motorcontrol::FeedbackDevice::IntegratedSensor, 0, kTimeOutMS);

    m_shooterMotor->Config_kP(0, 0.2, kTimeOutMS);
    m_shooterMotor->Config_kI(0, 0.0, kTimeOutMS);
    m_shooterMotor->Config_kD(0, 0.0, kTimeOutMS);
    m_shooterMotor->Config_kF(0, (1023.0/21000.0), kTimeOutMS);


    m_rollerMotor->Config_kP(0, 0.2, kTimeOutMS);
    m_rollerMotor->Config_kI(0, 0.0, kTimeOutMS);
    m_rollerMotor->Config_kD(0, 0.0, kTimeOutMS);
    m_rollerMotor->Config_kF(0, (1023.0/21000.0), kTimeOutMS);

    m_maxShooterVel = m_shooterMotor->GetSelectedSensorVelocity();
    m_maxRollerVel = m_rollerMotor->GetSelectedSensorVelocity();
    }



void DualShooter::UpdateSD() {
    // std::cout << "updating SD value\n";
    if (m_rollerMotor->GetControlMode() == ControlMode::Velocity){
    frc::SmartDashboard::PutNumber("DualShooter/Roller/Velocity", GetRollerVel());
    frc::SmartDashboard::PutNumber("DualShooter/Roller/ClosedLoopError", m_rollerMotor->GetClosedLoopError());
    }
    if (m_shooterMotor->GetControlMode() == ControlMode::Velocity){
        frc::SmartDashboard::PutNumber("DualShooter/Shooter/Velocity", GetShooterVel());
        frc::SmartDashboard::PutNumber("DualShooter/Shooter/ClosedLoopError", m_rollerMotor->GetClosedLoopError());
    }
}
