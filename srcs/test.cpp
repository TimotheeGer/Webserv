#include <algorithm>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    char *bin_image;
    int tailleImage = 0;
    char c_size[10 + sizeof(char)];
    FILE* image = fopen("maison.jpg", "rb");

    fseek(image, 0 ,SEEK_END);
    tailleImage = ftell(image);
    rewind(image);

	bin_image = (char*) malloc (sizeof(char) * tailleImage);
    printf("taille image  = %d\n", tailleImage);
    int res = fread(bin_image, 1, tailleImage, image);
    printf("res = %d\n", res);
    // image.read(bin_image, i);
    printf("bin = %s\n", bin_image);


    
    return (0);
}