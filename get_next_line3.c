/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:56:27 by hstander          #+#    #+#             */
/*   Updated: 2017/06/16 17:09:13 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./libft/libft.h"

#include <stdio.h>
int		fill_buf(const int fd, char **ptr)
{
	char buf[BUFF_SIZE + 1];
	int ret;
	char *newstr;

	ft_bzero(buf, BUFF_SIZE);
	ret = read(fd, buf, BUFF_SIZE);
	if (ret > 0)
	{
		newstr = ft_strjoin(*ptr, buf);
		free(*ptr);
		*ptr = newstr;
	}
	return (ret);
}

int     get_next_line(const int fd, char **line)
{
	static char *buf;
	char *endl_ptr;
	int ret;

	if (buf == NULL && (buf = (char *)malloc(sizeof(char))) == NULL)
		return (-1);
	endl_ptr = ft_strchr(buf, '\n');
	while (endl_ptr == NULL)
	{
		ret = fill_buf(fd, &buf);
		if (ret == 0)
		{
			if ((endl_ptr = ft_strchr(buf, '\0')) == buf)
				return (0);
		}
		else if (ret < 0)
			return (-1);
		else if ((endl_ptr = ft_strchr(buf, EOF)) == NULL)
		{
		//	printf("test\n");
			endl_ptr = ft_strchr(buf, '\n');
		}
	}
	if ((*line = ft_strsub(buf, 0, (endl_ptr - buf))) == NULL)
		return (-1);
	endl_ptr = ft_strdup(endl_ptr + 1);
	free(buf);
	buf = endl_ptr;
	return (1);
}
/*
int main(int ac, char **av)
{
	int fd;
	int ret;
	char *buf;
	//int fd2;
	//	char buf2[BUFF_SIZE +1];
	//	int ret2;

	//	ft_bzero(buf2, BUFF_SIZE);
	if (ac != 1)
	{
		fd = open(av[1], O_RDONLY);
		//	fd2 = open(av[2], O_RDONLY);

		//		ret2 = read(fd2, buf2, BUFF_SIZE);
		while ((ret = get_next_line(fd, &buf)) != 0)
		{
			printf("%s", buf);
			//			printf("ret val %d\n", ret);
			free(buf);
		}
		//		printf("%s\n", buf2);
		//		printf("ret val %d\n", ret2);
		//		ret = get_next_line(fd, &buf);
		//		printf("2nd return %s\n", buf);
		close(fd);
		//		close(fd2);
	}
}*/
