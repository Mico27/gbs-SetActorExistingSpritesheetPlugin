#pragma bank 255

#include <gbdk/platform.h>
#include "vm.h"
#include "gbs_types.h"
#include "actor.h"
#include "data_manager.h"
#include "set_actor_existing_spritesheet.h"

void set_actor_existing_spritesheet(const spritesheet_t *spritesheet, UBYTE spritesheet_bank, UWORD animation_set, actor_t *actor, UBYTE base_tile_idx) BANKED {
    actor->sprite.bank = spritesheet_bank;
    actor->sprite.ptr = (void *)spritesheet;
    actor->base_tile = base_tile_idx;
    load_animations(spritesheet, spritesheet_bank, animation_set, actor->animations);
    actor_reset_anim(actor);
}

void vm_set_actor_existing_spritesheet(SCRIPT_CTX *THIS) OLDCALL BANKED {
    (void)THIS;
    UBYTE spritesheet_bank = *(UBYTE *)VM_REF_TO_PTR(FN_ARG0);
    const spritesheet_t *spritesheet = *(spritesheet_t **)VM_REF_TO_PTR(FN_ARG1);
    actor_t *actor = actors + *(UBYTE *)VM_REF_TO_PTR(FN_ARG2);
    set_actor_existing_spritesheet(spritesheet, spritesheet_bank, ANIM_SET_DEFAULT, actor, *(UBYTE *)VM_REF_TO_PTR(FN_ARG3));
}
