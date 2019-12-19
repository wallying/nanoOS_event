/**
 * file:    lib_sort.c
 * author:  wallying@foxmail.com
 * date:    2019-12-18
 **/


#include "lib/lib_sort.h"


void sort_u8(unsigned char *buf, unsigned int num)
{
	unsigned int i, j;
	unsigned char temp;
	for (i = 0; i < num; ++i) {
		for (j = i + 1; j < num; ++j) {
			if (buf[j] < buf[i]) {
				temp = buf[i];
				buf[i] = buf[j];
				buf[j] = temp;
			}
		}
	}
}

void sort_u16(unsigned short *buf, unsigned int num)
{
	unsigned int i, j;
	unsigned short temp;
	for (i = 0; i < num; ++i) {
		for (j = i + 1; j < num; ++j) {
			if (buf[j] < buf[i]) {
				temp = buf[i];
				buf[i] = buf[j];
				buf[j] = temp;
			}
		}
	}
}

void sort_u32(unsigned int *buf, unsigned int num)
{
	unsigned int i, j;
	unsigned int temp;
	for (i = 0; i < num; ++i) {
		for (j = i + 1; j < num; ++j) {
			if (buf[j] < buf[i]) {
				temp = buf[i];
				buf[i] = buf[j];
				buf[j] = temp;
			}
		}
	}
}

