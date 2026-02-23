- TODO: 3. Terminer sprite_set
- TODO: 4. Terminer component

# TODO

**sprite_set**
1. Sprite_set doit être une banque indépendante, chargée en tout premier
2. Sprite_set ne doit pas être une référence dans la struct t_view !!! (valeur faster !)
3. C'est LE module critique (render) et le seul module qui en a besoin donc il doit y accéder instant

# VIEW

**Sprite_set_bank**
- Singleton
- Expose méthodes pour load / free des sprite_sets
- Evite les doublons en ne chargeant qu'une fois chaque sprite_set
- (Stocke toutes les références des path durant l'init puis load ?)

**Animation_bank**
- Singleton
- Charge ses sprite_sets via la **sprite_set_bank**
- Expose méthodes pour load / free des animations
- Evite les doublons en ne chargeant qu'une fois chaque sprite_set
- (Stocke toutes les références des path durant l'init puis load ?)

**Object**
- API de rendu
- Position, taille, image... (2D + time)
- callback (each frame / last frame)

# CONTROLLER

**Controller**
- Stocke des pointeurs vers ses **parents** et **enfants**
- Propage handlers frame/event à ses enfants
- Gère ses propres objets via sa propre **object_bank**
- 👴🏼 t_controller *parent
- 👶 t_controller children[]
- 📦 t_object	objects[]
- 📚 void *data (propre à chaque instance)
- 🤝 bool (*handle_frame)()
- 🤝 bool (*handle_event)()

# COMPONENTS

**Component**
- A son propre **controller**
- Charge ses animations via la **animation_bank**
- Génères ses objets
- Génères ses propres sous-controlleurs

## COMPORTEMENT VOULU

Tout pouvoir écrire au même endroit (un seul dossier component) :
```bash
component/hud
|
|- hud_loading.c
|- hud_loading.h
```
```c

```