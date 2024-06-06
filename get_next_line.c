#include "get_next_line.h"

static char	*read_line(int fd, char *leftover)
{
	char	*buffer;
	ssize_t	bytes_read;
	char	*newline;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		leftover = ft_strjoin(leftover, buffer);
		newline = ft_strchr(leftover, '\n');
		if (newline)
		{
			*newline = '\0';
			free(buffer);
			return (leftover);
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (leftover);
}

static char	*get_line(char **leftover)
{
	char	*newline;
	char	*line;

	newline = ft_strchr(*leftover, '\n');
	if (newline)
	{
		*newline = '\0';
		line = ft_strdup(*leftover);
		*leftover = ft_strdup(newline + 1);
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = read_line(fd, leftover);
	if (!leftover)
		return (NULL);
	line = get_line(&leftover);
	if (line)
		return (line);
	if (*leftover)
	{
		line = ft_strdup(leftover);
		free(leftover);
		leftover = NULL;
		return (line);
	}
	free(leftover);
	leftover = NULL;
	return (NULL);
}
