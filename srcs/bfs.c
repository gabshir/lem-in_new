#include "lem_in.h"

t_list *bfs_inc(t_list *startlinks)
{
	t_room	*read;
	t_list *combination;

	combination = NULL;
	while(startlinks)
	{
		read = startlinks->content;
		ft_lstadd(&combination, ft_lstnew_ptr(read));
		startlinks = startlinks->next;
	}
	return (combination);
}

t_list	*step(t_list *combination)
{
	t_list *next;

	next = NULL;
	if (combination)
	{
		next = combination->next;
		free(combination);
		combination = NULL;
	}
	return (next);
}

void	up_combination(t_list **new_combination, t_room *room)
{
	t_room	*read;
	t_list	*links;

	links = room->links;
	while (links)
	{
		read = links->content;
		!read->f ? ft_lstadd(new_combination, ft_lstnew_ptr(read)) : 0;
		links = links->next;
	}
}

int bfs(t_map *map)
{
	t_list	*combination;
	t_list	*new_combination;
	t_room	*read;
	unsigned gl;

	gl = 0;
	combination = bfs_inc(map->start->links);
	new_combination = NULL;
	map->start->f = 1;
	while (combination)
	{
		read = combination->content;
		ft_printf("%s ", read->name);
		!read->f ? read->gl = gl : 0;
		read->f = 1;
		if (read->n == map->end->n)
			return (1);
		up_combination(&new_combination, read);
		combination = step(combination);
		if (!combination)
		{
			combination = new_combination;
			new_combination = NULL;
			++gl;
			ft_printf("\n");
		}
	}
	return (0);
}