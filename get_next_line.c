#include "get_next_line.h"
char	*get_statc_temp(char *temp)
{
	char	*rtn;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!temp)
		return (0);
	while (temp[i] && temp[i] != '\n')
		i++;
	if (!temp[i])
	{
		free(temp);
		return (0);
	}
	if (!(rtn = malloc(sizeof(char) * ((ft_strlen(temp) - i) + 1))))
		return (0);
	i++;
	while (temp[i])
		rtn[j++] = temp[i++];
	rtn[j] = '\0';
	free(temp);
	return (rtn);
}

char	*get_line(char *str)
{
	int		i;
	char	*rtn;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(rtn = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

int			has_newline(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char			*buf;
	static char		*temp;
	int				read_size;

	read_size = 1;
	if (fd < 0 || !line || bufER_SIZE <= 0)
	{
		return (-1);
	}
	if (!(buf = malloc(sizeof(char) * (bufER_SIZE + 1))))
	{
		return (-1);
	}
	while (!has_newline(temp) && read_size != 0)
	{
		if ((read_size = read(fd, buf, bufER_SIZE)) == -1)
		{
			free(buf);
			return (-1);
		}
		buf[read_size] = '\0';
		temp = join_str(temp, buf);
	}
	free(buf);
	*line = get_line(temp);
	temp = get_statc_temp(temp);
	if (read_size == 0)
		return (0);
	return (1);
}