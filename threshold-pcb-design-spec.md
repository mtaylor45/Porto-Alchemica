# TP-MAIN rev A — Touch Point Mainboard Design Spec

**One board, two build variants.** Exterior and interior units share a single
PCB with different populated parts. Two separate designs would double the
fabrication cost, double the revision work, and split your bring-up debugging
across two unknowns. The delta between the variants is eleven components.

---

## 1. Architecture decisions

### 1.1 The board is a carrier, not a from-scratch design

The PN532 stays a module on a short cable. Designing a 13.56 MHz antenna coil
and matching network is real RF engineering, and getting it wrong shows up as
intermittent read failures that are miserable to diagnose. Keeping it modular
also buys a product win: the NFC antenna can sit directly behind the tap
target while the mainboard lives lower in the enclosure, out of the way.

Same reasoning for the LED ring and LD2410 — buy them, connect them.

### 1.2 ESP32-WROOM-32UE, not -32E

The -32E has a PCB antenna requiring a copper keepout and clear air around the
board edge. Your exterior enclosure has a **brass trim ring** around the face.
Metal that close will detune a PCB antenna, and you would discover this after
the enclosure is finished.

The -32UE takes a u.FL external antenna instead. Route the antenna to a spot
in the enclosure away from the brass, and the mechanical design and the RF
design stop fighting each other. Cost delta is about $1.

### 1.3 Four layers

Sig / GND / PWR / Sig. A solid ground plane under the switching regulator and
the digital bus is worth the ~$12 upcharge on a five-board order. Two layers
would work, but you would spend the savings on debugging.

### 1.4 Buck, not LDO

Peak 3.3V draw is ESP32 TX (~500mA) plus PN532 with its RF field energized
(~120mA) plus display backlight on the interior variant (~60mA). That is
roughly 700mA peak. An AP2112K at 600mA is under-spec, and an AMS1117
dissipating 1.2W inside a sealed outdoor enclosure in a Virginia July is a bad
idea. Use a 2A synchronous buck.

---

## 2. Power tree

```
5V in (PoE splitter or USB-C)
  ├─ PTC 2A resettable fuse
  ├─ SMAJ5.0A TVS (exterior only)
  ├─ P-FET reverse polarity protection
  │
  ├─ 5V rail ──┬─ SK6812 RGBW ring (2A budget, connector J2)
  │            ├─ 74AHCT125 level shifter
  │            ├─ MAX98357A amplifier
  │            └─ LD2410C sensor
  │
  └─ TPS562201 buck ─ 3.3V rail ─┬─ ESP32-WROOM-32UE
                                  ├─ PN532 module (via ferrite + 10µF local)
                                  └─ GC9A01 display (interior)
```

**Budget 2.5A at 5V.** A 24-pixel SK6812 ring at full white draws close to
1.9A on its own. Firmware caps brightness well below that, but the supply and
copper must survive someone setting brightness to 100%.

The ferrite bead on the PN532's 3.3V feed is not optional. Buck ripple
coupling into the NFC front end degrades read range.

---

## 3. Subcircuits

### 3.1 Input protection (J1)

| Ref | Part | Notes |
|---|---|---|
| F1 | 2A PTC resettable, 1812 | |
| D1 | SMAJ5.0A TVS | Exterior only, DNP interior |
| Q1 | DMG2301L P-MOSFET | Source to input, drain to rail, gate to GND through 100k |
| C1 | 470µF 10V electrolytic | Bulk at the input |
| C2 | 100nF 0402 | |

### 3.2 3.3V regulator

| Ref | Part | Value |
|---|---|---|
| U2 | TPS562201DDCR | SOT-23-6, 580kHz |
| L1 | 2.2µH shielded, 3A sat | |
| C3, C4 | 10µF 25V X5R 0805 | Input |
| C5, C6 | 22µF 6.3V X5R 0805 | Output |
| R1 | 100k 1% 0402 | Feedback high |
| R2 | 31.6k 1% 0402 | Feedback low, gives 3.30V |

Keep the input cap, switch node, and inductor loop tight. Switch node copper
small. Ground the output caps into the plane with two vias each.

### 3.3 LED level shifter

| Ref | Part | Notes |
|---|---|---|
| U3 | 74AHCT125 SOIC-14 | Powered from **5V**, this is the whole point |
| R3 | 470Ω 0402 | Series on the buffer output |
| C7 | 1000µF 10V | Across the LED 5V rail at J2 |
| — | — | Tie all three unused inputs to GND, unused OE pins to GND |

### 3.4 Audio

MAX98357A comes as a TDFN-16 that is unpleasant to hand-rework. Footprint the
**castellated breakout module** (U4) on 2.54mm pads instead. It solders flat,
costs a dollar more, and is replaceable.

Gain select: 100k from GAIN to GND gives 12dB, which is right for a 3W 4Ω
driver in a small sealed cavity. SD pin to GPIO2 with a 10k pulldown, so the
amp is muted at boot and GPIO2's strapping requirement is satisfied by the
same resistor.

### 3.5 Programming

Six-pin 2.54mm header (J7): 3V3, GND, TXD0, RXD0, EN, IO0. No onboard USB-UART
— after the first flash everything is OTA, and the bridge chip would be dead
weight inside a sealed enclosure. Include the standard two-transistor
auto-reset circuit (Q2, Q3, DTR/RTS) so an external adapter can flash without
button presses.

BOOT and EN as 3.2mm tactile switches, plus test pads next to each.

---

## 4. Pin assignment

