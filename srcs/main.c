#include <zconf.h>
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

void 	ft_sort_array(t_map *map)
{
	unsigned	i;
	t_room		*temp;

	i = 0;
	while (i < map->max_room - 1)
	{
		if (ft_strcmp(map->room[i]->name, map->room[i + 1]->name) > 0)
		{
			temp =  map->room[i + 1];
			map->room[i + 1] = map->room[i];
			map->room[i] = temp;
			i = i > 2 ? i - 2 : 0;
		}
		else
			++i;
	}
}

t_room	*seach_room(t_room **rooms, unsigned i, unsigned j, char *name)
{
	unsigned p;

	p = (i + j)/2;
	if (!ft_strcmp(name, rooms[p]->name))
		return (rooms[p]);
	else if (i == j)
		ft_error();
	else if (ft_strcmp(name, rooms[p]->name) > 0)
		return (seach_room(rooms, p, j, name));
	else if (ft_strcmp(name, rooms[p]->name) < 0)
		return (seach_room(rooms, i, p, name));
	return (NULL);
}

void 	create_links(t_map *map, char *str)
{
	char **room;
	t_room	*fist;
	t_room	*second;

	room = NULL;
	fist = NULL;
	second = NULL;
	room = ft_strsplit(str, '-');
	components(room, 0);
	fist = seach_room(map->room, 0, map->max_room, room[0]);
	second = seach_room(map->room, 0, map->max_room, room[1]);
	!fist || !second ? ft_error() : 0;
	ft_lstadd(&fist->links, ft_lstnew_ptr(second));
	ft_lstadd(&second->links, ft_lstnew_ptr(fist));
	free(str);
	str = NULL;
}

void	test_print(t_list *test)
{
	t_list *temp;
	t_room	*read;

	temp = test->content;
	while (temp)
	{
		read = temp->content;
		ft_printf("%s\n", read->name);
		temp = temp->next;
	}
}

int				main(int a, char **b)
{
	int fd;
	t_map map;

	fd = ft_read_file(b[1]);
	ft_bzero(&map, sizeof(map));
	ents(&map, fd);
	rooms(&map, fd);
	bfs(&map);
	patch(&map);
	test_print(map.fist_rooms_create);
	return (0);
}
