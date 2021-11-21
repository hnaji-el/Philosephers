
#include "../includes/philo.h"

t_list	*get_new_node(t_args *args, int ph_id, pthread_mutex_t mutex)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->philo_id = ph_id;
	node->mutex = mutex;
	node->args = args;
	node->next = NULL;
	return (node);
}

int	lstadd_front(t_list **lst, t_args *args, int ph_id, pthread_mutex_t mutex)
{
	t_list	*node;

	node = get_new_node(args, ph_id, mutex);
	if (node == NULL)
		return (-1);
	if (*lst == NULL)
	{
		node->next = node;
		*lst = node;
		return (0);
	}
	node->next = (*lst)->next;
	(*lst)->next = node;
	return (0);
}

int	lstadd_back(t_list **lst, t_args *args, int ph_id, pthread_mutex_t mutex)
{
	t_list	*node;

	node = get_new_node(args, ph_id, mutex);
	if (node == NULL)
		return (-1);
	if (*lst == NULL)
	{
		node->next = node;
		*lst = node;
		return (0);
	}
	node->next = (*lst)->next;
	(*lst)->next = node;
	*lst = node;
	return (0);
}

void	lstclear_front(t_list **lst)
{
	t_list	*temp;

	if (*lst == NULL)
		return ;
	temp = (*lst)->next;
	(*lst)->next = temp->next;
	if (temp == *lst)
		*lst = NULL;
	pthread_mutex_destroy(&temp->mutex);
	free(temp);
}
