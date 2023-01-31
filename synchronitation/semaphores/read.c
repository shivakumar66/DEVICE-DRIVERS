#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
        int fd;
        int ubuff;
        fd = open("/dev/read_device", O_RDWR,0777);
        if(fd > 0) {
                printf("Device File Opened successfully in the path /dev/mydriver_device...\n");
        }
        else {
                printf("Cannot open device file...\n");
                return 0;
        }
        printf("Data Reading ...");
        read(fd, (char *)&ubuff, sizeof(ubuff));
        printf("Done!\n\n");
        printf("Data = %d\n\n", ubuff);

                close(fd);
        return 0;
}
