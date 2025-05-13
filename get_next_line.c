/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmora-ro <jmora-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:02:00 by jmora-ro          #+#    #+#             */
/*   Updated: 2025/05/13 17:50:48 by jmora-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



char *get_next_line(int fd)
{
	static char *stash;
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		buffer = NULL;
		return (0);
	}
	if (!buffer)
		return (0);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[bytes_read] = '\0';
		printf("buf -> %s\n", buffer);
	}
	printf("Read %d bytes: %s\n", bytes_read, buffer);
	return (bytes_read);
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
