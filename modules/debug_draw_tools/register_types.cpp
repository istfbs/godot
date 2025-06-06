#include "register_types.h"
#include "debug_draw_shapes_2d.h"

void initialize_debug_draw_tools_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

void uninitialize_debug_draw_tools_module(ModuleInitializationLevel p_level) {
    	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}