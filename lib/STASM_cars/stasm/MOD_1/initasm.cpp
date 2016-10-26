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
            ESTART_RECT_ONLY, // estart
            datadir,
            yaw00_meanshape,
            yaw00_eigvals,
            yaw00_eigvecs,
            10,//1,//20,//55,  // neigs (value from empirical testing)
            3,//4.5,//3.0,//1.3, // bmax  (value from empirical testing)
            0, // hackbits
            YAW00_DESCMODS, // defined in yaw00.mh
            NELEMS(YAW00_DESCMODS));

        mods[0] = &mod_yaw00;
    }
}

} // namespace stasm
