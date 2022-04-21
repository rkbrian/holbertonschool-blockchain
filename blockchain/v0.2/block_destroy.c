#include "blockchain.h"

/**
 * block_destroy - delete an existing Block
 * @block: points to the Block to delete
 */
void block_destroy(block_t *block)
{
	if (!block)
		return;
	free(block);
}
