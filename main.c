#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "superblock.h"
#include "renderer.h"
#include "bgd_table.h"
#include "inode.h"
#include "dir.h"

int main(int argc, char **argv)
{
  struct Superblock sb;
  Bgd_table bgd_table;
  Inode * inode;

  char location[] = "disk.img";
  load_superblock(&sb, location);
  load_bgd_table(&bgd_table, &sb, location);

  inode = get_first_inode(&sb, &bgd_table, location);
  get_root_dir(inode, &sb, &bgd_table, location);
  free(inode);
  
  return 1;
  // render(&sb);
}
