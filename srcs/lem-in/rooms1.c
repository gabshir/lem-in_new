/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrooks <acrooks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 21:36:06 by acrooks           #+#    #+#             */
/*   Updated: 2019/09/09 21:37:40 by acrooks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	restore_room(t_map *map)
{
	t_list	*combination;
	t_list	*new_combination;
	t_room	*read;

	combination = bfs_inc(map->start->links, 0);
	new_combination = NULL;
	while (combination)
	{
		read = combination->content;
		if (read->f || read->gl)
		{
			read->f = 0;
			read->gl = 0;
			up_combination(&new_combination, read, 0);
		}
		combination = step(combination);
		if (!combination)
		{
			combination = new_combination;
			new_combination = NULL;
		}
	}
}

void	rooms_in_array(t_map *map, int *f)
{
	t_list		*temp;
	unsigned	i;

	i = 0;
	f[0] = 1;
	temp = map->first_room_create;
	if (!(map->room = ft_memalloc(sizeof(t_room *) * (map->max_room + 1))))
		exit(1);
	while (temp)
	{
		map->room[i] = temp->content;
		++i;
		temp = step(temp);
	}
	map->first_room_create = NULL;
	check_double_name(map);
	!map->start || !map->end ? ft_error("no start/finish") : 0;
	ft_sort_array(map);
	i = 0;
	while (i < map->max_room)
	{
		map->room[i]->n = i;
		++i;
	}
}

void	check_double_name(t_map *map)
{
	unsigned i;
	unsigned j;

	i = 0;
	j = 1;
	while (i < map->max_room)
	{
		while (j < map->max_room)
		{
			if (ft_strcmp(map->room[i]->name, map->room[i + j]->name) == 0)
			{
				ft_printf("Error: double room names\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	over_room(t_map *map, char *str)
{
	char	**room;
	t_room	*temp;

	room = NULL;
	room = ft_strsplit(str, ' ');
	room ? components(room, 1) : ft_error("dont have a room");
	free(str);
	temp = create_room(room);
	++map->max_room;
	ft_lstadd(&map->first_room_create, ft_lstnew_ptr(temp));
}
