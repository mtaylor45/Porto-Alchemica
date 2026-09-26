# Threshold — Product Plan

*A household touch point system. Working name; rename before anyone outside
the house hears it.*

---

## 1. What this is

Seven touch points around the house that respond to a MagicBand tap with
light, sound, and haptics on the band itself. The first one unlocks the front
door. The rest do whatever is worth doing at that spot in the house.

The product is not the reader. The product is the two seconds between a
raised wrist and a door opening, and whether those two seconds feel like
magic or like operating a device.

## 2. Why this is different from what exists

Seven public MagicBand reader projects were reviewed. Every one stops at the
same place: match a UID, play a sound, light an LED ring, done. Separately,
one project broadcasts Disney's BLE beacon commands to make MagicBand+ units
glow and buzz, but has no reader attached.

Threshold is the first to join those halves, and adds three things nobody has
shipped:

| | Prior art | Threshold |
|---|---|---|
| Decision | Local UID allow-list | Home Assistant decides, reader reflects |
| Band feedback | None | Band lights and buzzes in sync with the reader |
| Proximity | None | Band pre-announces a nearby touch point |
| Coverage | One reader | A vocabulary shared across every zone |
| Enclosure | 3D-printed prop | Designed object, mixed materials |

## 3. Who this is for

**Mike (owner).** Wants extensibility, logs, and the ability to add a zone in
an evening. Not the design target — he will tolerate rough edges nobody else
will.

**Partner (the veto).** Will not debug anything. Will use it exactly as long
as it is faster than a key and never once locks her out. A single lockout
kills the project permanently. Design for her first.

**Kids (the delight engine).** Will tap forty times in a row, will tap with
sticky hands, will show it to every friend who visits. The measure of success
is whether they choose to use it when nobody is watching.

**Guests.** Have never seen it. Should not be confused, should never be
stranded outside, and should be able to work it after watching one person do
it once.

## 4. Experience principles

These are non-negotiable and decide every design argument below.

1. **No visible technology.** No exposed boards, no blinking status LEDs, no
   USB ports, no dangling cables, no screens showing an IP address. If a
   household member can see a circuit, the illusion is gone.
2. **Respond before you think.** Local feedback fires on tag detection, not
   after the network round trip. Perceived latency is the entire illusion.
3. **Never fail silently, never fail confusingly.** Every tap produces a
   response, including "no."
4. **One vocabulary everywhere.** The same green means the same thing at the
   porch, the bookcase, and the theater. Learnable in one exposure.
5. **Degrade honestly.** When Wi-Fi is down or the lock is unreachable, the
   touch point says so *before* you tap, and the physical key still works.
6. **No instructions.** No labels, no "tap here" text. Shape, finish, and
   light do the teaching.
7. **Works at 2am, in the dark, with hands full.** This is the real test.

## 5. The interaction vocabulary

Defined once, reused at every zone. This table is the spec.

| State | Ring | Sound | Band |
|---|---|---|---|
| Idle | Warm white, 2.5s breathe, ~25% | — | — |
| Someone near | Brief brighten to zone color | — | Single soft pulse |
| Reading | Amber spinner | — | — |
| Granted | Green bloom outward | Rising two-note chime | Double pulse, green |
| Confirmed (lock reports open) | Green settle, fade to idle | Soft latch click | — |
| Denied | Red, hard stop | Single low tone | Long buzz, red |
| Degraded / offline | Amber slow pulse | — | — |
| Asleep (quiet hours) | Off | — | — |

**The granted/confirmed split matters.** The Nest x Yale runs through Google's
cloud, so unlock can take seconds. The chime fires on *command accepted* so the
tap feels instant; the latch click fires on *lock confirmed* so nobody walks
away from a door that never opened. If confirmation never arrives, the ring
goes amber and the phone gets a notification.

## 6. Phases

Each phase has an exit criterion. Do not start the next one until it is met.

**Phase 0 — Validate (1 evening).** Three kill risks, tested before buying
anything else:
- A PN532 reads a stable UID from each band, repeatably.
- The Nest x Yale is controllable from HA via the HACS integration, and the
  observed unlock latency is measured and written down.
- A published BLE code makes a charged MagicBand+ light up, tested from a
  phone with nRF Connect.

*Exit: all three confirmed, or the scope changes to match reality.*

**Phase 1 — The front porch (2 weekends).** One touch point, one job, in its
finished enclosure. Breadboard first, but do not declare the phase done until
it is weather-sealed and mounted.

*Exit: every adult in the house has used it to get in, three days running,
without comment.*

**Phase 2 — The vocabulary (1 weekend).** Interior goodbye touch point, auto
relock, quiet hours, degraded state, notification on every unlock.

*Exit: the offline state is visibly distinct, verified by pulling the HA
container mid-tap.*

**Phase 3 — Proximity and band haptics (2 weekends).** Beacon nodes with
mmWave presence at the porch and one interior zone. Tuned TX power, cooldowns.

*Exit: walking to the front door at night produces one pulse, not five, and
nothing buzzes when the house is empty.*

**Phase 4 — The bookcase (1-2 weekends).** Second experience zone: a tap
wakes a Lumos display of the library. First zone that proves the pattern
generalizes beyond locks.

*Exit: a guest tries it unprompted after seeing it once.*

**Phase 5 — Polish (ongoing).** Enclosure v2 based on what actually annoyed
people, sound design pass, family onboarding.

## 7. Risks

| Risk | Severity | Mitigation |
|---|---|---|
| Nest x Yale integration is reverse-engineered and can break on any Google update | High | Never the only way in. Keypad and key stay. Budget for a Matter or Z-Wave lock as the eventual fix. |
| UID is trivially cloneable | High | Presence and hours gating, notification on every unlock, and honesty that this adds convenience at some security cost |
| Cloud unlock latency ruins the moment | Medium | Granted/confirmed split above; measure in Phase 0 before committing |
| Household veto after one lockout | Fatal | Physical key always works; degraded state is visible before tapping |
| MagicBand+ battery dead, no haptics | Medium | Band feedback is always an extra, never load-bearing |
| Kids spam the touch point | Low | Rate limit with a playful response, not a dead one |
| Porch weather and summer heat | Medium | ASA or PETG, gasketed, drip lip, no PLA |

## 8. Success metrics

Measured two weeks after Phase 2:

- Tap to door-open under 3 seconds at the 90th percentile.
- More than 80% of household entries use the band rather than a key or app.
- Zero lockouts. Non-negotiable.
- A guest works it after one demonstration, with no verbal instruction.
- Kids show it to a visitor without being prompted.

That last one is the real metric. The rest are hygiene.
