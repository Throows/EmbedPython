#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define FUNC_NB 1

#ifdef MYGAME_MODULE    // While Compiling the module

static void SetMyInt(int num);

#else                   // While importing the module

static void **Pymygame_API;

#define SetMyInt (*(void (*)(int))Pymygame_API[0])

static int import_mygame(void)
{
    Pymygame_API = (void**) PyCapsule_Import("mygame._C_API", 0);
    return (Pymygame_API != NULL) ? 0 : -1;
}

#endif

#ifdef __cplusplus
}
#endif
