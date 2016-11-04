// initasm.cpp: initialize the ASM model
//
// Copyright (C) 2005-2013, Stephen Milborrow

#include "../stasm.h"
#include "mh/yaw00.mh"

namespace stasm
{
void InitMods(           // initialize ASM model
    vec_Mod&    mods,    // out: ASM model (only one model in this version of Stasm)
    const char* datadir) // in: directory of face detector files
{
    if (mods.empty())    // models not yet initialized?
    {
        mods.resize(1);  // 1 model

        static const Mod mod_yaw00( // constructor, see asm.h
            EYAW00,      // eyaw
            ESTART_RECT_ONLY, // estart. Antes de modificarlo: ESTART_EYES.
            datadir,
            yaw00_meanshape,
            yaw00_eigvals,
            yaw00_eigvecs,
            10,  // neigs (value from empirical testing). Antes de modificarlo: 20.
            3.0, // bmax  (value from empirical testing). Antes de modificarlo: 1.5.
            0, // hackbits. Antes de modificarlo: SHAPEHACKS_DEFAULT | SHAPEHACKS_SHIFT_TEMPLE_OUT
            YAW00_DESCMODS, // defined in yaw00.mh
            NELEMS(YAW00_DESCMODS));

        mods[0] = &mod_yaw00;
    }
}

} // namespace stasm
