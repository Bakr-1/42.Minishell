/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:08:16 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/13 11:55:34 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_nl(char *str, char *str1);
void		free_cmd_extras(t_arrcmd **cmd, int i);
t_arrcmd	*free_cmd(t_arrcmd *cmd, int i);
void		free_parse1(t_parse *parse);

void	print_nl(char *str, char *str1)
{
	if (str1)
		ft_fprintf(2, "%s %s\n", str, str1);
	else
		ft_fprintf(2, "%s\n", str);
	rl_on_new_line();
}

void	free_cmd_extras(t_arrcmd **cmd, int i)
{
	if ((*cmd)->p_type == TOK_S)
	{
		if ((*cmd)->tokens[i])
		{
			while (i < (*cmd)->t_size)
			{
				if ((*cmd)->tokens[i])
				{
					if ((*cmd)->tokens[i]->token)
						free((*cmd)->tokens[i]->token);
					(*cmd)->tokens[i]->token = NULL;
				}
				if ((*cmd)->tokens[i])
					free((*cmd)->tokens[i]);
				(*cmd)->tokens[i] = NULL;
				i++;
			}
			free((*cmd)->tokens);
			(*cmd)->tokens = NULL;
		}
	}
}

t_arrcmd	*free_cmd(t_arrcmd *cmd, int i)
{
	if (cmd == NULL)
		return (NULL);
	if (cmd->p_type == PIPEE_S)
	{
		while (i < cmd->p_size)
		{
			if (cmd->value[i])
				free_cmd(cmd->value[i], 0);
			cmd->value[i] = NULL;
			i++;
		}
		free(cmd->value);
		cmd->value = NULL;
	}
	free_cmd_extras(&cmd, 0);
	free(cmd);
	cmd = NULL;
	return (NULL);
}

void	free_parse1(t_parse *parse)
{
	if (!parse)
		return ;
	if (parse->s_r)
	{
		free(parse->s_r);
		parse->s_r = NULL;
	}
}
