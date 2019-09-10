/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrooks <acrooks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 21:35:28 by acrooks           #+#    #+#             */
/*   Updated: 2019/09/09 21:37:36 by acrooks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*create_room(char **room)
{
	t_room	*create;

	if (!(create = ft_memalloc(sizeof(t_room))))
		exit(1);
	create->name = room[0];
	if (!ft_strncmp(create->name, "L", 1))
	{
		ft_printf("Error: not valid room name");
		exit(1);
	}
	create->x = ft_mini_atoi(room[1]);
	create->y = ft_mini_atoi(room[2]);
	free(room);
	room = NULL;
	return (create);
}

void	ft_start(t_map *map, int fd, char *str)
{
	char **room;

	room = NULL;
	map->start ? ft_error("double start") : 0;
	while (get_next_line(fd, &str) && comments(str))
	{
	}
	ft_printf("%s\n", str);
	room = ft_strsplit(str, ' ');
	room ? components(room, 1) : ft_error("don't have a room");
	free(str);
	map->start = create_room(room);
	++map->max_room;
	ft_lstadd(&map->first_room_create, ft_lstnew_ptr(map->start));
}

void	ft_end(t_map *map, int fd, char *str)
{
	char **room;

	room = NULL;
	map->end ? ft_error("double finish") : 0;
	while (get_next_line(fd, &str) && comments(str))
	{
	}
	ft_printf("%s\n", str);
	room = ft_strsplit(str, ' ');
	room ? components(room, 1) : ft_error("don't have a room");
	free(str);
	map->end = create_room(room);
	++map->max_room;
	ft_lstadd(&map->first_room_create, ft_lstnew_ptr(map->end));
}

int		ft_start_and_end(t_map *map, int fd, char *str)
{
	if (!ft_strcmp(str, "##start"))
	{
		free(str);
		str = NULL;
		ft_start(map, fd, str);
		return (1);
	}
	else if (!ft_strcmp(str, "##end"))
	{
		free(str);
		str = NULL;
		ft_end(map, fd, str);
		return (1);
	}
	return (0);
}

void	rooms(t_map *map, int fd)
{
	char	*str;
	int		f;

	str = NULL;
	f = 0;
	while (get_next_line(fd, &str))
	{
		ft_printf("%s\n", str);
		if (comments(str))
			continue;
		else if (!f && ft_start_and_end(map, fd, str))
			continue;
		else if (!f && ft_strrchr(str, ' '))
			over_room(map, str);
		else if (!f && ft_strrchr(str, '-'))
		{
			rooms_in_array(map, &f);
			create_links(map, str);
		}
		else if (f && ft_strrchr(str, '-'))
			create_links(map, str);
		else
			ft_error("something wrong with links");
	}
	!map->room ? ft_error("no links") : 0;
}
