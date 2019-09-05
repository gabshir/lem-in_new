/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrooks <acrooks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 17:49:24 by acrooks           #+#    #+#             */
/*   Updated: 2019/08/28 16:12:47 by acrooks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// for bfc
// функция очищает остатки текущей комбинации и то что успело создаться для новой

void	last_free(t_list *combination, t_list *new_combination)
{
	ft_lstdel(&combination, NULL);
	ft_lstdel(&new_combination, NULL);
}

int		ft_mini_atoi(char *line)
{
	unsigned	ants;
	unsigned	i;

	ants = 0;
	i = 0;
	while(line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			ants = ants * 10 + line[i] - '0';
			++i;
		}
		else
			ft_error("not valid number of ants");
	}
	i == 0 || i > 10 || ants > 2147483647 ? ft_error("not valid number") : 0;
	free(line);
	return (ants);
}

int		comments(char *str)
{
	if (str[0] == '#' && (str[1] != '#' || !str[1]))
	{
		free(str);
		str = NULL;
		return (1);
	}
	return (0);
}

void 	ft_error(char *str)
{
	ft_printf("ERROR: %s\n", str);
	exit(1);
}

void	components(char **room, int f)
{
	unsigned i;

	i = 0;
	while (room[i])
		i++;
	i != 3 && f ? ft_error("not all coordinats") : 0;
	i != 2 && !f ? ft_error("only one room") : 0;
}

void	ft_clean_strstr(char **str)
{
	size_t i;

	i = 0;
	while (str && str[i])
		free(str[i++]);
	if (str)
		free(str);
}
