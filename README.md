# Porta Alchemica

*The alchemical door. Tap a band, the house recognises you.*

A household touch point system built on Disney MagicBands, ESP32 readers, and
Home Assistant. Bands are tapped against readers around the house; HA decides
what happens and the reader reflects the decision in light, sound, and — on
MagicBand+ — haptics on the band itself.

The front door is the first zone. Others follow.

## Status

**Phase 0 — validation. Nothing is built yet.**

Three assumptions need proving before hardware is ordered beyond the
validation kit. See `CLAUDE.md`.

## Why this is not another MagicBand reader

Seven public projects exist. All of them match a UID locally and play a sound.
This one adds:

- Home Assistant makes the decision; the reader shows the outcome
- The band itself lights and vibrates in sync, via BLE beacon commands
- Proximity nodes pre-announce a nearby touch point before you reach it
- One interaction vocabulary shared across every zone in the house
- Enclosures treated as product design rather than as a case for a PCB

## Quick start

```bash
# validation only — no hardware beyond the Phase 0 kit
cd firmware/touchpoint
esphome run validation.yaml
```

Then work `TASKS.md` top to bottom. Do not skip Phase 0.

## Documents

| File | What it covers |
|---|---|
| `docs/product-plan.md` | Vision, principles, personas, phases, risks, metrics |
| `docs/implementation-guide.md` | Build order, wiring, HA config, enclosure design |
| `docs/bom.md` | Parts by phase |
| `docs/pcb-design-spec.md` | TP-MAIN rev A hardware design |
| `docs/pcb-bom.csv` | PCB BOM |
| `docs/printed-finish-addendum.md` | All-printed enclosure finishing process |
| `docs/render-prompts.md` | Visual direction |

## Hardware

One PCB, two build variants. 70mm circular carrier board: ESP32-WROOM-32UE,
2A buck, level-shifted LED output, connectors for PN532, LD2410C, speaker, and
an optional display. Exterior and interior differ by eleven components.

Enclosures are 3D printed in ASA and hand-finished. The brass bezel is
cold-cast brass powder in epoxy, sanded back and chemically aged.

## Safety note

Tap-to-unlock adds convenience and expands attack surface. A MagicBand UID is
trivially cloneable by anyone who gets a reader near a band. Access is gated on
time of day and presence, every unlock sends a notification, and the physical
key is never removed from the equation. Read `docs/product-plan.md` section 7
before widening access.
