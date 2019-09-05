#include <zconf.h>
#include "lem_in.h"

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

t_room	*seach_room(t_room **rooms, unsigned st, unsigned f, char *name)
{
	unsigned	p;
 	int			i;
	
	p = (st + f) / 2;
	i = ft_strcmp(name, rooms[p]->name);
	if (st > f)
		ft_error("incorrect room name in link");
	if (st == f - 1 && i)
		ft_error("not found needed room");
	else if (!i)
		return (rooms[p]);
	else if (i > 0)
		return (seach_room(rooms, p, f, name));
	else if (i < 0)
		return (seach_room(rooms, st, p, name));
	return (NULL);
}

void 	create_links(t_map *map, char *str)
{
	char	**room;
	t_room	*first;
	t_room	*second;

	room = NULL;
	first = NULL;
	second = NULL;
	room = ft_strsplit(str, '-');
	components(room, 0);
	first = seach_room(map->room, 0, map->max_room, room[0]);
	second = seach_room(map->room, 0, map->max_room, room[1]);
	!first || !second ? ft_error("no first or second room") : 0;
	ft_lstadd(&first->links, ft_lstnew_ptr(second));
	ft_lstadd(&second->links, ft_lstnew_ptr(first));
	ft_clean_strstr(room);
	free(str);
	str = NULL;
}

void	test_print(t_list *test)
{
	t_list	*temp;
	t_room	*read;

	temp = test->content;
	while (temp)
	{
		read = temp->content;
		ft_printf("%s\n", read->name);
		temp = temp->next;
	}
}

// static	void print_ways(t_ind *ind) //
// {
// 	t_list	*begin;
// 	t_room	*room;
// 	t_list	*list;
// 	int		i;

// 	i = 0;
// 	begin = ind->all_ways;
// 	while (i < ind->count_ways)
// 	{
// 		list = begin->content;
// 		while (list)
// 		{
// 			room = list->content;
// 			list = list->next;
// 		}
// 		i++;
// 		begin = begin->next;
// 	}
// }

int				main(int argc, char **argv)
{
	int		fd;
	t_map	map;
	t_ind	ind;

	argc = 0;
	fd = ft_read_file(argv[1]);
	ft_bzero(&map, sizeof(map));
	ft_bzero(&ind, sizeof(ind));
	ants(&map, fd);
	rooms(&map, fd);
	while (bfs(&map))
	{
		patch(&map);
		restore_room(&map);
	}
	ft_lstpush(&map.combination, ft_lstnew_ptr(map.first_room_create));
	map.first_room_create = NULL;
	unpacking(&map, &ind);
	// list = recharge(&ind);
	// par_rooms()
	return (0);
}
