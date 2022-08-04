/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:34:47 by hakim             #+#    #+#             */
/*   Updated: 2021/12/01 01:40:08 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_glist
{
	char			*backup;
	int				fd;
	struct s_glist	*prev;
	struct s_glist	*next;
}	t_glist;

char	*get_next_line(int fd);
char	*gnl_read(char *backup, int fd);
char	*pick_line(char *backup);
char	*back_up(char *backup);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strdup(const char *src);
int		nl_loc(char *s);
size_t	gnl_strlen(const char *str);
void	free_node(t_glist *node);
t_glist	*find_fd(t_glist *head, int fd);

#endif
