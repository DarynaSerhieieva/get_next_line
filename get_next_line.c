#include "get_next_line.h"

static char	*read_fd(int fd)
{
	ssize_t	bytes_read;
	char	*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	return (buffer);
}

static char	*extract_line(char **leftover, char *newline)
{
	char	*line;
	size_t	line_length;

	line_length = newline + 1 - *leftover;
	line = (char *)malloc(line_length + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *leftover, line_length + 1);
	return (line);
}

static void	update_leftover(char **leftover, char *newline)
{
	char	*tmp;
	size_t	leftover_length;

	leftover_length = ft_strlen(newline + 1);
	if (leftover_length > 0)
	{
		tmp = (char *)malloc(leftover_length + 1);
		if (tmp)
		{
			ft_strlcpy(tmp, newline + 1, leftover_length + 1);
			free(*leftover);
			*leftover = tmp;
		}
	}
	else
	{
		free(*leftover);
		*leftover = NULL;
	}
}

static char	*process_leftover(char **leftover)
{
	char	*newline;
	char	*line;

	newline = ft_strchr(*leftover, '\n');
	line = NULL;
	if (newline)
	{
		line = extract_line(leftover, newline);
		update_leftover(leftover, newline);
	}
	else if (*leftover)
	{
		line = ft_strdup(*leftover);
		free(*leftover);
		*leftover = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*leftover = NULL;
	char		*buffer;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_fd(fd);
	while (buffer)
	{
		if (leftover)
			tmp = ft_strjoin(leftover, buffer);
		else
			tmp = ft_strdup(buffer);
		free(buffer);
		if (!tmp)
			return (NULL);
		free(leftover);
		leftover = tmp;
		if (ft_strchr(leftover, '\n'))
			break ;
		buffer = read_fd(fd);
	}
	if (leftover)
		return (process_leftover(&leftover));
	return (NULL);
}
