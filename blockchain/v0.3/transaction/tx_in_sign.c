#include "../blockchain.h"

/**
 * tx_in_sign - sign a transaction input, given the transaction id it is from
 * @in: points to the transaction input structure to sign
 * @tx_id: contains the ID (hash) of the transaction the transaction input
 *  to sign is stored in
 * @sender: contains the private key of the receiver of the coins contained
 *  in the transaction output referenced by the transaction input
 * @all_unspent: is the list of all unspent transaction outputs to date
 * Return a pointer to the resulting signature structure upon success,
 *  or NULL upon failure
 * Notes: - must verify the public key derived from the private key in sender
 *  matches the public key stored in the transaction output referenced by the
 *  transaction input to be signed.
 *  - must sign the ID of the transaction tx_id the transaction input is stored
 *  in, using s private keysender.
 */
sig_t *tx_in_sign(tx_in_t *in, uint8_t const tx_id[SHA256_DIGEST_LENGTH],
		  EC_KEY const *sender, llist_t *all_unspent)
{
	unspent_tx_out_t *curr_tx;
	uint8_t pubkey[EC_PUB_LEN];
	int i, unspent_size;

	/* define if the transaction input is valid / in the unspent list */
	unspent_size = llist_size(all_unspent);
	for (i = 0; i < unspent_size; i++)
	{
		curr_tx = llist_get_node_at(all_unspent, i);
		if (memcmp(in->tx_out_hash, curr_tx->out.hash,
			   SHA256_DIGEST_LENGTH) == 0)
			break;
	}
	if (i == unspent_size)
		return (NULL);
	ec_to_pub(sender, pubkey); /* pub key match test*/
	if (pubkey == NULL || memcmp(pubkey, curr_tx->out.pub, EC_PUB_LEN) != 0)
		return (NULL);
	if (!ec_sign(sender, tx_id, SHA256_DIGEST_LENGTH, &in->sig))
		return (NULL);
	return (&in->sig);
}
