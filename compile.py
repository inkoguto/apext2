import os

files = [
    "main.c",
    "inode.c",
    "renderer.c",
    "dir.c",
    "reader.c",
    "fs_metadata.c",
    "ui.c"
]

os.system("clang -fsanitize=address -g -Wall -lncurses {}".format(" ".join(files)))
# os.system("clang -g -Wall {}".format(" ".join(files)))