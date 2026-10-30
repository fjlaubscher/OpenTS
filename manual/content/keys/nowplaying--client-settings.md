---
key: NowPlaying
scope: client-settings
label: Now playing
summary: Names the current music track at the bottom left of the battlefield.
see_also: [MessageDelay, TextBackgroundColor, Name]
when_omitted:
  kind: value
  value: "no"
---

`NowPlaying=yes` prints `Now Playing: ` and the track title at the bottom left of the battlefield while a scenario is under way. The line uses the player's color, the same lettering as the alerts at the top left, and the alert background from [`TextBackgroundColor`](/keys/textbackgroundcolor/).

The line stays for the alert time, [`MessageDelay`](/keys/messagedelay/), and then leaves while the track continues. A different track replaces the line and the time starts again. When the music stops, the line leaves. A scenario that starts shows the track already playing.

The title is the track's [`Name`](/keys/name/#scope-themes). An empty name uses the track's section name.

The media next-track and previous-track keys run the [next track](/commands/nexttheme/) and [previous track](/commands/prevtheme/) commands. Those commands print their own short message at the top left.

`no` leaves the line off and leaves the media keys unused. The next track and previous track commands stay on their own keys.

The key is read from `[siliconsun]` in `SUN.INI` at startup. No dialog offers it. Leaving the options menu writes the value currently in force.
