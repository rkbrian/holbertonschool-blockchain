#include "../blockchain.h"

/**
 * transaction_hash - computes the ID (hash) of a transaction
 * @transaction: points to the transaction to compute the hash of
 * @hash_buf: a buffer in which to store the computed hash
 * Return: a pointer to hash_buf
 */
uint8_t *transaction_hash(transaction_t const *transaction,
			  uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	int buffer_len, input_len, output_len, tx_offset = 0, i;
	int8_t *hash_ptr;
	tx_in_t *curr_input;
	tx_out_t *curr_output;

	if (!transaction)
		return (NULL);
	input_len = llist_size(transaction->inputs);
	output_len = llist_size(transaction->outputs);
	buffer_len = input_len * 3 * 32 + output_len * 32;
	hash_ptr = malloc(buffer_len);
	if (!hash_ptr)
		return (NULL);
	for (i = 0; i < input_len; i++)
	{
		curr_input = llist_get_node_at(transaction->inputs, i);
		memcpy(hash_ptr + tx_offset, curr_input, 32 * 3);
		tx_offset += (32 * 3);
	}
	for (i = 0; i < output_len; i++)
	{
		curr_output = llist_get_node_at(transaction->outputs, i);
		memcpy(hash_ptr + tx_offset, curr_output->hash, 32);
		tx_offset += 32;
	}
	sha256(hash_ptr, buffer_len, hash_buf);
	free(hash_ptr);
	return (hash_buf);
}
