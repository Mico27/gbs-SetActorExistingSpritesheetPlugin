#ifndef SET_ACTOR_EXISTING_SPRITESHEET_H
#define SET_ACTOR_EXISTING_SPRITESHEET_H

#include "vm.h"
#include "actor.h"

// Repoints an actor at `spritesheet` (already resident in VRAM at
// `base_tile_idx`) without copying any tile data — unlike the stock
// vm_actor_set_spritesheet, which always calls load_sprite()/load_bounds()
// to (re)upload tiles. Use only when the caller guarantees the tiles are
// already loaded at that base_tile_idx (e.g. a per-room streamed tile band
// shared across multiple sprite "forms").
void set_actor_existing_spritesheet(const spritesheet_t *spritesheet, UBYTE spritesheet_bank, UWORD animation_set, actor_t *actor, UBYTE base_tile_idx) BANKED;

void vm_set_actor_existing_spritesheet(SCRIPT_CTX *THIS) OLDCALL BANKED;

#endif
