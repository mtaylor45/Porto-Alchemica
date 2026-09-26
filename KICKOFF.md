# Claude Code kickoff

## Setup, once

```bash
mkdir porta-alchemica && cd porta-alchemica
git init
mkdir -p docs firmware/{touchpoint,beacon,components/magicband_beacon} \
         homeassistant/packages tools/ble-capture hardware/{pcb,enclosure}
```

Copy in from the chat outputs:

| Chat file | Repo destination |
|---|---|
| `threshold-product-plan.md` | `docs/product-plan.md` |
| `threshold-implementation-guide.md` | `docs/implementation-guide.md` |
| `threshold-bom.md` | `docs/bom.md` |
| `threshold-pcb-design-spec.md` | `docs/pcb-design-spec.md` |
| `threshold-pcb-bom.csv` | `docs/pcb-bom.csv` |
| `threshold-pcb-placement.svg` | `docs/pcb-placement.svg` |
| `threshold-printed-finish-addendum.md` | `docs/printed-finish-addendum.md` |
| `threshold-render-prompts.md` | `docs/render-prompts.md` |
| `threshold-integrated-render-prompts.md` | `docs/render-prompts-integrated.md` |
| `magicband-porch.yaml` | `firmware/touchpoint/touchpoint.yaml` |
| `magicband-automations.yaml` | `homeassistant/packages/porch.yaml` |
| `beacon-node-bookcase.yaml` | `firmware/beacon/beacon.yaml` |
| `magicband_beacon/*` | `firmware/components/magicband_beacon/` |

Plus `CLAUDE.md`, `README.md`, `TASKS.md` at the root.

`.gitignore`:

```
secrets.yaml
.esphome/
*.local.md
band-uids*
```

Commit before the first session.

---

## First session prompt

> Read CLAUDE.md and TASKS.md, then read docs/product-plan.md sections 4 and 5
> — those are the experience principles and the interaction vocabulary, and
> they decide design questions.
>
> We are at Phase 0. Nothing is validated yet and three assumptions are listed
> in CLAUDE.md. Your job this session is task 0.1 only: write
> firmware/touchpoint/validation.yaml. ESP32-WROOM-32 devkit, PN532 over SPI
> on CLK 18 / MISO 19 / MOSI 23 / CS 5, esp-idf framework. It should log the
> UID on every tag read and do nothing else — no LEDs, no audio, no Home
> Assistant integration. Include a secrets.yaml.example.
>
> Then write tools/ble-capture/README.md documenting the nRF Connect procedure
> for task 0.5, including the open question about company-ID byte order.
>
> Do not start Phase 1. Do not write the LED or audio code yet. If you think
> something in the docs is wrong, say so rather than silently working around
> it.

---

## Session discipline

- One task per session where possible. This project has a long backlog and a
  short set of load-bearing decisions.
- When a Phase 0 result contradicts a doc, update the doc in the same commit
  as the finding.
- Never commit a MagicBand UID. They are access credentials.
- If Claude proposes adding a colour, sound, or state, check it against the
  vocabulary table first.
