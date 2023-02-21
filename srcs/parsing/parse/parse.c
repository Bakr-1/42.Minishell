/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:08:38 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/19 22:53:27 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_first_token(void);
void		main_parse(void);

/*
parsing the first token of input. The function starts by checking if
a global variable "g_gm.parse" is set, and if not it returns 0.
Then it sets the previous and next tokens for the global variable "g_gm.parse"
using the function "token_next()". If the next token is of type PIPEE,
it prints a syntax error message and sets the global variable "g_gm.status"
to 258, then it frees the memory allocated for "g_gm.parse" and sets it to NULL
If the next token is of type 8, it frees the memory allocated for
"g_gm.parse->s_r" and "g_gm.parse" and sets it to NULL.
If none of these conditions are met, the function returns 1.
*/
static int	parse_first_token(void)
{
	if (!g_gm.parse)
		return (0);
	g_gm.parse->prev_token = NULL;
	g_gm.parse->next_token = token_next();
	if (g_gm.parse->next_token->type == PIPEE)
	{
		print_nl("syntax error near unexpected token `|'\n", NULL);
		g_gm.status = 258;
		free_parse3(g_gm.parse);
		free(g_gm.parse);
		g_gm.parse = NULL;
		return (0);
	}
	if (g_gm.parse->next_token->type == 8)
	{
		free(g_gm.parse->s_r);
		g_gm.parse->s_r = NULL;
		free_parse3(g_gm.parse);
		free(g_gm.parse);
		g_gm.parse = NULL;
		return (0);
	}
	return (1);
}

/*
first we init the counter struct and set the global variable "g_gm.c" to it.
then we call the function "set_for_read()" to set g_gm.parse to read.
then we call the function "parse_first_token()" to parse the first token.
then we call the function "parse_next()" to parse the next tokens.
then we call the function "set_exec()" to set the global variable "g_gm.exec"
to parse any arguments.
then we call the function "executing()" to execute the commands.
*/
void	main_parse(void)
{
	g_gm.c = init_cc(g_gm.c);
	set_for_read();
	if (parse_first_token())
	{
		if (parse_next())
		{
			if (set_exec())
				executing();
			if (g_gm.pars2)
				free_pars2(g_gm.pars2);
		}
	}
}
