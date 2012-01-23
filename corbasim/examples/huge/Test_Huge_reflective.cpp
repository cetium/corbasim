#include "hugeC.h"
#include "huge_adapted.hpp"
#include "huge_servant.hpp"
#include <corbasim/core/reflective.hpp>

extern "C" const corbasim::core::interface_reflective_base * corbasim_reflective_Test_Huge()
{
    return corbasim::core::interface_reflective< Test::Huge >::get_instance();
}

