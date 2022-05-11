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
    if (m_rollerMotor->GetSelectedSensorVelocity() > m_maxRollerVel){ // balls
        m_maxRollerVel = m_rollerMotor->GetSelectedSensorVelocity();
    }

    frc::SmartDashboard::PutNumber("Shooter/Shooter/MaxVel", m_maxShooterVel);
    frc::SmartDashboard::PutNumber("Shooter/Roller/MaxVel", m_maxRollerVel);
    }
DualShooter::DualShooter() {
    PIDInit();
    m_maxShooterVel = m_shooterMotor->GetSelectedSensorVelocity();
    m_maxRollerVel = m_rollerMotor->GetSelectedSensorVelocity();
    }

void DualShooter::PIDInit() {
    m_shooterMotor->Config_kP(0, m_pidShooter["kP"], kTimeOutMS);
    m_shooterMotor->Config_kI(0, m_pidShooter["kI"], kTimeOutMS);
    m_shooterMotor->Config_kD(0, m_pidShooter["kD"], kTimeOutMS);

    m_rollerMotor->Config_kP(0, m_pidRoller["kP"], kTimeOutMS);
    m_rollerMotor->Config_kI(0, m_pidRoller["kI"], kTimeOutMS);
    m_rollerMotor->Config_kD(0, m_pidRoller["kD"], kTimeOutMS); // cpp dictionary lmao

}

void DualShooter::UpdateSD() {
    if (m_rollerMotor->GetControlMode() == ControlMode::Velocity){
    frc::SmartDashboard::PutNumber("DualShooter/Roller/Velocity", GetRollerVel());
    frc::SmartDashboard::PutNumber("DualShooter/Roller/ClosedLoopError", m_rollerMotor->GetClosedLoopError());
    
    }
    if (m_shooterMotor->GetControlMode() == ControlMode::Velocity){
        frc::SmartDashboard::PutNumber("DualShooter/Shooter/Velocity", GetShooterVel());
        frc::SmartDashboard::PutNumber("DualShooter/Shooter/ClosedLoopError", m_rollerMotor->GetClosedLoopError());
    }
}
