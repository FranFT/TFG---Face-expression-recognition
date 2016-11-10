#ifndef STASM_LANDTAB_HANDS11_H
#define STASM_LANDTAB_HANDS11_H

// Note that we use classical 1D descriptors on all points (no HATS)
// because all points are on edges.  HATs would probably work as well
// but I haven't tried them here (to use a HAT descriptor at a point,
// set the AT_Hat bit in the "bits" field).

static const LANDMARK_INFO LANDMARK_INFO_TAB[11] =
{  // par pre next weight bits
	{ -1, -1,  -1,     1,   0 }, //0
	{ -1, -1,  -1,     1,   0 }, //1
	{ -1, -1,  -1,     1,   0 }, //2
	{ -1, -1,  -1,     1,   0 }, //3
	{ -1, -1,  -1,     1,   0 }, //4
	{ -1, -1,  -1,     1,   0 }, //5
	{ -1, -1,  -1,     1,   0 }, //6
	{ -1, -1,  -1,     1,   0 }, //7
	{ -1, -1,  -1,     1,   0 }, //8
	{ -1, -1,  -1,     1,   0 }, //9
	{ -1, -1,  -1,     1,   0 }, //10
};

#endif //STASM_LANDTAB_HANDS11_H