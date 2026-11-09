#include <stdio.h>      // fclose(), fgets(), fopen(), perror(), printf()
#include <stdlib.h>     // exit()
#include <string.h>     // strlen()
#include <sys/wait.h>   // waitpid()
#include <unistd.h>     // close(), fork(), pipe(), read(), sleep(), write()

#define BUFFER_SIZE 4096
#define INTERVAL 5

int main(void)
{
  // File Descriptors
  int cpu_pipe[2];
  int mem_pipe[2];
  char cpu_buffer[BUFFER_SIZE];
  char mem_buffer[BUFFER_SIZE];

  // CPU Pipe
  if (pipe(cpu_pipe) == -1)
  {
    perror("CPU pipe");
    return -1;
  }

  if (pipe(mem_pipe) == -1){
    perror("Memory pipe");
    return -1;
  }


  // Create Child Processes
  pid_t cpu_pid, mem_pid;

  cpu_pid = fork();

  if (cpu_pid == 0)
  {
    // CPU MONITOR PROCESS (Child)

    // Close Read-End of CPU Pipe.
    close(cpu_pipe[0]);

    // Close the Memory Pipe
    close(*mem_pipe);

    // Buffer for Reading CPU Info.
    char buffer[BUFFER_SIZE];

    for (int i = 0; i < 5; i++)
    {
      FILE *file = fopen("/proc/loadavg", "r");

      if (file != NULL)
      {
        if (fgets(buffer, sizeof(buffer), file) != NULL)
        {
          // Send the CPU Info Through the Pipe.
          write(cpu_pipe[1], buffer, strlen(buffer) + 1);   
          
          // Close the CPU file.
          fclose(file);;
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
    // Create memory monitor process

    mem_pid = fork();

    if (mem_pid == 0){
      // MEMORY MONITOR PROCESS (Child).

      // Close the reed-end of the memory pipe.
      close(mem_pipe[0]);

      // Close the CPU pipe
      close(*cpu_pipe);

      // Buffer for reading memory Info
      char buffer[BUFFER_SIZE];

      for (int i = 0; i < 5; i++){
        FILE *file = fopen("/proc/meminfo", "r");

        if (file!= NULL){
          while (fgets(buffer, sizeof(buffer), file) != NULL){
            // Send the memory info through the memory pipe
            write(mem_pipe[1], buffer, strlen(buffer) + 1);
          }

          // Close the memory info file
          fclose(file);
        }

        sleep(INTERVAL);
      }

      // Close the write-end of the memory pipe
      close(mem_pipe[1]);

      exit(0);

    } else {
      
      // Parent Process

      // Close the Write-End of the CPU Pipe and Memory Pipe.
      close(cpu_pipe[1]);
      close(mem_pipe[1]);

      for (int i = 0; i < 5; i++)
      {
        // Read from the CPU Pipe
        read(cpu_pipe[0], cpu_buffer, sizeof(cpu_buffer));

        // Clear the Terminal and Move Cursor to the Top.
        //printf("\033[2J\033[H");

        // Display CPU Info.
        printf("CPU Load Average: %s\n", cpu_buffer);

        // Display Memory Info.
        
        // Read from the memory pipe
        ssize_t bytes_read = read(mem_pipe[0], mem_buffer, sizeof(mem_buffer));
        mem_buffer[bytes_read] = '\0';
       // while(read(mem_pipe[0], mem_buffer, sizeof(mem_buffer)) != 0){
       //   printf("%s", mem_buffer);
       // }
        printf("%s read by %d bytes", mem_buffer, bytes_read);
      }

      // Close the Read-End of the CPU Pipe and Memory Pipe.
      close(cpu_pipe[0]);
      close(mem_pipe[0]);

      // Wait for Child Processes.
      waitpid(cpu_pid, NULL, 0);
      waitpid(mem_pid, NULL, 0);
    }
  }

  return 0;
}
