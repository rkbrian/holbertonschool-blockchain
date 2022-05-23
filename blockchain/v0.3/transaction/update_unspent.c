#include "blockchain.h"

/**
 * update_unspent - function that updates the list of all unspent
 *  transaction outputs, given a list of processed transactions.
 * @transactions: the list of validated transactions.
 * @block_hash: Hash of the validated Block that contains the transaction list
 *  transactions.
 * @all_unspent: the current list of unspent transaction outputs
 * Return: a new list of unspent transaction outputs
 * Notes:
 *  - All transaction inputs from each transaction in transactions should not
 *    be included in the returned list of unspent transaction outputs.
 *  - All transaction outputs from each transaction in transactions should be
 *    appended in the returned list of unspent transaction outputs.
 *  - The list all_unspent must be deleted upon success.
 */
llist_t *update_unspent(llist_t *transactions,
			uint8_t block_hash[SHA256_DIGEST_LENGTH], llist_t *all_unspent)
{
	int i, j;
	transaction_t *tx;
	tx_out_t *tx_out;
	unspent_tx_out_t *uns;
	llist_t *new_uns; /* making a new all unspent is more feasible */

	if (!transactions || !block_hash || !all_unspent)
		return (all_unspent);
	new_uns = llist_create(MT_SUPPORT_FALSE);
	for (i = 0; i < llist_size(all_unspent); i++) /* this size can be 0 */
	{
		uns = llist_get_node_at(all_unspent, i);
		new_uns = find_io_match(uns, transactions, new_uns);
	}
	/* for safety's sake, do a new loop */
	for (i = 0; i < llist_size(transactions); i++)
	{
		tx = llist_get_node_at(transactions, i);
		for (j = 0; j < llist_size(tx->outputs); j++)
		{
			tx_out = llist_get_node_at(tx->outputs, j);
			uns = unspent_tx_out_create(block_hash, tx->id, tx_out);
			llist_add_node(new_uns, uns, ADD_NODE_REAR);
		}
	}
	llist_destroy(all_unspent, 0, NULL);
	return (new_uns);
}

/**
 * find_io_match - find the unspent transaction output that matches the
 *  transaction input, then add into the new unspent list.
 * @uns: the unspent transaction output.
 * @transactions: the list of validated transactions.
 * @new_uns: the new list of unspent transaction outputs built by this func.
 * Return: new_uns
 */
llist_t *find_io_match(unspent_tx_out_t *uns, llist_t *transactions,
		       llist_t *new_uns)
{
	int i, j, flag = 0;
	transaction_t *tx;
	tx_in_t *tx_in;

	for (i = 0; i < llist_size(transactions); i++)
	{
		tx = llist_get_node_at(transactions, i);
		for (j = 0; j < llist_size(tx->inputs); j++)
		{
			tx_in = llist_get_node_at(tx->inputs, j);
			if ((memcmp(tx_in->tx_out_hash, uns->out.hash, SHA256_DIGEST_LENGTH) == 0)
			    && (memcmp(tx_in->tx_id, uns->tx_id, SHA256_DIGEST_LENGTH) == 0))
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
			break;
	}
	if (flag == 1)
		free(uns);
	else /* llist_remove_node is too tricky to handle */
		llist_add_node(new_uns, uns, ADD_NODE_REAR);
	return (new_uns);
}
