#pragma once
#include <frc/GenericHID.h>
#include <frc/XboxController.h>

#include <frc2/command/button/Button.h>

namespace frc {
    namespace XboxTriggers {
        enum trigger {
        up = 0,
        down = 90
        };
    }
}

namespace frc2 {
/**
 * A class used to bind command scheduling to joystick POV presses.  Can be
 * composed with other buttons with the operators in Trigger.
 *
 * @see Trigger
 */
class TriggerButton : public Button {
 public:
  /**
   * Creates a POVButton that commands can be bound to.
   *
   * @param joystick The joystick on which the button is located.
   * @param trigger The left or right trigger.
   */
  TriggerButton(frc::GenericHID* controller, frc::XboxTriggers::trigger trigger)
      : Button([controller, trigger] {
        return controller->GetPOV(trigger);

        }) {}
};
}  // namespace frc2