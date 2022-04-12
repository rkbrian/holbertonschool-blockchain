#include "blockchain.h"

int main(void)
{
	FILE *fp = NULL;
	char a[5], b[4];

	fp = fopen("save.hblk", "rb"), fseek(fp, 0, SEEK_SET);
	fseek(fp, 0, SEEK_SET), fread(a, strlen(HBLK_MAGIC), 1, fp), a[4] = '\0';
	printf("%s, %d\n", a, strcmp(a, HBLK_MAGIC));
	fseek(fp, strlen(HBLK_MAGIC), SEEK_SET), fread(b, strlen(HBLK_VERSION), 1, fp), b[3] = '\0';
	printf("%s, %d\n", b, strcmp(b, HBLK_VERSION));
	fclose(fp);

	printf("%lu\n", sizeof(HBLK_MAGIC));
	printf("%lu\n", strlen(HBLK_MAGIC));
	printf("%lu\n", sizeof(HBLK_VERSION));
	printf("%lu\n", strlen(HBLK_VERSION));
	return (0);
}
