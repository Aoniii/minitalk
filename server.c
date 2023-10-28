/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:32:54 by snourry           #+#    #+#             */
/*   Updated: 2022/05/10 22:32:54 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_out	g_out;

static int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	else if (power == 0 && power == 0)
		return (1);
	else
		return (nb * ft_recursive_power(nb, power - 1));
}

static void	ft_reset(void)
{
	g_out.char_value = 0;
	g_out.byte = 0;
	g_out.len = 0;
	g_out.index = 0;
	g_out.connect = 0;
	if (g_out.str)
	{
		ft_putendl_fd(g_out.str, 1);
		free(g_out.str);
		g_out.str = NULL;
		kill((pid_t)g_out.client, SIGUSR1);
	}
	g_out.client = 0;
}

static void	ft_receive_strlen(int signal)
{
	if (signal == SIGUSR2 && g_out.byte < 32)
		g_out.len += ft_recursive_power(2, g_out.byte);
	else if (signal == SIGUSR2 && g_out.byte > 31)
		g_out.client += ft_recursive_power(2, (g_out.byte - 32));
	if (g_out.byte == 63)
	{
		g_out.str = ft_calloc(sizeof(char), (g_out.len + 1));
		g_out.len = 1;
		g_out.byte = 0;
		return ;
	}
	g_out.byte++;
}

static void	ft_receive(int signal)
{
	if (!g_out.connect)
		g_out.connect = 1;
	else if (!g_out.str)
		ft_receive_strlen(signal);
	else
	{
		if (signal == SIGUSR2)
			g_out.char_value += ft_recursive_power(2, g_out.byte);
		if (g_out.byte == 7)
		{
			g_out.str[g_out.index++] = g_out.char_value;
			g_out.byte = 0;
			if (g_out.char_value == 0)
				return (ft_reset());
			g_out.char_value = 0;
			return ;
		}
		g_out.byte++;
	}
}

int	main(void)
{
	ft_putstr_fd("[\e[33mINFO\e[39m] PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	signal(SIGUSR1, ft_receive);
	signal(SIGUSR2, ft_receive);
	g_out.str = NULL;
	ft_reset();
	while (1)
		usleep(100);
	return (0);
}
