#include <zconf.h>
#include "lem_in.h"

void ft_error(void)
{
	ft_printf("ERROR : INCORENT NUMBER ENTS!");
	exit(1);
}

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

void	components(char **room)
{
	unsigned i;

	i = 0;
	while (room[i])
		i++;
	 i != 3 ? ft_error() : 0;
}

void 	ents(t_map *map, int fd)
{
	char *str;

	str = NULL;
	while(get_next_line(fd, &str) && map->ents == 0)
	{
		if (comments(str))
		{
			free(str);
			str = NULL;
			continue;
		}
		map->ents = ft_mini_atoi(str);
		str = NULL;
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
	room ? components(room) : ft_error();
	free(str);
	map->start = create_room(room);
}

void	ft_end(t_map *map, int fd, char *str)
{
	t_room *ends;
	char **room;

	room = NULL;
	map->end ? ft_error() : 0;
	while(get_next_line(fd, &str) && comments(str))
	{
		free(str);
		str = NULL;
	}
	room = ft_strsplit(str, ' ');
	room ? components(room) : ft_error();
	free(str);
	map->end = create_room(room);
}

void over_room(t_map *map, char *str)
{
	char	**room;
	t_room	*temp;

	room = NULL;
	room = ft_strsplit(str, ' ');
	room ? components(room) : ft_error();
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
	char **room;

	str = NULL;
	room = NULL;
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
}

void	validition(t_map *map, int fd)
{
	char *str;
	t_list *temp;
	unsigned i;

	str = NULL;
	ents(map, fd);
	rooms(map, fd);
	i = 0;
	ft_lstadd(&map->fist_rooms_create, ft_lstnew_ptr(map->start));
	ft_lstpush(&map->fist_rooms_create, ft_lstnew_ptr(map->end));
	temp = map->fist_rooms_create;
	if(!(map->room = ft_memalloc(sizeof(t_room *) * map->max_room + 3)))
		exit(1);
	while(temp)
	{
		map->room[i] = temp->content;
		++i;
		temp = temp->next;
	}
}

int				main(int a, char **b)
{
	int fd;
	t_map map;

	fd = ft_read_file(b[1]);
	ft_bzero(&map, sizeof(map));
	validition(&map, fd);
	return (0);
}
