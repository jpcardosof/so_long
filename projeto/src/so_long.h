#ifndef SO_LONG_H
# define SO_LONG_H
#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <fcntl.h>
#include <stdio.h>

typedef struct s_all
{
	char	**map;
}			t_all;

char	**check_map(char* map_name);
char	**initialize_map(char *map_name);
int		check_border(char **mapa);
int		check_content(char **mapa);
#endif