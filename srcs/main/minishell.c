/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:08:29 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/19 22:50:16 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_gm	g_gm;
static int	parse_readline(void);
char		*print_prompt(void);
static void	reading_line(int i);
int			main(int ac, char **av, char **env);

static int	parse_readline(void)
{
	add_history(g_gm.s_r);
	if (g_gm.parse != NULL)
	{
		free(g_gm.parse);
		g_gm.parse = NULL;
	}
	g_gm.parse = calloc_minishell(1, sizeof(t_parse));
	init_parse();
	main_parse();
	return (0);
}

/*
we have a function called "print_prompt" that returns a string. it first checks
if the "PWD" and "HOME" variables are set in the environment. if they are not
set it returns the PROMPT string. if they are set it returns a string that
contains the current working directory and the user name. it also checks if the
last command was successful or not and changes the color of the prompt
accordingly.
*/
char	*print_prompt(void)
{
	char	*pro[5];

	pro[0] = find_in_env(g_gm.env, "PWD", 1);
	pro[1] = find_in_env(g_gm.env, "HOME", 1);
	pro[2] = find_in_env(g_gm.env, "USER", 1);
	if (g_gm.status == 0)
		pro[3] = BGBLKGRN" ✓"NC;
	else
		pro[3] = BGBLKRED" 𐄂"NC;
	if (pro[0] == NULL || pro[1] == NULL)
		return (free(pro[0]), free(pro[1]), free(pro[2]), ft_strdup(PROMPT));
	if (pro[2] == NULL)
		pro[2] = ft_strdup("MK~AB");
	pro[4] = strjoinvar(9, pro[3], BGBLK" ", pro[2], "@minishell"NC, \
	BGBLUEBLACK""NC, BGBLUEBLACK, "~", pro[0], NC BLUE""NC RESET);
	return (free(pro[0]), free(pro[1]), free(pro[2]), pro[4]);
}

/*
This is a function called "reading_line" that takes in an integer parameter "i"
just to save lines. It enters into an infinite loop and inside the loop 
it sets the "rl_catch_signals" variable to 0. It also sets the global 
variable "g_gm.fd_closed" to 3 to iindicate we are in parent
and then calls the "print_prompt" function to get
the prompt and assigns it to the global variable "g_gm.prompt". Then, it uses
the readline library function "readline" to read a line of input from 
the user and assigns it to the global variable "g_gm.s_r". 
The function then frees the memory allocated to "g_gm.prompt" 
and sets it to NULL.

If the value of "g_gm.s_r" is NULL, it means that the input stream is closed.
In this case, the function prints "exit" and calls the "free_global" function
to free any allocated memory, and then breaks out of the loop. If the value 
of "g_gm.s_r" is not NULL, the function uses the "parse_readline" function 
to parse the line of input, if it returns non-zero value, the function
immediately exits out of the infinite loop.

If the input line is not empty, it then checks the value of g_gm.s_r[i] if it 
is a space or not, if it is a space then it increments i and check again until
it finds a non-space character.

Overall, this function is used to read and process user input in a loop until 
the input stream is closed or the user enters a command that causes the loop 
to exit.
*/
static void	reading_line(int i)
{
	rl_outstream = stderr;
	while (1)
	{
		i = 0;
		rl_catch_signals = 0;
		g_gm.fd_closed = 3;
		g_gm.prompt = print_prompt();
		g_gm.s_r = readline(g_gm.prompt);
		free(g_gm.prompt);
		g_gm.prompt = NULL;
		if (!g_gm.s_r)
		{
			ft_fprintf(2, "exit\n");
			free_global();
			break ;
		}
		while (g_gm.s_r[i] && ft_isspace(g_gm.s_r[i]))
			i++;
		if (g_gm.s_r[i])
			if (parse_readline())
				return ;
	}
}

/*
first it calls the "init_global" function to initialize the global variables
and then it calls the "signals_hand" function to set up the signal handlers.
Then it calls the "reading_line" function to read and process user input.
After that, it calls the "rl_clear_history" function to clear the history
of the readline library. Then it checks if the global variable "g_gm.env" is
not NULL, if it is not NULL, it frees the memory allocated to it and sets it
to NULL. Then it checks if the global variable "g_gm.env_v2" is not NULL, if
it is not NULL, it frees the memory allocated to it and sets it to NULL.
Finally, it returns the value of the global variable "g_gm.status" 
for the next ./minishell if needed.
*/
int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1)
		return (ft_fprintf(2, "useage './minishell'"), EXIT_FAILURE);
	init_global(env);
	signals_hand();
	reading_line(420);
	rl_clear_history();
	if (g_gm.env)
	{
		ft_undo_alloc(g_gm.env);
		free(g_gm.env);
	}
	if (g_gm.env_v2)
	{
		ft_undo_alloc(g_gm.env_v2);
		free(g_gm.env_v2);
	}
	return (g_gm.status);
}
