/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:05:00 by mealjnei          #+#    #+#             */
/*   Updated: 2023/01/15 11:54:46 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	modify_env(char *arg, char *key);
static void	set_or_modify(char *arg);
static int	is_valid_env_key(char *arg);
void		bing_bong_in_env(char *arg);
void		ft_export(char **tokens);

static void	modify_env(char *arg, char *key)
{
	int		i;
	char	*new_value;
	char	*tmp;

	i = find_env_ri(g_gm.env_v2, key);
	if (i == -1)
		return ;
	else
	{
		new_value = ft_strdup(arg);
		tmp = g_gm.env_v2[i];
		g_gm.env_v2[i] = new_value;
		free (tmp);
	}
}

static void	set_or_modify(char *arg)
{
	int		is_set;
	int		i;
	char	*key;
	int		just_key;

	just_key = 0;
	if (arg == NULL)
		return ;
	i = char_index(arg, '=');
	if (i == -1)
	{
		just_key = 1;
		i = ft_strlen(arg);
	}
	key = ft_substr(arg, 0, i);
	is_set = find_env_ri(g_gm.env_v2, key);
	if (is_set == -1)
		set_new_env(arg);
	else
	{
		if (!just_key)
			modify_env(arg, key);
	}
	free (key);
}

static int	is_valid_env_key(char *arg)
{
	int	i;
	int	alpha;

	i = 0;
	alpha = 0;
	if (!ft_strcmp(arg, ""))
		return (0);
	if (arg == NULL || arg[0] == '=')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalpha(arg[i]))
			alpha = 1;
		else
		{
			if (ft_isdigit(arg[i]) && !alpha)
				return (0);
			else if (!ft_isdigit(arg[i]) && arg[i] != '_')
				return (0);
		}
		i++;
	}
	return (1);
}

void	bing_bong_in_env(char *arg)
{
	set_or_modify(arg);
	add_to_env(arg);
}

void	ft_export(char **tokens)
{
	int	i;

	i = 0;
	g_gm.status = 0;
	if (tokens[1] == NULL)
		return (ft_sort_print_env());
	while (tokens[i++])
	{
		if (tokens[i] && is_valid_env_key(tokens[i]) == 0)
		{
			ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n" \
				, tokens[i]);
			g_gm.status = 1;
			continue ;
		}
		bing_bong_in_env(tokens[i]);
	}
}
