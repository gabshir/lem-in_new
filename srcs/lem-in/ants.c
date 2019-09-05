#include "lem_in.h"

void 	ants(t_map *map, int fd)
{
	char *str;

	str = NULL;
	while(map->ants == 0 && get_next_line(fd, &str))
	{
		if (comments(str))
		{
			free(str);
			str = NULL;
			continue;
		}
		map->ants = ft_mini_atoi(str);
	}
}


int		lenways1(t_list *lst, int i, int ants)
{
	t_list	*tmp;
	int		len;
	int		was;
	t_list *list;

	was = i;
	len = 0;
	tmp = lst;
	while (i)
	{
		list = tmp->content;
		len += ft_lstlen(list) + 2;
		tmp = tmp->next;
		--i;
	}
	return ((len - 1 + ants) / was);
}

void	lenways(t_list *tmp, int i, int ants, t_ind *index)
{
	int		ind;

	ind = lenways1(tmp, i, ants);
	if (index->index_ram == 0 || ind < index->index_ram) // i == 1
	{
		index->index_ram = ind;
		index->count_ways = i;
		index->all_ways = tmp;
	}
	// ft_printf("%d\n", index->index_ram); //
}


void	way_ants(t_room *finish, t_list *way)
{
	t_list	*tmp;
	t_room	*read;
	t_room	*up_num;
	int		f;

	f = 1;
	tmp = way;
	while (f && tmp)
	{
		tmp = way;
		read = tmp->content;
		f = 0;
		while (tmp && !read->ant_num)
		{
			read = tmp->content;
			tmp = tmp->next;
		}
		while (tmp && read->ant_num)
		{
			read = tmp->content;
			tmp = tmp->next;
		}
		if (tmp && tmp->next)
		{
			up_num = tmp->next->content;
			up_num->ant_num = read->ant_num;
			read->ant_num = 0;
			ft_printf("L%d - %s ", up_num->ant_num, up_num->name);
			f = 1;
		}
		if (tmp && !tmp->next)
		{

			ft_printf("L%d - %s ", read->ant_num, read->name);
			read->ant_num = 0;
			++finish->ant_num;
			f = 1;
		}
	}
}

void	print_ants(t_room *start, t_room *finish, t_ind *combo, int ants)
{
	t_list	*tmp;
	t_room	*read;
	int		ant_num;

	ant_num = 1;
	start->ant_num = ant_num;
	while (finish->ant_num != ants)
	{
		ft_putchar('\n');
		//размещение муравьев
		tmp = combo->all_ways;
		while (tmp)
		{
			way_ants(finish, tmp->content);
			tmp = tmp->next;
		}

		while (combo->count_ways && start->ant_num)
		{
			read = tmp->content;
			read->ant_num = ant_num;
			ft_printf("L%d - %s ",read->ant_num, read->name);
			--combo->count_ways;
			--start->ant_num;
		}

	}
}

void	unpacking(t_map *map, t_ind *ind)
{
	t_list	*tmp;
	t_list	*st;
	int		index;
	int 	len_comb;

	index = 1;
	st = map->combination;
	while (st)
	{
		tmp = st->content;
		len_comb = ft_lstlen(tmp);
		while (len_comb)
		{
			lenways(tmp, index++, map->ants, ind);
			--len_comb;
		}
		st = st->next;
	}
	// print_ways(ind);
//	par_rooms(map->end, list, map->ants);
}