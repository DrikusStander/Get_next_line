/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 14:35:37 by hstander          #+#    #+#             */
/*   Updated: 2017/06/13 16:53:10 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 10
# include <libc.h>
# include <unistd.h>

/*typedef struct	s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;
*/
int     get_next_line(const int fd, char **line);

#endif
