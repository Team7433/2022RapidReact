#pragma once

#include <ctre/Phoenix.h>
#include <map>
#include <string>

#include <units/angle.h>
#include <units/velocity.h>
#include <units/math.h>
#include <units/acceleration.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/kinematics/SwerveModuleState.h>

namespace Iona {

    class SwerveModule {
        public:
        // SwerveModule(WPI_TalonFX* outputMotor, WPI_TalonSRX* angleMotor, double encoderCountsPD, std::string swerveModuleName) : m_outputMotor{outputMotor}, m_angleMotor{angleMotor}, encoderPerDegree{encoderCountsPD}, m_moduleName{swerveModuleName} {}
        SwerveModule(WPI_TalonFX* outputMotor, WPI_TalonFX* angleMotor, double encoderCountsPD, std::string swerveModuleName);
        //Set drive output and angle
        void setHeadingAngle(units::degree_t headingAngle);
        void setDriveOutput(double output) {m_outputMotor->Set(ControlMode::PercentOutput, output*m_outputInversion); }
        void setDriveVelocity(double velocity) {if (velocity > 0.001){ m_outputMotor->Set(ControlMode::Velocity, (m_outputInversion*(velocity*kencoderPerM)/10));} else {m_outputMotor->Set(ControlMode::PercentOutput, 0.0);} }
        void setModule(units::degree_t headingAngle, double output, bool velocityMode=false) { setHeadingAngle(headingAngle); if(!velocityMode){setDriveOutput(output);} else {setDriveVelocity(output);} }

        //get drive output and angle
        units::degree_t getHeadingAngle() { return units::degree_t(remainder(m_angleMotor->GetSelectedSensorPosition()/encoderPerDegree, 360)); }
        double getDriveOutput() { return m_outputMotor->GetMotorOutputPercent(); }
        frc::SwerveModuleState getModuleState();
        //display data
        void displayData();

        private:

            //Motors
            WPI_TalonFX* m_outputMotor;
            WPI_TalonFX* m_angleMotor;
            
            //Encoder counts per degree for angle motor
            const double encoderPerDegree{}; 

            //Member Variables
            const std::string m_moduleName{};


            //PID values
            std::map<std::string, double> m_PID_A{{"P", 0.2}, {"I", 0.0}, {"D", 0.1}};
            //calculating kf = (percent output * 1023) / max velocity
            std::map<std::string, double> m_PID_D{{"P", 0.3}, {"I", 0.0}, {"D", 0.0}, {"F", ((0.5*1023.0)/10053.0)}};
            const double kTimeoutMs{10.0};
            const int kslotIndex{0};
            const bool kInvertSensors{true};

            //output variables
            double m_outputInversion{1};

            const double kSetAngleDeadzone{0.05};
            const double kwheelCircumferenceM{0.319185813605};
            
            //12 tooth driven by falcon
            //40 tooth driven by 12 tooth
            //20 tooth driven by 40 tooth
            //40 tooth is driven by 20 tooth
            //wheel is driven by 40 tooth

            const double kencoderPerM{(2048.0*(6.67))/kwheelCircumferenceM};
    }; //Swerve Module
} // namespace 