#include "MotionProfile.h"


template <class velocity, class acceleration, class distance>
void Iona::MotionProfile<velocity, acceleration, distance>::SetProfile(velocity maxVel, velocity endVel, acceleration accel, distance targetDistance, units::millisecond_t timeSteps, bool invertDirection) {

    m_maxVelocity = maxVel;
    m_endVelocity = endVel;
    m_acceleration = accel;
    m_targetDistance = targetDistance;
    m_timesteps = timeSteps;
    m_invertDirection = invertDirection;

}

template <class velocity, class acceleration, class distance>
velocity Iona::MotionProfile<velocity, acceleration, distance>::Update(distance currentDistance) {

    m_direction = m_targetDistance > currentDistance ? 1 : -1;
    m_direction = m_invertDirection ? m_direction*-1 : m_direction;

    distance distanceRemaining{m_targetDistance - currentDistance};

    m_newVelocity = units::math::min(

        m_maxVelocity,
        units::math::min(
            m_currentVelocity + m_acceleration * m_timesteps,
            units::math::sqrt(units::math::pow<2>(m_endVelocity) + 2 * m_acceleration * units::math::fabs(distanceRemaining))
        )
    );
    m_currentVelocity = m_newVelocity;
    return m_newVelocity*m_direction;
}

template <class velocity, class acceleration, class distance>
velocity Iona::MotionProfile<velocity, acceleration, distance>::GetVelocity() {
    return m_newVelocity*m_direction;
}






// void MotionProfile::SetProfile(units::meters_per_second_t maxVel, units::meters_per_second_t endVel, units::meters_per_second_squared_t accel) {

//     m_maxVelocity = maxVel;
//     m_endVelocity = endVel;
//     m_acceleration = accel;
//     m_angleMode = false;

// }

// void MotionProfile::SetProfile(units::radians_per_second_t maxVel, units::radians_per_second_t endVel, units::radians_per_second_squared_t accel) {

//     m_maxVelocityA = maxVel;
//     m_endVelocityA = endVel;
//     m_accelerationA = accel;
//     m_angleMode = true;

// }

// units::radians_per_second_t MotionProfile::Update(int direction, units::degree_t angleRemaining) {
//     m_direction = direction;
//     m_newOutputA = units::math::min(
//         m_maxVelocityA,
//         units::math::min(

//             m_outputA + units::radians_per_second_t(m_accelerationA * 20_ms),
//             units::math::sqrt(units::math::pow<2>(m_endVelocityA) + 2 * m_accelerationA * units::math::fabs(angleRemaining))

//         )
//     );

//     m_outputA = m_newOutputA;
//     return m_newOutputA * m_direction;

// }

// units::meters_per_second_t MotionProfile::Update(int direction, units::meter_t distanceRemaining) {
//     m_direction = direction;
//     m_newOutput = units::math::min(
//         m_maxVelocity,
//         units::math::min(
            
//             m_output + units::meters_per_second_t(m_acceleration * 20_ms),
//             units::math::sqrt(units::math::pow<2>(m_endVelocity) + 2 * m_acceleration * units::math::fabs(distanceRemaining))

//         )
//     );

//     m_output = m_newOutput;
//     return m_newOutput * m_direction;

// }

// double MotionProfile::GetOutput() {

//     return (m_angleMode ? m_newOutputA.to<double>()*m_direction : m_newOutput.to<double>()*m_direction);

// }
