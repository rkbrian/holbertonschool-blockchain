CC = gcc
SRC = blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -pedantic
RM = rm -f
blockchain_create-test: # usage: ./blockchain_create-test
	$(CC) $(CFLAGS) -I. -o $@ blockchain_create.c test/blockchain_create-main.c provided/_blockchain_print.c provided/_blockchain_destroy.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
block_create-test: # usage: ./block_create-test
	$(CC) $(CFLAGS) -I. -o $@ blockchain_create.c block_create.c test/block_create-main.c provided/_blockchain_print.c provided/_blockchain_destroy.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
block_destroy-test: # usage: valgrind ./block_destroy-test
	$(CC) $(CFLAGS) -I. -o $@ blockchain_create.c block_create.c block_destroy.c test/block_destroy-main.c provided/_blockchain_destroy.c  -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
blockchain_destroy-test: # usage: valgrind ./blockchain_destroy-test
	$(CC) $(CFLAGS) -I. -o $@ blockchain_destroy.c blockchain_create.c block_create.c block_destroy.c test/blockchain_destroy-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
block_hash-test: # usage: ./block_hash-test
	$(CC) $(CFLAGS) -I. -o $@ blockchain_create.c block_create.c block_destroy.c blockchain_destroy.c block_hash.c test/block_hash-main.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread


$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
oclean:
	$(RM) $(OBJ)
testclean:
	$(RM) *-test
.PHONY: sha256-test ec_create-test ec_to_pub-test ec_from_pub-test ec_save-test ec_load-test ec_sign-test ec_verify-test oclean testclean $(CFLAGS)
