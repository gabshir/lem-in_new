#include "lem_in.h"

void	patch(t_map *map)
{
	t_list	*way;
	t_list	*temp;
	t_room	*read;
	unsigned 	gl;

	way = NULL;
	temp = map->end->links;
	gl = map->end->gl - 1;
	while (temp && gl)
	{
		read = temp->content;
		if (read->gl == gl)
		{
			ft_lstadd(&way, ft_lstnew_ptr(read));
			temp = read->links;
			read->isp = 1;
			--gl;
		}
		else
			temp = temp->next;
	}
	way ? ft_lstadd(&map->fist_rooms_create, ft_lstnew_ptr(way)) : 0;
}
