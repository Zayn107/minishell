/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:16:32 by zkepes            #+#    #+#             */
/*   Updated: 2024/09/07 22:19:10 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_signal(int signum)
{
	(void) signum;

	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signal(void)
{
	struct sigaction sa;

	// Set up the structure to specify the new action.
	sa.sa_handler = handle_signal;
	sa.sa_flags = 0; // Or SA_RESTART

	// Block every signal during the handler
	sigemptyset(&sa.sa_mask);

	// Set up the signal handler for SIGINT
	if (sigaction(SIGINT, &sa, NULL) == -1) {
		perror("Error in sigaction");
		exit(EXIT_FAILURE);
	}

	// Infinite loop to keep the program running to test signal handling
	// int counter = 20;
	// while (counter--) {
	//     printf("Running...\n");
	//     sleep(2);
	// }
}
