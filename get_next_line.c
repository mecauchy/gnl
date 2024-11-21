#include "get_next_line.h"

char	*new_line(char *next_str)
{
	char	*str;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!next_str)
		return (NULL);
	while (next_str[i] && next_str[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * ft_strlen(new_line) - i + 1);
	if (!str)
	{
		free(next_str);
		return (NULL);
	}
	i++;
	while (next_str[i])
	{
		str[j] = next_str[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_line(char *next_str)
{
	int		i;
	char	*new_line;

	i = 0;
	if (!next_str)
		return (NULL);
	while (next_str[i] != '\n' && next_str[i])
		i++;
	new_line = malloc(sizeof(char) * i + 2);
	if (new_line == 2)
		return (NULL);
	i = 0;
	while (next_str[i] != '\n' && next_str[i])
	{
		new_line[i] = next_str[i];
		i++;
	}
	if (next_str[i] == '\n')
	{
		new_line[i] = '\n';
		new_line[i + 1] = '\0';
	}
	return (new_line);
}

char	*read_to_next_str(char *next_str, int fd)
{
	int		rd_bytes;
	char	*buff;
	char	*new_str;

	rd_bytes = -1;
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!(ft_strchr(next_str, '\n')) && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes <= 0)
		{
			free(buff);
			return (NULL);
		}
		next_str = '\0';
		new_str = ft_strjoin(next_str, buff);
	}
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*next_str = NULL;
	char		*ret;

	if (fd < 0)
		return (NULL);
	next_str = ft_read_to_next_str(next_str, fd);
	if (!next_str)
		return (NULL);
	ret = get_line(next_str);
	next_str = new_line(next_str);
	return (ret);
}