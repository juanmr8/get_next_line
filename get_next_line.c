/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:02:00 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/05/27 17:14:52 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* char	*fill_line(int fd, char *stash, char *buffer)
{
	int	bytes_read;
	char	*line;


	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			return (NULL);

		}
		printf("Buffer: %s\n", buffer);
		if (found_line_break(buffer, line) == 1)
			return (line);
	}
	free(stash);
	return (NULL);
} */

/* void print_newline(char *buffer)
{
	while (*buffer && *buffer != '\0')
	{
		if (*buffer == '\n')
		{
			*buffer= '\\';
		}
		printf("%c",*buffer);
		buffer++;
	}

} */
char *find_line_break(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (str);
		str++;
	}
	return (NULL);
}
char *fill_line(int fd)
{
	int	bytes_read;
	char	*buffer;
	char	*accumulated;
	char	*temp;

	accumulated = ft_strdup("");
	bytes_read = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		temp = accumulated;
		accumulated = ft_strjoin(accumulated, buffer);
		free(temp);
		if (find_line_break(accumulated))
			break ;
	}
	if (bytes_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (accumulated);
}



char *get_next_line(int fd)
{
	static char *stash;
	char	*buffer;
	char *newline_pos;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		buffer = NULL;
		return (0);
	}
	if (stash == NULL)
	{
		buffer = fill_line(fd);
	}
	else if (stash[0] != '\0')
	{
		printf("Stash has data: %s\n", stash);
		buffer = stash;  // Just to avoid the buffer error for now
	}
	else
	{
		buffer = fill_line(fd);
	}
	if (!buffer)
		return (0);
	newline_pos = find_line_break(buffer);
	if (newline_pos != NULL)
	{
		printf("Found newline!\n");
		return (buffer);
	}
	else
	{
		printf("No newline found\n");
		return (buffer);
	}
}

int	main(void)
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return (1);
    }
    get_next_line(fd);
    close(fd);
    return (0);
}
