// SPDX-License-Identifier: GPL-3.0-or-later
#include "hud_crop.h"

#include <stdio.h>

using namespace woc;

static int failures = 0;

static void expect(bool ok, const char *what)
{
    if (!ok) {
        fprintf(stderr, "FAIL: %s\n", what);
        failures++;
    }
}

int main()
{
    expect(hud_cropped(200, 0) == 200, "0: nothing cut");
    expect(hud_cropped(200, 30) == 140, "30 % of the default HUD map's 200 rows cut: 140 left");
    expect(hud_cropped(480, 30) == 336, "the picture's 480 rows: its top 336 kept");
    expect(hud_cropped(201, 25) % 2 == 0, "always even");
    expect(hud_cropped(200, 90) == hud_cropped(200, kHudCropMaxPct), "over the most: the most");
    expect(hud_cropped(40, 60) == 32, "never under 32 rows");
    /* the shape kept: the quad and the picture cut alike */
    const double q = (double)hud_cropped(200, 30) / 453, p = (double)hud_cropped(480, 30) / 1088;
    expect(q / p > 0.98 && q / p < 1.02, "the cut map keeps the picture's shape");
    if (!failures)
        printf("hud_crop_test: ok\n");
    return failures ? 1 : 0;
}
