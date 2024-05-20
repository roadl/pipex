/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 10:06:00 by yojin             #+#    #+#             */
/*   Updated: 2023/11/25 13:19:53 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

# include "./libft/libft.h"

int		ft_printf(const char *s, ...);
int		ft_puthex(unsigned int hex, int is_upper);
int		ft_putptr(unsigned long long hex);
int		ft_putunbr(unsigned int i);
int		ft_putstr(const char *s);

char	hex_to_char(int hex, int is_upper);

#endif