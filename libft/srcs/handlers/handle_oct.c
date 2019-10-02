/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juochen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 19:00:40 by juochen           #+#    #+#             */
/*   Updated: 2018/04/17 22:45:17 by juochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		handle_oct(va_list args, t_arg *modi)
{
	uintmax_t	value;
	char		*res;
	int			ret_len;

	value = va_arg(args, uintmax_t);
	value = get_unsigned_length(modi, value);
	res = ft_itoa_base_uint_upper(value, 8);
	if (res[0] == '0' && res[1] == '\0' &&
		modi->got_precision && modi->precision_value == 0 &&
		modi->flag_hash != 1)
		res[0] = '\0';
	ret_len = print_all_int(modi, res);
	free(res);
	return (ret_len);
}
