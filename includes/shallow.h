#ifndef SHALLOW_H
# define SHALLOW_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <time.h>
# include "../mtwister/mtwister.h"


# define HEIGHT 1000
# define WIDTH 1000
# define ROW 27
# define COL 27
# define ON_DUR 5
# define OFF_DUR 200
# define MIN_OFF_DUR 200
# define PIXEL_INITAL_STATE 0
# define SOFT_DROP 80
# define DOT_GRAY 40


/* COLORS */
# define WHITE 0xFFFFFF
# define RED 0x960018
# define GREEN 0x00ab84
# define BLACK 0x000000
# define BLUE 0x0044FF
# define YELLOW 0xFFBC00
# define BROWN 0x9F6212
# define GRAY 0x1F1F1F

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
	int				active_high;
	int				color;
	int				on_time;
	int				off_time;
	// long			frame;
	long			prevframe_on;
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
	t_mlx				*mlx;
	t_img				*img_data;
	int					i;
	int					total_active;
	t_leaf				*leaf;
	int					spacing;
	int					on_dur;
	int					off_dur;
	int					min_off;
	int					moving; ///
	int					key;
	float				zooming; ///
	int					size[2]; ///
	int					offset[2]; ///
	unsigned long long	frame;
	// int			click_state; /// tbc
	// int			scroll_state; /// tbc
	// int			shift_state; /// tbc
}				t_meta;

/*keys*/
int		keypress(int key, t_meta *meta);
int		keypress_esc(t_meta *meta);

/*animation*/
int		pixel_move(t_meta *meta);
int		print_grid(t_meta *meta);

/*circle*/
void 	draw_circle(int x, int y, int r, int color, t_meta *meta);
void 	draw_disc(int x, int y, int r, int color, t_meta *meta);


/*mlx*/
void	my_mlx_pixel_put(t_img *imgdata, int x, int y, int color);
t_mlx	*mlx_init_struct(int win_size_x, int win_size_y);
void	my_new_mlx_img_data(t_meta *meta);
int		mlx_start(t_meta *meta);
void	random_time(t_meta **meta);
void	draw_pixel(t_meta *meta, int color);
int		create_trgb(int t, int r, int g, int b);


/*utils*/
void	print_list(t_leaf **leaf);

/*libft*/
char	*ft_itoa(int n);

/*random*/
int	random_limit(int nbr);
int mtwister(int mod);


#endif