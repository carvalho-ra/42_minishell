#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];  // Array para os descritores do pipe
    char message[] = "Hello, child process!";  // Mensagem a ser enviada pelo pai

    // Cria o pipe
    if (pipe(fd) == -1) {
        perror("Erro ao criar o pipe");
        return 1;
    }

    // Cria um novo processo
    pid_t pid = fork();
    printf("%i", pid);
    if (pid == -1) {
        perror("Erro ao criar o processo");
        return 1;
    }

    if (pid == 0) {
        // Processo filho
        close(fd[1]);  // Fecha a extremidade de escrita do pipe

        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));  // Lê a mensagem do pipe
        printf("Mensagem recebida pelo filho: %s\n", buffer);

        close(fd[0]);  // Fecha a extremidade de leitura do pipe
    } else {
        printf("%i", pid);
        // Processo pai
        close(fd[0]);  // Fecha a extremidade de leitura do pipe

        write(fd[1], message, sizeof(message));  // Escreve a mensagem no pipe

        close(fd[1]);  // Fecha a extremidade de escrita do pipe
    }

    return 0;
}
