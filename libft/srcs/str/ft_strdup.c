/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:04:33 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/02 14:24:55 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(char *src)
{
	char	*dst;

	dst = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strcpy(dst, src);
	return (dst);
}
