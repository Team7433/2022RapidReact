// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Vision.h"

Vision::Vision() = default;

// This method will be called once per scheduler run
void Vision::Periodic() {
    frc::SmartDashboard::PutNumber("Vision/Distance", getTargetDistance().to<double>());
    m_currentTx = table->GetNumber("tx", 0.0);
    m_txUpToDate = !(m_currentTx==m_oldTx);
    m_oldTx = m_currentTx;

}
// nvm