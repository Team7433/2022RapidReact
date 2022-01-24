// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.


#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>

#include <frc2/command/SwerveControllerCommand.h>
#include <utils/SwerveDrive.h>
#include <utils/SwerveModule.h>
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveDriveOdometry.h>

#include "subsystems/Gyro.h"

#include <map>
#include <string>
#include <units/length.h>

struct coordinate {
    units::meter_t xCoordinate;
    units::meter_t yCoordinate;
    units::degree_t angle;
};

class SwerveDriveTrain : public frc2::SubsystemBase {
 public:
  SwerveDriveTrain(Gyro* gyro) : m_gyro{gyro}, m_odometry{m_kinematics, 0_deg, frc::Pose2d{0_m, 0_m, 0_rad}} {}

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void Drive(double forward, double strafe, double rotate, bool squared=false, bool velocityMode=false);
  void ResetGyro() {m_odometry.ResetPosition(m_odometry.GetPose(), -m_gyro->GetYaw()); m_gyro->Reset();}
  void ResetOdometry() {m_odometry.ResetPosition(frc::Pose2d{0_m, 0_m, -m_gyro->GetYaw()}, -m_gyro->GetYaw());}
  coordinate getCoordinate();
 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  // (40 / 48) Gear Ratio
  // 71 Planetary gearbox ratio
  // 28 Encoder counts per motor rotation
  // const double encoderCountPerDegreeOne = ((40.0 / 48.0) * 71.0 * 28.0)/360.0;
  const double encoderCountPerDegreeOne = (2048*12.8)/360.0;

  static double constexpr wheelBase = 548.6;
  static double constexpr trackWidth = 596.9;
  static units::millimeter_t constexpr halveWheelBase= units::millimeter_t(wheelBase/2); 
  static units::millimeter_t constexpr halveTrackWidth= units::millimeter_t(trackWidth/2); 

  Gyro* m_gyro;
  //Init all angle motors
  WPI_TalonFX* m_motorFLA = new WPI_TalonFX{12};
  WPI_TalonFX* m_motorFRA = new WPI_TalonFX{22};
  WPI_TalonFX* m_motorBLA = new WPI_TalonFX{32};
  WPI_TalonFX* m_motorBRA = new WPI_TalonFX{42};
  //Init all drive motors
  WPI_TalonFX* m_motorFLD = new WPI_TalonFX{11};
  WPI_TalonFX* m_motorFRD = new WPI_TalonFX{21};
  WPI_TalonFX* m_motorBLD = new WPI_TalonFX{31};
  WPI_TalonFX* m_motorBRD = new WPI_TalonFX{41};

  //Init all can encoders
  WPI_CANCoder* m_encoderFL = new WPI_CANCoder{13};
  WPI_CANCoder* m_encoderFR = new WPI_CANCoder{23};
  WPI_CANCoder* m_encoderBL = new WPI_CANCoder{33};
  WPI_CANCoder* m_encoderBR = new WPI_CANCoder{43};

  //Encoder Offset Init
  const double m_offsetFL{351.562};
  const double m_offsetFR{248.203};
  const double m_offsetBL{4.482};
  const double m_offsetBR{323.438};

  Iona::SwerveModule* m_TopRightModule = new Iona::SwerveModule{m_motorFRD, m_motorFRA, m_encoderFR, m_offsetFR, encoderCountPerDegreeOne, "TopRight"};
  Iona::SwerveModule* m_TopLeftModule = new Iona::SwerveModule{m_motorFLD, m_motorFLA, m_encoderFL, m_offsetFL, encoderCountPerDegreeOne, "TopLeft"};
  Iona::SwerveModule* m_BackRightModule = new Iona::SwerveModule{m_motorBRD, m_motorBRA, m_encoderBR, m_offsetBR, encoderCountPerDegreeOne, "BottomRight"};
  Iona::SwerveModule* m_BackLeftModule = new Iona::SwerveModule{m_motorBLD, m_motorBLA, m_encoderBL, m_offsetBL, encoderCountPerDegreeOne, "BottomLeft"};

  Iona::SwerveDrive* m_swerveDrive = new Iona::SwerveDrive{m_TopRightModule, m_TopLeftModule, m_BackLeftModule, m_BackRightModule, wheelBase, trackWidth};
  
  std::map<std::string, frc::Translation2d> m_translations{{"TopRight", frc::Translation2d{halveTrackWidth, halveWheelBase}}, {"TopLeft", frc::Translation2d{-halveTrackWidth, halveWheelBase}}, {"BottomLeft", frc::Translation2d{-halveTrackWidth, -halveWheelBase}}, {"BottomRight", frc::Translation2d{halveTrackWidth, -halveWheelBase}}};

  frc::SwerveDriveKinematics<4> m_kinematics{m_translations["TopLeft"], m_translations["TopRight"], m_translations["BottomLeft"], m_translations["BottomRight"]};
  frc::SwerveDriveOdometry<4> m_odometry;
};
