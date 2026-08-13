# gbs-SetActorExistingSpritesheetPlugin

**Version 4.3.0 — Requires GB Studio ≥ 4.3.0**

Repoints an actor at a different spritesheet **without copying any tile data into VRAM**, for the case where the target tiles are already resident — a per-room streamed tile band, a shared sheet another actor already loaded, or a band filled by hand.

GB Studio's stock *Set Actor Sprite Sheet* always uploads the sheet's tiles. When the tiles are already in VRAM that upload is wasted VBlank time, and it can overwrite a band that something else owns. This plugin swaps the actor's sprite, animations and (optionally) bounds, and leaves VRAM alone.

---

## Table of Contents

1. [Concepts](#concepts)
2. [Project Setup](#project-setup)
3. [Size Limits and Restrictions](#size-limits-and-restrictions)
4. [Events Reference](#events-reference)
5. [Memory Footprint](#memory-footprint)
6. [Bank 0 (HOME) Usage](#bank-0-home-usage)
7. [Changelog](#changelog)

---

## Concepts

### Why a "no-upload" sprite swap?

An actor in GB Studio owns two things: the sprite definition (animations, frames, bounds) and the block of VRAM tiles those frames point at. The stock swap event replaces both. If the tiles you want are already sitting in VRAM — because another actor loaded the same sheet, or because a streaming system placed them there — re-uploading them costs VBlank time you don't have and can trample tiles another actor is relying on.

This plugin performs only the first half of the swap. The actor starts drawing the new sheet's frames immediately, reading whatever tiles are already in its VRAM band.

---

## Project Setup

1. Make sure the tiles for the target spritesheet are **already present in VRAM** at the position the actor's sprite base expects — loaded by another actor using the same sheet, streamed in by a tile-streaming plugin, or written by hand.
2. Add **Set actor existing spritesheet** to any script and pick the actor and the spritesheet to switch to.
3. Set **Base tile Idx** to the OBJ tile index those tiles already occupy in VRAM.

---

## Size Limits and Restrictions

- **The tiles must already be in VRAM.** This event does not upload anything. Pointing an actor at a spritesheet whose tiles are not resident shows garbage graphics.
- The new spritesheet should have the **same tile layout** as whatever occupies the actor's VRAM band, otherwise frames will reference the wrong tiles.
- Use the stock *Set Actor Sprite Sheet* event instead whenever the tiles are **not** already loaded.

---

## Events Reference

All events appear under the **Actor** group in the script editor.

---

### Set actor existing spritesheet

**`EVENT_SET_ACTOR_EXISTING_SPRITESHEET`**

Repoints an actor at a spritesheet whose tiles are already in VRAM. No tile data is copied.

| Field | Description |
|-------|-------------|
| Actor | The actor to repoint. |
| Sprite Sheet | Sprite sheet whose tiles are assumed to already be resident in VRAM at Base tile Idx. |
| Base tile Idx | The OBJ tile index the sprite's tiles already occupy in VRAM. |

---

### Set actor existing spritesheet By Index

**`EVENT_SET_ACTOR_EXISTING_SPRITESHEET_BY_INDEX`**

Identical to the above, but the actor is given as a value or variable holding an actor index (player = 0) instead of being picked from the actor list. Use this when the target actor is computed at runtime.

| Field | Description |
|-------|-------------|
| Actor Index | Value or variable holding the index of the actor to change (player = 0). |
| Sprite Sheet | Sprite sheet whose tiles are assumed to already be resident in VRAM at Base tile Idx. |
| Base tile Idx | The OBJ tile index the sprite's tiles already occupy in VRAM. |

---

## Memory Footprint

Measured against the stock GB Studio **4.3.0-e1** engine by `measure_plugin_memory.js` (per-file SDCC compile with GB Studio's own build flags, at default engine settings; report of 2026-08-13). Figures are this plugin's *delta* versus stock — a file that replaces a stock engine file counts only the difference, which is why a plugin can come out negative. Using the plugin's events additionally compiles a few bytes of GBVM script per call into your project's script banks, on top of the fixed cost below.

| Budget | Cost |
|---|---|
| Bank 0 (HOME) | 0 bytes |
| WRAM | 0 bytes |
| Banked ROM | +192 bytes |

- **Bank 0:** nothing. Every function the plugin adds is compiled into a switchable ROM bank.
- **WRAM:** none.
- **Banked ROM:** 192 bytes for the two native helpers behind the events.
- **Engine WRAM headroom:** a stock GB Studio 4.3.0 project leaves about **854 bytes** of WRAM free (usable engine WRAM is 7,776 bytes at 0xC0A0–0xDF00; the stock engine uses 6,922). With this plugin installed roughly **854 bytes** remain. That does not change with the number of global variables your project defines: the script memory array is a fixed 3,584 bytes at stock engine settings (VM_HEAP_SIZE + VM_MAX_CONTEXTS × VM_CONTEXT_STACK_SIZE = 768 + 16 × 64 words).
- **SRAM:** not used.

---

<!-- BANK0:BEGIN -->
## Bank 0 (HOME) Usage

Bank 0 is the 16 KB non-switchable ROM bank that the GB Studio engine core,
the interrupt handlers and the GBDK runtime all share. Banked ROM is cheap
(add another bank), bank 0 is not, so it is usually the first thing a project
runs out of.

| | Bytes |
|---|---|
| Bank 0 used by this plugin | **0** |

**This plugin costs nothing in bank 0.** Every one of its functions is compiled
into a switchable ROM bank; nothing it adds is resident in bank 0.
<!-- BANK0:END -->

## Changelog

This plugin has not been merged into the official [gb-studio-plugins](https://github.com/gb-studio-dev/gb-studio-plugins)
repository yet, and carries no version history to report.