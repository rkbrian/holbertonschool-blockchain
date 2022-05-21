#include "blockchain.h"

/**
 * transaction_destroy - function that deallocates a transaction structure
 * @transaction: points to the transaction to delete
 */
void transaction_destroy(transaction_t *transaction)
{
	if (transaction)
	{
		if (transaction->inputs)
			llist_destroy(transaction->inputs, 1, NULL);
		if (transaction->outputs)
			llist_destroy(transaction->outputs, 1, NULL);
		free(transaction);
	}
}
