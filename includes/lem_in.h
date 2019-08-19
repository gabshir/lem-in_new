#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include <stdio.h>
# include <limits.h>
# include <math.h>

typedef struct	s_room
{
	char	*name;
	int		x;
	int		y;
	int		n;
	int		f;
	int		isp;
	int		gl;
	t_list	*links;
	int		ant_num;
}				t_room;

typedef struct	s_map
{
	t_room	**room;
	t_room	*start;
	t_room	*end;
	t_list	*fist_rooms_create;
	int 	ents;
	unsigned max_room;
	t_list	*combination;

}				t_map;


#endif
