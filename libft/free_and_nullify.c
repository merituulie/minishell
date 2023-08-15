/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_nullify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:43:29 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/15 11:23:35 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_and_nullify(void *to_be_freed)
{
	free(to_be_freed);
	to_be_freed = NULL;
}
