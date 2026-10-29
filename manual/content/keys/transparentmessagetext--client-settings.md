---
key: TransparentMessageText
scope: client-settings
label: Transparent message text
summary: Draws the in-game message list with no background unless a palette index is set.
see_also: [TextBackgroundColor]
when_omitted:
  kind: value
  value: "yes"
---

`TransparentMessageText=yes` draws the in-game message list and the line being typed with no background while [`TextBackgroundColor`](/keys/textbackgroundcolor/#scope-client-settings) is missing or `0`. Any other `TextBackgroundColor` is the palette index drawn behind each character.

`no` draws palette index `12`, black, when `TextBackgroundColor` is missing or `0`. Any other index is used as written. After a save has stored `12`, set this key back to `yes` and `TextBackgroundColor=0` to make the list transparent again.

The key is read from `[siliconsun]` in `SUN.INI` at startup. No dialog offers it. Leaving the options menu writes the value currently in force.
