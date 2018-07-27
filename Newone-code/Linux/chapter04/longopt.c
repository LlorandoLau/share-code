#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>
/*
每一个结构体包含4个域，
第一个域为长选项字符串（--help），
第二个域是一个标识，只能为0、1或2，分别代表没有、有和可选。
第三个域永远为NULL。
第四个域为对应的短选项字符串（-h）。
*/
int main(int argc, char *argv[])
{
    int opt;
    int a;
    struct option longopts[] = {
	{"initialize", 0, &a, 'i'},
	{"file", 1, NULL, 'f'},
	{"list", 0, NULL, 'l'},
	{"restart", 0, NULL, 'r'},
	{0,0,0,0}};

    while((opt = getopt_long(argc, argv, ":if:lr", longopts, NULL)) != -1) {
        switch(opt) {
        case 'i':
        	printf("This is a: %c\n",a );
        	break;
        case 'l':
        case 'r':
            printf("option: %c\n", opt);
            break;
        case 'f':
            printf("filename: %s\n", optarg);
            break;
        case ':':
            printf("option needs a value\n");
            break;
        case '?':
            printf("unknown option: %c\n", optopt);
            break;
        }
    }
    for(; optind < argc; optind++)
        printf("argument: %s\n", argv[optind]);
    exit(0);
}
