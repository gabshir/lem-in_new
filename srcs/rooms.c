#include "lem_in.h"

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
	while (get_next_line(fd, &str) && comments(str))
	{
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

void	rooms_in_array(t_map *map, int *f)
{
	t_list *temp;
	unsigned i;

	i = 0;
	f[0] = 1;
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
	//тут должна быть проверка на одинаковые комнаты
	ft_sort_array(map);
	i = 0;
	while (i < map->max_room)
	{
		map->room[i]->n = i;
		++i;
	}
}

void rooms(t_map *map, int fd)
{
	char *str;
	int f;

	str = NULL;
	f = 0;
	while(get_next_line(fd, &str))
	{
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
			ft_error();
	}
}


