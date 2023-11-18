#include "pars.h"

int verify_map(t_vars *s_vars)
{
    int i;
    int j;
    int flag;
    int first;

    i = 0;
    j = 0;
    flag = 0;
    while(s_vars->map[i])
    {    
        j = 0;
        first = 0;
        while(s_vars->map[i][j])
        {
            while (s_vars->map[i][j] == ' ' || s_vars->map[i][j] == '\t')
            {
                j++;
                first = j;
            }
            if(s_vars->map[i][j] != '1' && s_vars->map[i][j] != '0' 
            && s_vars->map[i][j] != ' ' && s_vars->map[i][j] != s_vars->view)
                return(0);
            if (flag == 0)
	        {
		        flag = j;
		        while(s_vars->map[i][flag])
		        {
			        if (s_vars->map[i][flag] != '1' && s_vars->map[i][flag] != ' ')
				        return(0);
			        flag++;
		        }
	        }
            if(s_vars->map[i][first] != '1' || s_vars->map[i][ft_strlen(s_vars->map[i])- 1] != '1')
            {
                return(0);
            }
            if (flag != 0 && i == s_vars->size_map - 1)
	        {
		        flag = j;
		        while (s_vars->map[i][flag])
		        {
			        if (s_vars->map[i][flag] != '1' && s_vars->map[i][flag] != ' ')
				        return(0);
			        flag++;
		        }
	        }
            if (s_vars->map[i][j] == '0')
	        {
		    if (s_vars->map[i - 1] && ft_strlen(s_vars->map[i - 1]) - 1 < j)
			    return (0);
		    if (s_vars->map[i + 1] && ft_strlen(s_vars->map[i + 1]) - 1 < j)
			    return (0);
		    if (s_vars->map[i][j + 1] && s_vars->map[i][j + 1] != '0'
			    && s_vars->map[i][j + 1] != '1' && s_vars->map[i][j + 1] != s_vars->view)
			    return (0);
		    if (s_vars->map[i + 1][j] && s_vars->map[i + 1][j] != '0'
			    && s_vars->map[i + 1][j] != '1' && s_vars->map[i + 1][j] != s_vars->view)
			    return (0);
		    if (s_vars->map[i][j - 1] && s_vars->map[i][j - 1] != '0'
			    && s_vars->map[i][j - 1] != '1' && s_vars->map[i][j - 1] != s_vars->view)
			    return (0);
		    if (s_vars->map[i - 1][j] && s_vars->map[i - 1][j] != '0'
			    && s_vars->map[i - 1][j] != '1' && s_vars->map[i - 1][j] != s_vars->view)
			    return (0);
	    }
            j++;
        }
        i++;
    }
    return(1);
}
void    fill_check_map(char **av, t_vars *s_vars, char *line, int fd)
{
    int     i;
    int     j;
    int     check;

    i = 0;
    j = 0;
    s_vars->map = malloc(sizeof(char *) * s_vars->size_map + 1) ;
    close(fd);
    fd = open(av[1], O_RDWR);
    s_vars->map[0] = ft_strdup(line);
    line = get_next_line(fd);
    while(s_vars->index_file)
    {
        s_vars->index_file--;
        line = get_next_line(fd);
    }
    while(line && s_vars->size_map > j)
    {
        s_vars->map[j] = ft_strdup(line);
        i = 0;
        while(s_vars->map[j][i])
        {

            if(s_vars->map[j][i] == 'N' || s_vars->map[j][i] == 'S' 
                || s_vars->map[j][i] == 'W' || s_vars->map[j][i] == 'E')
            {
                s_vars->view = s_vars->map[j][i];
            }
            i++;
        }
        j++;
        line = get_next_line(fd);
    }
    s_vars->map[j] = NULL;
    check = verify_map(s_vars);
    if(check == 0)
    {
        write(2, "Error map\n", 10);
        exit(1);
    }
}

