CC = gcc
SRC = blockchain_create.c block_create.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -pedantic
RM = rm -f
blockchain_create-test: # usage: ./blockchain_create-test
	$(CC) $(CFLAGS) -I. -o $@ blockchain_create.c test/blockchain_create-main.c provided/_blockchain_print.c provided/_blockchain_destroy.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread
block_create-test: # usage: ./block_create-test
	$(CC) $(CFLAGS) -I. -o $@ blockchain_create.c block_create.c test/block_create-main.c provided/_blockchain_print.c provided/_blockchain_destroy.c -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread






$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
oclean:
	$(RM) $(OBJ)
testclean:
	$(RM) *-test
.PHONY: sha256-test ec_create-test ec_to_pub-test ec_from_pub-test ec_save-test ec_load-test ec_sign-test ec_verify-test oclean testclean $(CFLAGS)
