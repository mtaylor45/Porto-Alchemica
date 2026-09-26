# CLAUDE.md — Porta Alchemica

Context for Claude Code. Read this before touching anything.

> **Naming:** the project was previously called "Threshold" and the documents
> under `docs/` still use that name. Porta Alchemica supersedes it. Do not
> bulk-rename the docs; update names as files are touched for other reasons.

---

## What this is

A household touch point system. Disney MagicBands are tapped against readers
around the house; Home Assistant decides what happens. The first unit unlocks
the front door. Later units trigger experiences at other locations.

**The product is the two seconds between a raised wrist and a door opening.**
Every technical decision serves that. If a change makes the system more
capable but slower or less certain, it is the wrong change.

---

## Non-negotiable experience principles

These settle design arguments. Cite them in PRs.

1. **No visible technology.** No exposed boards, status LEDs, USB ports, or
   cables. Nothing on screen shows an IP address.
2. **Respond before you think.** Local feedback fires on tag detection, never
   after a network round trip. Target under 250ms.
3. **Never fail silently or confusingly.** Every tap produces a response,
   including refusal.
4. **One vocabulary everywhere.** The same colour means the same thing at
   every zone. See `docs/product-plan.md` section 5 — that table is the spec.
5. **Degrade honestly.** When HA or the lock is unreachable, the touch point
   shows its degraded state *before* someone taps. The physical key always
   works.
6. **No instructions.** No labels or printed text on any enclosure.
7. **Works at 2am, in the dark, with hands full.**

---

## Stack

| Layer | Choice | Notes |
|---|---|---|
| Firmware | ESPHome, esp-idf framework | Not Arduino, not raw ESP-IDF |
| MCU | ESP32-WROOM-32UE | External u.FL antenna, deliberate — see PCB spec 1.2 |
| NFC | PN532 over SPI, as a module | Never on-board; RF design stays vendor's problem |
| Transport | ESPHome native API | **Not MQTT.** Needs the two-way round trip |
| Orchestration | Home Assistant | Lock via HACS `ha-nest-yale-integration` |
| Band feedback | BLE beacon, custom ESPHome external component | `firmware/components/magicband_beacon/` |
| Presence | LD2410C mmWave over UART | |

---

## Repo layout

```
docs/                     design documents, treat as source of truth
firmware/
  touchpoint/             reader node ESPHome config
  beacon/                 proximity node ESPHome config
  components/
    magicband_beacon/     external component, BLE manufacturer-data advertiser
homeassistant/
  packages/               HA package YAML, one per concern
tools/
  ble-capture/            scripts for validating MagicBand+ BLE codes
hardware/
  pcb/                    KiCad project for TP-MAIN rev A
  enclosure/              CAD source and exported STLs
```

---

## Unvalidated assumptions — read this before building on them

Phase 0 has not been run. Three things are currently **assumed**, not proven.
Do not write code that depends on them without flagging it.

1. **MagicBand UIDs are stable.** Community reports say yes. Untested on
   Mike's specific bands.
2. **The Nest x Yale responds via the HACS integration, and its latency is
   tolerable.** The integration is reverse-engineered and can break with any
   Google update. Unlock latency is unmeasured and may be seconds, which
   changes the interaction design.
3. **Published BLE codes drive MagicBand+ lights and haptics.** The payload
   bytes in `firmware/beacon/` are placeholders. Company-ID byte order is an
   open question — see the comment in `magicband_beacon.h`.

If Phase 0 invalidates any of these, stop and raise it rather than working
around it.

---

## Conventions

- ESPHome configs use substitutions for zone name and colour so one file
  serves every node.
- Secrets in `secrets.yaml`, gitignored. Never commit a Wi-Fi password, API
  key, OTA password, or a MagicBand UID.
- **MagicBand UIDs are access credentials.** They belong in HA's tag registry
  and `secrets.yaml`, never in a committed config or a doc.
- HA config lives in `homeassistant/packages/`, one file per concern, not one
  giant automations.yaml.
- Every zone reuses the interaction vocabulary. Adding a new colour or sound
  requires updating the vocabulary table first.
- Firmware changes ship OTA. Nothing requires physical access after install.

---

## Ask before

- Adding a new state to the interaction vocabulary
- Anything that makes the band or the network load-bearing for entry
- Widening what a tap can do beyond the current zone's scope
- Committing anything that could contain a UID
- Changing the granted/confirmed split in the feedback flow

---

## Definition of done, per zone

- [ ] Rejoins Wi-Fi unattended after a 30-second power cut
- [ ] OTA succeeds from the mounted position
- [ ] Tap to local feedback under 250ms
- [ ] Degraded state verified by stopping HA mid-use
- [ ] Physical key tested
- [ ] Usable in full darkness
- [ ] No visible screws, cables, boards, or LEDs from any standing angle
- [ ] Someone who has never seen it works it after watching once, unprompted
