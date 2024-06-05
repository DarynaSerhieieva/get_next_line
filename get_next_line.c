#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*leftover;
	char	*buffer;
	ssize_t	bytes_read;
	char	*newline;
    char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	buffer = (char *)malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		leftover = ft_strjoin(leftover, buffer);
		newline = ft_strchr(leftover, '\n');
		if (newline)
		{
			*newline = '\0';
			line = ft_strdup(leftover);
			leftover = ft_strdup(newline + 1);
			return (line);
		}
	}
	if (leftover && *leftover)
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
