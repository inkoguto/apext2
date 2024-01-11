#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "superblock.h"

union Node
{
	int number;
	char bytes[64];
};


union Node get_node(char * buff, int offset, int size) {
  union Node node;
  memcpy(node.bytes, &buff[offset], size);
  return node;
}

void set_data(struct Superblock * sb, char * buff) {
	sb->s_inodes_count = get_node(buff, 0, 4).number;
	sb->s_blocks_count = get_node(buff, 4, 4).number;
	sb->s_r_blocks_count = get_node(buff, 8, 4).number;
	sb->s_free_blocks_count = get_node(buff,12, 4).number;
	sb->s_free_inodes_count = get_node(buff, 16, 4).number;
	sb->s_first_data_block = get_node(buff, 20, 4).number;
	sb->s_log_block_size = get_node(buff, 24, 4).number;
	sb->s_log_frag_size = get_node(buff, 28, 4).number;
	sb->s_blocks_per_group = get_node(buff, 32, 4).number;
	sb->s_frags_per_group = get_node(buff, 36, 4).number;
	sb->s_inodes_per_group = get_node(buff, 40, 4).number;
	sb->s_mtime = get_node(buff, 44, 4).number;
	sb->s_wtime = get_node(buff, 48, 2).number;
	sb->s_mnt_count = get_node(buff, 52, 2).number;
	sb->s_max_mnt_count = get_node(buff, 54, 2).number;
	sb->s_magic = get_node(buff, 56, 2).number;
	sb->s_state = get_node(buff, 58, 2).number;
	sb->s_errors = get_node(buff, 60, 2).number;
	sb->s_minor_rev_level = get_node(buff, 62, 2).number;
	sb->s_lastcheck = get_node(buff, 64, 4).number;
	sb->s_checkinterval = get_node(buff, 68, 4).number;
	sb->s_creator_os = get_node(buff, 72, 4).number;
	sb->s_rev_level = get_node(buff, 76, 4).number;
	sb->s_def_resuid = get_node(buff, 80, 2).number;
	sb->s_def_resgid = get_node(buff, 82, 2).number;
	sb->s_first_ino = get_node(buff, 84, 4).number;
	sb->s_inode_size = get_node(buff, 88, 2).number;
	sb->s_block_group_nr = get_node(buff, 90, 2).number;
	sb->s_feature_compat = get_node(buff, 92, 4).number;
	sb->s_feature_incompat = get_node(buff, 96, 4).number;
	sb->s_feature_ro_compat = get_node(buff, 100, 4).number;
	strcpy(sb->s_uuid, get_node(buff, 104, 16).bytes);
	strcpy(sb->s_volume_name, get_node(buff, 120, 16).bytes);
	strcpy(sb->s_last_mounted, get_node(buff, 136, 64).bytes);
	sb->s_algo_bitmap = get_node(buff, 200, 4).number;
	sb->s_prealloc_blocks = get_node(buff, 204, 1).number;
	sb->s_prealloc_dir_blocks = get_node(buff, 205, 1).number;
	strcpy(sb->s_journal_uuid, get_node(buff, 208, 16).bytes);
	sb->s_journal_inum = get_node(buff, 224, 4).number;
	sb->s_journal_dev = get_node(buff, 228, 4).number;
	sb->s_last_orphan = get_node(buff, 232, 4).number;
	strcpy(sb->s_hash_seed, get_node(buff, 236, 16).bytes);
	sb->s_def_hash_version = get_node(buff, 252, 1).number;
	sb->s_default_mount_options = get_node(buff, 256, 4).number;
	sb->s_first_meta_bg = get_node(buff, 260, 4).number;
}

void load_superblock(struct Superblock *sb, char *location)
{
	char buff[1024];
	FILE *fh;

	fh = fopen(location, "r");
	if (fseek(fh, 1024, SEEK_SET))
	{
		puts("fseek");
		exit(1);
	}

	fread(buff, 1024, 1, fh);
	fclose(fh);
	set_data(sb, buff);
	return;
}
