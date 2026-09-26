# TASKS

Work top to bottom. Do not start a phase before the previous one's exit
criterion is met.

---

## Phase 0 — Validation

Nothing else gets built until these three pass or the scope changes to match
what's actually true.

- [ ] **0.1** Write `firmware/touchpoint/validation.yaml` — ESP32 + PN532 over
      SPI, logs UID on tag read, nothing else. No LEDs, no audio, no HA.
- [ ] **0.2** Tap each band five times. Record UIDs in a **gitignored** local
      note, not in the repo.
- [ ] **0.3** Install `ha-nest-yale-integration` via HACS. Confirm
      `lock.unlock` works.
- [ ] **0.4** Measure unlock latency. Ten trials, service call to audible
      latch. Write the median and p90 into `docs/product-plan.md` section 5.
      **This number decides the interaction design.**
- [ ] **0.5** Validate a BLE code against a charged MagicBand+ using nRF
      Connect. Record working payloads in `tools/ble-capture/codes.md`.
- [ ] **0.6** Write findings into `docs/phase-0-results.md`, including
      anything that failed.

**Exit:** all three assumptions in `CLAUDE.md` resolved to proven or
disproven, in writing.

---

## Phase 1 — Front porch

- [ ] **1.1** `firmware/touchpoint/touchpoint.yaml` with substitutions for
      zone name and colour
- [ ] **1.2** Idle breathe animation. Stop and look at it for a full minute
      before continuing — if the idle state isn't pleasant, nothing later
      fixes it
- [ ] **1.3** Tag detection with local amber spinner, no HA involvement
- [ ] **1.4** `homeassistant.tag_scanned` wired up, tags named in the HA UI
- [ ] **1.5** HA-callable actions: granted, confirmed, denied, degraded
- [ ] **1.6** `homeassistant/packages/porta_alchemica_porch.yaml` — unlock
      automation with presence and hours gating
- [ ] **1.7** Granted/confirmed split (chime on accept, latch click on lock
      confirmation, amber + notification on timeout)
- [ ] **1.8** Auto-relock after 90 seconds
- [ ] **1.9** Unlock notification with band name and timestamp
- [ ] **1.10** Rate limit: >5 taps in 10s gives a playful response, no lock
      action
- [ ] **1.11** Three audio files, each under 800ms, loudness-normalised
- [ ] **1.12** Enclosure v1 printed, finished, sealed, mounted

**Exit:** every adult in the house has used it to get in, three days running,
without commenting on it.

---

## Phase 2 — Vocabulary

- [ ] **2.1** Interior goodbye touch point, same firmware, different zone
      colour
- [ ] **2.2** Degraded watchdog on lock entity `unavailable`
- [ ] **2.3** Quiet hours: ring off, sound muted, tap still works
- [ ] **2.4** Verify degraded state by stopping HA mid-tap

**Exit:** offline state visibly distinct, verified by pulling the container.

---

## Phase 3 — Proximity and haptics

- [ ] **3.1** Finish `firmware/components/magicband_beacon/` with validated
      payloads from Phase 0
- [ ] **3.2** `firmware/beacon/beacon.yaml` with LD2410C trigger and cooldown
- [ ] **3.3** Tune TX power down until range matches the intended zone
- [ ] **3.4** Tune cooldown until a normal walk past produces exactly one
      pulse
- [ ] **3.5** Empty-house test: one hour, zero activations

**Exit:** approaching the front door at night produces one pulse, not five.

---

## Phase 4 — Bookcase

- [ ] **4.1** Second experience zone: tap wakes a Lumos display of the library
- [ ] **4.2** Confirm the vocabulary transferred with no re-teaching

**Exit:** a guest tries it unprompted after seeing it once.

---

## Hardware track (parallel, gated on Phase 0)

- [ ] **H.1** KiCad schematic from `docs/pcb-design-spec.md` sections 3 and 4
- [ ] **H.2** Measure actual SK6812 ring current at full white before
      finalising copper widths
- [ ] **H.3** Layout per spec section 7
- [ ] **H.4** Fab five boards
- [ ] **H.5** Bring-up in the order given in spec section 9 — power first,
      never populate everything at once
- [ ] **H.6** Enclosure CAD with uniform 2.5mm walls and 1.5° draft
      throughout, so the design survives a move to injection moulding
- [ ] **H.7** Resolve open questions from the render review: acoustic port,
      NFC coil size, radar placement, drip lip above the bezel, mounting
      method
