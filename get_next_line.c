/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 08:41:35 by hstander          #+#    #+#             */
/*   Updated: 2017/06/14 12:42:34 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

int 	line_size(const int fd)
{
	int ret;
	int i;
	char buf[1];

	i = 0;
	while (buf[0] != '\n' && buf[0] != EOF)
	{
		ret = read(fd, buf, 1);
		i++;
	}
	i--;
//	printf("%d\n", i);
	return (i);
}

int		get_next_line(const int fd, char **line)
{
//	printf("fd = %d\n", fd);
	int ret;
	int cnt;
	t_list *start;
	t_list *list;
	t_list *tmp;
	int i;
	char *ptr;
	char buf[BUFF_SIZE + 1];

	list = (t_list *)malloc(sizeof(t_list));
	start = list;
	i = 1;
	cnt = 0;
	//read(fd, buf, 1);
	while (i != 0)
	{
		i = 0;
		ft_bzero(buf, BUFF_SIZE);
		while ((ret = read(fd, &buf[i], 1)) && buf[i] != '\n')
		{
//			printf("|%c|\n", buf[i]);
			if (i == BUFF_SIZE)
			{
				tmp = list;
				list = ft_lstnew(buf, BUFF_SIZE);
				//list->content = ft_strdup(buf, BUFF_SIZE);
				//read(fd, buf, 1);
				tmp->next = list;
			//	printf("%s\n", list->content);
				i = -1;
				ft_bzero(buf, BUFF_SIZE);
			}
			cnt++;
			i++;
		}
//		printf("break\n");
		if (i <= BUFF_SIZE)
		{
			buf[i] = '\0';
			tmp = list;
			list = ft_lstnew(buf, BUFF_SIZE);
			tmp->next = list;
			i = 0;
		}
		else
			break;
	}
	list->next = NULL;
//	printf("+\n");
	ptr = (char *)malloc(sizeof(char) * cnt);
	ft_bzero(ptr, cnt);
	*line = ptr;
//	printf("++\n");
	tmp  = start->next;
	while (tmp)
	{
 	//	printf("+++\n");
		ft_strlcat(*line,tmp->content, cnt);
//		printf("||%s\n", ptr);
		tmp = tmp->next;
	}
//	*line =  ptr;
 	start = start->next;
	while (start)
	{
		tmp = start->next;
//		printf("^\n");
		free(start->content);
//		printf("^^\n");
		start->content_size = 0;
//		printf("^^^\n");
		start = NULL;
		start = tmp;
	}
	//printf("@@%s\n", *line);
//	printf("%s\n", ptr);
//	printf("|%d|\n", ret);
	return (1);
}

int main(int ac, char **av)
{
	int fd;
	int ret;
	char *buf;
	
	if (ac != 1)
	{
		fd = open(av[1], O_RDONLY);
	//	printf("|fd| = %d\n", fd);
	//	buff_size = line_size(fd);
	//	buf = (char *)malloc(sizeof(char) * buff_size);
	//	ret = read(fd, buf, buff_size);
		ret = get_next_line(fd, &buf);
		printf("%s\n", buf);
		ret = get_next_line(fd, &buf);
		printf("%s\n", buf);
	//	get_next_line(fd, av[1]);
		close(fd);
	}
}
