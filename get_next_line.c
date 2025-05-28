/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:41:05 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/05/28 14:38:02 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	fill_line(char **stash, char *buffer, char **line)
{
	char	*newline_pos;
	int		len_a;
	int		len_b;
	char	*temp;

	newline_pos = ft_strchr(*stash, '\n');
	len_a = newline_pos - *stash;
	len_b = ft_strlen(*stash) - (len_a + 1);
	*line = ft_substr(*stash, 0, (len_a + 1));
	temp = *stash;
	*stash = ft_substr(*stash, len_a + 1, len_b);
	free(temp);
}

char	*handle_eof(char **stash, char *buffer, char **line)
{
	if (ft_strlen(*stash) > 0)
	{
		*line = *stash;
		*stash = NULL;
		free(buffer);
		return (*line);
	}
	free(buffer);
	return (NULL);
}

int	handle_reading(int fd, char **stash, char **buffer, char **line)
{
	char	*temp;
	int		b_read;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, *buffer, BUFFER_SIZE);
		*buffer[b_read] = '\0';
		temp = *stash;
		*stash = ft_strjoin(*stash, *buffer);
		if (ft_strchr(stash, '\n'))
		{
			fill_line(&stash, *buffer, &line);
			free(*buffer);
			free(temp);
			break;
		}
		free(temp);
	}
	return (b_read);
}

char *get_next_line(int fd)
{
	static char *stash;
	char		*buffer;
	int			bytes_read;
	char		*temp;
	char		*line;

	bytes_read = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (stash == NULL)
		stash = ft_strdup("");
	bytes_read = handle_reading(fd, &stash, &buffer, &line);
/* 	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		temp = stash;
		stash = ft_strjoin(stash, buffer);
		if (ft_strchr(stash, '\n'))
		{
			fill_line(&stash, buffer, &line);
			free(buffer);
			free(temp);
			break;
		}
		free(temp);
	} */
	if (bytes_read <= 0)
		return (handle_eof(&stash, buffer, &line));
	return (line);
}

int	main(void)
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
}
