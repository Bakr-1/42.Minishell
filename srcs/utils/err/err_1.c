/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mealjnei <mealjnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:53:07 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/12 18:06:33 by mealjnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parse2(t_parse *parse);
void	free_parse3(t_parse *parse);
void	free_pars2_extra(t_pa *pars2, int *i, int *j);
void	free_pars2(t_pa *pars2);

void	free_parse2(t_parse *parse)
{
	if (!parse)
		return ;
	if (parse->next_token)
	{
		if (parse->next_token->token)
		{
			free(parse->next_token->token);
			parse->next_token->token = NULL;
		}
		free(parse->next_token);
		parse->next_token = NULL;
	}
	if (parse->s_r)
	{
		free(parse->s_r);
		parse->s_r = NULL;
	}
}

void	free_parse3(t_parse *parse)
{
	if (parse == NULL)
		return ;
	if (parse->next_token)
	{
		if (parse->next_token->token)
		{
			free(parse->next_token->token);
			parse->next_token->token = NULL;
		}
		free(parse->next_token);
		parse->next_token = NULL;
	}
	if (parse->prev_token)
	{
		if (parse->prev_token->token)
			free(parse->prev_token->token);
		parse->prev_token->token = NULL;
		free(parse->prev_token);
		parse->prev_token = NULL;
	}
	if (parse->s_r)
		free(parse->s_r);
	parse->s_r = NULL;
}

void	free_pars2_extra(t_pa *pars2, int *i, int *j)
{
	if (pars2[*i].tokens)
	{
		while (++(*j) < pars2[*i].tokens_size)
		{
			if (pars2[*i].tokens[*j])
				free(pars2[*i].tokens[*j]);
			pars2[*i].tokens[*j] = NULL;
		}
		free(pars2[*i].tokens);
		pars2[*i].tokens = NULL;
	}
	*j = -1;
	if (pars2[*i].redirec)
	{
		while (++(*j) < pars2[*i].n_redirec)
		{
			if (pars2[*i].redirec[*j].file)
			{
				free(pars2[*i].redirec[*j].file);
				pars2[*i].redirec[*j].file = NULL;
			}
		}
		free(pars2[*i].redirec);
		pars2[*i].redirec = NULL;
	}
}

void	free_pars2(t_pa *pars2)
{
	int	i;
	int	j;

	i = -1;
	if (pars2 == NULL)
		return ;
	while (++i < pars2->n_cmds)
	{
		j = -1;
		free_pars2_extra(pars2, &i, &j);
	}
	free(pars2);
	pars2 = NULL;
}
