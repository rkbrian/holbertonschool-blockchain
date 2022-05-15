#include "../blockchain.h"

/**
 * transaction_create - function that creates a transaction
 * @sender: contains the private key of the transaction sender
 * @receiver: contains the public key of the transaction receiver
 * @amount: the amount to send
 * @all_unspent: the list of all the unspent outputs to date
 * Return: a pointer to the created transaction upon success,
 *  or NULL upon failure
 */
transaction_t *transaction_create(EC_KEY const *sender,
				  EC_KEY const *receiver, uint32_t amount, llist_t *all_unspent)
{
	transaction_t *tran;

	tran = malloc(sizeof(transaction_t));
	if (!tran)
		return (NULL);
	memset();
	memcpy();
	return ();
}
