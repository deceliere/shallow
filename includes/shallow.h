#ifndef SHALLOW_H
# define SHALLOW_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <mlx.h>
# include <time.h>


# define HEIGHT 1000
# define WIDTH 1000
# define ROW 23
# define COL 23


/* COLORS */
# define WHITE 0xFFFFFF
# define RED 0x960018
# define GREEN 0x00ab84
# define BLACK 0x000000
# define BLUE 0x0044FF
# define YELLOW 0xFFBC00
# define BROWN 0x9F6212
# define GRAY 0xACACAC

/*KEYS*/
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_ESC 53
# define KEY_1	18
# define KEY_2	19
# define KEY_P	35
# define KEY_I	34
# define KEY_Q	12
# define KEY_W	13
# define KEY_E	14
# define KEY_A	0
# define KEY_S	1
# define KEY_D	2
# define KEY_O	31

typedef struct s_leaf
{
	int				x;
	int				y;
	int				active;
	long			on_time;
	long			off_time;
	long			prevframe;
	long			currframe;
	struct s_leaf	*leaf;
	struct s_leaf	*leaf0;
	struct s_leaf	*leaf_line0;
	struct s_leaf	*next;
	struct s_leaf	*down;

}			t_leaf;


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
	int			i;
	t_leaf		*leaf;
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

/*keys*/
int	keypress(int key, t_meta *meta);
int	keypress_esc(t_meta *meta);

/*animation*/
int	pixel_move(t_meta *meta);
int	print_grid(t_meta *meta);


/*mlx*/
void	my_mlx_pixel_put(t_img *imgdata, int x, int y, int color);
t_mlx	*mlx_init_struct(int win_size_x, int win_size_y);
void	my_new_mlx_img_data(t_meta *meta);
int		mlx_start(t_meta *meta);
void	random_color(t_meta **meta);


#endif