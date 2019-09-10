/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrooks <acrooks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 21:18:28 by acrooks           #+#    #+#             */
/*   Updated: 2019/09/09 22:00:13 by acrooks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ants(t_map *map, int fd)
{
	char *str;

	str = NULL;
	while (map->ants == 0 && get_next_line(fd, &str))
	{
		ft_printf("%s\n", str);
		if (comments(str))
			continue;
		map->ants = ft_mini_atoi(str);
	}
}

int		lenways1(t_list *lst, int i, int ants)
{
	t_list	*tmp;
	int		len;
	int		was;
	t_list	*list;

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
	if (index->index_ram == 0 || ind < index->index_ram)
	{
		index->index_ram = ind;
		index->count_ways = i;
		index->all_ways = tmp;
	}
}

t_room	**room_way_in_array(t_list *way, t_way *link)
{
	t_room		**room;
	t_list		*temp;
	unsigned	i;

	link->i = ft_lstlen(way);
	if (!(room = ft_memalloc(sizeof(t_room *) * (link->i + 1))))
		exit(1);
	temp = way;
	i = 0;
	while (temp)
	{
		room[i] = temp->content;
		++i;
		temp = temp->next;
	}
	return (room);
}

t_way	**way_transform(t_ind *ind)
{
	t_way	**all;
	t_list	*tmp_all;
	t_list	*temp_vn;
	int		way;

	way = 0;
	tmp_all = ind->all_ways;
	if (!(all = (t_way **)ft_memalloc(sizeof(t_way *) * (ind->count_ways + 1))))
		exit(1);
	all[ind->count_ways] = NULL;
	while (way < ind->count_ways)
	{
		temp_vn = tmp_all->content;
		all[way] = ft_memalloc(sizeof(t_way));
		all[way]->room = room_way_in_array(temp_vn, all[way]);
		++way;
		tmp_all = tmp_all->next;
	}
	return (all);
}

void	print_ants_on_one_way(t_way *way, t_room *finish)
{
	int		len;
	t_room	**room;

	room = way->room;
	len = way->i - 1;
	while (len > -1)
	{
		if (room[len + 1] && room[len]->ant_num)
		{
			room[len + 1]->ant_num = room[len]->ant_num;
			ft_printf("L%d-%s ", room[len + 1]->ant_num, room[len + 1]->name);
			room[len]->ant_num = 0;
		}
		else if (!room[len + 1] && room[len]->ant_num)
		{
			++finish->ant_num;
			ft_printf("L%d-%s ", room[len]->ant_num, finish->name);
			room[len]->ant_num = 0;
		}
		--len;
	}
}

void	combo(t_list *tmp, t_ind *ind, int ants)
{
	int	len_comb;
	int	index;

	index = 1;
	len_comb = ft_lstlen(tmp);
	while (len_comb)
	{
		lenways(tmp, index++, ants, ind);
		--len_comb;
	}
}

void	print_ants_on_way(t_way **r, t_room *finish, int ants, t_ind *ind)
{
	int		a;
	int		i;

	a = 1;
	while (finish->ant_num != ants)
	{
		i = 0;
		ft_putchar('\n');
		while (r[i])
		{
			print_ants_on_one_way(r[i], finish);
			++i;
		}
		i = 0;
		combo(ind->all_ways, ind, ants - a + 1);
		while (a <= ants && i < ind->count_ways)
		{
			r[i]->room[0]->ant_num = a;
			ft_printf("L%d-%s ", r[i]->room[0]->ant_num, r[i]->room[0]->name);
			++i;
			++a;
		}
	}
}

void	unpacking(t_map *map, t_ind *ind)
{
	t_list	*tmp;
	t_list	*st;
	t_way	**all;

	st = map->combination;
	while (st)
	{
		tmp = st->content;
		combo(tmp, ind, map->ants);
		st = st->next;
	}
	all = way_transform(ind);
	print_ants_on_way(all, map->end, map->ants, ind);
	write(1, "\n", 1);
	free_array(all);
	free_map(map);
}
