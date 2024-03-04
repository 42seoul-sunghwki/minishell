/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:51:56 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/04 15:50:48 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SIGNAL_H
# define SIGNAL_H

# include "../main.h"

void	set_signal_handler(void);
void	set_signal_dfl(void);
void	set_heredoc_parent();
void	set_sigint_ign(void);

#endif