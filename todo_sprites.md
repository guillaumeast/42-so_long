# HUD

- head							= h128 x w135
- text							= h128 x w500	=> Font = Palatino (size 90)
- moves + collec_count + lifes	= h128 x w135
- Total							= h128 x w800	=> spaces between cols = w15
- ⚠️ Forcer la fenêtre à toujours faire au moins w830!

# REQUIRED

- [OK] **PLAYER**			⇢ Xavier en tenue de prisonnier (orange car cliché et visible)
- [OK] **FLOOR**			⇢ Béton gris (prison)
- [OK] **WALL**				⇢ Barreaux noirs (prison)
- [OK] **COLLECTIBLES**		⇢ Billets (verts $ / violets €)
- [OK] **EXIT**				⇢ Porte de prison (Bernard Arnault qui lui tend la main depuis l'extérieur ??)

# BONUS

- **ENNEMIS**			⇢ Journalistes / agents du FISC
- **ARMES ENNEMIS**		⇢ Appareil photo (scandale, leak) / Facture (redressement fiscal)
- **ARMES XAVIER**		⇢ Clavier (cac) / Carte sim FREE (distance tel des shurikens)
- **NIVEAU BONUS**		⇢ Magasin Lidl			⇢ Combat 1v1 contre le mec des réseaux
- **NIVEAU BONUS**		⇢ Chateau marbre rose	⇢ Tenter de pecho la fille de Bernard Arnault
- **RENFORTS**			⇢ Téléphone rose fait apparaître des renforts IA

# UI

- **COMPTEUR MOVES**	⇢ "Jours en prison: x"
- **WIN**				⇢ "Libéré sous caution" + photo de Xavier tug (lunettes + joint + chaine en or)
- **LOSE**				⇢ "Retour en cellule" + photo de Xavier blasé

---

# CONVERT

```bash
magick <source_img> -resize 64x64! -gravity center <output_img>
```

---

# PROMPTS

STYLE GLOBAL (à garder identique partout)

À copier-coller au début de chaque prompt :

pixel art, 2D top-down game sprite, simple shapes, flat colors, no gradients, no text, no watermark, no background details, strong contrast, clean outlines, cartoon style, readable at small size, 64x64 pixels

1. PLAYER — Xavier prisonnier

Prompt :

pixel art, 2D top-down game sprite, simple shapes, flat colors, strong contrast, clean outlines, cartoon style, readable at small size, 64x64 pixels,
character inspired by a french tech entrepreneur, wearing an orange prison jumpsuit, black stripes, short dark hair, small beard, neutral expression, standing idle, front view, centered, transparent background

Optionnel plus tard :

version “face gauche / droite”

version “victory pose”

2. FLOOR — sol béton prison

Prompt :

pixel art, 2D top-down game tile, simple shapes, flat colors, strong contrast, clean outlines, cartoon style, readable at small size, 64x64 pixels,
gray concrete prison floor tile, subtle cracks, minimal texture, neutral look, seamless tile, top-down view, transparent background

3. WALL — barreaux de prison

Prompt :

pixel art, 2D top-down game tile, simple shapes, flat colors, strong contrast, clean outlines, cartoon style, readable at small size, 64x64 pixels,
prison bars wall, vertical black metal bars, dark gray frame, solid and blocking, top-down view, seamless tile, transparent background

4. COLLECTIBLE — billets

👉 Je te conseille un seul type au début (vert).

Prompt :

pixel art, 2D top-down game sprite, simple shapes, flat colors, strong contrast, clean outlines, cartoon style, readable at small size, 64x64 pixels,
stack of green banknotes, cartoon money, small white highlights, no symbols, top-down view, centered, transparent background

(Option bonus plus tard : version violette €)

5. EXIT — porte de prison

Version safe (recommandée pour mandatory) :

Prompt :

pixel art, 2D top-down game tile, simple shapes, flat colors, strong contrast, clean outlines, cartoon style, readable at small size, 64x64 pixels,
open prison door, metal door with bars, light coming from outside, symbol of freedom, top-down view, centered, transparent background

Variante “Bernard Arnault” (à garder très caricaturale, bonus visuel)

Si tu veux tenter sans risque :

pixel art, 2D top-down game tile, simple shapes, flat colors, strong contrast, clean outlines, cartoon style, readable at small size, 64x64 pixels,
open prison door, outside silhouette of a rich businessman in suit extending a hand, generic cartoon billionaire style, no real person likeness, top-down view, centered, transparent background

