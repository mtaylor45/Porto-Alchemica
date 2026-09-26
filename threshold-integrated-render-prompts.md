# Threshold — Integrated Doorbell + Touch Point Render Prompts

A single vertical entry plate carrying a Ring video doorbell above and the
Threshold touch point below. Guests press the doorbell. Household members tap
the trefoil.

**Measure your actual Ring before any of this reaches CAD.** Wired, battery,
and Pro models differ by 30mm in length and 6mm in depth, and the bay has to
be model-specific. The renders below describe a slim wired unit.

---

## 1. Hero render — dusk, idle

> Product photography of a vertical wall-mounted entry plate beside a dark
> painted front door, mounted on weathered white wood trim. The plate is a
> single elongated form, roughly 290mm tall and 120mm wide, in matte
> charcoal-graphite with a fine even surface texture. The upper third holds a
> slim black video doorbell set flush into a recessed bay, its small dark
> camera lens near the top and a subtle round illuminated button below it. The
> lower third holds a circular element 110mm across: an aged brass ring with
> hand-finished patina surrounding a narrow frosted white acrylic lens ring
> glowing soft warm white at low intensity, with a shallow recessed brushed
> brass disc at its center engraved with a simple three-lobed trefoil
> ornament. Between the two elements the charcoal plate narrows slightly into
> a waist, creating one continuous object rather than two devices bolted
> together. A fine brass pinstripe runs along the outer edge of the entire
> plate, tying the top to the bottom. No visible screws, no labels, no text,
> no exposed cables. A subtle beveled drip lip crowns the top edge. Dusk,
> blue hour, soft directional light from camera-left, one warm porch light
> off-frame. Shot on 85mm, f/2.8, shallow depth of field. Craftsman-era door
> hardware crossed with restrained modern industrial design. Photorealistic,
> natural materials, muted palette.

---

## 2. Night, activated

> Night product photography of the same vertical charcoal and brass entry
> plate. The lower circular element's frosted lens ring glows clear emerald
> green at moderate brightness, light blooming across the aged brass bezel and
> spilling softly onto the white painted trim. The video doorbell above
> remains dark except for a faint cool blue ring around its button, visibly
> separate in color and character from the green below. Deep night
> background, the porch beyond nearly black. Shot on 85mm, f/2.0. The two
> lights read as two different invitations. Photorealistic, no lens flare, no
> light rays, no sparkle.

---

## 3. Three-quarter, service access

> Three-quarter angled product photograph of a vertical charcoal entry plate
> on white wood trim, viewed from the lower left so the depth of the assembly
> is visible. Roughly 30mm deep. A slim black video doorbell sits recessed in
> the upper bay with a visible fine shadow gap around it indicating it lifts
> out independently. A narrow slotted acoustic vent runs along the underside
> of the lower circular section, tucked beneath its brass bezel and nearly
> invisible from straight on. The whole plate sits on a slim matching rear
> cleat with a single cable gland at the bottom. Matte finishes, crisp edges,
> soft overcast daylight. Shot on 50mm, f/5.6, moderate depth of field.
> Photorealistic.

---

## 4. Exploded technical view

> Clean exploded technical product render of a vertical wall-mounted entry
> plate, components separated along a single horizontal axis against a soft
> neutral off-white background. From front to back: an aged brass edge trim
> and a separate brass circular bezel ring, a frosted white acrylic lens ring,
> a tall matte charcoal front plate with a recessed rectangular doorbell bay
> and a circular lower opening with an engraved brass center disc, a slim
> black video doorbell unit with its own small white factory backplate, a
> circular ring of 24 addressable LEDs on a black PCB, a large square NFC
> antenna coil module roughly the diameter of the brass center disc, a small
> rectangular radar sensor board, a 70mm circular dark green four-layer
> circuit board with a silver shielded module and small connectors along its
> lower edge, a small speaker driver, a closed-cell foam gasket, and a tall
> matte charcoal rear housing with a cable gland at its base. Even soft studio
> lighting, gentle contact shadows, thin neutral-grey alignment lines. No text
> callouts, no numbers.

---

## 5. Negative prompt

```
Mickey Mouse, Disney, cartoon character, mouse ears, theme park, two separate
devices, gap between devices, mismatched housings, intercom panel, keypad,
touchscreen, RGB rainbow, neon, gamer aesthetic, glossy plastic, visible
screws, exposed wiring, brand logos, text, labels, watermarks, second camera,
camera obstructed, overhang above lens, lens flare, light rays, sparkles,
magic dust, oversaturated, cluttered background, fisheye, tilted horizon
```

---

## 6. When it comes back wrong

- **Two devices on one board, not one object.** Push the shared language:
  "continuous brass edge trim running the full height," "single seamless
  plate," "the two elements share one body."
- **Something overhangs the camera.** Add "completely unobstructed camera
  field of view, nothing protruding above or in front of the lens." Check
  every render for this specifically; it is the one flaw that ruins the
  product rather than the picture.
- **It invents a second camera or a speaker grille circle.** Add both to the
  negative list explicitly.
- **The proportions go squat.** State the ratio: "roughly 2.4 times taller
  than wide."
- **The brass creeps up around the doorbell.** Add "brass only on the lower
  circular element and the outer edge pinstripe."

---

## 7. What the renders cannot settle

Carry these into CAD regardless of how good the images look:

- **Trim width.** Typical brick mould is 89-114mm. A 120mm plate will overhang
  most of it. Either narrow the plate or accept mounting onto the siding.
- **Camera keepout.** Model the actual field of view as a cone and confirm the
  housing stays outside it, including the drip lip.
- **Thermal separation.** A Ring and an ESP32 in one sealed south-facing
  cavity will cook. Vent the bays separately or put a divider between them.
- **Chime wiring.** If the Ring is wired, its transformer feed and your 5V
  supply both enter through one gland. Plan the separation.
- **Angle.** Many porches need 15 degrees of toe-in for a usable camera view.
  Design the rear cleat to accept an optional wedge rather than retrofitting
  one later.
