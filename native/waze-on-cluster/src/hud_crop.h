// SPDX-License-Identifier: GPL-3.0-or-later
/* The HUD map with its bottom cut off (hud_crop_bottom_pct): the part of
 * the phone's map below the car is the road already driven, and on the HUD
 * it lands on BMW's own speed and limit sign. Cut, the map keeps its top,
 * place and width; it is only shorter, and the picture's bottom rows are
 * left out (not squeezed), so the map's shape is kept. The rows free below
 * it are left to other apps' layers (gear, rpm, turn signals). */
#ifndef WOC_HUD_CROP_H
#define WOC_HUD_CROP_H

#include <stdint.h>

namespace woc {

/* At most this much is cut: the map keeps at least 40 % of its height. */
const unsigned kHudCropMaxPct = 60;

/* h with its bottom pct cut, even and at least 32 (the renderer's least
 * video height): a quad's height or the picture's rows kept. */
inline uint32_t hud_cropped(uint32_t h, unsigned pct)
{
    if (!pct)
        return h;
    if (pct > kHudCropMaxPct)
        pct = kHudCropMaxPct;
    uint32_t c = (uint32_t)((uint64_t)h * (100 - pct) / 100) & ~1u;
    if (c < 32)
        c = h < 32 ? h : 32;
    return c;
}

}  // namespace woc

#endif
