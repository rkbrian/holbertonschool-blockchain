#include "blockchain.h"

block_t const GEN_BLOCK = {
	{ /* info */
		0,
		0,
		1537578000,
		0,
		{0}
	},
	{ /* data */
		GENESIS_STRING,
		16
	},
	GENESIS_HASH /* hash */
};

/**
 * blockchain_create - create a Blockchain structure, and initializes it.
 * Notes: The Blockchain must contain one block upon creation. This block
 *  is called the Genesis Block. Its content is static, and pre-defined.
 * Return: created blockchain structure, or NULL.
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain;
	block_t *block;

	blockchain = malloc(sizeof(blockchain_t));
	if (!blockchain)
		return (NULL);
	block = malloc(sizeof(block_t));
	if (!block)
	{
		free(blockchain);
		return (NULL);
	}
	blockchain->chain = llist_create(MT_SUPPORT_FALSE);
	/*block->info.index = 0, block->info.difficulty = 0;*/
	/*block->info.timestamp = 1537578000, block->info.nonce = 0;*/
	/*memset(block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);*/
	/*block->data.len = strlen(GENESIS_STRING);*/
	/*memset(block->data.buffer, 0, sizeof(block->data.buffer));*/
	/*memcpy(block->data.buffer, GENESIS_STRING, block->data.len);*/
	/*memcpy(block->hash, GENESIS_HASH, sizeof(GENESIS_HASH));*/
	memcpy(block, &GEN_BLOCK, sizeof(block_t));
	llist_add_node(blockchain->chain, block, ADD_NODE_FRONT);
	return (blockchain);
}
