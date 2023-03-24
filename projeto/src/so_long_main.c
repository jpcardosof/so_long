#include "so_long.h"

int	main(int ac, char **av)
{
	t_all	tudao;

	if (ac != 2)
	{
		ft_putendl_fd("Deu ruim meu chapa", 2);
		return(1);
	}
	ft_memset(&tudao, 0, sizeof(tudao));
	tudao.map = check_map(av[1]);
}
