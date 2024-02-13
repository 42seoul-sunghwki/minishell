/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:01:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/13 11:36:54 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

long	find_quot(char *input, int is_double)
{
	long	index;
	char	c;

	index = 0;
	if (is_double == FALSE)
		c = SINGLEQUOT[0];
	else
		c = DOUBLEQUOT[0];
	while (input[index])
	{
		if (!str_cmp(&input[index], &c))
			break ;
		index++;
	}
	return (index);
}

long	find_end_quote(char *input)
{
	long	index;
	char	c;

	index = 0;
	while (input[index])
	{
		if (!str_cmp(&input[index], DOUBLEQUOT)
			|| !str_cmp(&input[index], SINGLEQUOT))
		{
			c = input[index];
			while (input[++index])
			{
				if (!str_cmp(&input[index], &c))
					break ;
			}
		}
	}
	return (index);
}

long	find_bracket(char *input)
{
	long	index;
	char	c;

	index = 0;
	while (input[index])
	{
		index = find_end_quote(input);
		if (!input[index])
			return (index);
		if (!str_cmp(&input[index], &BRACKET[0])
			|| !str_cmp(&input[index], &BRACKET[1]))
			break ;
		if (!input[index])
			break ;
		index++;
	}
	return (index);
}

long	find_pipe(char *input)
{
	long	index;
	char	c;

	index = 0;
	while (input[index])
	{
		index = find_end_quote(input);
		if (!input[index])
			return (index);
		if (!str_cmp(&input[index], PIPE)
			&& str_cmp(&input[index], OR))
			break ;
		if (!input[index])
			break ;
		index++;
	}
	return (index);
}

long	find_or_and_bracket(char *input)
{
	long	index;
	char	c;

	index = 0;
	while (input[index])
	{
		index = find_end_quote(input);
		if (!input[index])
			return (index);
		if (!str_cmp(&input[index], OR))
			return (index);
		if (!str_cmp(&input[index], AND))
			return (index);
		if (!str_cmp(&input[index], &BRACKET[0])
			|| !str_cmp(&input[index], &BRACKET[1]))
			return (index);
		if (!input[index])
			break ;
		index++;
	}
	return (index);
}

long	find_redirect(char *input)
{
	long	index;
	char	c;

	index = 0;
	while (input[index])
	{
		index = find_end_quote(input);
		if (!input[index])
			return (index);
		 
		index++;
	}
	return (index);
}
