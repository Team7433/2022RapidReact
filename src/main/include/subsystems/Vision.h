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


class Vision : public frc2::SubsystemBase {
 public:
  Vision();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  double getTargetOffsetX(){return table->GetNumber("tx", 0.0);}
  double getTargetOffsetY() {return table->GetNumber("ty",0.0);}
  double getTargetArea() {return table->GetNumber("ta",0.0);}
  double getTargetSkew() {return table->GetNumber("ts", 0.0);}
  double getTargetVisible() {return table->GetNumber("tv", 0.0);}


 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

  
};
