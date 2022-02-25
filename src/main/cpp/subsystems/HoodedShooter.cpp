// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/HoodedShooter.h"


using namespace HoodedShooterConstants;

HoodedShooter::HoodedShooter(){
    m_motor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, kTimeOutMS);
}

// This method will be called once per scheduler run
void HoodedShooter::Periodic() {
    
}
