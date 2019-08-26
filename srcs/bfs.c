#include "lem_in.h"

t_list *bfs_inc(t_list *startlinks, int f)
{
	t_room	*read;
	t_list *combination;

	combination = NULL;
	while(startlinks)
	{
		read = startlinks->content;
		!read->isp && !read->f ? ft_lstadd(&combination, ft_lstnew_ptr(read)) : 0;
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
		!read->f && !read->isp ? ft_lstadd(new_combination, ft_lstnew_ptr(read)) : 0; //если мы в этот заход не заходили в комнату и она не используется в текущей комбинации путей
		links = links->next;
	}
}

//функция очищает остатки текущей комбинации и то что успело создаться для новой
void	last_free(t_list *combination, t_list *new_combination)
{
	ft_lstdel(&combination, NULL);
	ft_lstdel(&new_combination, NULL);
}

int bfs(t_map *map)
{
	t_list	*combination;
	t_list	*new_combination;
	t_room	*read;
	unsigned gl;

	gl = 1;
	combination = bfs_inc(map->start->links);
	new_combination = NULL;
	map->start->f = 1;
	while (combination)
	{
		read = combination->content;
		!read->f && !read->isp ? read->gl = gl : 0; //если мы в этот заход не заходили в комнату и она не используется в текущей комбинации путей
		read->f = 1;
		if (read->n == map->end->n)
		{
			last_free(combination, new_combination);
			return (1);
		}
		up_combination(&new_combination, read);
		combination = step(combination);
		if (!combination)
		{
			combination = new_combination;
			new_combination = NULL;
			++gl;
		}
	}
	return (0);
}