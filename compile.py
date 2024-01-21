import os

files = [
    "main.c",
    "inode.c",
    "bgd_table.c",
    "node.c",
    "renderer.c",
    "superblock.c",
    "dir.c"
]

os.system("gcc -g -Wall {}".format(" ".join(files)))