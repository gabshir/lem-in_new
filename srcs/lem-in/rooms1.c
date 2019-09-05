#include "lem_in.h"

/*
* посещение уже посещенных комнат для восстановления флагов и глубины
*/

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

// void	saveway()
// {
	
// }

// int		way_cut(t_map *map)
// {
// 	int		i;
// 	t_list	*cut;

// 	cut = NULL;
// 	i = 0;
// 	map->start->gl = 0;
// 	map->start->f = 1;
// 	while (bfs(map) == 1 && i == 0)
// 	{
// 		map->start->gl = 0;
// 		map->start->f = 1;
// 		map->end->isp = 1;
// 		// saveway
// 		// free room
// 		// make flags free
// 	}
// 	cut ? ft_lstpush(&map->combination, ft_lstnew_ptr(cut)) : 0;
// 	return (i);
// }

// void	
