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
    aux = shell->env;
    //contar o número de tokens na lista
    while (aux)
    {
        aux = aux->next;
        i++;
    }
    //alocar memória para o array de strings
    shell->env_strs = (char **)malloc(sizeof(char *) * (i + 1));
    if (!shell->env_strs)
        return (1);
    //zerar contador;
    i = 0;
    //apontar aux de novo para head da lista
    aux = shell->env;
    //iterar pela lista com o número de tokens dando dup para
    // criar array de strings
    while (aux)
    {
        
        shell->env_strs[i] = ft_strdup(aux->str);
        aux = aux->next;
        i++;
    }
    printf("exiting ft_env_to_str\n");
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
    char    **cmd_full_paths;
    t_env   *aux;
    int i;
    printf("on ft_cmd_full_paths\n");

    i = 0;
    while (shell->env_strs[i])
    {
        i++;
    }
    paths = (char **)malloc(sizeof(char *) * (i));
    //aux aponta para head da lista de env
    aux = shell->env;
    //caminha pela lista
    while (aux)
    {
        //se encontrar a variável PATH
        if (ft_strncmp(aux->str, "PATH", 4) == 0)
        {
            printf("found PATH\n");
            //path recebe o valor da varqiável PATH
            path = ft_substr(aux->str, 5, ft_strlen(aux->str) - 5);
            //quebrar o path em um array de strings
            paths = ft_split(path, ':');
            //liberar a memória de path
            free(path);
            path = NULL;
            i = 0;
            //join com o comando;
            while(paths[i])
                i++;
            printf("number of paths = %i\n", i);
            //alocar memória para o array de strings
            cmd_full_paths = (char **)malloc(sizeof(char *) * (i));
            if (!cmd_full_paths)
                return (NULL);
            i = 0;
            while (paths[i])
            {
                cmd_full_paths[i] = ft_strjoin(paths[i], "/");
                free(paths[i]);
                paths[i] = ft_strdup(cmd_full_paths[i]);
                free(cmd_full_paths[i]);
                cmd_full_paths[i] = ft_strjoin(paths[i], shell->list->cmd[0]);
                printf("full path %i - %s\n", i, cmd_full_paths[i]);
                i++;
            }
            //retornar o array de strings
            return (cmd_full_paths);
        }
        aux = aux->next;
    }
    printf("fond NO PATH exiting ft_cmd_full_paths\n");
    return (NULL);
}

// função que procura pelo arquivo
//retorna o path funcional se existir
char    *ft_search_cmd_path(t_token *current, char **full_paths)
{
    char  *cmd;
    int         i;
    
    printf("on ft_search_cmd_path\n");
    // aqui preciso do comando que está no current token (verificar)
    // (shell->list->cmd[0]) é o comando no primeiro token
    cmd = current->cmd[0];
    
    //criar nova variável na struct t_token
    // char *full_cmd;

    printf("cmd = %s\n", cmd);

    // Verifica a existência do arquivo usando access()
    // e F_OK para checar se o arquivo existe
    i = 0;
    while (full_paths[i])
    {
        // Verifica se o arquivo existe
        if (access(full_paths[i], F_OK) == 0)
        {
            printf("found cmd %s\n", cmd);
            return (full_paths[i]);
        }
        printf("searching[%i] = %s\n", i, full_paths[i]);
        i++;
    }
    write(2, "exiting ft_search_cmd_path\n", 28);
    write(2, "comand not found\n", 18);
    //retorna erro
    return (NULL);
}

// função que executa o comando
int ft_execve(t_token *current)
{
    char *cmd;
    char **args;
    char **full_cdm_paths;

    printf("on ft_execve\n");

    ft_env_to_str(current->shell);
    full_cdm_paths = ft_cmd_full_paths(current->shell);
    cmd = ft_search_cmd_path(current, full_cdm_paths);
    args = current->cmd;
    printf("full cmd = %s\n", cmd);
    if (!cmd)
    {
        printf("command not found?\n");
        return (-1); // perror() imprime uma mensagem de erro padrão
    }
    else
        execve(cmd, args, current->shell->env_strs);
    // Se o execve tiver sucesso, o código abaixo não será impresso
    // Se houver um erro, o execve retornará -1
    
    return (0);
}



