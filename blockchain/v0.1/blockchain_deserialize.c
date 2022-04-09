#include "blockchain.h"

/**
 * blockchain_deserialize - deserialize a Blockchain from a file
 * @path: the path to a file to load the Blockchain from
 * Return: a pointer to the deserialized Blockchain upon success,
 *  or NULL upon failure involving:
 *  - Unable to open/read file,
 *  - Incorrect magic number
 *  - Version mismatch
 */
blockchain_t *blockchain_deserialize(char const *path)
{
	FILE *fp = NULL;
	blockchain_t *bc;
	block_t *block;
	char magicnum[4], version[4];
	size_t byte_i = 0, blocks_count, i = 0;
	uint8_t endi;

	if (!path)
		return (NULL);
	fp = fopen(path, "rb");
	if (!fp)
		return (NULL);
	fseek(fp, 0, SEEK_SET), fread(magicnum, strlen(HBLK_MAGIC), 1, fp);
	fseek(fp, strlen(HBLK_MAGIC), SEEK_SET); /* strlen() = sizeof() - 1 */
	fread(version, strlen(HBLK_VERSION), 1, fp), byte_i += strlen(HBLK_MAGIC);
	if (strcmp(magicnum, HBLK_MAGIC) != 0 || strcmp(version, HBLK_VERSION) != 0)
		return (NULL);
	bc = blockchain_create(), byte_i += strlen(HBLK_VERSION);
	if (!bc)
		return (NULL);
	block = llist_get_head(blockchain->chain), fseek(fp, byte_i, 1, fp);
	fread(&endi, sizeof(uint8_t), 1, fp), byte_i += sizeof(uint8_t);
	fseek(fp, byte_i, 1, fp), fread(&blocks_count, sizeof(int), 1, fp);
	printf("endian: %u; blocks count: %u\n", endi, blocks_count); /* debug checking */
	while (i < blocks_count)
	{
		;
		block = block_create(block, (int8_t *)"Holberton", 9);
		;
	}
	fclose(fp);
	return (bc);
}

/**
 * block_sweep - function to swap bytes for proper endianness
 * @block_content: block content
 * @size: size of the block content
 * @fp: file pointer
 * @endianness: endianness
 */
void block_sweep(void *block_content, size_t size, FILE *fp, int endianness)
{
	if (endianness == 2) /* big endianness */
		_swap_endian(block_content, size);
	fread(block_content, size, 1, fp);
}
