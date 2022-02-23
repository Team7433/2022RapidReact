#pragma once

#include <utils/SwerveModule.h>
#include <AHRS.h>

#include <cmath>
#include <units/angle.h>
#include <units/length.h>

#include <map>
#include <string>

#include <frc/smartdashboard/SmartDashboard.h>

namespace Iona{

    class SwerveDrive{

        public:
            // SwerveDrive(Iona::SwerveModule* topRightModule, Iona::SwerveModule* topLeftModule, Iona::SwerveModule* bottomLeftModule, Iona::SwerveModule* bottomRightModule, double wheelBase, double trackWidth) : m_topRightModule{topRightModule}, m_topLeftModule{topLeftModule}, m_bottomLeftModule{bottomLeftModule}, m_bottomRightModule{bottomRightModule}, kwheelBase{wheelBase}, ktrackWidth{trackWidth} {}
            SwerveDrive(Iona::SwerveModule* topRightModule, Iona::SwerveModule* topLeftModule, Iona::SwerveModule* bottomLeftModule, Iona::SwerveModule* bottomRightModule, double wheelBase, double trackWidth) : m_swerveModules{{"TopRight", topRightModule}, {"TopLeft", topLeftModule}, {"BottomLeft", bottomLeftModule}, {"BottomRight", bottomRightModule}}, kwheelBase{wheelBase}, ktrackWidth{trackWidth} {}
            void Drive(double forward, double strafe, double rotate, units::degree_t gyroAngle, bool invertHeading= false, bool invertRotation=false , bool squaredInputs=false, bool velocityMode=false, bool squareRotation=false);
            void DisplayData();

        private:

            //Swerve Modules
            // Iona::SwerveModule* m_topRightModule;
            // Iona::SwerveModule* m_topLeftModule;
            // Iona::SwerveModule* m_bottomLeftModule;
            // Iona::SwerveModule* m_bottomRightModule;

            std::map<std::string, Iona::SwerveModule*> m_swerveModules;

            //robot size
            const double kwheelBase{};
            const double ktrackWidth{};
            const double kradius{sqrt(pow(kwheelBase, 2.0) + pow(ktrackWidth, 2.0))};

            //constants
            const double kPi = 3.14159265359;

            //constants for swerve math
            double A{0.0};
            double B{0.0};
            double C{0.0};
            double D{0.0};

            //Angle and Output variables
            std::map<std::string, double> outputs{{"TopRight", 0.0}, {"TopLeft", 0.0}, {"BottomLeft", 0.0}, {"BottomRight", 0.0}};
            std::map<std::string, units::degree_t> angles{{"TopRight", 0_deg}, {"TopLeft", 0_deg}, {"BottomLeft", 0_deg}, {"BottomRight", 0_deg}};

            //field centric forward and strafe
            double FWD{0.0};
            double STR{0.0};

            //gyro angle
            units::degree_t currentRobotAngle{0.0};

            //velocity control
            double maxVel{1.0};




    }; //SwerveDrive
} //namespace