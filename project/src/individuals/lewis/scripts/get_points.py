critical_points_file = open('critical_points.txt', 'r')

lines = critical_points_file.readlines()

for line in lines:
    comps_int = [int(c) for c in line.split()]

    x = comps_int[0] / 512.0 * 2.0 - 1.0
    y = comps_int[1] / 512.0 * 2.0 - 1.0

    print(str(x) + " " + str(y))

# Output

# 0.1015625 -0.65234375
# 0.3359375 -0.63671875
# 0.42578125 -0.64453125
# 0.60546875 -0.8984375
# 0.0625 -0.921875