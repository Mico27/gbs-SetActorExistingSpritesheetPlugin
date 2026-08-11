const l10n = require("../helpers/l10n").default;

export const id = "EVENT_SET_ACTOR_EXISTING_SPRITESHEET";
export const name = "Set actor existing spritesheet";
export const groups = ["EVENT_GROUP_ACTOR"];

export const autoLabel = (fetchArg) => {
  return `Set actor existing spritesheet`;
};

export const fields = [
  {
    key: "actorId",
    label: l10n("ACTOR"),
    description: l10n("FIELD_ACTOR_DEACTIVATE_DESC"),
    type: "actor",
    defaultValue: "$self$",
  },
  {
    key: "existingSpriteSheetId",
    label: l10n("FIELD_SPRITE_SHEET"),
    description:
      "Sprite sheet whose tiles are assumed to already be resident in VRAM at Base Tile Idx (no tile data is copied).",
    type: "sprite",
    defaultValue: "LAST_SPRITE",
  },
  {
    key: "base_tile_idx",
    label: "Base tile Idx",
    description:
      "OBJ tile index the sprite's tiles already occupy in VRAM.",
    type: "value",
    defaultValue: {
      type: "number",
      value: 0,
    },
  },
];

export const compile = (input, helpers) => {
  const {
    options,
    _callNative,
    _stackPush,
    _stackPushConst,
    _stackPop,
    _addComment,
    _declareLocal,
    variableSetToScriptValue,
    setActorId,
  } = helpers;
  const { sprites } = options;
  const sprite = sprites.find((s) => s.id === input.existingSpriteSheetId);
  if (!sprite) {
    return;
  }
  const tmp0 = _declareLocal("tmp0", 1, true);
  const tmp1 = _declareLocal("tmp1", 1, true);

  setActorId(tmp0, input.actorId);
  variableSetToScriptValue(tmp1, input.base_tile_idx);

  _addComment("Set actor existing spritesheet");

  _stackPush(tmp1);
  _stackPush(tmp0);
  _stackPushConst(`_${sprite.symbol}`);
  _stackPushConst(`___bank_${sprite.symbol}`);

  _callNative("vm_set_actor_existing_spritesheet");
  _stackPop(4);
};
