#include "blockchain.h"

int main(void)
{
	FILE *fp = NULL;
	char magicnum[4], version[4];

	fp = fopen("save.hblk", "rb"), fseek(fp, 0, SEEK_SET);
	fread(magicnum, strlen(HBLK_MAGIC), 1, fp);
	printf("%d\n", strcmp(magicnum, HBLK_MAGIC));
	fseek(fp, strlen(HBLK_MAGIC), SEEK_SET); /* ???? */
	fread(version, strlen(HBLK_VERSION), 1, fp);
	printf("version: %s, %d\n", version, strcmp(version, HBLK_VERSION));
	fclose(fp);
	printf("%lu\n", sizeof(HBLK_MAGIC));
	printf("%lu\n", strlen(HBLK_MAGIC));
	printf("%lu\n", sizeof(HBLK_VERSION));
	printf("%lu\n", strlen(HBLK_VERSION));
	return (0);
}
