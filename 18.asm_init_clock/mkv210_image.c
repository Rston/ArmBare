/*
 * mkv210_image.c作用：将usb启动时使用的xxx_usb.bin制作得到由sd卡启动的镜像xxx_sd.bin
 * 本文件来自于友善之臂的裸机教程，据友善之臂的文档中讲述，本文件是一个热心网友提供，在此表示感谢。
 *
 * 在BL0阶段，Irom内固化的代码读取nandflash或SD卡前16K的内容，
 * 并比对前16字节中的校验和是否正确，正确则继续，错误则停止。
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE                 (16*1024)
#define IMG_SIZE                (16*1024)
#define SPL_HEADER_SIZE         16
#define SPL_HEADER            "S5PC110 HEADER  "	// 16字节，随便16个字节即可

int main (int argc, char *argv[])
{
	FILE *fp;
	char *Buf, *a;
	int	BufLen;
	int	nbytes, fileLen;
	unsigned int checksum, count;
	int	i;
	
	// 1.检查参数个数是否为3
	if (argc != 3)
	{
		printf("Usage: %s <source file> <destination file>\n", argv[0]);
		return -1;
	}

	// 2.分配16K的buffer并请零
	BufLen = BUFSIZE;
	Buf = (char *)malloc(BufLen);
	if (!Buf)
	{
		printf("malloc buffer failed!\n");
		return -1;
	}
	memset(Buf, 0x00, BufLen);

	// 3.读源bin到buffer
	// 3.1 打开源bin
	fp = fopen(argv[1], "rb");
	if( fp == NULL)
	{
		printf("source file open error\n");
		free(Buf);
		return -1;
	}
	// 3.2获取源bin长度
	fseek(fp, 0L, SEEK_END);								// 定位到文件尾
	fileLen = ftell(fp);									// 得到文件长度
	fseek(fp, 0L, SEEK_SET);								// 再次定位到文件头
	// 3.3源bin长度不得超过16K-16byte，
	// 注意若裸机程序大于16KB，则裸机程序会出问题，在后续做LCD实验时需特别注意
	count = (fileLen < (IMG_SIZE - SPL_HEADER_SIZE))
		? fileLen : (IMG_SIZE - SPL_HEADER_SIZE);
	// 3.4在buffer[0~15]中存放"S5PC110 HEADER  "
	memcpy(&Buf[0], SPL_HEADER, SPL_HEADER_SIZE);
	// 3.5读源bin到buffer[16]
	nbytes = fread(Buf + SPL_HEADER_SIZE, 1, count, fp);
	if ( nbytes != count )
	{
		printf("source file read error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}
	fclose(fp);

	// 4.计算校验和
	// 4.1从第16byte开始计算，把buffer中所有的字节数据加和起来得到的结果
	a = Buf + SPL_HEADER_SIZE;
	for(i = 0, checksum = 0; i < IMG_SIZE - SPL_HEADER_SIZE; i++)
		checksum += (0x000000FF) & *a++;
	// 4.2将校验和保存在buffer[8~12]
	a = Buf + 8;	// Buf是xxx_sd.bin的起始地址，+8表示向后位移2个字，也就是说写入到第3个字
	*((unsigned int *)a) = checksum;

	// 5.拷贝buffer中的内容到目的bin
	// 5.1打开目的bin
	fp = fopen(argv[2], "wb");
	if (fp == NULL)
	{
		printf("destination file open error\n");
		free(Buf);
		return -1;
	}
	// 5.2将16k的buffer拷贝到目的bin中
	a = Buf;
	nbytes = fwrite(a, 1, BufLen, fp);
	if (nbytes != BufLen)
	{
		printf("destination file write error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	free(Buf);
	fclose(fp);

	return 0;
}
