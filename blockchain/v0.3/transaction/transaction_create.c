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
	transaction_t *tran = NULL;
	tx_out_t *tx_out;
	tx_in_t *tx_in;
	uint8_t key_in[EC_PUB_LEN], key_out[EC_PUB_LEN];
	int i;
	uint32_t balance = 0;

	ec_to_pub(sender, key_in), ec_to_pub(receiver, key_out);
	tran = tx_init();
	if (tran == NULL)
		return (NULL);
	balance = input_selector(tran->inputs, all_unspent, amount, key_in);
	if (balance < amount) /* if not enough to proceed the transaction */
	{
		llist_destroy(tran->inputs, 0, NULL);
		llist_destroy(tran->outputs, 0, NULL), free(tran);
		return (NULL);
	}
	tx_out = tx_out_create(amount, key_in); /* create outputs */
	llist_add_node(tran->outputs, tx_out, ADD_NODE_REAR);
	if (balance > amount) /* extra action for sending back the difference */
	{
		tx_out = tx_out_create(balance - amount, key_in);
		llist_add_node(tran->outputs, tx_out, ADD_NODE_REAR);
	}
	transaction_hash(tran, tran->id);
	/* sign the inputs with computed hash */
	for (i = 0; i < llist_size(tran->inputs); i++)
	{
		tx_in = llist_get_node_at(tran->inputs, i);
		if (tx_in_sign(tx_in, tran->id, sender, all_unspent) == 0)
		{
			llist_destroy(tran->inputs, 0, NULL);
			llist_destroy(tran->outputs, 0, NULL), free(tran);
			return (NULL);
		}
	}
	return (tran);
}

/**
 * tx_init - create and initialize a transaction struct
 * Return: created and initialized transaction pointer, or null
 */
transaction_t *tx_init(void)
{
	transaction_t *tran;

	tran = malloc(sizeof(transaction_t));
	if (tran == NULL)
		return (NULL);
	tran->inputs = NULL, tran->outputs = NULL;
	tran->inputs = llist_create(MT_SUPPORT_FALSE);
	if (tran->inputs == NULL)
	{
		free(tran);
		return (NULL);
	}
	tran->outputs = llist_create(MT_SUPPORT_FALSE);
	if (tran->outputs == NULL)
	{
		llist_destroy(tran->inputs, 0, NULL), free(tran);
		return (NULL);
	}
	return (tran);
}

/**
 * input_selector - function to select inputs
 * @input_list: input list
 * @all_unspent: the list of all the unspent outputs to date
 * @amount: the amount to send
 * @key_in: sender public key
 * Return: balance for the transaction
 */
uint32_t input_selector(llist_t *input_list, llist_t *all_unspent,
		       uint32_t amount, uint8_t key_in[EC_PUB_LEN])
{
	tx_in_t *tx_in_curr;
	unspent_tx_out_t *usp;
	int i, diff;
	uint32_t balance = 0;

	for (i = 0; i < llist_size(all_unspent); i++)
	{
		usp = llist_get_node_at(all_unspent, i);
		diff = memcmp(usp->out.pub, key_in, EC_PUB_LEN);
		if (diff == 0)
		{
			tx_in_curr = tx_in_create(usp);
			llist_add_node(input_list, tx_in_curr, ADD_NODE_REAR);
			balance += usp->out.amount;
			if (balance >= amount)
				break;
		}
	}
	return (balance);
}
