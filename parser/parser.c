/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:52:54 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/06 13:28:06 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../main.h"



t_ast_node	*parser(char *input)
{
	t_ast_node	*list;
	
	list = init_parse(input);
	//split with space
	
	//splitting
	//merge
}
