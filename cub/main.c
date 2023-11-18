/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosseili <nosseili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:37:09 by nosseili          #+#    #+#             */
/*   Updated: 2023/11/08 20:09:08 by nosseili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pars.h"

int ft_strcmp(char *str1, char *str2)
{
    int i;

    i = 0;
    while(str1[i] && str2[i] && str1[i] == str2[i])
        i++;
    return(str1[i] - str2[i]);
}

void	check_format(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '.')
		i++;
	if (ft_strcmp(".cub", &av[i]) == 1)
	{
		write(2, "Error format\n", 12);
		exit(1);
	}
}

int main(int ac, char **av)
{
    t_vars  s_vars;
    int     fd;
    
    if(ac == 2)
    {
        check_format(av[1]);
        fd = open(av[1], O_RDWR);
        if(fd < 0)
		    exit(1);
	    check_map(av, &s_vars);
    }
}