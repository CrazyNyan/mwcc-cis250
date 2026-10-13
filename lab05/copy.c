#include <fcntl.h>  // open()
#include <unistd.h> // read, write, close
#include <stdio.h> // printf

// Function declaration
int copy(const char *sourceFile, const char *targetFile);

int main(int argc, char *argv[]){
	// Check command-line arguments
	if (argc != 3){
		printf("Usage: %s source target\n", argv[0]);
		return 1; // Return an error
	}

	return copy(argv[1], argv[2]);
}

int copy(const char *sourceFile, const char *targetFile){
	char buffer[1024];
	ssize_t bytesRead;
	ssize_t bytesWritten;

	// Open source file for reading
	int fd_source = open(sourceFile, O_RDONLY);

	if (fd_source == -1){
		perror("open source");
		close(fd_source);
		return 1;
	}

	// Open target file for writting
	int fd_target = open(targetFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (fd_target == -1){
		perror("open target");
		close(fd_target);
		return 1;
	}

	// Read into the buffer from the source and write from the buffer to the target
	while((bytesRead = read(fd_source, buffer, sizeof(buffer))) > 0){
		bytesWritten = write(fd_target, buffer, bytesRead);

		if (bytesWritten == -1){
			perror("write");
			close(fd_source);
			close(fd_target);
			return 1;
		}

		printf("%ld bytes written...\n", bytesWritten);
	}

	// Close the file descriptors
	if (close(fd_source) == -1){
		perror("close source");
		return 1;
	}

	if (close(fd_target) == -1){
		perror("close target");
		return 1;
	}

	return 0;
}
