# Threshold — Bill of Materials

Prices are rough US street prices and will drift. Quantities assume one porch
unit, one interior unit, and two beacon nodes. Buy Phase 0 parts only until
Phase 0 passes.

---

## Phase 0 — validation kit (buy first, ~$35)

| Item | Qty | ~$ | Notes |
|---|---|---|---|
| PN532 NFC module, red board | 1 | 12 | Set DIP switches to SPI. Buy two from different sellers; quality varies wildly |
| ESP32-WROOM-32 devkit | 1 | 8 | Needs classic ESP32 for BLE + Wi-Fi |
| Breadboard + dupont jumpers | 1 | 10 | |
| MagicBand+ (charged) | 1 | — | Already owned |

Nothing else gets ordered until a PN532 reads your bands, the lock responds
from HA, and a BLE code makes a band glow.

---

## Porch touch point (~$120 plus enclosure)

### Electronics

| Item | Qty | ~$ | Notes |
|---|---|---|---|
| ESP32-WROOM-32 devkit | 1 | 8 | |
| PN532 NFC module | 1 | 12 | Better range through an enclosure than RC522 |
| SK6812 RGBW ring, 24 LED, 86mm | 1 | 12 | **RGBW, not RGB.** The white channel is what makes the idle glow look like the parks instead of a gadget |
| MAX98357A I2S amplifier | 1 | 6 | Cleaner than DFPlayer, and audio files live on the ESP |
| 3W 4Ω speaker, 40mm | 1 | 5 | |
| LD2410C mmWave presence sensor | 1 | 6 | Phase 3 |
| 74AHCT125 level shifter | 1 | 2 | 3.3V data to 5V LEDs; skip it and you get intermittent flicker |
| 1000µF electrolytic cap, 6.3V+ | 1 | 1 | Across the LED 5V rail |
| 470Ω resistor | 1 | — | In series on LED data |
| Perfboard or small custom PCB | 1 | 5 | Five PCBs from JLCPCB cost about this; worth it for a permanent install |
| WAGO 221 lever nuts | 1 pk | 8 | Serviceability without a soldering iron on the porch |

### Power

| Item | Qty | ~$ | Notes |
|---|---|---|---|
| PoE splitter, 5V 2.4A | 1 | 18 | **Strongly preferred.** One cable, no wall wart, no visible power brick |
| *or* 5V 3A supply + outdoor-rated low-voltage run | 1 | 15 | Fallback if no ethernet reaches the porch |
| Waterproof cable gland, M12 | 1 | 2 | |

### Enclosure and finish

| Item | Qty | ~$ | Notes |
|---|---|---|---|
| ASA filament, opaque dark | 1 kg | 30 | **Not PLA.** A Virginia porch in July will sag it |
| Frosted acrylic disc, 3mm, cut to ring OD | 1 | 8 | Even diffusion; printed diffusers band and look cheap |
| Brass or aged-bronze trim ring | 1 | 12 | The single most important $12 in this BOM — see the guide |
| M3 brass threaded inserts | 20 | 6 | |
| M3 socket screws, stainless, bottom entry | 10 | 5 | Never visible from the front |
| Closed-cell foam gasket tape, 3mm | 1 roll | 6 | |
| Neodymium magnets, 6x2mm | 8 | 5 | Hidden front-panel retention |
| Matte clear UV coat | 1 | 10 | |

---

## Interior touch point (~$95)

Same as above, minus the PoE splitter, gland, gasket, ASA, and UV coat. Add:

| Item | Qty | ~$ | Notes |
|---|---|---|---|
| GC9A01 round LCD, 1.28" | 1 | 10 | Optional. Only where a screen earns its place |
| USB-C 5V 3A supply | 1 | 10 | |
| Walnut or oak veneer / hardwood offcut | 1 | 15 | Interior units should read as furniture |

---

## Beacon node, per zone (~$25)

| Item | Qty | ~$ | Notes |
|---|---|---|---|
| ESP32-WROOM-32 devkit | 1 | 8 | |
| LD2410C mmWave sensor | 1 | 6 | |
| USB-C 5V 1A supply + short cable | 1 | 8 | |
| Small printed shell | 1 | 2 | These genuinely should be invisible — behind furniture, above a door frame |

---

## Shared tools and consumables

| Item | ~$ | Notes |
|---|---|---|
| Soldering iron, flux, solder | 40 | If not already owned |
| Heat-set insert tip for the iron | 10 | Makes brass inserts painless |
| Multimeter | 25 | |
| Logic analyzer, cheap clone | 12 | Saves an evening the first time SPI misbehaves |
| Flipper Zero *or* an Android phone with nRF Connect | 0-170 | The phone is free and sufficient |

---

## Rough totals

| | ~$ |
|---|---|
| Phase 0 | 35 |
| Phase 1 (porch unit, complete) | 120 |
| Phase 2 (interior unit) | 95 |
| Phase 3 (two beacon nodes) | 50 |
| Enclosure materials, first run | 80 |
| **Through Phase 4** | **~380** |

Budget a second print run. The first enclosure is a prototype whether you
intend it to be or not.
