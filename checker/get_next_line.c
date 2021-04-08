/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarias-p <rarias-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:01:25 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/25 13:44:24 by rarias-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

char	*ft_acc(char *file, char *buffer)
{
	char	*acc;

	acc = ft_strjoin(file, buffer);
	free(file);
	return (acc);
}

int	get_next_line(int fd, char **line)
{
	int				ret;
	char			*buffer;
	static char		*file[4096];

	if (fd < 0 || line == NULL)
		return (-1);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (1)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret <= 0)
			break ;
		buffer[ret] = '\0';
		if (file[fd] == NULL)
			file[fd] = ft_strdup(buffer);
		else
			file[fd] = ft_acc(file[fd], buffer);
		if (ft_strchr(file[fd], '\n'))
			break ;
	}
	free(buffer);
	if (ret == 0 && !file[fd])
		return (ft_aux(line));
	else
		return (ft_checker(fd, line, file, ret));
}

int	ft_aux(char **line)
{
	*line = ft_strdup("");
	return (0);
}

int	ft_checker(int fd, char **line, char **file, int ret)
{
	int		i;
	char	*temp;

	if (ret == -1)
		return (-1);
	i = 0;
	while (file[fd][i] && file[fd][i] != '\n')
		i++;
	if (file[fd][i] == '\n')
	{
		*line = ft_substr(file[fd], 0, i);
		temp = ft_strdup(&((file[fd])[i + 1]));
		free(file[fd]);
		file[fd] = temp;
	}
	else
	{
		*line = ft_strdup(file[fd]);
		free(file[fd]);
		file[fd] = 0;
		return (0);
	}
	return (1);
}
