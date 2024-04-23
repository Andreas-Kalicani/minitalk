/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andreasgjertsenkalicani <andreasgjertse    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:48:59 by andreasgjer       #+#    #+#             */
/*   Updated: 2024/04/22 14:51:41 by andreasgjer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	send_signals(int pid, char *message)
{
	int				letter;
	int				i;

	letter = 0;
	while (message[letter])
	{
		i = -1;
		while (++i < 8)
		{
			if (((char)(message[letter] >> (7 - i)) & 1) == 0)
				kill(pid, SIGUSR1);
			else if (((char)(message[letter] >> (7 - i)) & 1) == 1)
				kill(pid, SIGUSR2);
			usleep(50);
		}
	letter++;
	}
	i = 0;
	while (i++ < 8)
	{
		kill(pid, SIGUSR1);
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	char				*message;
	int					server_id;

	if (argc == 3)
	{
		server_id = atoi(argv[1]);
		if (!server_id)
		{
			printf("[ERROR]. Wrong arg");
			return (0);
		}
		message = argv[2];
		if (message[0] == 0)
		{
			printf("Tu n'as envoyé aucun texte ! Ecris qqch pls :)");
			return (0);
		}
		send_signals(server_id, message);
	}
	else
	{
		printf("[ERROR]. Too much or too few arguments.\n Make sure ");
		printf("you enter arguments as follow: ./client <PID> <MESSAGE>");
	}
	return (0);
}
