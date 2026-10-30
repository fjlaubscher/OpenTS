---
title: Restore the last skirmish setup
category: feature
release: 0.2.0
targets:
- type: key
  id: PersistSkirmishSettings
  effect: added
credit:
- fjlaubscher
---

`PersistSkirmishSettings=yes` under `[siliconsun]` in `SUN.INI` reopens the skirmish setup screen with the map and game options it held when it last closed. The engine keeps that setup in the `[Skirmish]` section of the same file, so it survives quitting and relaunching. A saved map that has since been removed falls back to the first scenario.
