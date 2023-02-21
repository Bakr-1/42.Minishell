/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_text.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:16:30 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/13 16:52:54 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_TEXT_H
# define C_TEXT_H

# define CYN   "\x1B[36m"

# define BGBLKGRN "\x1b[40m\x1b[32m"
# define BGBLK "\x1b[40m"
# define BGBLUE "\x1b[44m"
# define BGBLUEBLACK "\x1b[44m\x1b[30m"
# define BGBLKGRN "\x1b[40m\x1b[32m"
# define BGBLKRED "\x1b[40m\x1b[31m"
# define BLACK "\x1b[30m"
# define GRN "\x1b[32m"
# define NC "\033[0m"

# define RED			"\033[0;31m"
# define BLUE			"\033[0;34m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define PURPLE			"\033[0;35m"
# define LIGHT_BLUE		"\033[0;36m"
# define RESET			"\x1B[0m"

# define RED1			"\033[1;31m"
# define BLUE1			"\033[1;34m"
# define GREEN1			"\033[1;32m"
# define YELLOW1		"\033[1;33m"
# define PURPLE1		"\033[1;35m"
# define LIGHT_BLUE1	"\033[1;36m"

# define RED2			"\033[2;31m"
# define BLUE2			"\033[2;34m"
# define GREEN2			"\033[2;32m"
# define YELLOW2		"\033[2;33m"
# define PURPLE2		"\033[2;35m"
# define LIGHT_BLUE2	"\033[2;36m"

# define RED3			"\033[3;31m"
# define BLUE3			"\033[3;34m"
# define GREEN3			"\033[3;32m"
# define YELLOW3		"\033[3;33m"
# define PURPLE3		"\033[3;35m"
# define LIGHT_BLUE3	"\033[3;36m"

# define RED4			"\033[4;31m"
# define BLUE4			"\033[4;34m"
# define GREEN4			"\033[4;32m"
# define YELLOW4		"\033[4;33m"
# define PURPLE4		"\033[4;35m"
# define LIGHT_BLUE4	"\033[4;36m"

# define RED5			"\033[5;31m"
# define BLUE5			"\033[5;34m"
# define GREEN5			"\033[5;32m"
# define YELLOW5		"\033[5;33m"
# define PURPLE5		"\033[5;35m"
# define LIGHT_BLUE5	"\033[5;36m"

# define RED6			"\033[6;31m"
# define BLUE6			"\033[6;34m"
# define GREEN6			"\033[6;32m"
# define YELLOW6		"\033[6;33m"
# define PURPLE6		"\033[6;35m"
# define LIGHT_BLUE6	"\033[6;36m"

# define RED7			"\033[7;31m"
# define BLUE7			"\033[7;34m"
# define GREEN7			"\033[7;32m"
# define YELLOW7		"\033[7;33m"
# define PURPLE7		"\033[7;35m"
# define LIGHT_BLUE7	"\033[7;36m"

int		ft_isalnum(int i);

#endif