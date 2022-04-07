#include "blockchain.h"

/**
 * blockchain_serialize - contain the path to a file to serialize
 *  the Blockchain into
 * @blockchain: points to the Blockchain to be serialized
 * @path: points to an existing file, it must be overwritten
 * Return: 0 upon success, or -1 upon failure
 */
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	FILE *fp = NULL;
	block_t *block = NULL;
	int blocks_count, i = 0;
	uint8_t endi;

	if (!blockchain || !path)
		return (-1);
	endi = _get_endianness();
	if (!endi) /* case not possible */
		return (-1);
	fp = fopen(path, "w");
	if (!fp)
		return (-1);
	blocks_count = llist_size(blockchain->chain);
	fwrite(HBLK_MAGIC, 1, sizeof(HBLK_MAGIC) - 1, fp); /* no null byte */
	fwrite(HBLK_VERSION, 1, sizeof(HBLK_VERSION) - 1, fp);
	fwrite(&endi, 1, sizeof(uint8_t), fp);
	fwrite(&blocks_count, 1, sizeof(int), fp);
	while (i < blocks_count)
	{
		block = llist_get_node_at(blockchain->chain, i);
		block_swap(&block->info.index, sizeof(block->info.index), fp, endi);
		block_swap(&block->info.difficulty, sizeof(block->info.difficulty),
			   fp, endi);
		block_swap(&block->info.timestamp, sizeof(block->info.timestamp), fp, endi);
		block_swap(&block->info.nonce, sizeof(block->info.nonce), fp, endi);
		block_swap(block->info.prev_hash, sizeof(block->info.prev_hash), fp, endi);
		block_swap(&block->data.len, sizeof(block->data.len), fp, endi);
		block_swap(block->data.buffer, block->data.len, fp, endi);
		block_swap(block->hash, sizeof(block->hash), fp, endi);
		i++;
	}
	fclose(fp);
	return (0);
}

/**
 * block_swap - function to swap bytes for proper endianness
 * @block_content: block content
 * @size: size of the block content
 * @fp: file pointer
 * @endianness: endianness
 */
void block_swap(void *block_content, size_t size, FILE *fp, int endianness)
{
	if (endianness == 2) /* big endianness */
		_swap_endian(block_content, size);
	fwrite(block_content, 1, size, fp);
}
