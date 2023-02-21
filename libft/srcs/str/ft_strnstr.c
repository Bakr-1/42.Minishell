/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:05:37 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/15 01:39:36 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	if (s1 == s2 || !*s2)
		return ((char *)s1);
	i = 0;
	while (s1[i] && i < n)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while ((s1[i + j] == s2[j]) && (i + j) < n)
			{
				j++;
				if (s2[j] == '\0')
					return ((char *)s1 + i);
			}
		}
		i++;
	}
	return (0);
}
/*
char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
    size_t	len2;

    if (*s2 == '\0')
        return ((char *)s1);
    len2 = ft_strlen(s2);
    while (*s1 != '\0' && n-- >= len2)
    {
        if (*s1 == *s2 && ft_memcmp(s1, s2, len2) == 0)
            return ((char *)s1);
        s1++;
    }
    return (NULL);
}

int main(void)
{
	char haystack[30] = "aaabcabcd";
	char needle[10] = "aabc";
	char * empty = (char*)"";
	printf("%s",ft_strnstr(haystack, "abcd", 9));
	write(1, "\n", 1);
	return (0);
}
*/
