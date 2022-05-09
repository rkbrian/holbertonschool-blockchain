#include "blockchain.h"

/**
 * blockchain_deserialize - deserialize a Blockchain from a file
 * @path: the path to a file to load the Blockchain from
 * Return: a pointer to the deserialized Blockchain upon success,
 *  or NULL upon failure involving:
 *  - Unable to open/read file,
 *  - Incorrect magic number
 *  - Version mismatch
 * Note: fread may not successfully read, init blocks_count = 0 is safer
 */
blockchain_t *blockchain_deserialize(char const *path)
{
	FILE *fp = NULL;
	blockchain_t *bc;
	block_t *block;
	char magicnum[5], version[4]; /* strlen(string) = sizeof(string) - 1 */
	size_t blocks_count = 0, i = 0;
	uint8_t endi;

	if (!path)
		return (NULL);
	fp = fopen(path, "rb");
	if (!fp)
		return (NULL);
	fseek(fp, 0, SEEK_SET), fread(magicnum, strlen(HBLK_MAGIC), 1, fp);
	magicnum[strlen(HBLK_MAGIC)] = 0, fread(version, strlen(HBLK_VERSION), 1, fp);
	version[strlen(HBLK_VERSION)] = 0, bc = malloc(sizeof(blockchain_t));
	if (strcmp(magicnum, HBLK_MAGIC) != 0 || strcmp(version, HBLK_VERSION) != 0 ||
	    !bc)
	{
		fclose(fp);
		return (NULL);
	}
	bc->chain = llist_create(MT_SUPPORT_FALSE);
	fread(&endi, sizeof(uint8_t), 1, fp);
	fread(&blocks_count, sizeof(int), 1, fp);
	while (i < blocks_count)
	{
		block = malloc(sizeof(block_t));
		if (!block)
		{
			llist_destroy(bc->chain, i, NULL), fclose(fp);
			return (NULL);
		}
		block_sweep(block, endi, fp);
		llist_add_node(bc->chain, block, ADD_NODE_REAR), i++;
	}
	fclose(fp);
	return (bc);
}

/**
 * block_sweep - function to swap bytes for proper endianness
 * @block: block
 * @endianness: endianness
 * @fp: file pointer
 */
void block_sweep(block_t *block, int endianness, FILE *fp)
{
	fread(&block->info.index, sizeof(block->info.index), 1, fp);
	fread(&block->info.difficulty, sizeof(block->info.difficulty), 1, fp);
	fread(&block->info.timestamp, sizeof(block->info.timestamp), 1, fp);
	fread(&block->info.nonce, sizeof(block->info.nonce), 1, fp);
	fread(block->info.prev_hash, sizeof(block->info.prev_hash), 1, fp);
	fread(&block->data.len, sizeof(block->data.len), 1, fp);
	memset(block->data.buffer, 0, sizeof(block->data.buffer));
	fread(block->data.buffer, block->data.len, 1, fp);
	fread(block->hash, sizeof(block->hash), 1, fp);
	if (endianness == 2) /* big endianness */
	{
		_swap_endian(&block->info.index, sizeof(block->info.index));
		_swap_endian(&block->info.difficulty, sizeof(block->info.difficulty));
		_swap_endian(&block->info.timestamp, sizeof(block->info.timestamp));
		_swap_endian(&block->info.nonce, sizeof(block->info.nonce));
		_swap_endian(block->info.prev_hash, sizeof(block->info.prev_hash));
		_swap_endian(&block->data.len, sizeof(block->data.len));
		_swap_endian(block->data.buffer, block->data.len);
		_swap_endian(block->hash, sizeof(block->hash));
	}
}
