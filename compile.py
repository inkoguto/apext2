import os

files = [
    "main.c",
    "fs/inode.c",
    "fs/renderer.c",
    "fs/entity.c",
    "fs/reader.c",
    "fs/fs_metadata.c",
    "ui/ui.c",
    "ui/windows.c"
]

os.system("clang -fsanitize=address -g -Wall -I./ui -I./fs -lncurses {}".format(" ".join(files)))
# os.system("clang -g -Wall {}".format(" ".join(files)))