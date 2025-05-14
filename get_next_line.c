/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:02:00 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/05/14 16:07:52 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_line(int fd, char *stash, char *buffer)
{
	int	bytes_read;

	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			return (NULL);

		}

		printf("buf -> %s\n", buffer);
	}
}

char *get_next_line(int fd)
{
	static char *stash;
	char	*buffer;
	char	*line;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		buffer = NULL;
		return (0);
	}
	line = fill_line(fd, stash, buffer);
	if (!buffer)
		return (0);

	/* printf("Read %d bytes: %s\n", bytes_read, buffer); */
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
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    close(fd);
    return (0);
}
