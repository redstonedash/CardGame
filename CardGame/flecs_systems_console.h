#pragma once
#include "flecs.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct EcsConsole {
    int __dummy;
} EcsConsole;

/* Stats module component */
typedef struct FlecsSystemsConsole {
    ECS_DECLARE_COMPONENT(EcsConsole);
} FlecsSystemsConsole;

FLECS_EXPORT
void FlecsSystemsConsoleImport(
    ecs_world_t *world,
    int flags);

#define FlecsSystemsConsoleImportHandles(handles)\
    ECS_IMPORT_COMPONENT(handles, EcsConsole);

#ifdef __cplusplus
}
#endif