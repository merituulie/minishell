/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_null_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:09:31 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/03 16:11:27 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*free the str & null terminates the entire str and return it*/
char	*ft_free_null_str(char *str)
{
	free(str);
	str = NULL;
	return (str);
}
