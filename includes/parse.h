/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 06:28:39 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/10 22:43:35 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

// parse.c
void		main_parse(void);

//parse_pipes_1.c
int			parse_next(void);

//parse_pipes_2.c
t_token		**token_realloc(t_arrcmd *cmd, int i);
t_arrcmd	**cmd_realloc1(t_arrcmd *cmd, int i);
char		*quoted_(char *str, int *i, t_parse *parse);
t_token		*verify_token(t_parse *parse, t_arrcmd *cmd);

//parse_args.c
int			set_exec(void);

// token.c
t_token		*token_next(void);
t_token		*create_token(t_parse *parse, int i);
t_token		*ret_tok(t_parse *parse, int i);

// token_string.c
t_token		*create_token_str(t_parse *parse);
char		*token_str(t_parse *parse, char *str);

// token_utils.c
char		*str_var(t_parse *parse);
int			check_lines(t_parse *parse, char c);
char		*token_env(t_parse *parse);

#endif