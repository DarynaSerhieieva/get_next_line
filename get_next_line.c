#include "get_next_line.h"

static int	read_fd(char *buffer, int fd)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		free(buffer);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	return (bytes_read);
}

static char	*get_leftover(char *buffer, int fd)
{
	static char	*leftover;
	char		*newline;
	char		*line;

	while (read_fd(buffer, fd) > 0)
	{
		leftover = ft_strjoin(leftover, buffer);
		newline = ft_strchr(leftover, '\n');
		if (newline)
		{
			*newline = '\0';
			free(buffer);
			line = ft_strdup(leftover);
			leftover = ft_strdup(newline + 1);
			return (line);
		}
	}
	free(buffer);
	line = ft_strdup(leftover);
	leftover = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;

	if (!fd || !BUFFER_SIZE)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE +1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = get_leftover(buffer, fd);
	if (!line)
		return (NULL);
	return (line);
}
