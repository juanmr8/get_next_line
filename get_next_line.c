/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:05 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/05/29 18:44:31 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	fill_line(char **stash, char **line)
{
	char	*newline_pos;
	int		len_a;
	int		len_b;
	char	*temp;

	newline_pos = ft_strchr(*stash, '\n');
	if (!newline_pos)
	{
		*line = NULL;
		return ;
	}
	len_a = newline_pos - *stash;
	len_b = ft_strlen(*stash) - (len_a + 1);
	*line = ft_substr(*stash, 0, (len_a + 1));
	temp = *stash;
	*stash = ft_substr(*stash, len_a + 1, len_b);
	free(temp);
}

char	*handle_eof(char **stash, char *buffer, char **line)
{
	free(buffer);
	if (*stash && ft_strlen(*stash) > 0)
	{
		*line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
		return (*line);
	}
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (NULL);
}

int	safe_append(char **stash, char *buffer)
{
	char	*temp;
	char	*new_stash;

	temp = *stash;
	new_stash = ft_strjoin(*stash, buffer);
	if (!new_stash)
	{
		free(temp);
		*stash = NULL;
		return (0);
	}
	*stash = new_stash;
	free(temp);
	return (1);
}

int	handle_reading(int fd, char **stash, char **buffer, char **line)
{
	int	b_read;

	while (1)
	{
		b_read = read(fd, *buffer, BUFFER_SIZE);
		if (b_read < 0)
		{
			free(*stash);
			*stash = NULL;
			break ;
		}
		if (b_read <= 0)
			break ;
		(*buffer)[b_read] = '\0';
		if (!safe_append(stash, *buffer))
			return (-1);
		if (ft_strchr(*stash, '\n'))
		{
			fill_line(stash, line);
			return (1);
		}
	}
	return (b_read);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	int			bytes_read;
	char		*line;

	line = NULL;
	if (stash == NULL)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(stash), stash = NULL, NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (ft_strchr(stash, '\n'))
		return (fill_line(&stash, &line), free(buffer), line);
	bytes_read = handle_reading(fd, &stash, &buffer, &line);
	if (bytes_read < 0)
		return (free(buffer), NULL);
	if (bytes_read == 0)
		return (handle_eof(&stash, buffer, &line));
	return (free(buffer), (line));
}

/* int	main(void)
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return (1);
    }
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    close(fd);
    return (0);
} */
