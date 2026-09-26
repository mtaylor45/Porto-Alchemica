# Threshold — Implementation Guide

---

## Phase 0 — Validate before you build

Three tests. Any failure changes the project, so do them first.

**0.1 Read the bands.** Wire a PN532 to an ESP32 over SPI (CLK 18, MISO 19,
MOSI 23, CS 5), flash the ESPHome config from the earlier draft, and tap each
band five times. Record the UIDs.

*Pass:* the same UID every time, for every band. *Fail:* a UID that changes
means the reader path needs rethinking before anything else proceeds.

**0.2 Drive the lock.** Install the Nest x Yale HACS integration, confirm
`lock.unlock` works, and **time it**. Use a stopwatch, ten trials, from
service call to audible latch.

*This number sets the whole interaction design.* Under 1.5s, a single
granted state is enough. Over that, the granted/confirmed split in the product
plan is mandatory.

**0.3 Light a band.** Charge a MagicBand+, open nRF Connect, advertiser tab,
add manufacturer data with company ID 0183 and a published code. Confirm the
band responds.

*Fail here and Phases 3 loses its band-side half.* The readers still work; say
so out loud rather than quietly carrying a dead assumption forward.

---

## Phase 1 — The porch touch point

### Wiring

| From | To | Note |
|---|---|---|
| PN532 SCK/MISO/MOSI/CS | GPIO 18 / 19 / 23 / 5 | DIP switches to SPI mode |
| PN532 VCC | 3.3V | Not 5V |
| LED ring DIN | GPIO 13 via 74AHCT125, 470Ω in series | |
| LED ring 5V | 5V rail, 1000µF across it | |
| MAX98357A BCLK/LRC/DIN | GPIO 26 / 25 / 22 | |
| LD2410 TX/RX | GPIO 16 / 17, 256000 baud | |
| All grounds | Common | Single star point on the perfboard |

Two failure modes worth pre-empting. Long LED runs without the level shifter
work on the bench and glitch on the porch. And one community build documented
GPIO18 refusing to drive LED data despite the guide saying otherwise, so if
the ring misbehaves, move the data pin before you suspect the ring.

### Firmware

Start from the ESPHome config already drafted. Confirm in this order:

1. Boot, Wi-Fi, OTA. Never flash by cable again after this.
2. Idle breathe animation only. Stare at it for a minute. If the idle state
   is not pleasant to look at, nothing later will save the product.
3. Tag detection with local amber spinner, no HA involvement.
4. `homeassistant.tag_scanned`, tags named in the HA UI.
5. HA-called actions for granted, confirmed, denied, degraded.
6. Audio last. It is the easiest thing to get wrong and the easiest to tune.

### Home Assistant

Use the automations already drafted, plus:

- **Degraded watchdog.** If the lock entity is `unavailable`, push the reader
  into the amber degraded state. The touch point should look wrong *before*
  someone tries it.
- **Quiet hours.** Ring off and sound muted 10pm-6am; the tap still works.
- **Unlock notification.** Every band unlock sends a phone notification with
  which band and what time. This is the security backstop that makes the UID
  weakness tolerable.
- **Rate limit.** More than five taps in ten seconds gets a playful rainbow
  and no lock action. Kids will find this. Make finding it fun.

### Sound design

Three files, nothing more. A rising two-note chime for granted, a soft latch
click for confirmed, a single low tone for denied. Keep every one under 800ms.
Normalize them to the same perceived loudness, then set the volume so it is
audible from the sidewalk but not from the neighbor's porch. Test at night.

---

## Phase 2-3 — Vocabulary and proximity

Roll out the interior goodbye touch point using the identical firmware with a
different zone color. The point of Phase 2 is not features, it is proving the
vocabulary transfers without re-teaching anyone.

For beacons, use the external component and node config already drafted. Tune
in this order: TX power down until the band only responds where you want it
to, then cooldown up until a normal walk past produces exactly one pulse.
Then leave the house empty for an hour and confirm silence.

---

## Enclosure — the part that decides whether this is a product

The seven prior projects all print a Mickey-head box and stop. That is the
single clearest place to differentiate, and it costs less than the
electronics.

### The rule

**Mixed materials read as a product. Fully 3D-printed reads as a project.**
One brass ring, one piece of real wood, or one cut acrylic lens does more for
perceived quality than fifty hours of modeling. Budget for one non-printed
element per unit minimum.

### Porch unit

- **Material:** ASA. PETG acceptable. PLA will deform on a south-facing porch
  in a Virginia summer, and it will do it in year one.
- **Form:** think lantern or door medallion, not gadget. It should look
  plausible as something a previous owner installed. Ornament is fine;
  buttons, vents, and visible fasteners are not.
- **The tap target must be findable by hand in the dark.** Recess it 2-3mm,
  change the surface finish, give it a tactile edge. No printed "TAP HERE."
  Shape teaches; labels admit failure.
- **Diffusion:** print the light ring housing in opaque dark filament, paint
  the interior cavity matte black to kill bleed, and use a separate 3mm
  frosted acrylic disc as the lens. Printed diffusers band visibly.
- **Fasteners:** brass heat-set inserts, stainless screws entering from the
  bottom or back only. Magnets for the front bezel so it comes off without
  tools.
- **Weather:** gasket channel with closed-cell foam tape, a drip lip above the
  seam, cable gland on the underside, and everything sloped so water leaves.
  Print the shell at 4 walls minimum; 2 walls will wick.
- **Finish:** matte UV clear coat. Layer lines catch dirt outdoors, and gloss
  makes the print obvious.

### Interior units

More freedom, more whimsy. A brass plate set into a bookcase, a false book
spine, a wall sconce. The bookcase unit should be genuinely hidden until it
glows, which is the whole trick.

### Beacon nodes

These should never be seen. Above a door frame, behind a books, under a shelf
lip. Print them in whatever is on the spool. If someone notices one, move it.

### Cable discipline

One cable per unit, entering from below or behind, and nothing visible from
standing height. A perfect enclosure with a visible white USB cable is a
failed enclosure.

---

## Commissioning checklist

Before declaring any zone done:

- [ ] Boots and rejoins Wi-Fi after a 30-second power cut, unattended
- [ ] OTA update succeeds from its mounted position
- [ ] Idle state is pleasant to look at for a full minute
- [ ] Tap to local feedback is under 250ms
- [ ] Degraded state verified by stopping Home Assistant mid-use
- [ ] Physical key tested and confirmed working
- [ ] Audible from where people stand, not from the neighbor's yard
- [ ] Readable and usable in full darkness
- [ ] No visible screws, cables, boards, or status LEDs from any standing angle
- [ ] Someone who has never seen it works it after watching once, without being told anything

That last box is the only one that matters. The other nine are how you earn
the right to check it.

---

## Family rollout

Do not demo it. Set it up, say nothing, and let someone find it. If it needs
an explanation, go back to the enclosure.
