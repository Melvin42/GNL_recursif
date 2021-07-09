/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_realloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 14:33:55 by melperri          #+#    #+#             */
/*   Updated: 2021/07/09 14:35:30 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static char	*ft_realloc(char *line, unsigned char tmp)
{
	char	*buf;
	int		i;

	buf = NULL;
	i = -1;
	while (line[++i])
		;
	buf = malloc(sizeof(char) * (i + 2));
	if (buf == NULL)
		return (NULL);
	buf[i + 1] = '\0';
	buf[i] = tmp;
	while (i-- > 0)
		buf[i] = line[i];
	free(line);
	line = NULL;
	return (buf);
}

static int	ft_recurs(int fd, char **line)
{
	int				ret;
	unsigned char	tmp;

	tmp = 0;
	ret = read(fd, &tmp, 1);
	if (ret <= -1)
		return (-1);
	else if (tmp == '\n')
		return (1);
	else if (ret == 0)
		return (0);
	else
	{
		*line = ft_realloc(*line, tmp);
		if (*line == NULL)
			return (-1);
		return (ft_recurs(fd, line));
	}
}

int	get_next_line(int fd, char **line)
{
	if (fd == -1)
		return (-1);
	else
	{
		*line = malloc(sizeof(char));
		if (*line == NULL)
			return (-1);
		*line[0] = '\0';
		return (ft_recurs(fd, line));
	}
}

int	main(int ac, char **av)
{
	char	*line;
	int		fd;

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
