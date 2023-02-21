/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:58:39 by aalseri           #+#    #+#             */
/*   Updated: 2022/12/29 17:56:02 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl_extra(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		k;

	k = -1;
	i = -1;
	if (!s2)
		return (s1);
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen_gnl(s2) + ft_strlen_gnl(s1) + 1));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++k])
		str[i++] = s2[k];
	str[i] = '\0';
	ft_free_gnl(&s1);
	ft_free_gnl(&s2);
	return (str);
}

char	*get_str(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!*s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	str = malloc(i + 2);
	if (!str)
		return (NULL);
	while (*s && *s != '\n')
		str[j++] = *s++;
	if (*s == '\n')
		str[j++] = '\n';
	str[j] = '\0';
	return (str);
}

char	*get_read(int fd, char *s)
{
	char	*str;
	int		i;
	size_t	h;

	h = BUFFER_SIZE;
	str = malloc(h + 1);
	if (!str)
		return (NULL);
	i = 1;
	while (!ft_strnl(s) && i)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i == -1)
			return (ft_free_gnl(&str));
		str[i] = '\0';
		s = ft_strjoin_gnl(s, str);
	}
	ft_free_gnl(&str);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*s[2048];

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	s[fd] = get_read(fd, s[fd]);
	if (!s[fd])
		return (NULL);
	str = get_str(s[fd]);
	s[fd] = stringdup(s[fd]);
	return (str);
}

// int main()
// {
// 	int		fd;
// 	char *line;

// 	fd = open("cat.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	// line = get_next_line(fd);
// 	// printf("%s", line);
// }
