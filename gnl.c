/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 08:41:35 by hstander          #+#    #+#             */
/*   Updated: 2017/06/16 15:55:45 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

int		readbuf(const int fd, char *ptr, int cntr, int *len)
{
	static char buf[BUFF_SIZE + 1];
	static int reti;
	static int ret;
	static int i;
//	static int eof;

	printf("ret %d ^^^ ", ret);
	printf("reti%d\n", reti);
	if (reti == 0)
	{
		printf("----\n");
		i = 0;
		ret = read(fd, buf, BUFF_SIZE);
//		if ((ret == 0 && cntr == 0) || (eof == 1))
//			return (0);
		if (ret == 0 || ret == -1)
			return (ret);
//			eof = 1;
		ptr[cntr] = buf[i];
		i++;
		*len += 1;
		reti = ret;
		reti--;
	}
	else 
	{
		printf("++++\n");
		ptr[cntr] = buf[i];
		i++;
		reti--;
		*len += 1;
	}
	printf("len %d\n", *len);
	return (1);
}

int		ft_realloc(char *ptr, int size)
{
	char *tmp;

	if ((tmp = (char *)malloc(sizeof(char) * ft_strlen(ptr) + size + 1)) == NULL)
		return (-1);
	ft_strcpy(tmp, ptr);
	free(ptr);
	ptr = tmp;
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	int i;
	int len;
	int ret;
	
	ret = 0;
	i = 0;
	len = 0;
	if ((*line = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)) == NULL)
		return (-1);
	ft_bzero(*line, BUFF_SIZE);
	while (1)
	{
		ret = readbuf(fd, *line, i, &len);
		if (ret == 0 || ret == -1)
			return (ret);
//		printf("**%d**\n", len);
		if (*(*line + i) == '\n' ||	*(*line + i) == EOF)
		{
			if (*(*line) + i == EOF)
				printf("EOF\n");
			printf("**%s\n", *line);
			printf("\\n\n");
			break ;
		}
		if (len == BUFF_SIZE)
		{
			len = 0;
//			printf("test\n");
			if (ft_realloc(*line, BUFF_SIZE) != 0)
				return (-1);
		}
		i++;
	}
 	*(*line + i) = '\0';
	return (ret > 0 ? 1 : 0);
}

int main(int ac, char **av)
{
	int fd;
	int ret;
	char *buf;
//	int fd2;
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
			printf("%s\n", buf);
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
}
