#ifndef SHALLOW_H
# define SHALLOW_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <mlx.h>


# define HEIGHT 800
# define WIDTH 600

/* COLORS */
# define WHITE 0xFFFFFF
# define RED 0x960018
# define GREEN 0x00ab84
# define BLACK 0x000000
# define BLUE 0x0044FF
# define YELLOW 0xFFBC00
# define BROWN 0x9F6212
# define GRAY 0xACACAC


typedef struct t_mlx
{
	void	*ptr;
	void	*win;
}				t_mlx;

typedef struct t_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct t_meta
{
	t_mlx		*mlx;
	t_img		*img_data;
	// t_q_cache	quats;
	// t_point		*point;
	// t_quat		rotation_quat;
	int			spacing;
	int			moving;
	int			key;
	float		zooming;
	int			size[2];
	int			offset[2];
	// int			click_state; /// tbc
	// int			scroll_state; /// tbc
	// int			shift_state; /// tbc
}				t_meta;



#endif