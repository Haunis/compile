#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
参考： https://gitee.com/changyuet/android-tools-dat2img/blob/master/sdat2img.py


system.new.dat： 纯数据文件
system.transfer.list： 记录 system.new.dat每个块的起始位置

将system.new.dat映射成system.img后，可以看到system.img体积变大了(1.2G-->2.0G)


使用：
    解压：sudo ./un_update.py update.zip

    删除：sudo umount update/system
          sudo rm -rf update

"""

import sys, os, errno

# TRANSFER_LIST_FILE = 'system.transfer.list'
# NEW_DATA_FILE = 'system.new.dat'

BLOCK_SIZE = 4096

# try:
#     TRANSFER_LIST_FILE = str(sys.argv[1])  # system.transfer.list
#     NEW_DATA_FILE = str(sys.argv[2])  # system.new.dat
# except IndexError:
#     print('\nUsage: sdat2img.py <transfer_list> <system_new_file> [system_img]\n')
#     print('    <transfer_list>: transfer list file')
#     print('    <system_new_file>: system new dat file')
#     print('    [system_img]: output system image\n\n')
#     print('Visit xda thread for more information.\n')
#     try:
#         input = raw_input
#     except NameError:
#         pass
#     input('Press ENTER to exit...')
#     sys.exit()

# try:
#     OUTPUT_IMAGE_FILE = str(sys.argv[3])  # 指定输出文件名，可以不指定
# except IndexError:
#     OUTPUT_IMAGE_FILE = 'system.img'


TRANSFER_LIST_FILE = 'update/system.transfer.list'
NEW_DATA_FILE = 'update/system.new.dat'
OUTPUT_IMAGE_FILE = 'update/system.img'

# 执行cmd命令并返回结果
def execute_cmd(cmd):
    # f = os.popen(r"adb devices", "r")
    f = os.popen(cmd, "r")
    ret = f.read()
    f.close()
    return ret


# 数据格式转换
# "0,32770,32897,32899,33411,65535..." -->((0,32770),(32897,32899),(33411,65535)....)
def rangeset(src):
    src_set = src.split(',')
    num_set = [int(item) for item in src_set]
    if len(num_set) != num_set[0] + 1:
        print('Error on parsing following data to rangeset:\n%s' % src)
        sys.exit(1)
    return tuple([(num_set[i], num_set[i + 1]) for i in range(1, len(num_set), 2)])


# 解析system.transfer.list文件
def parse_transfer_list_file(path):
    trans_list = open(TRANSFER_LIST_FILE, 'r')

    # First line in transfer list is the version number
    version = int(trans_list.readline())

    # Second line in transfer list is the total number of blocks we expect to write
    new_blocks = int(trans_list.readline())

    if version >= 2:
        # Third line is how many stash entries are needed simultaneously
        trans_list.readline()  # 跳过一行
        # Fourth line is the maximum number of blocks that will be stashed simultaneously
        trans_list.readline()  # 再跳过一行

    # Subsequent lines are all individual transfer commands
    commands = []
    for line in trans_list:
        line = line.split(' ')
        cmd = line[0]
        if cmd in ['erase', 'new', 'zero']:
            commands.append([cmd, rangeset(line[1])])
        else:
            # Skip lines starting with numbers, they are not commands anyway
            if not cmd[0].isdigit():
                print('Command "%s" is not valid.' % cmd)
                trans_list.close()
                sys.exit(1)

    trans_list.close()
    return version, new_blocks, commands


def gen_img():
    version, new_blocks, commands = parse_transfer_list_file(TRANSFER_LIST_FILE)

    if version == 1:
        print('Android Lollipop 5.0 detected!\n')
    elif version == 2:
        print('Android Lollipop 5.1 detected!\n')
    elif version == 3:
        print('Android Marshmallow 6.x detected!\n')
    elif version == 4:
        print('Android Nougat 7.x / Oreo 8.x detected!\n')
    else:
        print('Unknown Android version!\n')

    # Don't clobber existing files to avoid accidental data loss
    try:
        output_img = open(OUTPUT_IMAGE_FILE, 'wb')
    except IOError as e:
        if e.errno == errno.EEXIST:
            print('Error: the output file "{}" already exists'.format(e.filename))
            print('Remove it, rename it, or choose a different file name.')
            sys.exit(e.errno)
        else:
            raise

    new_data_file = open(NEW_DATA_FILE, 'rb')
    all_block_sets = [i for cmd in commands for i in cmd[1]]
    max_file_size = max(pair[1] for pair in all_block_sets) * BLOCK_SIZE  # 文件最大有多大； 也就是最有一个块文件的结束位置

    # 按照解析出来的数据，读取出一块块数据，在写入目标文件
    for command in commands:
        if command[0] == 'new':
            for block in command[1]:  # ((0,32770),(32897,32899),(33411,65535)....)
                begin = block[0]
                end = block[1]
                block_count = end - begin
                print('Copying {} blocks into position {}...'.format(block_count, begin))

                # Position output file
                output_img.seek(begin * BLOCK_SIZE)

                # Copy one block at a time
                while (block_count > 0):
                    output_img.write(new_data_file.read(BLOCK_SIZE))
                    block_count -= 1
        else:
            print('Skipping command %s...' % command[0])

    # Make file larger if necessary
    if (output_img.tell() < max_file_size):
        output_img.truncate(max_file_size)

    output_img.close()
    new_data_file.close()
    print('Done! Output image: %s' % os.path.realpath(output_img.name))


if __name__ == '__main__':
    zip_file = sys.argv[1]

    print('unzip......')
    execute_cmd("unzip %s -d update" % zip_file)

    gen_img()

    execute_cmd("mkdir update/system")

    execute_cmd("mount -o loop -t ext4 update/system.img update/system")
