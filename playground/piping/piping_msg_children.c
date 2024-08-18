/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_msg_children.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:53:55 by zkepes            #+#    #+#             */
/*   Updated: 2024/04/24 12:50:04 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_CHILDREN 3

int main() {
	int pipes[NUM_CHILDREN][2]; // Array to hold pipes for communication with children
	int i;

	// Create pipes
	i = 0;
	while (i < NUM_CHILDREN)
	{
		if (pipe(pipes[i]) == -1)
		{
		perror("pipe");
		exit(EXIT_FAILURE);
		}
		i++;
	}

	// Fork children
	i =0;
	while (i < NUM_CHILDREN)
	{
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{ // Child process
			// close(pipes[i][0]); // Close unused read end
			// Perform child-specific tasks here
			// Write to the pipe
			// char message[] = "Hello from child process";
			char buffer[100];
			if (i == 0)
			{
				buffer[0] = 'f';
				buffer[1] = 'i';
			}
			else
			{
				read(pipes[i][0], buffer, sizeof(buffer));
			}
			write(pipes[i][1], buffer, sizeof(buffer));

			close(pipes[i][1]); // Close write end after writing
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	// Parent process
	i = 0;
	while (i < NUM_CHILDREN)
	{
		close(pipes[i][1]); // Close write end of pipe
		// Read from the pipe
		char buffer[100];
		read(pipes[i][0], buffer, sizeof(buffer));
		printf("Parent received from child %d: %s\n", i, buffer);
		close(pipes[i][0]); // Close read end after reading
		i++;
	}
	// Wait for all children to terminate (could be swapped with the previous loop)
	i = 0;
	while (i < NUM_CHILDREN)
	{
		wait(NULL);
		i++;
	}
	return 0;
}
