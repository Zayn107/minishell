#include "../include/minishell.h"

void	signals_to_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sigint_handler(int sig)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	(void) sig;
}

void	init_signals(void)
{
	t_sigaction	act;
	t_sigaction	ign;

	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	act.sa_handler = &sigint_handler;
	ign.sa_flags = SA_RESTART;
	sigemptyset(&ign.sa_mask);
	ign.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &act, NULL) != 0)
		exit(EXIT_FAILURE);
	if (sigaction(SIGQUIT, &ign, NULL) != 0)
		exit(EXIT_FAILURE);
}

/*
rl_replace_line clears the input buffer,
discarding any previous input and clearing the undo list.
rl_on_new_line notifies Readline that the cursor is on a new line, 
typically used to ensure proper display of the prompt for new input.
rl_redisplay requests the GNU Readline library 
to redisplay the current input line.
This is necessary after modifying the line (such as clearing it)
to ensure that the changes are reflected on the terminal.
*/