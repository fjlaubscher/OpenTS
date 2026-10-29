---
key: TextBackgroundColor
scope: client-settings
label: Chat text background
see_also: [MessageDelay, IncomingMessage]
when_omitted:
  kind: value
  value: "0"
---

`TextBackgroundColor` is the palette index drawn behind every character of the in-game message list and of the line being typed. `0` draws no background; `12` is black. [In-game chat](/systems/chat/) describes the message list.

`TransparentMessageText=no` under `[siliconsun]` in `SUN.INI` draws index `12` when this key is missing or `0`. Any other index is used whether that key is `yes` or `no`. A missing `TransparentMessageText` leaves a missing color at `0`.

No dialog offers the setting. Leaving the options menu writes the index in force, including a `12` substituted when `TransparentMessageText=no` and this key is `0`, so a value set by hand is kept once it has been saved.

```ini title="sun.ini"
[Options]
TextBackgroundColor=12
```
