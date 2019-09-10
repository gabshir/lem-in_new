/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrooks <acrooks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 17:49:24 by acrooks           #+#    #+#             */
/*   Updated: 2019/09/09 22:54:28 by acrooks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	while (line[i])
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
	if (str[0] && str[1] && str[0] == '#' && str[1] == '#' && ft_strcmp(str, "##end") && ft_strcmp(str, "##start"))
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
	unsigned i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		++i;
	}
	free(str);
	str = NULL;
}

void	free_array(t_way **all)
{
	unsigned i;

	i = 0;
	while (all[i])
	{
		free(all[i]->room);
		all[i]->room = NULL;
		free(all[i]);
		++i;
	}
	free(all);
}

void	free_way(t_list *combo)
{
	t_list	*next;
	t_list	*vn;

	next = combo->next;
	while(combo)
	{
		vn = combo->content;
		ft_lstdel(&vn, NULL);
		free(combo);
		combo = next;
		if (combo)
			next = combo->next;
	}
}

void	free_combination(t_list *combo)
{
	t_list *next;
	t_list *way_combo;

	next = combo->next;
	while (combo)
	{
		way_combo = combo->content;
		free_way(way_combo);
		free(combo);
		combo = next;
	}
}

void	free_map(t_map *map)
{
	unsigned i;

	i = 0;
	free_combination(map->combination);
	while (map->room[i])
	{
		free(map->room[i]->name);
		ft_lstdel(&map->room[i]->links, NULL);
		free(map->room[i]);
		map->room[i] = NULL;
		++i;
	}
	free(map->room);
	map->room = NULL;
}