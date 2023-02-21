/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:04:47 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/02 16:28:55 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	str = (char *)malloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (!str)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strjoinee(char *s1, char *s2, int f_s1, int f_s2)
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
	if (f_s1)
		ft_free_gnl(&s1);
	if (f_s2)
		ft_free_gnl(&s2);
	return (str);
}

char	*strjoinvar(size_t size, ...)
{
	va_list		ap;
	char		*str[3];
	size_t		i;

	i = 0;
	va_start(ap, size);
	str[1] = va_arg(ap, char *);
	str[2] = va_arg(ap, char *);
	str[0] = ft_strjoin(str[1], str[2]);
	size -= 2;
	while (i < size)
	{
		str[1] = va_arg(ap, char *);
		str[0] = ft_strjoinee(str[0], str[1], 1, 0);
		i++;
	}
	va_end(ap);
	return (str[0]);
}

/*
modified version of ft_strjoin() to join a character to a string
*/
char	*ft_scjoin(char *s1, char c)
{
	char	*str;
	int		i;

	if (!s1)
	{
		s1 = malloc(1);
		*s1 = '\0';
	}
	str = malloc(ft_strlen(s1) + 2);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	str[i] = c;
	str[i + 1] = '\0';
	free(s1);
	return (str);
}
