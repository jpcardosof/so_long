#include "so_long.h"

char	**initialize_map(char *map_name)
{
	char	**matriz;
	int		fd;
	int		vertical_len;
	char	buf[1];

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Can't open file", 2);
		return (NULL);
	}
	vertical_len = 0;
	while (read(fd, buf, 1))
		if (buf[0] == '\n')
			vertical_len++;
	if (buf[0] != '\n')
		vertical_len++;
	if (vertical_len < 3)
	{
		ft_putendl_fd("Error\nMap is too small", 2 );
		return (NULL);
	}
	matriz = malloc((vertical_len + 1) * sizeof(char*));
	close(fd);
	fd = open(map_name, O_RDONLY);
	vertical_len = 0;
	matriz[vertical_len] = get_next_line(fd);
	while (matriz[vertical_len])
		matriz[++vertical_len] = get_next_line(fd);
	vertical_len = 0;
	while (matriz[vertical_len])
	{
		printf("matriz[%d] = %s\n", vertical_len, matriz[vertical_len]);
		vertical_len++;
	}
	return (matriz);
}

	// Verificar extenção do map

char	**check_map(char* map_name)
{
	char	**mapa;
	size_t	i;
	int		i2;

	i = ft_strlen(map_name);
	if (i <= 4 || map_name[i-4] != '.'|| map_name[i-3] != 'b' || \
	map_name[i-2] != 'e' || map_name[i-1] != 'r')
	{
		ft_putendl_fd("Bad File Extension Meu chapa" ,2);
		exit(EXIT_FAILURE);
	}

	// Verificar inicialização do mapa

	mapa = initialize_map(map_name);
	if (!mapa)
		return (NULL);
	// Verificar regras do mapa
	i = ft_strlen(mapa[0]);
	i2 = 0;
	while (mapa[++i2])
	{
		if (ft_strlen(mapa[i2]) != i && mapa[i2][ft_strlen(mapa[i2]) - 1] == '\n')
		{
			ft_putendl_fd("Error\nMap ins't rectangular", 2);
			return (NULL);
		}
	}
  //Verificar se o mapa possui um P e pelo menos um E e um C
	if (!check_content(mapa))
	{
		ft_putendl_fd("Error\nMap Without Player,Colectable or Exit", 2);
		return (NULL);
	}
	if (!check_border(mapa))
		return (NULL);
	return (NULL);
}

int	check_content(char **mapa)
{
	int	y;
	int	x;
	int	p;
	int	c;
	int	e;

	y = 0;
	p = 0;
	c = 0;
	e = 0;
	while (mapa[y])
	{
		x = 0;
		while (mapa[y][x])
		{
			if (mapa[y][x] == 'P')
				p++;
			if (mapa[y][x] == 'C')
				c++;
			if (mapa[y][x] == 'E')
				e++;
			x++;
		}
		y++;
	}
	if (p != 1 || !c || !e)
		return (0);
	return (1);
}

  //Verificar se a primeira e ultima linha são so "1" e se o primeiro e ultimo digito de cada linha é 1

int	check_border(char **mapa)
{
	int	i;
	int	i2;

	i = ft_strlen(mapa[0]);
	i2 = 0;
	while (mapa[i2])
	{
		if (mapa[i2][0] != '1' || mapa[i2][i - 2] != '1')
		{
			ft_putendl_fd("Error\nMap is not closed", 2);
			return (0);
		}
		i2++;
	}
	i2--;
	i = 0;
	while (mapa[i2][i])
	{
		if (mapa[i2][i] != '1' && mapa[i2][i] != '\n')
		{
			ft_putendl_fd("Error\nMap is not closed", 2);
			return (0);
		}
		i++;
	}
	i = 0;
	while (mapa[0][i])
	{
		if (mapa[0][i] != '1' && mapa[0][i] != '\n')
		{
			ft_putendl_fd("Error\nMap is not closed", 2);
			return (0);
		}
		i++;
	}
	return (1);
}


  // Verificar se existe um caminho possivel para finalizar o mapa

int	validpath(char **mapa, int x, int y, t_cenas *cenas)
{
	if (mapa[y][x] == 'C')
		check_collect(cenas, x, y);
	mapa[y][x] = '2';
	if (mapa[y][x - 1] == 'E' || mapa[y][x + 1] == 'E' \
		|| mapa[y - 1][x] == 'E' || mapa[y + 1][x] == 'E' && cenas->exit)
		cenas->exit--;
	if (mapa[y][x - 1] != '1' && mapa[y][x - 1] != '2' \
	&& mapa[y][x - 1] != 'E' && mapa[y][x - 1] != 'X')
		validpath(mapa, x - 1, y, cenas);
	if (mapa[y][x + 1] != '1' && mapa[y][x + 1] != '2' \
	&& mapa[y][x + 1] != 'E' && mapa[y][x + 1] != 'X')
		validpath(mapa, x + 1, y, cenas);
	if (mapa[y - 1][x] != '1' && mapa[y - 1][x] != '2' \
	&& mapa[y - 1][x] != 'E' && mapa[y - 1][x] != 'X')
		validpath(mapa, x, y - 1, cenas);
	if (mapa[y + 1][x] != '1' && mapa[y + 1][x] != '2' \
	&& mapa[y + 1][x] != 'E' && mapa[y + 1][x] != 'X')
		validpath(mapa, x, y + 1, cenas);
	if (!cenas->collecc && cenas->exit <= 0)
		return (0);
	return (1);
}
