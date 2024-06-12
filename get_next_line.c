#include "get_next_line.h"

static ssize_t	read_fd(char *buffer, int fd)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		buffer[0] = '\0';
	else
		buffer[bytes_read] = '\0';
	return (bytes_read);
}

static int	new_line(char *leftover, char **line)
{
	char	*newline;

	if (!leftover)
		return (0);
	newline = ft_strchr(leftover, '\n');
	if (newline)
	{
		*newline = '\0';
		*line = ft_strdup(leftover);
		if (!*line)
			return (-1);
		ft_strlcpy(leftover, newline + 1, ft_strlen(newline + 1) + 1);
		return (1);
	}
	return (0);
}

static char	*get_leftover(int fd, char **leftover, char *buffer)
{
	char	*line;

	line = NULL;
	while (read_fd(buffer, fd) > 0)
	{
		*leftover = ft_strjoin(*leftover, buffer);
		if (!*leftover)
		{
			free(buffer);
			return (NULL);
		}
		if (new_line(*leftover, &line))
		{
			free(buffer);
			return (line);
		}
	}
	free(buffer);
	if (*leftover && **leftover)
		line = ft_strdup(*leftover);
	free(*leftover);
	*leftover = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*leftover = NULL;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (leftover && new_line(leftover, &line))
		return (line);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = get_leftover(fd, &leftover, buffer);
	return (line);
}

/*static char	*get_leftover(int fd, char **leftover, char *buffer)
{
	char	*line;
	char	*temp;

	line = NULL;
	while (read_fd(buffer, fd) > 0)
	{
		temp = ft_strjoin(*leftover, buffer);
		if (!temp)
		{
			free(buffer);
			return (NULL);
		}
		free(*leftover);
		*leftover = temp;
		if (new_line(*leftover, &line))
		{
			free(buffer);
			return (line);
		}
	}
	free(buffer);
	if (*leftover && **leftover)
		line = ft_strdup(*leftover);
	free(*leftover);
	*leftover = NULL;
	return (line);
}*/