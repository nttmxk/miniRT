/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:12:00 by hakim             #+#    #+#             */
/*   Updated: 2022/01/19 05:27:50 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_glist	head;
	t_glist			*node;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	node = find_fd(&head, fd);
	if (node == 0)
		return (0);
	node->backup = gnl_read(node->backup, fd);
	if (node->backup == 0)
	{
		free_node(node);
		return (0);
	}
	line = pick_line(node->backup);
	node->backup = back_up(node->backup);
	return (line);
}

char	*gnl_read(char *backup, int fd)
{
	char	*buffer;
	int		rlen;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == 0)
		return (0);
	rlen = 1;
	while (rlen > 0 && nl_loc(backup) == -1)
	{
		rlen = read(fd, buffer, BUFFER_SIZE);
		if (rlen == 0)
			break ;
		if (rlen == -1)
		{
			free(buffer);
			buffer = 0;
			return (0);
		}
		buffer[rlen] = '\0';
		backup = gnl_strjoin(backup, buffer);
	}
	free(buffer);
	buffer = 0;
	return (backup);
}

char	*pick_line(char *backup)
{
	char	*line;
	int		len;
	int		ldex;

	len = 0;
	if (backup[0] == '\0')
		return (0);
	while (backup[len] != '\0' && backup[len] != '\n')
		++len;
	if (backup[len] == '\n')
		++len;
	line = malloc(sizeof(char) * (len + 1));
	if (line == 0)
		return (0);
	ldex = -1;
	while (++ldex < len)
		line[ldex] = backup[ldex];
	line[ldex] = '\0';
	return (line);
}

char	*back_up(char *backup)
{
	char	*new;
	int		index;
	int		deldex;

	deldex = 0;
	while (backup[deldex] != '\0' && backup[deldex] != '\n')
		++deldex;
	if (backup[deldex] == '\n')
		++deldex;
	if (backup[deldex] == '\0')
	{
		free(backup);
		backup = 0;
		return (0);
	}
	new = malloc(sizeof(char) * (gnl_strlen(backup) - deldex + 1));
	if (new == 0)
		return (0);
	index = 0;
	while (backup[deldex] != '\0')
		new[index++] = backup[deldex++];
	new[index] = '\0';
	free(backup);
	backup = 0;
	return (new);
}

t_glist	*find_fd(t_glist *head, int fd)
{
	t_glist	*temp;

	temp = head;
	while (temp->next != 0)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	if (temp->fd == fd)
		return (temp);
	temp->next = malloc(sizeof(t_glist));
	if (temp->next == 0)
		return (0);
	temp->next->backup = 0;
	temp->next->fd = fd;
	temp->next->prev = temp;
	temp->next->next = 0;
	return (temp->next);
}
