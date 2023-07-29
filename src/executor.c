#include "../inc/minishell.h"

//escrever uma função que transforme a t_env em char **env
//para passar para o execve

int ft_env_to_str(t_shell *shell)
{
    //token auxiliar para andar na lista de env
    t_env *aux;
    //criar nova variável na struct t_shell?? ou na t_env???
    //char **env_strs; criada na t_env
    int i;
    
    printf("on ft_env_to_str\n");
    //aux aponta para head da lista de env
    if (!shell->env)
        write(2, "there's env!!!\n", 16);
    else
        write(2, "nao tem env aqui pq?\n", 22);
    printf("%s\n", shell->env->str);
    aux = shell->env;
    //contar o número de tokens na lista
    while (aux)
    {
        printf("%s", aux->str);
        aux = aux->next;
        i++;
    }
    printf("ft_env_to_str\n");
    //alocar memória para o array de strings
    shell->env->env_strs = (char **)malloc(sizeof(char *) * (i + 1));
    if (!shell->env->env_strs)
        return (1);
    printf("ft_env_to_str can malloc\n");

    //zerar contador;
    i = 0;
    //apontar aux de novo para head da lista
    aux = shell->env;
    //iterar pela lista com o número de tokens dando dup para
    // criar array de strings
    while (aux)
    {
        shell->env->env_strs[i] = ft_strdup(aux->str);
        aux = aux->next;
        i++;
    }
    return (0);
}

// a função access(); é permitida, ela procura por um arquivo
// em um diretório específico
// retorna 0 se o arquivo existir
// para usar precisa fornecer o caminho completo
// do arquivo para a função access().
// /home/Desktop/<filename>

// escrever uma função que pegue o caminho completo do arquivo
// pegar a nossa env, e usar a função ft_split(); no ":"
// retornar um array de strings com os paths
char    **ft_cmd_full_paths(t_shell *shell)
{
    char    *path;
    char    **paths;
    t_env   *aux;

    //aux aponta para head da lista de env
    aux = shell->env;
    //caminha pela lista
    while (aux)
    {
        //se encontrar a variável PATH
        if (ft_strcmp(aux->str, "PATH") == 0)
        {
            //path recebe o valor da variável PATH
            path = aux->str;
            //quebrar o path em um array de strings
            paths = ft_split(path, ':');
            //retornar o array de strings
            return (paths);
        }
        aux = aux->next;
    }
    return (NULL);
}

// função que procura pelo arquivo
//retorna o path funcional se existir
char    *ft_search_cmd_path(t_token *current, char **full_paths)
{
    char  *cmd;
    int         i;
    
    // aqui preciso do comando que está no current token (verificar)
    // (shell->list->cmd[0]) é o comando no primeiro token
    cmd = current->cmd[0];
    
    //criar nova variável na struct t_token
    // char *full_cmd;

    // Verifica a existência do arquivo usando access()
    // e F_OK para checar se o arquivo existe
    while (full_paths[i])
    {
        // Verifica se o arquivo existe
        if (access(cmd, F_OK) == 0) {
            return (full_paths[i]);
        }
        i++;
    }
    //retorna erro
    return (NULL);
}

// função que executa o comando
int ft_execve(t_token *current)
{
    ft_env_to_str(current->shell);
    char *cmd;
    char **args;

    cmd = ft_search_cmd_path(current, ft_cmd_full_paths(current->shell));
    args = current->cmd;
    
    printf("%s\n", cmd);
    //printf("%s\n", args[1]);
    printf("%s\n", current->shell->env->env_strs[0]);

    execve(cmd, args, current->shell->env->env_strs);

    // Se o execve tiver sucesso, o código abaixo não será impresso
    // Se houver um erro, o execve retornará -1
    
    printf("command not found?\n"); // perror() imprime uma mensagem de erro padrão

    return 0;
}



