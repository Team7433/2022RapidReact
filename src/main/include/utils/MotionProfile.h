#pragma once

#include <frc/smartdashboard/SmartDashboard.h>

#include <units/length.h>
#include <units/velocity.h>
#include <units/angle.h>
#include <units/angular_acceleration.h>
#include <units/acceleration.h>
#include <units/time.h>
#include <units/math.h>





namespace Iona{
    
    template <class velocity, class acceleration, class distance>
    class MotionProfile{
        public:
            MotionProfile(velocity maxVel, velocity endVel, acceleration accel, distance targetDistance, units::millisecond_t timeSteps, bool invertDirection = false) : m_maxVelocity{maxVel}, m_endVelocity{endVel}, m_acceleration{accel}, m_targetDistance{targetDistance}, m_timesteps{timeSteps}, m_invertDirection{invertDirection} {}
            void SetProfile(velocity maxVel, velocity endVel, acceleration accel, distance targetDistance, units::millisecond_t timeSteps, bool invertDirection = false);
            void SetTargetDistance(distance targetDistance) { m_targetDistance = targetDistance; }
            velocity Update(distance currentDistance);
            velocity GetVelocity();

        private:
            velocity m_maxVelocity, m_endVelocity, m_newVelocity, m_currentVelocity;
            acceleration m_acceleration;
            distance m_targetDistance;
            units::millisecond_t m_timesteps;
            bool m_invertDirection;
            int m_direction{1};

    }; // Motion Profile
} // namespace
#include "MotionProfile.cpp"