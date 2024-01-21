#include <stdlib.h>
#include <string.h>
#include "node.h"

union Node get_node(char * buff, int offset, int size) {
  union Node node;
  memcpy(node.bytes, &buff[offset], size);
  return node;
}
