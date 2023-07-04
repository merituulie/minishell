/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:42:15 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/04 17:43:55 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsing.h"
#include "../../libft/libft.h"

/*initialize the quotes count to zero*/
void	quotes_init(t_data *ms)
{
	ms->s_quotes = 0;
	ms->d_quotes = 0;
}
