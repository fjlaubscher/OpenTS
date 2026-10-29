# siliconsun

siliconsun is an Apple Silicon client of *Command & Conquer: Tiberian Sun*,
and a Windows x64 client of the same engine. The engine is
[OpenTS](https://github.com/OpenTS-Developers/OpenTS).

I use a MacBook Air M5 as my dev laptop, and I want to play Tiberian Sun on it
during breaks. That is the machine the Apple Silicon build is tested on. I also
play the Windows x64 build on an HP Victus 15 (Ryzen 7, RTX 3050) from 2021,
including on a 4K display, and on a Steam Deck through Proton 11.

<img src="menu.png" alt="Tiberian Sun main menu running on Apple Silicon" width="900">

<img src="gameplay.png" alt="Tiberian Sun in-game on Apple Silicon" width="900">

## What this is

OpenTS rebuilds the Tiberian Sun engine as a standalone program instead of
patching the retail executable. siliconsun keeps that engine, adds an arm64
macOS build, and ships both clients from a tagged release.

Everything about the engine — what OpenTS is and is not, its status and
roadmap, the manual, history, and license — lives in the
[upstream README](https://github.com/OpenTS-Developers/OpenTS) and its
[documentation](https://github.com/OpenTS-Developers/OpenTS/tree/main/docs).
This file covers the macOS build, the Windows x64 build, where the game data
comes from, and the settings siliconsun adds.

## Building on macOS (Apple Silicon)

The macOS build is the one I develop with. It builds with Apple Clang and
Ninja on arm64.

1. Install CMake and Ninja:

   ```bash
   brew install cmake ninja
   ```

2. Fetch the submodules:

   ```bash
   git submodule update --init --recursive
   ```

3. Configure and build a Debug binary:

   ```bash
   cmake -S . -B build/macos -G Ninja \
     -DCMAKE_BUILD_TYPE=Debug \
     -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
   cmake --build build/macos
   ```

   The binary is `build/macos/bin/GameD`.

4. Point the game at a Tiberian Sun data directory and run:

   ```bash
   build/macos/bin/GameD -DATADIR="$HOME/Games/OpenTS"
   ```

## Building on Windows

The Windows client published here is 64-bit (x64).
[BUILDING.md](docs/BUILDING.md) is the Visual Studio 2022 procedure; configure
the x64 target.

## siliconsun settings

Player options live in `SUN.INI`. The game writes that file beside the
executable, or in the user directory when `-USERDIR` names one. siliconsun
reads its own keys from a `[siliconsun]` section in that file. Each key
defaults to `yes`. A missing key, or a missing section, leaves the feature on.
`no`, `false`, and `0` turn that one feature off. Leaving the options menu
writes the section back out.

```ini
[siliconsun]
DoubleClickSelectType=yes
CampaignIntroMovie=yes
```

`DoubleClickSelectType=yes` selects every on-screen unit of one type when you
double-click one of your own, the same selection as Select Same Type. The
first click of the double-click still selects only that unit. `no` leaves the
double-click as an ordinary click. A double-click on an enemy, on empty
ground, or under fog does nothing beyond the ordinary click.

`CampaignIntroMovie=yes` plays each campaign's own introduction when that
introduction plays at all: the first mission of a campaign whose disc number
is below 2, and not on a restart. Disc 0 prefers `MOVIES01.MIX` and disc 1
prefers `MOVIES02.MIX`, so Nod plays the Nod introduction when both campaigns
are installed. `no` leaves the movie archives in alphabetical order, and
`INTRO.VQA` then comes from the first of those archives. A file named
`INTR<n>.VQA` still plays for side `n` when it is present.

In-game messages have no background when `TextBackgroundColor` under
`[Options]` is missing or `0`. Any other palette index is drawn as written.
`12` is black. A saved `SUN.INI` that still has `TextBackgroundColor=12` keeps
that black box; set it to `0`.

```ini
[Options]
TextBackgroundColor=0
```

## Playing on a Steam Deck

The Steam Deck runs the Windows x64 build under Proton 11. The panel is
1280×800 (16:10).

The display options list that desktop size, and 640×400 with it. 640×400 is
the original Tiberian Sun picture, and it is exactly half of 1280×800, so it
fills the panel at double size. 1280×800 draws the battlefield at the panel's
own pixels, which shows more of the map and smaller units. The sidebar is 168
pixels of the render width, so the higher size leaves a wider map.

A fresh `SUN.INI` opens at 640×480. That picture is 4:3, so on the Deck it
fills the height and leaves a bar at each side. Pick 1280×800 or 640×400 in
the display options, or write the size yourself:

```ini
[Video]
ScreenWidth=1280
ScreenHeight=800
Fullscreen=yes
```

`ScaleMode=PixelArt` is the default. `IntegerScaling=yes` keeps the
enlargement on whole multiples of the rendered picture. A 640×400 picture in
the Deck's 1280×800 window is an exact double with either setting.

## Playing on a 4K display

I play the Windows x64 build on the Victus at 3840×2160. The executable is
per-monitor DPI aware, so the window uses the panel's pixels.

The display options list the desktop's modes from 640×400 through 4096×4096,
including 3840×2160 when that is the primary display. They also list each
whole fraction of that desktop that is still at least 640×400, and the size
Windows scaling corresponds to. A 3840×2160 desktop at 200% therefore offers
1920×1080. At 150% it offers 2560×1440 as well.

3840×2160 draws units at their sprite size across the whole panel, so the map
is large and the units and menus are small. 1920×1080 draws them twice as
large and the window scales that picture by 2 onto the panel.
`ScaleMode=PixelArt` keeps a whole-number enlargement sharp.

With `CursorScale=0`, the pointer follows the Windows display scale when the
picture itself is enlarged less than that. A 3840×2160 picture on a display
set to 200% gets a double-size pointer. `CursorScale` under `[Video]` sets
another size, from 1 to 8, and a negative value keeps the artwork's own size.
`SystemCursor=yes` uses the Windows pointer, at the size Windows is set to.

The list follows the primary display. A 4K panel that is not the primary
display is absent from it; set `ScreenWidth` and `ScreenHeight` to the size
you want.

## How to get the game data

siliconsun ships the engine only. Download the freeware GDI, Nod, and Firestorm
disc images from the
[Command & Conquer Communications Center](https://cnc-comm.com/tiberian-sun/downloads/the-game):

| Disc | Page | File |
| --- | --- | --- |
| GDI | [GDI CD](https://cnc-comm.com/tiberian-sun/downloads/the-game/gdi-disc) | [TS_GDI.zip](https://downloads.cnc-comm.com/tiberian-sun/iso/TS_GDI.zip) |
| Nod | [Nod CD](https://cnc-comm.com/tiberian-sun/downloads/the-game/nod-disc) | [TS_Nod.zip](https://downloads.cnc-comm.com/tiberian-sun/iso/TS_Nod.zip) |
| Firestorm | [Firestorm CD](https://cnc-comm.com/tiberian-sun/downloads/the-game/firestorm-disc) | [TS_Firestorm.zip](https://downloads.cnc-comm.com/tiberian-sun/iso/TS_Firestorm.zip) |

Ask an agent to run the `retail-install` skill, or run the script yourself.
Pass Firestorm last. A mounted disc, an extracted disc, or an existing install
folder is a source too. The files land in `~/Games/OpenTS`.

```bash
python3 .agents/skills/retail-install/scripts/install-retail.py \
  ~/Downloads/TS_GDI.zip ~/Downloads/TS_Nod.zip ~/Downloads/TS_Firestorm.zip
```

`--no-movies`, `--no-music`, and `--no-firestorm` leave those groups out.
`--dry-run` prints the plan. On Windows, run
`.agents/skills/retail-install/scripts/install-retail.ps1` instead.

## Windows download

The x64 release is a drop-in replacement for the Steam install.

> [!WARNING]
> Back up the `Saved Games` folder before you replace `SUN.EXE`. OpenTS does
> not load saves from the original game, and the original game does not load
> saves OpenTS writes. There is no converter.

A published release includes `siliconsun-<tag>-x64.zip`: `SUN.EXE`, `Language.dll`,
`ui`, `Game.pdb`, and the license notices. Copy `SUN.EXE`, `Language.dll`,
`Game.pdb`, and `ui` into the Steam Tiberian Sun folder, or run
`SUN.EXE -DATADIR=<path>` from the unzipped folder. The Steam Deck and the
Victus both run this build. On the Deck, use Proton 11.

## macOS download

A published release includes `siliconsun-<tag>-macos.zip`: `Game`, `ui`, and the
license notices. It is an unsigned arm64 binary. `ui` has to stay beside
`Game`. After unzipping, clear quarantine and point the binary at the game
data:

```bash
xattr -dr com.apple.quarantine .
./Game -DATADIR="$HOME/Games/OpenTS"
```

Run that from the unzipped folder. The shell expands `$HOME` before the game
sees the path. The folder has to exist already.

## Windows Steam install

> [!WARNING]
> Back up the `Saved Games` folder before you deploy. OpenTS does not load
> saves from the original game, and the original game does not load saves
> OpenTS writes. There is no converter.

`.agents/skills/steam-release/` rebuilds the x64 Release and copies it onto the
Steam Tiberian Sun install on Windows, replacing `SUN.EXE`, `Language.dll`,
`Game.pdb`, and `ui/`. A build that is not x64 is refused. The Steam Deck runs
that Windows build under Proton 11.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .agents\skills\steam-release\scripts\deploy.ps1
```

## License

This fork keeps the upstream license: GPL-3.0-or-later, with the additional
Section 7 terms for material derived from Electronic Arts source. See
[LICENSE.md](LICENSE.md).
