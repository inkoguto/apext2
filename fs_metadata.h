#ifndef FS_METDATA_H
#define FS_METDATA_H

struct Superblock
{
	int s_inodes_count;
	int s_blocks_count;
    int s_r_blocks_count;
	int s_free_blocks_count;
	int s_free_inodes_count;
	int s_first_data_block;
	int s_log_block_size;
	int s_log_frag_size;
	int s_blocks_per_group;
	int s_frags_per_group;
	int s_inodes_per_group;
	int s_mtime;
	int s_wtime;
	short int s_mnt_count;
	short int s_max_mnt_count;
	short int s_magic;
	short int s_state;
	short int s_errors;
	short int s_minor_rev_level;
	int s_lastcheck;
	int s_checkinterval;
	int s_creator_os;
	int s_rev_level;
	short int s_def_resuid;
	short int s_def_resgid;
	int s_first_ino;
	short int s_inode_size;
	short int s_block_group_nr;
	int s_feature_compat;
	int s_feature_incompat;
	int s_feature_ro_compat;
	char s_uuid[16];
	char s_volume_name[16];
	char s_last_mounted[64];
	int s_algo_bitmap;
	char s_prealloc_blocks;
	char s_prealloc_dir_blocks;
	short int _alignment;
	char s_journal_uuid[16];
	int s_journal_inum;
	int s_journal_dev;
	int s_last_orphan;
	char s_hash_seed[16];
	int s_def_hash_version;
	char __padding[3];
	int s_default_mount_options;
	int s_first_meta_bg;
};

typedef struct {
    int bg_block_bitmap;
    int bg_inode_bitmap;
    int bg_inode_table;
    int bg_free_blocks_count;
    int bg_free_inodes_count;
    int bg_used_dirs_count;
    int bg_pad;
    char bg_reserved[12];
} Bgd_table;

Bgd_table * get_bgd_table();

struct Superblock * get_superblock();

#endif