Strapping pins (0, 2, 12, 15) and flash pins (6-11) handled deliberately.

| ESP32 GPIO | Net | Direction | Note |
|---|---|---|---|
| 18 | SPI_SCK | out | Shared bus |
| 19 | SPI_MISO | in | |
| 23 | SPI_MOSI | out | |
| 5 | NFC_CS | out | Strapping, pull-up is fine |
| 36 | NFC_IRQ | in | Input-only pin, correct use |
| 33 | NFC_RST | out | |
| 13 | LED_DATA | out | To 74AHCT125 |
| 26 | I2S_BCLK | out | |
| 25 | I2S_LRCLK | out | |
| 27 | I2S_DOUT | out | |
| 2 | AMP_SD | out | 10k pulldown, amp muted at boot |
| 17 | RADAR_TX | out | To LD2410 RX |
| 16 | RADAR_RX | in | From LD2410 TX |
| 35 | RADAR_PRESENCE | in | Input-only, digital out of LD2410 |
| 4 | LCD_CS | out | Interior |
| 32 | LCD_DC | out | Interior |
| 14 | LCD_RST | out | Interior |
| 15 | LCD_BL | out | Interior, 10k pulldown, PWM dimming |
| 21 | I2C_SDA | bidir | Expansion header |
| 22 | I2C_SCL | out | Expansion header |
| 0 | BOOT | in | Button + auto-reset |
| 34, 39 | spare | in | Broken out to test pads |

---

## 5. Connectors

All connectors face the **back** of the board. Nothing routes toward the lens.

| Ref | Type | Pins | Function |
|---|---|---|---|
| J1a | 5.08mm screw terminal | 2 | 5V in, exterior |
| J1b | USB-C 16-pin, power only | — | 5V in, interior. 5.1k CC pulldowns |
| J2 | JST-XH 3 | 3 | LED ring: 5V, DATA, GND |
| J3 | JST-XH 8 | 8 | PN532: 3V3, GND, SCK, MISO, MOSI, CS, IRQ, RST |
| J4 | JST-PH 2 | 2 | Speaker |
| J5 | JST-XH 5 | 5 | LD2410: 5V, GND, TX, RX, OUT |
| J6 | JST-SH 8 | 8 | Display, interior only |
| J7 | 2.54 header | 6 | Programming |
| J8 | JST-SH 4 (Qwiic) | 4 | I2C expansion |

Pin 1 silkscreened with a square pad and a triangle on every connector. You
will thank yourself at 11pm.

---

## 6. Mechanical

- **Outline:** 70.0mm circle. Sits behind the 86mm LED ring, not inside it.
- **Mounting:** 4× 3.2mm holes on a 60mm bolt circle at 45°, 135°, 225°, 315°.
  Plated, tied to GND, 6mm annular keepout.
- **Orientation notch:** 4mm flat on the outline at 0° so it cannot be
  installed rotated.
- **Height:** tallest component is the electrolytic at ~11mm. Reserve 15mm.
- **Antenna:** u.FL at the 180° edge, pointing away from the brass ring.
- **Keepout:** 5mm clear of all mounting holes for enclosure bosses.

---

## 7. Layout rules

| Item | Value |
|---|---|
| Stackup | 4 layer, 1oz, JLC7628 |
| Min trace / space | 0.15mm |
| Via | 0.3mm drill / 0.6mm pad |
| 5V LED rail | 2.0mm minimum, or a pour |
| 3.3V rail | 0.8mm |
| Signals | 0.25mm |
| Layer 2 | Solid ground, unbroken under the SPI bus and the regulator |
| Layer 3 | Power planes, 5V and 3V3 split |

Specifics that matter:
- Stitch ground vias every 5mm along the board perimeter.
- Keep the buck switch node under 25mm² of copper.
- Route SPI as a group, 5mm clear of the inductor.
- Every IC gets a 100nF 0402 within 2mm of its supply pin.
- Thermal relief on the screw terminal pads or you will fight the iron.

---

## 8. Variant BOM delta

| Ref | Exterior | Interior |
|---|---|---|
| D1 TVS | Populate | DNP |
| J1a screw terminal | Populate | DNP |
| J1b USB-C | DNP | Populate |
| J6 display connector | DNP | Populate |
| LCD pull-downs (R8-R9) | DNP | Populate |
| Conformal coating | Yes, mask all connectors | No |

---

## 9. Bring-up order

Do not populate everything and hope.

1. Power section only. Confirm 3.30V ±2% at no load, then at 500mA dummy load.
   Check ripple on a scope; over 50mV means the layout needs work.
2. Add the ESP32 and programming header. Flash a blink. Confirm Wi-Fi RSSI
   with the antenna in its final enclosure position, with the brass ring
   installed. This is the test the -32UE decision exists for.
3. Add the level shifter and ring. Confirm no flicker at full white for ten
   minutes, and check the regulator temperature.
4. Add PN532. Measure read range through the actual lens material, not open
   air. If range dropped, that is what the ferrite and local decoupling are
   for.
5. Add audio, then radar.
6. Only then conformal coat.

---

## 10. Known open items for rev B

- The 1000µF electrolytic is the tallest part and the first thing to fail in
  heat. A polymer cap costs more and would let the enclosure get thinner.
- No onboard temperature sensor. Worth adding to monitor the exterior unit
  through a summer.
- No provision for a tamper switch, which the exterior unit arguably wants.
- If interior units never get displays in practice, J6 and its four GPIOs come
  back for something better.
