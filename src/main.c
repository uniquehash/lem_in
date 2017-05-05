/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelange <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 09:43:04 by obelange          #+#    #+#             */
/*   Updated: 2016/10/27 09:43:07 by obelange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


void	read_from_stdin(t_farm *farm)
{
	int		phase;
	char	*line;
	int		ret;
	int		i;

	phase = 0;
	i = 0;
	line = NULL;	
	while((get_next_line(0, &line)) > 0)
	{
		// printf("\n%s\n", line);
		// printf("phase: %d\n", phase);
		ret = 1;
		i = 0;
		while (ret == 1)
			ret = farm->parsing[i++](farm, &phase, line);

		ft_strdel(&line);
		if (ret == -1)
			break;
		// printf("%s\n", line);
		
	}	
}





int	find_path(t_farm *farm, char *room)
{
	int		i;
	t_room	*curr;
	int		ret;

	
	curr = t_room_get(farm->spawns, room);
	i = ft_strlist_len(curr->connections);

	if (ft_strlist_findindex(curr->connections, farm->end) > -1)
	{
		farm->path = ft_strlist_add(farm->path, room);
		farm->path = ft_strlist_add(farm->path, farm->end);
		return (1);
	}

	// printf("room: %s\n", room);
	// printf("find_path:\n");
	// ft_strlist_print(farm->path);

	while(--i >= 0)
	{
		// printf("i: %d\n", i);		
		if (ft_strlist_findindex(farm->path, curr->connections[i]) == -1)
		{
			farm->path = ft_strlist_add(farm->path, room);
			// printf("_find_path:\n");
			// ft_strlist_print(farm->path);			
			if (find_path(farm, curr->connections[i]) == 1)
			{
				// farm->path = ft_strlist_add(farm->path, curr->connections[i]);
				// farm->path = ft_strlist_add(farm->path, farm->end);
				return (1);
			}
			else
				farm->path = ft_strlist_remove(farm->path, room);
		}
		// printf("term\n");
	}
	return (0);
}
















int	main(void){

	t_farm	*farm;


	farm = t_farm_build();
	read_from_stdin(farm);



	// int phase = 2;
	// printf("ret: %d, phase: %d\n", farm->parsing[2](farm, &phase, "room-4"), phase);



	// t_farm_print(farm);
	
	int path_res = -1;
	path_res = find_path(farm, farm->start);
	printf("path found: %d\n", path_res);
	printf("path-->\n");
	ft_strlist_print(farm->path);

	// t_room	*a;
	// t_room	*b;
	// t_room	*c;

	// farm->spawns = t_room_build(ft_strdup("fosho"));

	// t_room_print(farm->spawns);

	// a = t_room_build(ft_strdup("swag"));
	// b = t_room_build(ft_strdup("dag"));
	// c = t_room_build(ft_strdup("rag"));

	// printf("farm:\n");
	// t_rooms_print(farm->spawns);
	
	// printf("\nroom a------->\n");
	// t_rooms_print(a);
	// printf("\nroom b------->\n");
	// t_rooms_print(b);
	// printf("\nroom c------->\n");
	// t_rooms_print(c);

	// t_room_add(farm->spawns, a);
	// t_room_add(farm->spawns, b);
	// t_room_add(farm->spawns, c);

	// printf("\nfarm------->\n");
	// t_rooms_print(farm->spawns);

	// printf("valid link: %d\n", t_room_valid_link(farm, "dag", "swag"));

	// t_room_destroy_all(&farm->spawns);




	// printf("room: %p\n", farm->spawns);
	// printf("\n\n\n\n\n\n");
	// find_path(farm, "start");



	t_farm_destroy(&farm);




}















