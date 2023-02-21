/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:32:00 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/15 12:19:27 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pwd(void);
static void	ft_env(void);
int			check_builtin(char **tokens);
int			exec_builtin(t_exec *exec, char **tokens);

static void	ft_pwd(void)
{
	char	*pwd;

	g_gm.status = 0;
	pwd = find_in_env(g_gm.env, "PWD", 1);
	if (!pwd)
	{
		pwd = getcwd(NULL, 1024);
		ft_fprintf(1, "%s\n", pwd);
		free(pwd);
		return ;
	}
	ft_fprintf(1, "%s\n", pwd);
	free(pwd);
}

static void	ft_env(void)
{
	int	i;

	i = 0;
	g_gm.status = 0;
	while (g_gm.env[i])
		ft_printf("%s\n", g_gm.env[i++]);
}

int	check_builtin(char **tokens)
{
	if (tokens && tokens[0])
	{
		if (ft_strcmp(tokens[0], "echo") == 0)
			return (1);
		else if (ft_strcmp(tokens[0], "cd") == 0)
			return (1);
		else if (ft_strcmp(tokens[0], "pwd") == 0)
			return (1);
		else if (ft_strcmp(tokens[0], "export") == 0)
			return (1);
		else if (ft_strcmp(tokens[0], "unset") == 0)
			return (1);
		else if (ft_strcmp(tokens[0], "env") == 0)
			return (1);
		else if (ft_strcmp(tokens[0], "exit") == 0)
			return (1);
	}
	return (0);
}

int	exec_builtin(t_exec *exec, char **tokens)
{
	if (exec->error)
		return (0);
	if (!tokens || !tokens[0])
		return (0);
	if (!ft_strcmp(tokens[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(tokens[0], "env"))
		ft_env();
	else if (!ft_strcmp(tokens[0], "echo"))
		ft_echo(tokens);
	else if (!ft_strcmp(tokens[0], "exit"))
		ft_exit(tokens);
	else if (!ft_strcmp(tokens[0], "export"))
		ft_export(tokens);
	else if (!ft_strcmp(tokens[0], "cd"))
		ft_cd(tokens);
	else if (!ft_strcmp(tokens[0], "export"))
		ft_export(tokens);
	else if (!ft_strcmp(tokens[0], "unset"))
		ft_unset(tokens);
	else
		return (0);
	return (1);
}
