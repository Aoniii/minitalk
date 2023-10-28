/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:33:17 by snourry           #+#    #+#             */
/*   Updated: 2022/05/10 22:33:17 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_confirm;

static void	ft_send_byte(pid_t pid, int c, int byte)
{
	int	i;

	i = -1;
	while (++i < byte)
	{
		if (c & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c >>= 1;
		usleep(100);
	}
}

static void	ft_send(pid_t pid, char *str)
{
	int	i;

	i = -1;
	ft_send_byte(pid, ft_strlen(str), 32);
	ft_send_byte(pid, getpid(), 32);
	while (str[++i])
		ft_send_byte(pid, str[i], 8);
	ft_send_byte(pid, '\0', 8);
}

static void	ft_confirm(int signal)
{
	if (signal == SIGUSR1)
	{
		ft_putendl_fd("[\e[33mINFO\e[39m] message received !", 1);
		g_confirm = 0;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	g_confirm = 1;
	signal(SIGUSR1, ft_confirm);
	if (argc != 3)
	{
		ft_putendl_fd("[\e[31mERROR\e[39m] Usage: ./client <PID> <message>", 1);
		return (0);
	}
	pid = (pid_t)ft_atoi(argv[1]);
	if (kill(pid, SIGUSR1) == -1)
	{
		ft_putendl_fd("[\e[31mERROR\e[39m] Wrong PID !", 1);
		return (0);
	}
	usleep(100);
	ft_send(pid, argv[2]);
	while (g_confirm)
		pause();
	return (0);
}