void    size_map(int fd, t_vars *s_vars)
{
    char    *line;
    int     j;

    j = 0;
    s_vars->size_map = 1;
    line = get_next_line(fd);
    while(line)
    {
        j = 0;
        while(line[j] == ' ' || line[j] == '\t')
            j++;
        if(line[j] == '1' || line[j] == '0')
        {
            s_vars->size_map++;
        }
        line = get_next_line(fd);
    }
}
void    check_map(char **av, t_vars *s_vars)
{
    char    *line;
    char    *str;
    char    **str2;
    int     i;
    int     j;
    int     x;
    int     y;
    int     fd;

    i = 0;
    j = 0;
    fd = open(av[1], O_RDWR);
    line = get_next_line(fd);
    s_vars->index_file = 0;
    while(line)
    {
        i = 0;
        while(line[i] == ' ' || line[i] == '\t')
            i++;
        if(line[i] == '1' || line[i] == '0')
        {
            size_map(fd, s_vars);
            fill_check_map(av, s_vars, line, fd);
        }
        if(line[i] == 'F')
        {
            i++;
            y = 0;
            y = i;
            while(line[y])
            {
                if((line[y] < '0' || line[y] > '9') && line[y] != ',' 
                    && line[y] != ' ' && line[y] != '\t')
                    exit(1);
                y++;
            }
            while(line[i] && (line[i] == ' ' || line[i] == '\t'))
                i++;
            j = i;
            str = ft_strdup(line + j);
            str2 = ft_split(str, ',');
            x = 0;
            i = 0;
            while(str2[x])
                x++;
            if(x != 3)
                exit(1);
            s_vars->floor = malloc(sizeof(int) * (x));
            while (str2[i])
	        {
		        if (atoi(str2[i]) > 255 || atoi(str2[i]) < 0)
			        exit(1);
		        s_vars->floor[i] = atoi(str2[i]);
		        i++;
	        }
        }
        if(line[i] == 'C')
        {
            i++;
            y = 0;
            y = i;
            while(line[y])
            {
                if((line[y] < '0' || line[y] > '9') && line[y] != ',' 
                    && line[y] != ' ' && line[y] != '\t')
                    exit(1);
                y++;
            }
            if(line[i] != ' ' && line[i] != '\t')
                exit(1);
            while(line[i] && (line[i] == ' ' || line[i] == '\t'))
                i++;
            j = i;
            str = ft_strdup(line + j);
            str2 = ft_split(str, ',');
            x = 0;
            i = 0;
            while(str2[x])
                x++;
            if(x != 3)
                exit(1);
            s_vars->ceiling = malloc(sizeof(int) * (x));
            while (str2[i])
	        {
		        if (atoi(str2[i]) > 255 || atoi(str2[i]) < 0)
			        exit(1);
		        s_vars->ceiling[i] = atoi(str2[i]);
		        i++;
	        }
        }
        if (line[i] == 'E' && line[i + 1] == 'A')
	    {
		    i = i + 2;
	        while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		            i = i + 1;
	        j = i;
	        if (line[i] != ' ' && line[i] != '\t')
	        {
		        while (line[i] && (line[i] != ' ' && line[i] != '\t'))
			        i = i + 1;
		        while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			        i = i + 1;
	        }
	        if (line[i] && (line[i] != '\0' && line[i] != '\n' && line[i] != 8))
		        exit(1);
		    s_vars->east = ft_strdup(line + j);
	    }
        if (line[i] == 'S' && line[i + 1] == 'O')
	    {
		    i = i + 2;
	        while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		    i = i + 1;
	        j = i;
	        if (line[i] != ' ' && line[i] != '\t')
	        {
		        while (line[i] && (line[i] != ' ' && line[i] != '\t'))
			        i = i + 1;
		        while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			        i = i + 1;
	        }
	        if (line[i] && (line[i] != '\0' && line[i] != '\n' && line[i] != 8))
            	exit(1);
		    s_vars->south = ft_strdup(line + j);
	    }
        if (line[i] == 'N' && line[i + 1] == 'O')
	    {
		    i = i + 2;
	        while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		    i = i + 1;
	        j = i;
	        if (line[i] != ' ' && line[i] != '\t')
	        {
		        while (line[i] && (line[i] != ' ' && line[i] != '\t'))
			        i = i + 1;
		        while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			        i = i + 1;
	        }
	        if (line[i] && (line[i] != '\0' && line[i] != '\n' && line[i] != 8))
		        exit(1);
		    s_vars->north = ft_strdup(line + j);
	    }
        if (line[i] == 'W' && line[i + 1] == 'E')
	    {
		    i = i + 2;
	        while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		    i = i + 1;
	        j = i;
	        if (line[i] != ' ' && line[i] != '\t')
	        {
		        while (line[i] && (line[i] != ' ' && line[i] != '\t'))
			        i = i + 1;
		        while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			        i = i + 1;
	        }
	        if (line[i] && (line[i] != '\0' && line[i] != '\n' && line[i] != 8))
		        exit(1);
		    s_vars->west = ft_strdup(line + j);
	    }
        s_vars->index_file++;
        line = get_next_line(fd);
    }
    if(s_vars->north == NULL || s_vars->south == NULL || s_vars->west == NULL || s_vars->east == NULL)
    {
        write(2, "Error texture\n", 14);
        exit(1);
    }
    if(s_vars->floor == NULL || s_vars->ceiling == NULL)
    {
        write(2, "Error color\n", 12);
        exit(1);
    }
    if(s_vars->view == '\0')
    {
        write(2, "Error view\n", 11);
        exit(1);
    }
    i = 0;
    while(s_vars->floor[i])
    {
        printf("floor[%d] = %d\n", i, s_vars->floor[i]);
        i++;
    }
    i = 0;
    while(s_vars->ceiling[i])
    {
        printf("ceiling[%d] = %d\n", i, s_vars->ceiling[i]);
        i++;
    }
    i = 0;
    while(s_vars->map[i])
    {
        printf("map[%d] = %s\n", i, s_vars->map[i]);
        i++;
    }
    printf("view = %c\n", s_vars->view);
    printf("north = %s\n", s_vars->north);
    printf("south = %s\n", s_vars->south);
    printf("west = %s\n", s_vars->west);
    printf("east = %s\n", s_vars->east);
}