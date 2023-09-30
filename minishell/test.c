#include "minishell.h"

int main(void)
{
	printf("%d\n",access("usr/local/bin/",X_OK));
}