def process_line(line):
    data = line.split(",")[:3]
    return "{0} {1} {2}\n".format(data[0], data[1], data[2])


if __name__ == "__main__":
    with open("sTree.txt", 'r') as ptx, open("sTree" + ".pcd", 'w') as pcd:
        col = 94803
        row = 1
        pcd_head = '''# .PCD v0.7 - Point Cloud Data file format
    VERSION 0.7
    FIELDS x y z
    SIZE 4 4 4
    TYPE F F F
    COUNT 1 1 1
    WIDTH {0}
    HEIGHT {1}
    VIEWPOINT 0 0 0 1 0 0 0
    POINTS {2}
    DATA ascii\n'''.format(col, row, col * row)
        pcd.writelines(pcd_head)
        count = 0
        line = ptx.readline()
        while line:
            pcd.write(process_line(line))
            count += 1
            line = ptx.readline()
        ptx.close()
        pcd.close()
