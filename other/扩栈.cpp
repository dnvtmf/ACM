//64-bit
int size = 20 << 20;//256M
char *p = (char *)malloc(size) + size;
__asm__("movq %0, %%rsp\n" :: "r"(p));
//32-bit
int size = 20 << 20;//256M
char *p = (char *)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p));
