union Node
{
	short int short_number;
	int number;
	char bytes[64];
	int f_bytes[15];
	char o_byte;
};

union Node get_node(char * buff, int offset, int size);