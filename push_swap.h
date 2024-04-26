/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:57:41 by bposa             #+#    #+#             */
/*   Updated: 2024/04/26 12:37:23 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h> //?
#include <stdarg.h> //?
#include <limits.h>
#include <stdio.h>

/* #define FAIL_MALLOC_TEST  // Define this macro to make malloc fail

void* custom_malloc(size_t size) {
    #ifdef FAIL_MALLOC_TEST
        return NULL;  // Simulate malloc failure
    #else
        return malloc(size);
    #endif
}

int main() {
    // Use custom_malloc instead of malloc in your code
    void* ptr = custom_malloc(sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        // Handle the failure appropriately
    } else {
        // Proceed with normal operations
    }
    return 0;
}
*/

struct s_stack
{
	char	name;	 // Arnold: change this from 'name' which sounds inconsequential into 'order' to clarify the ascending/descending property
	char	cmd[3]; // next command to be executed, if any
	char	is_top_heavier;
	int		maxsize; // DO I REALLY NEED THIS?  size (length) of the given input, stack_a.
	int		top;	 //(SIZE of the current array) indicates index of next insertion
	int		*array;	 // pointer to given input arrray
};

// int		ft_printf();
int		ft_atoi(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*my_memmove(int *dst, const int *src, size_t len);

size_t	my_strlcpy(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

int		initializer(int argc, char **argv, struct s_stack *stack_a, struct s_stack *stack_b);
int		swapper(struct s_stack *stack, ...); //passing char flag instead of int or using a variadic function is more optimal
int		swap_one(struct s_stack *stack, char do_i_print);
int		pusher(struct s_stack *from_stack, struct s_stack *into_stack);
int		rotator(char reverse, char which_stck, struct s_stack *a, struct s_stack *b);
int		rotate_one(char r_for_reverse, struct s_stack *stack, char do_i_print);
int		is_sorted(struct s_stack *stack);
int		find_min(struct s_stack *stack);
int		find_max(struct s_stack *stack);
int		find_midvalue(struct s_stack *stack);
int		sort_three(struct s_stack *stack, struct s_stack *other_stk);
int		sort_five(struct s_stack *a, struct s_stack *b);
char	top_half_weigher(struct s_stack *stack);
int		stack_breaker(struct s_stack *a, struct s_stack *b);
int		chunk_sorter(struct s_stack *a, struct s_stack *b);


#ifndef SUCCESS
# define SUCCESS 0
#endif

#ifndef ERROR
# define ERROR -1
#endif

#ifndef EMPTY
# define EMPTY -2
#endif

#endif