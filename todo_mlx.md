# INIT

- mlx_init()
- mlx_new_window()
- mlx_xpm_file_to_image() pour chaque sprite
- stocker tout ça dans une structure mlx / game
- ⚠️ Récupérer la taille de l'écran via MLX et throw error si map trop grande pour être affichée (plus tard caméra dynamique)

# RENDU

- Format XMP taille fixe (32x32 / 64/64)
- Conversion `convert input.png -resize 32x32^ -gravity center -extent 32x32 output.xpm` ou carrément :
```bash
for img in *.png; do
	convert "$img" -resize 32x32 "${img%.png}.xpm"
done
```
- Pour chaque case de la map :
	- choisir le bon sprite (1, 0, C, E, P)
	- mlx_put_image_to_window()

# INPUTS

- hook clavier (WASD, ZQSD, UP-LEFT-DOWN-RIGHT, ESC)
- ⚠️ Defines pour keycodes car différents sur mac / linux
- à chaque touche :
	- vérifier collision
	- mettre à jour la position du joueur
	- mettre à jour la map (supprimer collectibles ramassés)
	- incrémenter le compteur de moves
	- redraw

# BOUCLE

- mlx_loop()

# Events

- mlx_hook()
- mlx_key_hook()
- mlx_destroy_window()

---

1. Créer une structure MLX minimale

Avant tout affichage, tu dois avoir une seule structure centrale qui contient :

pointeur MLX

fenêtre

toutes les images (sprites)

ta map déjà parsée

la position du joueur

👉 Tant que cette structure n’existe pas, n’écris aucune logique MLX.

2. Initialiser MLX (sans images)

Étape suivante :

mlx_init()

mlx_new_window()

À ce stade :

fenêtre vide

pas de sprite

pas d’input

Objectif :

vérifier que la fenêtre s’ouvre

qu’elle se ferme proprement

👉 ESC + croix doivent déjà fonctionner.

3. Charger les sprites (une seule fois)

Ensuite seulement :

charger chaque .xpm

stocker les pointeurs images

vérifier qu’aucun mlx_xpm_file_to_image() ne retourne NULL

⚠️ Jamais dans une boucle.

4. Afficher la map une fois (statique)

Avant de gérer le joueur :

parcourir la map

afficher :

floor partout

wall / exit / collectible

player à sa position initiale

À la fin de cette étape :

ta map s’affiche

rien ne bouge

aucune touche ne fait rien

👉 C’est une étape clé.
Si elle est propre, le reste est trivial.

5. Ajouter les hooks clavier

Une fois l’affichage OK :

hook clavier (WASD, ESC)

au début :

affiche juste la touche pressée dans le terminal

👉 Tu vérifies :

les keycodes

la réception des events

la stabilité

6. Implémenter un déplacement simple

Ensuite :

calculer la nouvelle position

vérifier :

mur → refus

mettre à jour :

position joueur

redraw toute la map

Pas d’optimisation.
Pas de delta.
Pas de partiel.

7. Ajouter les règles du jeu

Quand le déplacement marche :

collecte de C

compteur de moves

accès à E uniquement si C == 0

win / exit propre
