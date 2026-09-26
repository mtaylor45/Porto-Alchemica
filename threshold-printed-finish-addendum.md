# Threshold — All-Printed Enclosure Addendum

Amends the product plan and BOM. No machined metal, no wood. Every housing
component printed and finished.

---

## 1. What actually changes

The original rule was that one real material per unit separates a product from
a project. That still holds, but the material no longer has to be *sourced* —
it has to be *convincing*. A printed bezel with brass powder in an epoxy skin
is real metal on the surface, patinas honestly, and costs an afternoon instead
of twelve dollars.

The new rule: **finish one part to a high standard rather than all parts to a
medium one.** The brass bezel carries the whole object. The charcoal body only
has to be clean and matte, which the printer can do unassisted.

Budget four to six hours of finishing per exterior unit for the first one, two
to three once you have the process down. Put it on the Phase 1 schedule
explicitly or it will get skipped.

---

## 2. The charcoal body — nearly free

Use the slicer, not sandpaper.

- **ASA, fuzzy skin enabled** on the external face. Thickness 0.3mm, point
  distance 0.6mm. This produces exactly the fine stippled texture in the
  renders *and* it hides layer lines, which is why it's the efficient path.
- 4 walls minimum for water resistance. 0.12mm layers on visible surfaces.
- Print the face down on a textured PEI plate if you want an alternative
  grain, though fuzzy skin gives more control.
- Finish: scuff lightly, one coat of matte UV-resistant clear. Done.

Important revision from the earlier spec: **paint the interior cavity matte
black** regardless. ASA is translucent enough at thin walls to glow at the
edges, which will look like a light leak rather than a feature.

---

## 3. The brass bezel — two routes

### Route A: cold-cast brass (recommended)

Genuinely metal on the surface. Ages correctly because it *is* aging.

1. Print the bezel in PETG or ASA, 0.12mm layers.
2. Sand the outer face 220 → 400. Don't chase perfection; the next step fills.
3. Mix fine brass powder into slow-cure epoxy, roughly 2:1 by volume, and
   brush a thin even coat over the visible faces.
4. Cure fully. Sand back 400 → 800 → 1500 until the brass particles are
   exposed and the surface shines. Chuck the ring on a bolt in a drill and
   sand while it spins for a true concentric brushed grain.
5. Age it: Birchwood Casey Brass Black or liver of sulfur, brushed on and
   quickly rinsed, darkens the recesses. Buff the high points back with 0000
   steel wool.
6. Seal with 2K automotive clear.

### Route B: Rub 'n Buff over dark base (faster, less durable)

1. Print, sand 220 → 400, two coats filler primer, sand 600.
2. Gloss black base coat. The dark ground is what makes metallics read as
   metal rather than paint.
3. Rub 'n Buff Antique Gold applied with a fingertip, buffed with a soft cloth.
4. Thinned burnt umber oil wash into the recesses, wiped off the highs.
5. **Must be sealed.** Rub 'n Buff is wax-based and will not survive a porch
   unprotected. 2K clear, not rattle-can lacquer.

Route B is about ninety minutes and looks excellent indoors. For the exterior
unit in full sun, Route A will still look right in three years.

---

## 4. The lens — keep buying it

A 3mm frosted acrylic disc is a bought part, not a machined one, and it stays.
Printed diffusers band visibly no matter how carefully you tune them, and the
even glow is the single most important optical quality in the whole product.
Eight dollars, and it's the one thing the printer genuinely can't match.

If you insist on printing it: translucent white PETG, 3 walls, concentric top
and bottom layers, a 3mm air gap to the LEDs, and interior cavity painted
gloss white. It will still band. Look at it before committing.

---

## 5. Exterior durability

The finish is now the weather barrier as much as the plastic is.

| Threat | Mitigation |
|---|---|
| UV on ASA | Dark pigment helps; 2K clear with UV inhibitor is the real answer |
| UV on metallic finish | Route A survives; Route B fades without 2K clear |
| Thermal cycling | Uniform 2.5mm walls, avoid thick-to-thin transitions that crack |
| Water at seams | Gasket channel, drip lip above the bezel, no upward-facing ledges |
| Pollen and grime | Raise the trefoil as relief rather than engraving it — a wipe should clean it |

SprayMax 2K aerosol is the accessible option for real two-part clear. Use it
outdoors with a respirator; it contains isocyanates.

---

## 6. Keeping the commercial door open

If this might become a product, five CAD decisions now cost nothing and save a
full redesign later:

1. **Uniform wall thickness, 2.5mm.** Injection molding demands it; printing
   doesn't care.
2. **1.5 degrees of draft** on every vertical face. Invisible in a print,
   mandatory in a tool.
3. **No undercuts** that a two-part mold couldn't release.
4. **Model bosses for heat-set inserts as bosses**, not as plain holes. They
   become molded bosses directly.
5. **Specify the texture as a Mold-Tech number** in your notes, not as a
   slicer setting. MT-11020 is close to what fuzzy skin produces.

At volume the bezel becomes a spun or stamped brass part and the finishing
labor disappears entirely, which is exactly the economics that justifies
tooling. Design as though that day comes.

---

## 7. BOM delta

**Remove:** brass trim ring ($12), hardwood offcut ($15).

**Add, mostly one-time:**

| Item | ~$ | Notes |
|---|---|---|
| Fine brass powder, 100g | 18 | Route A. Enough for many units |
| Slow-cure epoxy, 250ml | 14 | |
| Wet/dry sandpaper, 220-1500 | 12 | |
| Birchwood Casey Brass Black | 12 | |
| 0000 steel wool | 5 | |
| SprayMax 2K clear, matte | 28 | Per can, a few units each |
| Filler primer | 10 | Route B only |
| Rub 'n Buff Antique Gold | 9 | Route B only |
| Burnt umber oil paint | 8 | |
| Respirator, organic vapor | 35 | Not optional with 2K |

First unit lands around $110 in consumables, most of it reusable. Marginal
cost per unit after that is under $10, which is cheaper than the brass ring
was.
