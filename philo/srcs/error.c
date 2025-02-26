/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfradj <yfradj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:26:52 by yfradj            #+#    #+#             */
/*   Updated: 2025/02/20 17:14:36 by yfradj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	handle_error_limit(int ac, char **av)
{
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200)
		return (1);
	if (ft_atoi(av[2]) < 0 || ft_atoi(av[2]) > INT_MAX)
		return (1);
	if (ft_atoi(av[3]) < 0 || ft_atoi(av[3]) > INT_MAX)
		return (1);
	if (ft_atoi(av[4]) < 0 || ft_atoi(av[4]) > INT_MAX)
		return (1);
	if (ac == 6)
	{
		if (ft_atoi(av[5]) < 0
			|| ft_atoi(av[5]) > INT_MAX)
			return (1);
	}
	return (0);
}

int	check_is_int(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	handle_error(int ac, char **av)
{
	if (check_is_int(av[1]) == 1)
		return (1);
	if (check_is_int(av[2]) == 1)
		return (1);
	if (check_is_int(av[3]) == 1)
		return (1);
	if (check_is_int(av[4]) == 1)
		return (1);
	if (ac == 6)
	{
		if (check_is_int(av[5]) == 1)
			return (1);
	}
	return (0);
}

int	check_arg(int ac, char **av)
{
	if (handle_error(ac, av) == 1)
	{
		printf("Bad argument\n");
		return (1);
	}
	if (handle_error_limit(ac, av) == 1)
	{
		printf("Bad argument\n");
		return (1);
	}
	return (0);
}
