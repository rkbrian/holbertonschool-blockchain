#include "blockchain.h"

/**
 * block_hash - compute the hash of a Block
 *  Notes: block->hash must be left unchanged.
 * @block: points to the Block to be hashed
 * @hash_buf: where the resulting hash must be stored in
 * Return: a pointer to hash_buf
 */
uint8_t *block_hash(block_t const *block,
		    uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t new_len, i, tx_size;
	int8_t *buffer;
	transaction_t *tx_temp;

	if (!block)
		return (NULL);
	new_len = sizeof(block->info) + block->data.len; /* offset */
	tx_size = llist_size(block->transactions);
	buffer = malloc(new_len + (SHA256_DIGEST_LENGTH * tx_size));
	memcpy(buffer, block, new_len); /* offset copy */
	for (i = 0; i < tx_size; i++, new_len += SHA256_DIGEST_LENGTH)
	{
		tx_temp = llist_get_node_at(block->transactions, i);
		memcpy(buffer + new_len, tx_temp->id, SHA256_DIGEST_LENGTH);
	}
	sha256(buffer, new_len, hash_buf); /* now new_len = buffer size */
	free(buffer);
	return (hash_buf);
}
