/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:03:06 by mealjnei          #+#    #+#             */
/*   Updated: 2023/01/11 21:16:09 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_old_env(char **env_pointer);
static char	**realloc_new_env(int env_num, char *arg, char **env_pointer);
static void	new_env(char *arg, char *key);
void		set_new_env(char *arg);
void		add_to_env(char *arg);

static void	free_old_env(char **env_pointer)
{
	int	i;

	i = 0;
	while (env_pointer[i])
	{
		free(env_pointer[i]);
		env_pointer[i] = NULL;
		i++;
	}
	free (env_pointer);
	env_pointer = NULL;
}

static char	**realloc_new_env(int env_num, char *arg, char **env_pointer)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (env_num + 2));
	if (!new_env)
		return (NULL);
	while (env_pointer[i])
	{
		new_env[i] = ft_strdup(env_pointer[i]);
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[env_num + 1] = 0;
	free_old_env(env_pointer);
	return (new_env);
}

static void	new_env(char *arg, char *key)
{
	int		i;
	char	*new_value;
	char	*tmp;

	i = find_env_ri(g_gm.env, key);
	if (i == -1)
	{
		i = 0;
		while (g_gm.env[i])
			i++;
		g_gm.env = realloc_new_env(i, arg, g_gm.env);
	}
	else
	{
		i = find_env_ri(g_gm.env, key);
		if (i == -1)
			return ;
		else
		{
			new_value = ft_strdup(arg);
			tmp = g_gm.env[i];
			g_gm.env[i] = new_value;
			free (tmp);
		}
	}
}

void	set_new_env(char *arg)
{
	int		index;
	int		i;

	index = 0;
	i = -1;
	if (arg == NULL)
		return ;
	while (arg[++i])
		if (arg[i] == '=')
			index = 1;
	index = ft_strlen2d(g_gm.env_v2);
	g_gm.env_v2 = realloc_new_env(index, arg, g_gm.env_v2);
}

void	add_to_env(char *arg)
{
	int		i;
	char	*key;

	if (arg == NULL)
		return ;
	i = char_index(arg, '=');
	if (i == -1)
		return ;
	key = ft_substr(arg, 0, i);
	new_env(arg, key);
	free (key);
}
