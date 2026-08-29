# gbs-SetActorExistingSpritesheetPlugin

**Version 4.3.0. Requires GB Studio 4.3.0 or newer.**

Points an actor at a different sprite sheet without copying any tile data into video memory.
Use it when the tiles are already loaded: a shared sheet another actor brought in, a band a
streaming plugin filled, or tiles you wrote there yourself.

The stock **Set Actor Sprite Sheet** event always uploads the sheet's tiles. When those tiles are
already loaded, that upload spends screen-blanking time for nothing and can overwrite tiles
another actor is using. This event swaps the actor's sprite, animations and bounds, and leaves
video memory untouched.

---

## Table of Contents

1. [Concepts](#concepts)
2. [Project Setup](#project-setup)
3. [Size Limits and Restrictions](#size-limits-and-restrictions)
4. [Events Reference](#events-reference)
5. [FAQ](#faq)
6. [Memory Footprint](#memory-footprint)
7. [Bank 0 (HOME) Usage](#bank-0-home-usage)
8. [Changelog](#changelog)

---

## Concepts

### What a sprite swap actually involves

An actor owns two things: the sprite definition, which is the list of animations, frames and
bounds, and the block of video memory tiles those frames draw from. The stock swap event replaces
both.

This event replaces only the sprite definition. The actor starts drawing the new sheet's frames on
the next frame, reading whatever tiles are already sitting in its video memory band. On a Game Boy
that upload is the expensive half, so skipping it is worth a lot when you swap sprites often.

---

## Project Setup

1. Get the target sheet's tiles into video memory first, by having another actor use the same
   sheet, by streaming them in, or by writing them there yourself.
2. Add **Set actor existing spritesheet** to any script and pick the actor and the sheet.
3. Set **Base tile Idx** to the tile position those tiles already occupy.

---

## Size Limits and Restrictions

- **The tiles must already be loaded.** This event copies nothing. Pointing an actor at a sheet
  whose tiles are absent shows scrambled graphics.
- The new sheet needs the **same tile arrangement** as whatever occupies the actor's video memory
  band, or its frames land on the wrong tiles.
- When the tiles are not already loaded, use the stock **Set Actor Sprite Sheet** event.

---

## Events Reference

Both events appear under the **Actor** group in the script editor.

### Set actor existing spritesheet

Points an actor at a sprite sheet whose tiles are already loaded. Copies no tile data.

| Field | Description |
|-------|-------------|
| Actor | The actor to change. |
| Sprite Sheet | The sheet to draw from. Its tiles must already sit at Base tile Idx. |
| Base tile Idx | The tile position the sheet's tiles already occupy. |

### Set actor existing spritesheet By Index

The same event, with the actor given as a value or variable holding an actor index (the player is
0). Use it when the target actor is worked out while the game runs.

| Field | Description |
|-------|-------------|
| Actor Index | Value or variable holding the index of the actor to change (player = 0). |
| Sprite Sheet | The sheet to draw from. Its tiles must already sit at Base tile Idx. |
| Base tile Idx | The tile position the sheet's tiles already occupy. |

---

## FAQ

**When should I use this over the stock Set Actor Sprite Sheet event?**
Use it whenever the tiles are already loaded. Two common cases: several actors share one sheet and
you want a second actor to switch to it, or a streaming plugin keeps a band of video memory
loaded and you want to point actors at whatever currently occupies it.

**My actor turned into scrambled tiles. Why?**
The tiles for that sheet were never loaded, or **Base tile Idx** points somewhere else. Load the
sheet with a stock **Set Actor Sprite Sheet** on any actor first, then check the tile position.

**How do I find the right Base tile Idx?**
It is the tile position the sheet occupies. If another actor loaded that sheet, use that actor's
base tile. If a streaming plugin owns the band, use the position it reports.

**Does this save memory?**
It saves time, not ROM. A stock sprite swap copies every tile of the sheet during the screen blank
and can drop a frame on a large sheet. This one copies nothing, so it finishes immediately.

**Can I use it to give an enemy a palette-swapped look?**
Only if the alternative art is already loaded. If you want new art on screen, something has to
upload it first.

**Can the actor be chosen while the game runs?**
Yes. Use **Set actor existing spritesheet By Index** and feed it a variable holding the actor
index. The player is index 0.

**Does it work with the player?**
Yes. Pick the player in the actor field, or pass index 0 to the By Index version.

---

## Memory Footprint

Measured against the stock GB Studio **4.3.0-e1** engine at default engine settings, report of
2026-08-13. Figures are the difference against a stock project. Each event you use also compiles a
few bytes of script into your project, on top of the fixed cost below.

| Budget | Cost |
|---|---|
| Bank 0 (HOME) | 0 bytes |
| WRAM | 0 bytes |
| Banked ROM | +192 bytes |

- **Bank 0:** nothing. Everything the plugin adds is compiled into a switchable ROM bank.
- **WRAM:** none.
- **Banked ROM:** 192 bytes for the code behind the two events.
- **Engine WRAM headroom:** a stock GB Studio 4.3.0 project leaves about **854 bytes** of WRAM
  free (the engine has 7,776 bytes to work with and uses 6,922 of them). With this plugin
  installed roughly **854 bytes** remain. Adding more global variables to your project does not
  change that figure, because script memory is a fixed 3,584 byte block at stock engine settings.
- **SRAM:** not used.

---

<!-- BANK0:BEGIN -->
## Bank 0 (HOME) Usage

Bank 0 is the 16 KB fixed ROM bank shared by the GB Studio engine core, the
interrupt handlers and the GBDK runtime. Extra banked ROM is cheap to add,
bank 0 is not, so bank 0 is usually the first thing a project runs out of.

| | Bytes |
|---|---|
| Bank 0 used by this plugin | **0** |

**This plugin costs nothing in bank 0.** Everything it adds is compiled into a
switchable ROM bank.
<!-- BANK0:END -->

## Changelog

This plugin has not been merged into the official
[gb-studio-plugins](https://github.com/gb-studio-dev/gb-studio-plugins) repository yet, so it has
no version history to report.
