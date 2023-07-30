/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:00:03 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/26 10:21:41 by rmakinen         ###   ########.fr       */
=======
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:00:03 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/26 14:53:36 by jhusso           ###   ########.fr       */
>>>>>>> fb3df867e9c62376efe02f65e689733506e38162
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\t %p\n", str[i], &(str[i]));
		i++;
	}
	return (0);
}
