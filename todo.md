# TODO

- Paupière qui s'ouvre et ferme au changement de gif
- Bouche animée

🎬 **INTRO**
1. Trésor: cropped (détails, billets, pièces, entreprises Xav ??)
**===> [unzoom] ===>** (tas d'or etc vu du dessus)
2. Trésor au centre avec exit_open autourAjouter cadre porte ouverte
**===> [unzoom] ===>**
3. 

**AUTRES**
- Floor				=> random
- Walls (alone)		=> random
- Walls	(multiple)	=> barrels
- Collectibles		=> ???
- Exit				=> ???
- Player			=> ???

1. Chercher un pack de sprites de joueur avec **idle**, **move**, **cac**, **distance**
2. Regrouper tous les sprites dont je vais avoir besoin dans un dossier :
	- `sprites/`
		- `player/`
			- `player_idle.png`
			- `player_collec_0.png` ... `player_collec_9.png`
			- `player_run_0.png` ... `player_run_9.png`
3. Créer un script pour convertir les sprites à la volée (argument = size)
4. Implémenter les animations (déplacer le sprite de `SPRITE_SIZE / 10` à chaque frame pour qu'il ait parcouru 1 SPRITE_SIZE à la fin de l'animation)
5. Modifier les images pour mettre la tête du Xav

- Change SPRITE_SIZE to 128x128
- Use Dongeons sprites modified by Gemini
- Add animations
- Add Win screen
- Add Ennemis
- Add Niveaux bonus
- check `.ber` (à la fin du fichier !)
- Mettre floor en fond de tous les sprites et arrêter de rendre floor partout + sprite => rendre uniquement sprites
- Installer [**funcheck**](https://github.com/froz42/funcheck?tab=readme-ov-file#quick-install) (container + vm)

# QUESTIONS

- Makefile doit compiler la mlx et la clean ??

# TESTS

- Add missing wall at top / bot / left /right
- Add empty map
- Add 2x2 map (to check affichage)
- Add invalid extension (`test.txt`, `test.ber.txt`, `test.ber`, `.ber`)

# SUBMIT

- Replace `libft/` submodule by files
- Delete `logs/` dir
- Delete `tests/` dir
- Update `make test` to curl the tests dir and execute the test script
- Delete `subject`
