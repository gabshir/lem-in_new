#include "lem_in.h"

/*
* посещение уже посещенных комнат для восстановления флагов и глубины
*/

void	restor_room(t_map *map)
{
	t_list	*combination;
	t_list	*new_combination;
	t_room	*read;

	combination = bfs_inc(map->start->links, 0);
	new_combination = NULL;
	while(combination)
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