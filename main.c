#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "superblock.h"
#include "renderer.h"

int main(int argc, char **argv)
{
  struct Superblock sb;
  char location[] = "disk.img";
  load_superblock(&sb, location);
  render(&sb);
}
