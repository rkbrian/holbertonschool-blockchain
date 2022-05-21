#include "blockchain.h"

/**
 * block_destroy - delete an existing Block
 * @block: points to the Block to delete
 */
void block_destroy(block_t *block)
{
	if (!block)
		return;
	/* transaction destroy and free */
	llist_destroy(block->transactions, 1, transaction_destroy);
	free(block);
}
