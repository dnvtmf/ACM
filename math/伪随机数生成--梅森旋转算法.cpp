//伪随机数生成--梅森旋转算法（Mersenne twister）
/*是一个伪随机数发生算法. 对于一个k位的长度，Mersenne Twister会在[0,2^k - 1](1 <= k <= 623) 的区间之间生成离散型均匀分布的随机数.梅森旋转算法的周期为梅森素数2^19937 - 1*/
//32位算法
int mtrand_init = 0;
int mtrand_index;
int mtrand_MT[624];
void mt_srand(int seed)
{
    mtrand_index = 0;
    mtrand_init = 1;
    mtrand_MT[0] = seed;
    for(int i = 1; i < 624; i++)
    {
        int t = 1812433253 * (mtrand_MT[i - 1] ^ (mtrand_MT[i - 1] >> 30)) + i;//0x6c078965
        mtrand_MT[i] = t & 0xffffffff;   //取最后的32位赋给MT[i]
    }
}

int mt_rand()
{
    if(!mtrand_init)
        srand((int)time(NULL));
    int y;
    if(mtrand_index == 0)
    {
        for(int i = 0; i < 624; i++)
        {
            //2^31 -1 = 0x7fff ffff  2^31 = 0x8000 0000
            int y = (mtrand_MT[i] & 0x80000000) + (mtrand_MT[(i + 1) % 624] & 0x7fffffff);
            mtrand_MT[i] = mtrand_MT[(i + 397) % 624] ^ (y >> 1);
            if(y & 1) mtrand_MT[i] ^= 2567483615; // 0x9908b0df
        }
    }
    y = mtrand_MT[mtrand_index];
    y = y ^ (y >> 11);
    y = y ^ ((y << 7) & 2636928640);	//0x9d2c5680
    y = y ^ ((y << 15) & 4022730752); 	// 0xefc60000
    y = y ^ (y >> 18);
    mtrand_index = (mtrand_index + 1) % 624;
    return y;
}
