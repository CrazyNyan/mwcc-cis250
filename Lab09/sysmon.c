#include <stdio.h>      // fclose(), fgets(), fopen(), perror(), printf()
#include <stdlib.h>     // exit()
#include <string.h>     // strlen()
#include <sys/wait.h>   // waitpid()
#include <unistd.h>     // close(), fork(), pipe(), read(), sleep(), write()

#define BUFFER_SIZE 1024
#define INTERVAL 5

int main(void)
{
  // File Descriptors
  int cpu_pipe[2];

  char cpu_buffer[BUFFER_SIZE];

  // CPU Pipe
  if (pipe(cpu_pipe) == -1)
  {
    perror("pipe");
    return -1;
  }

  // Create Child Process.
  pid_t cpu_pid = fork();

  if (cpu_pid == 0)
  {
 
    // CPU MONITOR PROCESS

    // Close Read-End of CPU Pipe.
    close(cpu_pipe[0]);

    // Buffer for Reading CPU Info.
    char buffer[BUFFER_SIZE];

    while(1)
    {
      FILE *file = fopen("/proc/loadavg", "r");

      if (file != NULL)
      {
        if (fgets(buffer, sizeof(buffer), file) != NULL)
        {
          // Send the CPU Info Through the Pipe.
          write(cpu_pipe[1], buffer, strlen(buffer) + 1);

          // Close the CPU file.
          fclose(file);
        }
      }

      sleep(INTERVAL);
    }

    // Close the Write-End of the CPU Pipe.
    close(cpu_pipe[1]);

    exit(0);
  }
  else
  {
    // PARENT PROCESS

    // Close the Write-End of the CPU Pipe.
    close(cpu_pipe[1]);

    while(1)
    {
      // Read from the CPU Pipe.
      read(cpu_pipe[0], cpu_buffer, sizeof(cpu_buffer));

      // Clear the Terminal and Move Cursor to the Top.
      printf("\033[2J\033[H");

      // Display CPU Info.
      printf("CPU Load Average: %s", cpu_buffer);
    }

    // Close the Read-End of the CPU Pipe.
    close(cpu_pipe[0]);

    // Wait for Child Process.
    waitpid(cpu_pid, NULL, 0);

  }

  return 0;
}