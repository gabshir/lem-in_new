#include "lem_in.h"

int		ft_mini_atoi(char *line)
{
	unsigned	ents;
	unsigned	i;

	ents = 0;
	i = 0;
	while(line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			ents = ents * 10 + line[i] - '0';
			++i;
		}
		else
			ft_error();
	}
	i == 0 || i > 10 || ents > 2147483647 ? ft_error() : 0;
	free(line);
	return (ents);
}

int comments(const char *str)
{
	if (str[0] == '#' && (str[1] != '#' || !str[1]))
		return (1);
	return (0);
}

void ft_error(void)
{
	ft_printf("ERROR : INCORENT NUMBER ENTS!");
	exit(1);
}

void	components(char **room, int f)
{
	unsigned i;

	i = 0;
	while (room[i])
		i++;
	i != 3 && f ? ft_error() : 0;
	i != 2 && !f ? ft_error() : 0;
}
