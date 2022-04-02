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
	;
}
