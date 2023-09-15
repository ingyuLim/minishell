#include "minishell.h"

int	syntax_check(t_list *head)
{
	t_list	*tmp = head;

	t_state	current_state = START;
	t_bool	paren_count = FALSE; // 괄호 쌍 개수를 추적하기 위한 변수
	t_bool	logical_operator_expected = FALSE; // 논리 연산자(&&, ||)가 기대되는지 여부를 추적하기 위한 변수

	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->token, "|", 2) == 0)
		{
			if (current_state != WORD)
			{
				printf("유효하지 않은 명령어입니다.\n");
				return (1);
			}
			current_state = PIPE;
			logical_operator_expected = 0;
		}
		else if (ft_strncmp(tmp->token, "<", 2) == 0)
		{
			if (current_state != WORD)
			{
				printf("유효하지 않은 명령어입니다.\n");
				return (1);
			}
			current_state = IN_REDIRECT;
			logical_operator_expected = 0;
		}
		else if (ft_strncmp(tmp->token, ">", 2) == 0)
		{
			if (current_state != WORD)
			{
				printf("유효하지 않은 명령어입니다.\n");
				return (1);
			}
			current_state = OUT_REDIRECT;
			logical_operator_expected = 0;
		}
		 else if (ft_strncmp(tmp->token, "<<", 3) == 0)
		 {
			if (current_state != WORD)
			{
				printf("유효하지 않은 명령어입니다.\n");
				return (1);
			}
			current_state = DOUBLE_IN_REDIRECT;
			logical_operator_expected = 0;
		}
		else if (ft_strncmp(tmp->token, ">>", 3) == 0)
		{
			if (current_state != WORD)
			{
				printf("유효하지 않은 명령어입니다.\n");
				return (1);
			}
			current_state = DOUBLE_OUT_REDIRECT;
			logical_operator_expected = 0;
		}
		else if (ft_strncmp(tmp->token, "(", 2) == 0)
		{
			if (logical_operator_expected)
			{
				printf("유효하지 않은 명령어입니다.\n");
				return (1);
			}
			current_state = OPEN_PAREN;
			paren_count++;
		}
		else if (ft_strncmp(tmp->token, ")", 2) == 0)
		{
			if (current_state != WORD)
			{
				printf("유효하지 않은 명령어입니다.\n");
				return (1);
			}
			current_state = CLOSE_PAREN;
			paren_count--;
		}
		else if (ft_strncmp(tmp->token, "&&", 3) == 0 || ft_strncmp(tmp->token, "||", 3) == 0)
		{
			if (!logical_operator_expected || current_state != WORD)
			{
				printf("유효하지 않은 명령어입니다.\n");
				return (1);
			}
			current_state = (ft_strncmp(tmp->token, "&&", 3) == 0) ? AND_OPERATOR : OR_OPERATOR;
			logical_operator_expected = 0;
		}
		else
		{
			if (logical_operator_expected)
			{
				printf("유효하지 않은 명령어입니다.\n");
				return (1);
			}
			current_state = WORD;
			logical_operator_expected = 1;
		}
		tmp = tmp->next;
	}

	if (paren_count != 0 || !logical_operator_expected) {
		printf("유효하지 않은 명령어입니다.\n");
		return (1);
	}

	printf("유효한 명령어입니다.\n");
	return (0);
}
