// landtab_cars.h: definitions for UIUC Image Database for Car detection.

#ifndef STASM_LANDTAB_CARS30_H
#define STASM_LANDTAB_CARS30_H

// Note that we use classical 1D descriptors on all points (no HATS)
// because all points are on edges.  HATs would probably work as well
// but I haven't tried them here (to use a HAT descriptor at a point,
// set the AT_Hat bit in the "bits" field).

static const LANDMARK_INFO LANDMARK_INFO_TAB[30] = // 30 points
{ // par pre next weight bits
    { -1, -1,  -1,     1,   0 }, // 00: Sobre la luz delantera.
    { -1, -1,  -1,     1,   0 }, // 01: Mitad del capó.
    { -1, -1,  -1,     1,   0 }, // 02: Final del capó - inicio luna.
    { -1, -1,  -1,     1,   0 }, // 03: Final de la luna - inicio del techo.
    { -1, -1,  -1,     1,   0 }, // 04: Mitad del techo.
    { -1, -1,  -1,     1,   0 }, // 05: Final del techo - inicio luna trasera.
    { -1, -1,  -1,     1,   0 }, // 06: Final luna trasera - inicio maletero.
    { -1, -1,  -1,     1,   0 }, // 07: Mitad maletero.
    { -1, -1,  -1,     1,   0 }, // 08: Final maletero.
    { -1, -1,  -1,     1,   0 }, // 09: Paragolpes trasero (arriba).
    { -1, -1,  -1,     1,   0 }, // 10: Paragolpes trasero (abajo).
    { -1, -1,  -1,     1,   0 }, // 11
    { -1, -1,  -1,     1,   0 }, // 12
    { -1, -1,  -1,     1,   0 }, // 13
    { -1, -1,  -1,     1,   0 }, // 14
    { -1, -1,  -1,     1,   0 }, // 15
    { -1, -1,  -1,     1,   0 }, // 16
    { -1, -1,  -1,     1,   0 }, // 17
    { -1, -1,  -1,     1,   0 }, // 18
    { -1, -1,  -1,     1,   0 }, // 19
    { -1, -1,  -1,     1,   0 }, // 20
    { -1, -1,  -1,     1,   0 }, // 21
    { -1, -1,  -1,     1,   0 }, // 22
    { -1, -1,  -1,     1,   0 }, // 23
    { -1, -1,  -1,     1,   0 }, // 24
    { -1, -1,  -1,     1,   0 }, // 25
    { -1, -1,  -1,     1,   0 }, // 26
    { -1, -1,  -1,     1,   0 }, // 27
    { -1, -1,  -1,     1,   0 }, // 28
    { -1, -1,  -1,     1,   0 }, // 29
};

#endif // STASM_LANDTAB_CARS30_H
