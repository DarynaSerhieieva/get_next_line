#include "get_next_line.h"

static char	*read_fd(int fd)
{
	ssize_t	bytes_read;
    char		*buffer;

    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
        {
            free(buffer);
            return (NULL);
        }
	else
		buffer[bytes_read] = '\0';
	return (buffer);
}

static char	*new_line(char *leftover)
{
	char	*newline;
    char    *line;
    char    *tmp;
	size_t	line_length;
	size_t	leftover_length;

	newline = ft_strchr(leftover, '\n');
	if (newline)
	{
		line_length = newline + 1 - leftover;
		line = (char *)malloc(line_length + 1);
		if (!line)
			return (NULL);
        ft_strlcpy(line, leftover, line_length + 1);
        leftover_length = ft_strlen(newline + 1);
        if (leftover_length > 0)
        {
            tmp = (char *)malloc(leftover_length + 1);
            if (!tmp)
                return (NULL);
            ft_strlcpy(tmp, newline + 1, leftover_length + 1);
            free(leftover);
            leftover = ft_strdup(tmp);
            return (line);
        }
        free(leftover);
		return (line);
	}
	return (NULL);
}

static char	*get_next(int fd, char **leftover)
{
	char	*line;
	char	*tmp;
    char	*buffer;

    buffer = read_fd(fd);
    if (!buffer)
         return (NULL);
    if (*leftover)
    {
    	tmp = ft_strjoin(*leftover, buffer); 
    	free(buffer);
    	free(*leftover);
		*leftover = ft_strdup(tmp);
		free(tmp);
    }
	else
	{
		*leftover = ft_strdup(buffer);
		free(buffer);
	}
	if (ft_strchr(*leftover, '\n'))
        line = new_line(*leftover);
	else
		line = ft_strdup(*leftover);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!leftover || !ft_strchr(leftover, '\n'))
	{
		line = get_next(fd, &leftover);
		if (!line &&!leftover)
			return (NULL);
	}
	else
    	line = new_line(leftover);
    return (line);
}


