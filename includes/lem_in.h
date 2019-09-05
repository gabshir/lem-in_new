#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include <stdio.h>
# include <limits.h>
# include <math.h>

typedef struct	s_room
{
	char		*name;
	int			x;
	int			y;
	int			n;
	int			f;
	int			isp;
	int			gl;
	t_list		*links;
	int			ant_num;
}				t_room;

typedef struct	s_map
{
	int			ants;
	t_room		**room;
	t_room		*start;
	t_room		*end;
	t_list		*first_room_create;
	char		*first_link;
	unsigned	max_room;
	t_list		*combination;
}				t_map;

typedef struct	s_ind
{
	int			count_ways;
	t_list		*all_ways;
	int			index_ram;
}				t_ind;

int				main(int argc, char **argv);

void 			ants(t_map *map, int fd);
int				comments(char *str);
int				ft_mini_atoi(char *line);
void			ft_error(char *str);
void			ft_clean_strstr(char **str);

void			rooms(t_map *map, int fd);
int				ft_start_and_end(t_map *map, int fd, char *str);
void			ft_starts(t_map *map, int fd, char *str);
void			components(char **room, int f);
t_room			*create_room(char **room);
void			ft_end(t_map *map, int fd, char *str);
void			over_room(t_map *map, char *str);
void			rooms_in_array(t_map *map, int *f);
void			check_double_name(t_map *map);
void 			ft_sort_array(t_map *map);
void 			create_links(t_map *map, char *str);
t_room			*seach_room(t_room **rooms, unsigned i, unsigned j, char *name);

int				bfs(t_map *map);
t_list			*bfs_inc(t_list *startlinks, int f);
void			up_combination(t_list **new_combination, t_room *room, int f);
t_list			*step(t_list *combination);
void			last_free(t_list *combination, t_list *new_combination);
void			restore_room(t_map *map);

void			patch(t_map *map);
int				way_cut(t_map *map);
void			lenways(t_list *tmp, int i, int ants, t_ind *index, t_list *temp_save);
int				lenways1(t_list *tmp, int i, int ants);
int				len_ant_way(t_list **list, int i, int ants);
t_list			**recharge(t_ind *ind);
void			par_rooms(t_room *finish, t_list **list, int ants);
void			print_ants(t_list *list, t_room *finish);
int				check_zero(t_list *list);

#endif
