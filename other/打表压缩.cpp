/*
压缩算法: 非结束位以01开头,保存6位数字的二进制位; 结束位以001开头, 保存5位数字的二进制位; 从低位往高位保存.
例: 12538 --> 11 0000 1111 1010 --> 01111010 01000011 00100011 --> zC#
压缩效率: 约一半
*/
class Archive
{
private:
	string archive;
public:
	void init() {archive = "";}
	void add(LL x)
	{
		if(x < 0) {
			printf("only archive natural number\n");
			assert(0);
		}
		char c;
		while(true) {
			if((x >> 5) == 0) {
				c = (0x20 + x);
				archive += c == '"' ? '\t' : c;
				return ;
			}
			archive += (c = 0x40 + (x & 0x3f));
			if(c == '\\') archive += c;
			x >>= 6;
		}
	}
	void output(const char *filename)
	{
		FILE *out = fopen(filename, "w");
		fprintf(out, "%s", archive.data());
		fclose(out);
	}
};

void unpack(const char s[], int v[], int n)
{
	n = 0;
	int x = 0;
	int offset = 0;
	for(int i = 0; s[i]; ++i) {
		if(s[i] & 0x40) {
			x += (s[i] - 0x40) << offset;
			offset += 6;
		}
		else {
			x += (s[i] - 0x20) << offset;
			v[n++] = x;
			x = offset = 0;
		}
	}
}

