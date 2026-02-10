#include "mlx.h"
#include "libft.h"
#include "so_long.h"
#include "sprite_priv.h"
#include <stdlib.h>

static inline bool			sprite_load_letters_and_numbers(t_game *game);
static inline const char	*get_sprite_path(t_sprite sprite);
static inline bool			load_sprite(t_game *game, t_sprite_load *target);

bool	sprite_load_all(t_game *game)
{
	t_sprite_load	target;
	t_sprite		sprite;

	sprite = 0;
	while (sprite < SPRITE_COUNT)
	{
		target.index = sprite;
		target.file_path = (char *)get_sprite_path(sprite);
		target.array = game->sprites;
		target.expected_height = SPRITE_SIZE;
		target.expected_width = SPRITE_SIZE;
		if (!load_sprite(game, &target))
			return (false);
		sprite++;
	}
	return (sprite_load_letters_and_numbers(game));
}

static inline bool	sprite_load_letters_and_numbers(t_game *game)
{
	static char		path[] = SPRITE_HUD_FONT;
	t_sprite_load	target;
	size_t			i;

	target.expected_height = HUD_FONT_HEIGHT;
	target.expected_width = HUD_FONT_WIDTH;
	target.array = game->letters;
	i = 0;
	while (i < 26)
	{
		path[SPRITE_HUD_IDX] = (char)('A' + i);
		target.file_path = path;
		target.index = i++;
		if (!load_sprite(game, &target))
			return (false);
	}
	target.array = game->numbers;
	i = 0;
	while (i < 10)
	{
		path[SPRITE_HUD_IDX] = (char)('0' + i);
		target.file_path = path;
		target.index = i++;
		if (!load_sprite(game, &target))
			return (false);
	}
	return (true);
}

static inline const char	*get_sprite_path(t_sprite sprite)
{
	static const char	*paths[] = {
		SPRITE_WALL_TOP_LEFT,
		SPRITE_WALL_TOP_BOT,
		SPRITE_WALL_TOP_RIGHT,
		SPRITE_WALL_LEFT,
		SPRITE_WALL_RIGHT,
		SPRITE_WALL_BOT_LEFT,
		SPRITE_WALL_BOT_RIGHT,
		SPRITE_WALL,
		SPRITE_FLOOR,
		SPRITE_COLLEC,
		SPRITE_EXIT_CLOSE,
		SPRITE_EXIT_OPEN,
		SPRITE_PLAYER,
		SPRITE_PLAYER_COLL_1,
		SPRITE_PLAYER_COLL_2,
		SPRITE_PLAYER_COLL_3
	};

	if (sprite > sizeof(paths) / sizeof(paths[0]))
		return (NULL);
	return (paths[sprite]);
}

static inline bool	load_sprite(t_game *game, t_sprite_load *target)
{
	int	height;
	int	width;

	target->array[target->index] = mlx_xpm_file_to_image(
		game->mlx_ptr,
		(char *)target->file_path,
		&width,
		&height
	);
	if (!target->array[target->index])
	{
		fprint_err(true, "Sprite loading failed", " %s", target->file_path);
		return (false);
	}
	if (width != target->expected_width || height != target->expected_height)
	{
		fprint_err(false,
			"Invalid sprite size",
			" '%s': width = %i x height = %i (expected %i x %i)",
			target->file_path, width, height,
			target->expected_width, target->expected_height
		);
		return (false);
	}
	return (true);
}
