/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:44:02 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/03 21:09:08 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	ft_atol(const char *str, long *ret)
{
	int		sign;
	long	num;

	num = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		num *= 10;
		num += *str - '0';
		str++;
	}
	if (num * -1 == num || num % 10 != *(str - 1) - '0')
		return (NOTDEFINED);
	*ret = num * sign;
	return (0);
}

static int	exit_arg_check(t_cmd_node *cmd_node, t_minishell *minishell)
{
	int		index;
	long	ret;
	t_error	*err;

	index = 0;
	ret = 0;
	err = set_error_msg(minishell->execute_name, cmd_node->str[0],
			cmd_node->str[1], "numeric argument required");
	if (cmd_node->str[1][index] == '+' || cmd_node->str[1][index] == '-')
		index++;
	while (cmd_node->str[1][index])
	{
		if (!ft_isdigit(cmd_node->str[1][index]))
			return (print_error_msg(err, 255, 0));
		index++;
	}
	if (ft_atol(cmd_node->str[1], &ret) == NOTDEFINED)
		return (print_error_msg(err, 255, 0));
	return (ret);
}

int	ft_exit(t_cmd_node *cmd_node, t_minishell *minishell)
{
	t_error	*err;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!cmd_node->str[1])
		exit(0);
	if (cmd_node->str[2])
	{
		err = set_error_msg(minishell->execute_name, cmd_node->str[0],
				NULL, "too many arguments");
		return (print_error_msg(err, 1, 0));
	}
	minishell->exit_code = exit_arg_check(cmd_node, minishell);
	free_t_minishell(minishell);
	exit(minishell->exit_code);
}
