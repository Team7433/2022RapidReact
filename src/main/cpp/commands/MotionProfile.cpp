// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/MotionProfile.h"

MotionProfile::MotionProfile(SwerveDriveTrain* drivetrain, Gyro* gyro, coordinate targetCoord) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({gyro, drivetrain});

  m_targetCoord = targetCoord;
  m_driveTrain = drivetrain;
  m_gyro = gyro;
}

// Called when the command is initially scheduled.
void MotionProfile::Initialize() {
  // quandale dingle level coding
  // aughhhh
  //Calculates distance remaining
  std::cout << "Motion Profile Init: " << m_targetCoord.xCoordinate.to<double>() << " yCoord: " << m_targetCoord.yCoordinate.to<double>() << std::endl ;
  m_distanceLeft = units::meter_t(sqrt(pow(m_targetCoord.xCoordinate() - m_driveTrain->getCoordinate().xCoordinate(), 2) + pow(m_targetCoord.yCoordinate() - m_driveTrain->getCoordinate().yCoordinate(), 2)));
  m_Xdirection = (m_targetCoord.xCoordinate() > m_driveTrain->getCoordinate().xCoordinate() ? 1 : -1);
  m_Ydirection = (m_targetCoord.yCoordinate() > m_driveTrain->getCoordinate().yCoordinate() ? 1 : -1);
  m_angleDistance = (m_driveTrain->getCoordinate().angle - m_targetCoord.angle);
  m_angleDirection = (m_angleDistance > 0_deg ? 1 : -1);
  m_angleOutput = 0.0;
  std::cout << "xDIR: " << m_Xdirection << std::endl;
  std::cout << "yDIR: " << m_Ydirection << std::endl;

}

