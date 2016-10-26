// landtab_cars.h: definitions for UIUC Image Database for Car detection.

#ifndef STASM_LANDTAB_CARS20_H
#define STASM_LANDTAB_CARS20_H

// Note that we use classical 1D descriptors on all points (no HATS)
// because all points are on edges.  HATs would probably work as well
// but I haven't tried them here (to use a HAT descriptor at a point,
// set the AT_Hat bit in the "bits" field).

static const LANDMARK_INFO LANDMARK_INFO_TAB[20] = // 20 points
{ // par pre next weight bits
    { -1, -1,  -1,     1,   AT_Hat }, // 00: Sobre la luz delantera.
    { -1, -1,  -1,     1,   AT_Hat }, // 01: Mitad del capó.
    { -1, -1,  -1,     1,   AT_Hat }, // 02: Final del capó - inicio luna.
    { -1, -1,  -1,     1,   AT_Hat }, // 03: Final de la luna - inicio del techo.
    { -1, -1,  -1,     1,   AT_Hat }, // 04: Mitad del techo.
    { -1, -1,  -1,     1,   AT_Hat }, // 05: Final del techo - inicio luna trasera.
    { -1, -1,  -1,     1,   AT_Hat }, // 06: Final luna trasera - inicio maletero.
    { -1, -1,  -1,     1,   AT_Hat }, // 07: Mitad maletero.
    { -1, -1,  -1,     1,   AT_Hat }, // 08: Final maletero.
    { -1, -1,  -1,     1,   AT_Hat }, // 09: Paragolpes trasero (arriba).
    { -1, -1,  -1,     1,   AT_Hat }, // 10: Paragolpes trasero (abajo).
    { -1, -1,  -1,     1,   AT_Hat }, // 11
    { -1, -1,  -1,     1,   AT_Hat }, // 12
    { -1, -1,  -1,     1,   AT_Hat }, // 13
    { -1, -1,  -1,     1,   AT_Hat }, // 14
    { -1, -1,  -1,     1,   AT_Hat }, // 15
    { -1, -1,  -1,     1,   AT_Hat }, // 16
    { -1, -1,  -1,     1,   AT_Hat }, // 17
    { -1, -1,  -1,     1,   AT_Hat }, // 18
    { -1, -1,  -1,     1,   AT_Hat }, // 19
};

#endif // STASM_LANDTAB_CARS20_H
