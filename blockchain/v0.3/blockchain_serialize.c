#include "blockchain.h"

/**
 * blockchain_serialize - contain the path to a file to serialize
 *  the Blockchain into
 * @blockchain: points to the Blockchain to be serialized
 * @path: points to an existing file, it must be overwritten
 * Return: 0 upon success, or -1 upon failure
 */
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	FILE *fp = NULL;
	block_t *block = NULL;
	int blocks_count, i = 0;
	uint8_t endi;

	if (!blockchain || !path)
		return (-1);
	endi = _get_endianness();
	if (!endi) /* case not possible */
		return (-1);
	fp = fopen(path, "w");
	if (!fp)
		return (-1);
	blocks_count = llist_size(blockchain->chain);
	fwrite(HBLK_MAGIC, 1, sizeof(HBLK_MAGIC) - 1, fp); /* no null byte */
	fwrite(HBLK_VERSION, 1, sizeof(HBLK_VERSION) - 1, fp);
	fwrite(&endi, 1, sizeof(uint8_t), fp);
	fwrite(&blocks_count, 1, sizeof(int), fp);
	while (i < blocks_count)
	{
		block = llist_get_node_at(blockchain->chain, i);
		block_swap(&block->info.index, sizeof(block->info.index), fp, endi);
		block_swap(&block->info.difficulty, sizeof(block->info.difficulty),
			   fp, endi);
		block_swap(&block->info.timestamp, sizeof(block->info.timestamp), fp, endi);
		block_swap(&block->info.nonce, sizeof(block->info.nonce), fp, endi);
		block_swap(block->info.prev_hash, sizeof(block->info.prev_hash), fp, endi);
		block_swap(&block->data.len, sizeof(block->data.len), fp, endi);
		block_swap(block->data.buffer, block->data.len, fp, endi);
		block_swap(block->hash, sizeof(block->hash), fp, endi);
		tx_serialize(block->transactions, fp, endi);
		i++;
	}
	uns_serialize(blockchain->unspent, fp, endi);
	fclose(fp);
	return (0);
}

/**
 * tx_serialize - function to serialize the list of transactions.
 * @transactions: the list of validated transactions
 * @fp: file pointer
 * @endianness: endianness
 */
void tx_serialize(llist_t *transactions, FILE *fp, int endianness)
{
	int i, j, tx_size = 0;
	int nb_inputs, nb_outputs;
	transaction_t *tx;
	tx_in_t *tx_in;
	tx_out_t *tx_out;

	tx_size = llist_size(transactions);
	for (i = 0; i < tx_size; i++)
	{
		tx = llist_get_node_at(transactions, i);
		nb_inputs = llist_size(tx->inputs), nb_outputs = llist_size(tx->outputs);
		block_swap(&tx->id, sizeof(tx->id), fp, endianness);
		block_swap(&nb_inputs, sizeof(nb_inputs), fp, endianness);
		block_swap(&nb_outputs, sizeof(nb_outputs), fp, endianness);
		for (j = 0; j < llist_size(tx->inputs); j++)
		{
			tx_in = llist_get_node_at(tx->inputs, j);
			block_swap(&tx_in->block_hash, sizeof(tx_in->block_hash), fp, endianness);
			block_swap(&tx_in->tx_id, sizeof(tx_in->tx_id), fp, endianness);
			block_swap(&tx_in->tx_out_hash, sizeof(tx_in->tx_out_hash), fp, endianness);
			block_swap(&tx_in->sig.sig, sizeof(tx_in->sig.sig), fp, endianness);
			block_swap(&tx_in->sig.len, sizeof(tx_in->sig.len), fp, endianness);
		}
		for (j = 0; j < llist_size(tx->outputs); j++)
		{
			tx_out = llist_get_node_at(tx->outputs, j);
			block_swap(&tx_out->amount, sizeof(tx_out->amount), fp, endianness);
			block_swap(&tx_out->pub, sizeof(tx_out->pub), fp, endianness);
			block_swap(&tx_out->hash, sizeof(tx_out->hash), fp, endianness);
		}
	}
}

/**
 * uns_serialize - function to serialize the list of unspent outputs.
 * @unspent: the list of validated unspent outputs
 * @fp: file pointer
 * @endianness: endianness
 */
void uns_serialize(llist_t *unspent, FILE *fp, int endianness)
{
	unspent_tx_out_t *uns;
	int i;

	for (i = 0; i < llist_size(unspent); i++)
	{
		uns = llist_get_node_at(unspent, i);
		block_swap(&uns->block_hash, sizeof(uns->block_hash), fp, endianness);
		block_swap(&uns->tx_id, sizeof(uns->tx_id), fp, endianness);
		block_swap(&uns->out.amount, sizeof(uns->out.amount), fp, endianness);
		block_swap(&uns->out.pub, sizeof(uns->out.pub), fp, endianness);
		block_swap(&uns->out.hash, sizeof(uns->out.hash), fp, endianness);
	}
}

/**
 * block_swap - function to swap bytes for proper endianness
 * @block_content: block content
 * @size: size of the block content
 * @fp: file pointer
 * @endianness: endianness
 */
void block_swap(void *block_content, size_t size, FILE *fp, int endianness)
{
	if (endianness == 2) /* big endianness */
		_swap_endian(block_content, size);
	fwrite(block_content, 1, size, fp);
}
