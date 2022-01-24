#include "utils/SwerveModule.h"

using namespace Iona;

SwerveModule::SwerveModule(WPI_TalonFX* outputMotor, WPI_TalonFX* angleMotor, WPI_CANCoder* angleEncoder, double encoderOffset, double encoderCountsPD, std::string swerveModuleName) : m_outputMotor{outputMotor}, m_angleMotor{angleMotor}, m_angleEncoder{angleEncoder}, m_encoderOffset{encoderOffset}, encoderPerDegree{encoderCountsPD}, m_moduleName{swerveModuleName} {

    //Config Factory Defaults
    m_outputMotor->ConfigFactoryDefault();
    m_angleMotor->ConfigFactoryDefault();

    m_outputMotor->SetNeutralMode(motorcontrol::Brake);

    //init encoder on angle motor
    // m_angleMotor->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, kslotIndex, kTimeoutMs);

    //config PID for angle motor
    m_angleMotor->Config_kP(kslotIndex, m_PID_A["P"], kTimeoutMs);
    m_angleMotor->Config_kI(kslotIndex, m_PID_A["I"], kTimeoutMs);
    m_angleMotor->Config_kD(kslotIndex, m_PID_A["D"], kTimeoutMs);

    //invert encoders
    m_angleMotor->SetSensorPhase(kInvertSensors);

    //confid PID for drive motors
    m_outputMotor->Config_kP(kslotIndex, m_PID_D["P"], kTimeoutMs);
    m_outputMotor->Config_kI(kslotIndex, m_PID_D["I"], kTimeoutMs);
    m_outputMotor->Config_kD(kslotIndex, m_PID_D["D"], kTimeoutMs);
    m_outputMotor->Config_kF(kslotIndex, m_PID_D["F"], kTimeoutMs);


    m_angleMotor->SetSelectedSensorPosition((m_angleEncoder->GetAbsolutePosition() - m_encoderOffset)*encoderPerDegree, kslotIndex, kTimeoutMs);

}

void SwerveModule::setHeadingAngle(units::degree_t headingAngle) {
    //sets error
    units::degree_t error = -headingAngle - units::degree_t(remainder(m_angleMotor->GetSelectedSensorPosition()/encoderPerDegree, 360.0));
    
    //Output Inversion Logic
    m_outputInversion = 1;
    if(fabs(remainder((error.to<double>() + 180.0 ), 360.0 )) < 90) {
        m_outputInversion = -1;
        error = units::degree_t(remainder((error.to<double>() + 180.0), 360.0));
    }

    //Closest Path Logic
    if(units::math::fabs(error) > 180_deg) {
        if (units::math::fabs(error + 360_deg) < 180_deg) {
            error += 360_deg;
        } else {
            error -= 360_deg;
        }
    }
    // sets encoder target
    double encoderTarget = m_angleMotor->GetSelectedSensorPosition() + (error.to<double>() * encoderPerDegree);

    //sets position if output is greater than set deadzone
    if (fabs(getDriveOutput()) > kSetAngleDeadzone) {
        m_angleMotor->Set(ControlMode::Position, encoderTarget);
    }

    frc::SmartDashboard::PutNumber("SwerveDrive/SetAngle/" + m_moduleName, headingAngle.to<double>());
    frc::SmartDashboard::PutNumber("SwerveDrive/AngleError/" + m_moduleName, error.to<double>());
}

void SwerveModule::displayData() {
    //display output and angle on the network table
    frc::SmartDashboard::PutNumber("SwerveDrive/CurrentAngle/" + m_moduleName, getHeadingAngle().to<double>());
    frc::SmartDashboard::PutNumber("SwerveDrive/Output/" + m_moduleName, getDriveOutput());
    frc::SmartDashboard::PutNumber("SwerveDrive/Speed/" + m_moduleName, getModuleState().speed.to<double>());
    if (m_outputMotor->GetControlMode() == ctre::phoenix::motorcontrol::ControlMode::Velocity) {
        frc::SmartDashboard::PutNumber("SwerveDrive/ClosedLoopError/" + m_moduleName, m_outputMotor->GetClosedLoopError());
        frc::SmartDashboard::PutNumber("SwerveDrive/VelocitySet/" + m_moduleName, m_outputMotor->GetClosedLoopTarget());
    }
    if (fabs(m_outputMotor->GetSelectedSensorVelocity()) > frc::SmartDashboard::GetNumber("SwerveDrive/maxVelocityEC/" + m_moduleName, 0.0)) {
        frc::SmartDashboard::PutNumber("SwerveDrive/maxVelocityEC/" + m_moduleName, fabs(m_outputMotor->GetSelectedSensorVelocity()));
        frc::SmartDashboard::PutNumber("SwerveDrive/MaxPOutput/" + m_moduleName, fabs(m_outputMotor->GetMotorOutputPercent()));
    }
}


frc::SwerveModuleState SwerveModule::getModuleState() {
    frc::SwerveModuleState state{};
    state.angle = getHeadingAngle();
    state.speed = units::meters_per_second_t((((m_outputMotor->GetSelectedSensorVelocity()-((m_angleMotor->GetSelectedSensorVelocity()/12.8)*(50/14))))*10)/kencoderPerM);
    return state;
}