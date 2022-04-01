#include "blockchain.h"

/**
 * blockchain_create - create a Blockchain structure, and initializes it.
 * Notes: The Blockchain must contain one block upon creation. This block
 *  is called the Genesis Block. Its content is static, and pre-defined.
 * Return: created blockchain structure, or NULL.
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *bloke;

	bloke = malloc(sizeof(blockchain_t));
	if (!bloke)
		return (NULL);
	bloke->chain = malloc(sizeof(block_t));
	if (bloke->chain == NULL)
	{
		free(bloke);
		return (NULL);
	}
	bloke->chain->info = malloc(sizeof(block_info_t));
	if (bloke->chain->info == NULL)
	{
		free(bloke->chain), free(bloke);
		return (NULL);
	}
	bloke->chain->data = malloc(sizeof(block_data_t));
	if (bloke->chain->data == NULL)
	{
		free(bloke->chain->info), free(bloke->chain), free(bloke);
		return (NULL);
	}
	bloke->chain->info->index = 0, bloke->chain->info->difficulty = 0;
	bloke->chain->info->timestamp = 1537578000, bloke->chain->info->nonce = 0;
	memset(bloke->chain->info->prev_hash, 0, SHA256_DIGEST_LENGTH);
	bloke->chain->data->buffer = "Holberton School", bloke->chain->data->len = 16;
	bloke->chain->hash = "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\
\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"
	return (bloke);
}
