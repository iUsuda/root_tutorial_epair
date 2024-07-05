import os
import sys
import subprocess

args = sys.argv
argc = len(args)

if argc != 3:
    print("Error")
    sys.exit(1)

start_pl = int(args[1])
end_pl = int(args[2])

output_rootfile = "EventAbsUnit15PL{0:03d}-{1:03d}.root".format(start_pl, end_pl)
if os.path.isfile(output_rootfile):
    os.remove(output_rootfile)

cmd = "hadd {}".format(output_rootfile)
for pl in range(start_pl, end_pl + 1, 1):
    cmd = cmd + " ..\\..\\PL{0:03d}\\6-EventAbs\\EventAbsUnit15PL{0:03d}-{0:03d}.root".format(pl)

print(cmd)
subprocess.run(cmd)