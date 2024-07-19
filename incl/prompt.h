/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:20:09 by irsander          #+#    #+#             */
/*   Updated: 2024/07/12 15:14:06 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

//Colors:
#define	RED		"\x1b[31m"
#define GREEN	"\x1b[32m"
#define YELLOW	"\x1b[33m"
#define BLUE	"\x1b[34m"
#define MAGENTA	"\x1b[35m"
#define CYAN	"\x1b[36m"
#define RESET	"\x1b[0m"

//Colored prompt:
#define PROMPT RED "✿ M" GREEN "i" YELLOW "n" BLUE"i" MAGENTA"s" \
		CYAN"h" RED"e" GREEN "l" YELLOW "l ✿" BLUE " >" RESET " "

// //Basic prompt:
// # define PROMPT "Minishell> "

#endif