/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snourry <snourry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:20:52 by snourry           #+#    #+#             */
/*   Updated: 2022/05/10 22:20:52 by snourry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "libft/libft.h"

int	ft_printf(const char *format, ...);

typedef struct s_out
{
	char	*str;
	int		byte;
	int		client;
	int		char_value;
	int		index;
	int		len;
	int		connect;
}				t_out;

#endif