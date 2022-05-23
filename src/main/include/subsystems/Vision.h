// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableValue.h"
#include "wpi/span.h"
#include "Constants.h"
#include "units/angle.h"
#include "units/math.h"

using namespace VisionConstants;
class Vision : public frc2::SubsystemBase {
 public:
  Vision();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  units::degree_t getTargetOffsetX(){ return units::degree_t(m_currentTx);}
  units::degree_t getTargetOffsetY() {return units::degree_t(table->GetNumber("ty", 1.0));}
  units::degree_t getTargetArea() {return units::degree_t(table->GetNumber("ta",0.0));}
  units::degree_t getTargetSkew() {return units::degree_t(table->GetNumber("ts", 0.0));}
  units::meter_t getTargetDistance() {return (kTowerHeight-kLimelightHeight)/units::math::tan(kLimelightOffsetAngle+getTargetOffsetY());} // 1 goal off ground dist, 2 limelight off ground dist, 3 limelight angle from vertical
  double getTargetDistanceNum() {return getTargetDistance().to<double>();}
  bool getTargetVisible() {return table->GetNumber("tv", 0.0);}
  bool getTXUpToDate() {return m_txUpToDate;}


 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  double m_oldTx{0.0};
  double m_currentTx{0.0};
  bool m_txUpToDate{true};




  
};
