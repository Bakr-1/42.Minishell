/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:45:50 by mealjnei          #+#    #+#             */
/*   Updated: 2023/01/13 21:24:07 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	**realloc_dp(void **ptr, size_t size, size_t count);
static char	**del_env2_var(ssize_t element);
static char	**del_env_var(ssize_t element);
static void	norm_unset(char *token);
void		ft_unset(char **token);

static void	**realloc_dp(void **ptr, size_t size, size_t count)
{
	void	**new_ptr;
	size_t	i;

	i = 0;
	new_ptr = ft_calloc(sizeof(count), size + 1);
	if (!new_ptr)
		return (NULL);
	while ((i < size) && ptr[i])
	{
		new_ptr[i] = ft_strdup(ptr[i]);
		i++;
	}
	new_ptr[i] = 0;
	ft_undo_alloc((void *)ptr);
	free(ptr);
	ptr = NULL;
	return (new_ptr);
}

static char	**del_env2_var(ssize_t element)
{
	char	*new_env;
	size_t	len;
	size_t	i;

	i = element;
	len = ft_strlen2d(g_gm.env_v2);
	while (g_gm.env_v2[i + 1])
	{
		new_env = ft_strdup(g_gm.env_v2[i + 1]);
		free(g_gm.env_v2[i]);
		g_gm.env_v2[i] = new_env;
		i++;
	}
	g_gm.env_v2 = (char **)realloc_dp((void *)g_gm.env_v2, len - 1, \
		sizeof(char *));
	return (g_gm.env_v2);
}

static char	**del_env_var(ssize_t element)
{
	char	*new_env;
	size_t	len;
	size_t	i;

	i = element;
	len = ft_strlen2d(g_gm.env);
	while (g_gm.env[i + 1])
	{
		new_env = ft_strdup(g_gm.env[i + 1]);
		free(g_gm.env[i]);
		g_gm.env[i] = new_env;
		i++;
	}
	g_gm.env = (char **)realloc_dp((void *)g_gm.env, len - 1, sizeof(char *));
	return (g_gm.env);
}

static void	norm_unset(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (env_check(token[i]))
		{
			g_gm.status = 1;
			return (ft_printf("minishell: unset: `%s'", token), \
				ft_printf(": not a valid identifier\n"), (void)0);
		}
		i++;
	}
	return ((void)0);
}

void	ft_unset(char **token)
{
	size_t	i;
	ssize_t	index_1;
	ssize_t	index_2;

	g_gm.status = 0;
	i = 0;
	if (!token[1])
		return ;
	while (token[++i])
	{
		index_1 = find_env_ri(g_gm.env, token[i]);
		index_2 = find_env_ri(g_gm.env_v2, token[i]);
		if (index_1 != -1)
		{
			if (g_gm.env[index_1])
				del_env_var(index_1);
		}
		if (index_2 != -1)
		{
			if (g_gm.env_v2[index_2])
				del_env2_var(index_2);
		}
		else
			return (norm_unset(token[i]));
	}
}
