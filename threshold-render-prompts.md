# Threshold — Exterior Touch Point Render Prompts

Four prompts, one negative list. Keep the material and dimension language
identical across all four so the renders stay recognizably the same object.

**A note on the motif.** Every prompt below uses an original three-lobed
trefoil / clover ornament rather than a Disney character silhouette. The park
shape is trademarked, and asking an image model for it produces IP you can't
use in documentation, a listing, or anything public. The trefoil reads as
"this is the tap spot" just as clearly and is yours.

---

## 1. Hero render — idle state, dusk

> Product photography of a wall-mounted circular smart doorway device, 115mm
> diameter, 35mm deep, mounted on weathered white-painted wood trim beside a
> dark front door. The outer bezel is a solid aged brass ring with a
> hand-finished patina, slightly darkened in its recesses and warmly polished
> on its high edges. Inside the brass sits a narrow frosted white acrylic lens
> ring emitting a soft, even, warm-white glow at low intensity — diffused, no
> visible individual LEDs, no hotspots. The body is matte charcoal-graphite
> with a fine sandstone texture, completely free of screws, seams, labels,
> ports, and status lights. At the center, a shallow recessed circular plate
> in brushed dark brass, 2mm below the surrounding face, engraved with a
> simple three-lobed trefoil ornament. A subtle beveled drip lip crowns the
> top edge of the housing. Dusk, blue hour, soft directional light from
> camera-left, one warm practical light off-frame. Shot on 85mm, f/2.8,
> shallow depth of field, the background porch falling into soft bokeh.
> Restrained industrial design — Craftsman-era door hardware crossed with
> modern minimalism. Photorealistic, natural materials, muted palette.

---

## 2. Activated state — night, granted

Same object, the moment after a successful tap.

> Night product photography of the same wall-mounted circular brass and
> charcoal doorway device. The frosted acrylic lens ring is now glowing a
> clear emerald green at full brightness, the light blooming outward across
> the aged brass bezel and catching its patina, spilling softly onto the white
> painted wood trim around it. The recessed brushed-brass center plate with
> its three-lobed trefoil engraving catches a rim of green light along its
> lower bevel. Deep night background, the porch beyond almost black. Shot on
> 85mm, f/2.0, shallow depth of field. Dramatic but restrained — the glow is
> the only light source in frame. Photorealistic, no lens flare, no light
> rays, no glitter or sparkle effects.

---

## 3. Macro detail — the tap target

For documenting the tactile affordance.

> Extreme close-up macro photograph of the center of a circular brass doorway
> device. A shallow 2mm recessed disc of brushed dark brass, engraved with a
> fine three-lobed trefoil ornament, surrounded by matte charcoal textured
> housing and a thin ring of softly glowing warm-white frosted acrylic at the
> edge of frame. Visible brush grain in the metal, a crisp machined chamfer
> where the recess meets the face, faint honest wear on the high points.
> Shot on a 100mm macro lens, f/4, raking side light revealing surface
> texture. No text, no logos, no icons other than the trefoil.

---

## 4. Exploded view — for build documentation

> Clean exploded technical product render of a circular wall-mounted device,
> components separated vertically along a single axis against a soft neutral
> off-white background. From front to back: an aged brass bezel ring, a
> frosted white acrylic lens ring, a matte charcoal front housing with a
> recessed engraved center plate, a circular ring of 24 addressable LEDs on a
> black PCB, a small square NFC antenna module, a 70mm circular dark green
> four-layer circuit board with a prominent silver module and small
> connectors around its lower edge, a closed-cell foam gasket, and a matte
> charcoal rear housing with a single cable gland on its underside. Even soft
> studio lighting, gentle contact shadows, thin neutral-grey alignment guide
> line running through all parts. Technical illustration realism, no text
> callouts, no annotation numbers.

---

## 5. Negative prompt (use with all four)

```
Mickey Mouse, Disney, cartoon character, mouse ears, three circles logo,
theme park, RGB rainbow lighting, gamer aesthetic, neon, glossy plastic,
visible screws, exposed circuit boards, USB ports, wires, cables, status LEDs,
text, labels, watermarks, brand names, buttons, keypad, touchscreen, lens
flare, light rays, sparkles, magic dust, bokeh orbs, oversaturated colors,
cluttered background, fisheye distortion, tilted horizon, low resolution
```

---

## 6. Consistency notes

If a render comes back wrong, these are usually the reasons:

- **It made it glossy.** Add "deeply matte, non-reflective, powder-coated"
  and repeat "matte" a second time.
- **It added screws or a seam.** Add "seamless single-piece housing" and put
  "screws" earlier in the negative list.
- **The glow looks like LEDs.** Add "perfectly diffused light, the source
  entirely hidden behind the diffuser."
- **It drifted toward a doorbell camera.** Add "no camera, no lens, no
  aperture" — the round frosted ring reads as a camera to most models.
- **Wrong scale.** Include a hand or the door edge for reference, or state
  "roughly the size of a coffee cup lid."

Keep the brass, the charcoal, the frosted ring, and the recessed trefoil
fixed. Everything else can vary between takes.
