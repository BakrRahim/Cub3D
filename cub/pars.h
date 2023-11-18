/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosseili <nosseili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:45:51 by nosseili          #+#    #+#             */
/*   Updated: 2023/11/08 20:11:51 by nosseili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
#define PARS_H

#include "unistd.h"
#include "stdio.h"
#include "fcntl.h"
#include "stdlib.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_vars
{
    int index_file;
    int size_map;
    char view;
    char *north;
    char *south;
    char *west;
    char *east;
    int *floor;
    int *ceiling;
    char **map;
    
}   t_vars;

void   check_map(char **av, t_vars *s_vars);
int	ft_strlen(char *str);
char	*ft_strdup(char *s);
char	*get_next_line(int fd);
int ft_strcmp(char *str1, char *str2);
char	**ft_split(const char *str, char c);

#endif