// Called repeatedly when this Command is scheduled to run
void MotionProfile::Execute() {
  m_angleDirection = (m_driveTrain->getCoordinate().angle - m_targetCoord.angle) > 0_deg ? 1 : -1;
  m_distanceLeft = units::meter_t(sqrt(pow(m_targetCoord.xCoordinate() - m_driveTrain->getCoordinate().xCoordinate(), 2) + pow(m_targetCoord.yCoordinate() - m_driveTrain->getCoordinate().yCoordinate(), 2)));
  m_Xdirection = (m_targetCoord.xCoordinate() > m_driveTrain->getCoordinate().xCoordinate() ? 1 : -1);
  m_Ydirection = (m_targetCoord.yCoordinate() > m_driveTrain->getCoordinate().yCoordinate() ? 1 : -1);

  if (m_maxVelocity.to<double>() * m_Xdirection > 0.0) {
    m_newXVelocity = units::math::min(

      m_maxVelocity, 
      units::math::min(
        m_currentXVelocity + units::meters_per_second_t(m_maxAcceleration * 20_ms),
        units::math::sqrt(units::math::pow<2>(m_endVelocity) + (2 * m_maxAcceleration * units::meter_t(units::math::fabs(units::math::fabs(m_driveTrain->getCoordinate().xCoordinate) - units::math::fabs(m_targetCoord.xCoordinate)))))
      )

    );
  } else {
    m_newXVelocity = units::math::max(
      m_maxVelocity * m_Xdirection,
      units::math::max(
        m_currentXVelocity + units::meters_per_second_t(-m_maxAcceleration * 20_ms),
        -units::math::sqrt(units::math::pow<2>(m_endVelocity) + (2 * m_maxAcceleration * units::meter_t(units::math::fabs(units::math::fabs(m_driveTrain->getCoordinate().xCoordinate) - units::math::fabs(m_targetCoord.xCoordinate)))))

      )
    );
      
  }

    if (m_maxVelocity.to<double>() * m_Ydirection > 0.0) {
    m_newYVelocity = units::math::min(
      m_maxVelocity,
      units::math::min(
        m_currentYVelocity + units::meters_per_second_t(m_maxAcceleration * 20_ms),
        units::math::sqrt((units::math::pow<2>(m_endVelocity) + 2 * m_maxAcceleration * units::meter_t( units::math::fabs(units::math::fabs(m_driveTrain->getCoordinate().yCoordinate) - units::math::fabs(m_targetCoord.yCoordinate)))))
      )
    );
  } 
  else {

    m_newYVelocity = units::math::max(
      m_maxVelocity * m_Ydirection,
      units::math::max(

        m_currentYVelocity + units::meters_per_second_t(-m_maxAcceleration * 20_ms),
        -units::math::sqrt(units::math::pow<2>(m_endVelocity) + (2 * m_maxAcceleration * units::meter_t( units::math::fabs(units::math::fabs(m_driveTrain->getCoordinate().yCoordinate) - units::math::fabs(m_targetCoord.yCoordinate)))))

      )
    );  
  }

  m_angleDistanceTravelled = (units::math::fabs(m_angleDistance) - units::math::fabs(m_targetCoord.angle - m_driveTrain->getCoordinate().angle)).to<double>();

  if (m_angleOutput >= 0){
    // m_newAngleOutput = std::min(
    //   sqrt(2 * m_maxDegAccel * units::math::fabs(m_targetCoord.angle - m_driveTrain->getCoordinate().angle).to<double>()),
    //   m_angleOutput + m_maxDegAccel*0.02
    // );
    double maxPossibleVelocity = sqrt(2 * m_maxDegAccel * units::math::fabs(m_targetCoord.angle - m_driveTrain->getCoordinate().angle).to<double>());
    double velWithAccel = m_angleOutput + m_maxDegAccel*0.02;
    if (maxPossibleVelocity > velWithAccel) {
      m_newAngleOutput = velWithAccel;
    } else {
      std::cout << "slowing down \n";
      m_newAngleOutput = maxPossibleVelocity;
    }
  }

  // if (m_angleOutput >= 0){
  //   if (m_angleDistanceTravelled < units::math::fabs(m_angleDistance/2).to<double>()) {
  //     m_newAngleOutput = m_angleOutput + m_maxDegAccel*0.02;
  //     m_angleMaxVel = m_newAngleOutput;
  //   } else {
  //     std::cout << "slowing down \n";
  //     m_newAngleOutput = m_angleOutput - m_maxDegAccel*0.02;
  //   }
  // }


  // if ((units::math::fabs(m_newXVelocity) > 0.2_mps || units::math::fabs(m_newYVelocity) > 0.2_mps) && m_distanceLeft > 0.1_m) {
  //   m_rotateKP = 0.01;
  // } else {m_rotateKP = 0.01;}

  // m_angleOutput = (m_targetCoord.angle() - m_driveTrain->getCoordinate().angle()) * m_rotateKP;

  m_newXVelocity = units::math::fabs(m_newXVelocity) < 0.01_mps ? 0_mps : m_newXVelocity;
  m_newYVelocity = units::math::fabs(m_newYVelocity) < 0.01_mps ? 0_mps : m_newYVelocity;

  m_driveTrain->Drive(m_newXVelocity.to<double>(), -m_newYVelocity.to<double>(), m_newAngleOutput*m_angleDirection*kPi/180, false, true);
  m_angleOutput = m_newAngleOutput;
  m_currentXVelocity = m_newXVelocity;
  m_currentYVelocity = m_newYVelocity;
  // std::cout << m_currentYVelocity << std::endl;
  frc::SmartDashboard::PutNumber("MotionProfile/SetXVelocity", m_newXVelocity.to<double>());
  frc::SmartDashboard::PutNumber("MotionProfile/SetYVelocity", m_newYVelocity.to<double>());
  frc::SmartDashboard::PutNumber("MotionProfile/DistanceLeft", m_distanceLeft.to<double>());
  frc::SmartDashboard::PutNumber("MotionProfile/AngleOutput", m_angleOutput);
  frc::SmartDashboard::PutNumber("MotionProfile/AngleError", units::math::fabs(m_targetCoord.angle - m_driveTrain->getCoordinate().angle).to<double>());
  frc::SmartDashboard::PutNumber("MotionProfile/AngleDistanceTravelled", m_angleDistanceTravelled);
  frc::SmartDashboard::PutNumber("MotionProfile/TargetX", m_targetCoord.xCoordinate());
  frc::SmartDashboard::PutNumber("MotionProfile/TargetY", m_targetCoord.yCoordinate());
  // std::cout << "Motion Profile Running\n";

}

// Called once the command ends or is interrupted.
void MotionProfile::End(bool interrupted) {

  m_driveTrain->Drive(0.0, 0.0, 0.0, 0.0, false);
  m_currentXVelocity = 0.0_mps;
  m_currentYVelocity = 0.0_mps;
  std::cout << "Motion Profile Finished \n";

}

// Returns true when the command should end.
bool MotionProfile::IsFinished() {
  return m_distanceLeft < 1_cm && units::math::fabs(m_targetCoord.angle - m_driveTrain->getCoordinate().angle) < 1_deg;
  return false;
}
