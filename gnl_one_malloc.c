/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_one_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 13:33:29 by melperri          #+#    #+#             */
/*   Updated: 2021/07/09 14:32:46 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int	ft_malloc_line(char **line, int i)
{
	*line = malloc(sizeof(char) * (i + 1));
	if (*line == NULL)
		return (-1);
	line[0][i] = '\0';
	return (0);
}

static int	ft_recurs(int fd, char **line, int i)
{
	int		ret;
	char	tmp;

	ret = read(fd, &tmp, 1);
	if (ret == -1)
		return (-1);
	else if (ret == 0)
	{
		if (ft_malloc_line(line, i) == -1)
			return (-1);
		return (0);
	}
	else if (tmp == '\n')
	{
		if (ft_malloc_line(line, i) == -1)
			return (-1);
		return (1);
	}
	else
		ft_recurs(fd, line, i + 1);
	line[0][i] = tmp;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	if (fd == -1)
		return (-1);
	return (ft_recurs(fd, line, 0));
}

int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	(void)ac;
	line = NULL;
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close(fd);
	return (0);
}
