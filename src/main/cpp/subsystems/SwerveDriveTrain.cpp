// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SwerveDriveTrain.h"

// This method will be called once per scheduler run


void SwerveDriveTrain::Periodic() {

    m_swerveDrive->DisplayData();
    m_odometry.Update(-m_gyro->GetYaw(), m_TopLeftModule->getModuleState(), m_TopRightModule->getModuleState(), m_BackLeftModule->getModuleState(), m_BackRightModule->getModuleState());
    frc::SmartDashboard::PutNumber("Odometry/Xcoord", m_odometry.GetPose().X().to<double>());
    frc::SmartDashboard::PutNumber("Odometry/Ycoord", m_odometry.GetPose().Y().to<double>());
    frc::SmartDashboard::PutNumber("Odometry/angle", m_odometry.GetPose().Rotation().Degrees().to<double>());


}

void SwerveDriveTrain::Drive(double forward, double strafe, double rotate, bool squaredInputs, bool velocityMode) {

    m_swerveDrive->Drive(forward, strafe, rotate, m_gyro->GetYaw(), true, false, squaredInputs, velocityMode);

}
 
coordinate SwerveDriveTrain::getCoordinate() {

    coordinate currentCoordinate{{m_odometry.GetPose().X()}, {m_odometry.GetPose().Y()}, {m_odometry.GetPose().Rotation().Degrees()}};
    return currentCoordinate;
}