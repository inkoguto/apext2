#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fs_metadata.h"
#include "renderer.h"
#include "inode.h"
#include "entity.h"
#include "ui.h"
#include "reader.h"

int main(int argc, char **argv)
{
  set_location(argv[1]);
  ui();
  
  return 0;
}
