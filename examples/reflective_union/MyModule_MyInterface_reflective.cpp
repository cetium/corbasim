
#include "unionC.h"
#include "union_adapted.hpp"
#include "union_servant.hpp"
#include <corbasim/core/reflective.hpp>

extern "C" const corbasim::core::interface_reflective_base * corbasim_reflective_MyModule_MyInterface()
{
	return corbasim::core::interface_reflective< MyModule::MyInterface >::get_instance();
}

