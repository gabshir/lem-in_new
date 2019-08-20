#include "lem_in.h"

void 	ents(t_map *map, int fd)
{
	char *str;

	str = NULL;
	while(map->ents == 0 && get_next_line(fd, &str))
	{
		if (comments(str))
		{
			free(str);
			str = NULL;
			continue;
		}
		map->ents = ft_mini_atoi(str);
	}
}

t_room	*create_room(char **room)
{
	t_room	*create;

	if (!(create = ft_memalloc(sizeof(t_room))))
		exit(1);
	create->name = room[0];
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
	map->start ? ft_error() : 0;
	while(get_next_line(fd, &str) && comments(str))
	{
		free(str);
		str = NULL;
	}
	room = ft_strsplit(str, ' ');
	room ? components(room, 1) : ft_error();
	free(str);
	map->start = create_room(room);
	++map->max_room;
	ft_lstadd(&map->fist_rooms_create, ft_lstnew_ptr(map->start));
}

void	ft_end(t_map *map, int fd, char *str)
{
	char **room;

	room = NULL;
	map->end ? ft_error() : 0;
	while(get_next_line(fd, &str) && comments(str))
	{
		free(str);
		str = NULL;
	}
	room = ft_strsplit(str, ' ');
	room ? components(room, 1) : ft_error();
	free(str);
	map->end = create_room(room);
	++map->max_room;
	ft_lstadd(&map->fist_rooms_create, ft_lstnew_ptr(map->end));
}

void over_room(t_map *map, char *str)
{
	char	**room;
	t_room	*temp;

	room = NULL;
	room = ft_strsplit(str, ' ');
	room ? components(room, 1) : ft_error();
	free(str);
	temp = create_room(room);
	++map->max_room;
	ft_lstadd(&map->fist_rooms_create, ft_lstnew_ptr(temp));
}

int	ft_start_and_end(t_map *map, int fd, char *str)
{
	if(!ft_strcmp(str, "##start"))
	{
		free(str);
		str = NULL;
		ft_start(map, fd, str);
		return (1);
	}
	else if(!ft_strcmp(str, "##end"))
	{
		free(str);
		str = NULL;
		ft_end(map, fd, str);
		return (1);
	}
	return (0);
}

void rooms(t_map *map, int fd)
{
	char *str;

	str = NULL;
	while(get_next_line(fd, &str))
	{
		if (comments(str))
		{
			free(str);
			str = NULL;
			continue;
		}
		else if (ft_start_and_end(map, fd, str))
			continue;
		else if (ft_strrchr(str, ' '))
			over_room(map, str);
		else break;
	}
	map->fist_link = str;
}

void	rooms_in_mass(t_map *map, int fd)
{
	t_list *temp;
	unsigned i;

	ents(map, fd);
	rooms(map, fd);
	i = 0;
	temp = map->fist_rooms_create;
	if(!(map->room = ft_memalloc(sizeof(t_room *) * map->max_room + 1)))
		exit(1);
	while(temp)
	{
		map->room[i] = temp->content;
		++i;
		temp = temp->next;
	}
	free(map->fist_rooms_create);
	map->fist_rooms_create = NULL;
}
