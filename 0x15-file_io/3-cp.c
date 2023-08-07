#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void copy_file(const char *src_filename, const char *dest_filename);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: cp file_from file_to\n");
        exit(1);
    }

    copy_file(argv[1], argv[2]);

    return 0;
}

void copy_file(const char *src_filename, const char *dest_filename)
{
    int src_fd, dest_fd;
    char buffer[BUFFER_SIZE];
    ssize_t num_read, num_written;

    src_fd = open(src_filename, O_RDONLY);
    if (src_fd == -1)
    {
        perror("Error: Can't read from file");
        exit(2);
    }

    dest_fd = open(dest_filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (dest_fd == -1)
    {
        perror("Error: Can't write to file");
        close(src_fd);
        exit(3);
    }

    while ((num_read = read(src_fd, buffer, BUFFER_SIZE)) > 0)
    {
        num_written = write(dest_fd, buffer, num_read);
        if (num_written == -1)
        {
            perror("Error: Can't write to file");
            close(src_fd);
            close(dest_fd);
            exit(4);
        }
    }

    if (num_read == -1)
    {
        perror("Error: Can't read from file");
        close(src_fd);
        close(dest_fd);
        exit(5);
    }

    close(src_fd);
    close(dest_fd);
}
