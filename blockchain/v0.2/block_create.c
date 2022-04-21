#include "blockchain.h"

/**
 * block_create - create a Block structure and initializes it.
 * @prev: a pointer to the previous Block in the Blockchain
 * @data: points to a memory area to duplicate in the Block's data
 * @data_len: stores the number of bytes to duplicate in data.
 * Notes: If data_len is bigger than BLOCKCHAIN_DATA_MAX, then only
 *  BLOCKCHAIN_DATA_MAX bytes must be duplicated.
 * Return: a pointer to the allocated Block
 */
block_t *block_create(block_t const *prev, int8_t const *data,
		      uint32_t data_len)
{
	block_t *block;

	block = malloc(sizeof(block_t));
	if (!block)
		return (NULL);
	if (data_len > BLOCKCHAIN_DATA_MAX)
		data_len = BLOCKCHAIN_DATA_MAX;
	block->info.difficulty = 0;
	time((time_t *)&block->info.timestamp);
	block->info.nonce = 0;
	if (prev)
	{
		block->info.index = prev->info.index + 1;
		memset(block->data.buffer, 0, sizeof(block->data.buffer));
		memcpy(block->info.prev_hash, prev->hash, sizeof(prev->hash));
	}
	else /* genesis block is created in blockchain_create, impossible */
	{
		block->info.index = 0;
		memset(block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
	}
	memset(block->hash, 0, SHA256_DIGEST_LENGTH);
	memcpy(block->data.buffer, data, data_len), block->data.len = data_len;
	return (block);
}
