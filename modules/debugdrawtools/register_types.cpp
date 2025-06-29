#include "register_types.h"

#include "core/object/class_db.h"
#include "debug_draw_shapes_2d.h"

void initialize_debugdrawtools_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    ClassDB::register_class<DebugDrawShapes>();
}

void uninitialize_debugdrawtools_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}