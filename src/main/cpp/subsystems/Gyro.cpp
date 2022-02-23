// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Gyro.h"
#include <frc/DriverStation.h>
#include <units/math.h>
#include <frc/Errors.h>
#include <iostream>

Gyro::Gyro() {
    try {
       /* Communicate w/navX-MXP via the MXP SPI Bus.                                       */
       /* Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB */
       /* See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */
        m_gyro = new AHRS(frc::SPI::Port::kMXP);

    } catch (std::exception ex ) {

        std::string err_string = "Error Instantiating navX-MXP: ";
        err_string += ex.what();
        std::cout << err_string.c_str() << std::endl;
    }



    Reset();

}

// This method will be called once per scheduler run
void Gyro::Periodic() {
    frc::SmartDashboard::PutNumber("Gyro/Yaw", GetYaw().to<double>());
    frc::SmartDashboard::PutNumber("Gyro/Roll", GetRoll().to<double>());
    frc::SmartDashboard::PutNumber("Gyro/Pitch", GetPitch().to<double>());
}

units::degree_t Gyro::GetYaw() {
    return units::degree_t( m_gyro->GetYaw() );
}

void Gyro::Reset() {
    // m_gyro->SetYaw(0.0);
    std::cout << "gyro has been reset!!! \n";
    m_gyro->Reset();
}

units::degree_t Gyro::GetPitch() {
    return units::degree_t( m_gyro->GetPitch() );
}

units::degree_t Gyro::GetRoll() {
    return units::degree_t( m_gyro->GetRoll() );
}

units::degree_t Gyro::GetClosestError(units::degree_t target) {

    units::degree_t error = target - GetYaw();

    if (units::math::fabs(error) > 180_deg ) {
        if (units::math::fabs( error + 360_deg ) < 180_deg) {
            return error + 360_deg;

        } else {

            return error - 360_deg;

        }
    }
    return error;


}
