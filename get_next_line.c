/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:19:24 by mcauchy-          #+#    #+#             */
/*   Updated: 2024/11/24 16:38:36 by mcauchy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*new_line(char *next_str)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!next_str)
		return (NULL);
	while (next_str[i] && next_str[i] != '\n')
		i++;
	if (!next_str[i])
	{
		free(next_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * ft_strlen(next_str) - i + 1);
	if (!str)
		return (free(next_str), NULL);
	i++;
	j = 0;
	while (next_str[i])
		str[j++] = next_str[i++];
	str[j] = '\0';
	free(next_str);
	return (str);
}

char	*ft_get_line(char *next_str)
{
	int		i;
	char	*new_line;

	i = 0;
	if (!next_str || !next_str[i])
		return (NULL);
	while (next_str[i] != '\n' && next_str[i])
		i++;
	new_line = (char *)malloc(sizeof(char) * i + 2);
	if (!new_line)
		return (NULL);
	i = 0;
	while (next_str[i] != '\n' && next_str[i])
	{
		new_line[i] = next_str[i];
		i++;
	}
	if (next_str[i] && next_str[i] == '\n')
	{
		new_line[i] = next_str[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*read_to_next_str(char *next_str, int fd)
{
	int		rd_bytes;
	char	*buff;

	rd_bytes = 1;
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while ((!ft_find_newline(next_str)) && rd_bytes > 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if ((rd_bytes == -1) || (rd_bytes == 0 && next_str == NULL))
		{
			free(next_str);
			next_str = NULL;
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		next_str = ft_strjoin(next_str, buff);
	}
	free(buff);
	return (next_str);
}

char	*get_next_line(int fd)
{
	static char	*next_str = NULL;
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	next_str = read_to_next_str(next_str, fd);
	if (!next_str)
		return (NULL);
	ret = ft_get_line(next_str);
	if (!ret && next_str && *next_str != '\0')
	{
		ret = ft_strdup(next_str);
		free(next_str);
		next_str = NULL;
	}
	else
		next_str = new_line(next_str);
	return (ret);
}
