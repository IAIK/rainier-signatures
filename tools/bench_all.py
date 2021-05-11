#!/usr/bin/env python3
import sys
import os

executable = "./bench_free"
parser = "./"
logfile = "bench_output.txt"
iterations = 100

# kappa, N, Tau
parameters = [
    (128, 3, 4, 65),
    (128, 3, 8, 44),
    (128, 3, 16, 33),
    (128, 3, 32, 27),
    (128, 3, 64, 23),
    (128, 3, 128, 20),
    (128, 3, 256, 17),
    (128, 3, 512, 16),
    (128, 3, 1024, 14),
    (128, 3, 2048, 13),
    (128, 3, 4096, 12),
    (128, 3, 8192, 11),
    (128, 3, 32768, 10),
    (128, 3, 65536, 9),
    (192, 3, 16, 49),
    (192, 3, 32, 40),
    (192, 3, 64, 33),
    (192, 3, 128, 29),
    (192, 3, 256, 25),
    (256, 3, 16, 65),
    (256, 3, 32, 53),
    (256, 3, 64, 44),
    (256, 3, 128, 38),
    (256, 3, 256, 33),
]

min_parameters = [
    (128, 3, 4, 65),
    (128, 3, 8, 44),
    (128, 3, 16, 33),
    (128, 3, 31, 27),
    (128, 3, 48, 24),
    (128, 3, 57, 23),
    (128, 3, 69, 22),
    (128, 3, 85, 21),
    (128, 3, 107, 20),
    (128, 3, 139, 19),
    (128, 3, 185, 18),
    (128, 3, 256, 17),
    (128, 3, 371, 16),
    (128, 3, 565, 15),
    (128, 3, 920, 14),
    (128, 3, 1624, 13),
    (128, 3, 3180, 12),
    (128, 3, 7121, 11),
    (128, 3, 19077, 10),
    (128, 3, 65384, 9),
    (192, 3, 8, 65),
    (192, 3, 16, 49),
    (192, 3, 31, 40),
    (192, 3, 64, 33),
    (192, 3, 116, 29),
    (192, 3, 256, 25),
    (192, 3, 424, 23),
    (192, 3, 776, 21),
    (192, 3, 1625, 19),
    (192, 3, 4094, 17),
    (192, 3, 13430, 15),
    (192, 3, 65466, 13),
    (256, 3, 16, 65),
    (256, 3, 31, 53),
    (256, 3, 62, 44),
    (256, 3, 121, 38),
    (256, 3, 256, 33),
    (256, 3, 455, 30),
    (256, 3, 921, 27),
    (256, 3, 1626, 25),
    (256, 3, 3183, 23),
    (256, 3, 11371, 20),
    (256, 3, 65496, 17)

]

SCALING_FACTOR = 1000 * 3600


def parse_bench(filename):
    with open(filename, "r") as f:
        content = f.read()

    testruns = content.split("Instance: ")
    if len(testruns) > 1:
        testruns.pop(0)

    for test in testruns:
        lines = test.splitlines()
        # first line is instance:
        # print(lines[0])
        lines.pop(0)
        # second line is header:
        # print(lines[0])
        lines.pop(0)

        count = 0
        keygen, sign, ver, size = 0, 0, 0, 0

        for line in lines:
            if len(line.strip()) == 0:
                continue
            vals = line.strip().split(",")
            keygen += int(vals[0])
            sign += int(vals[1])
            ver += int(vals[2])
            size += int(vals[3])
            count += 1

        keygen = (keygen / SCALING_FACTOR) / count
        sign = (sign / SCALING_FACTOR) / count
        ver = (ver / SCALING_FACTOR) / count
        size = float(size) / count
        print("{:.2f} & {:.2f} & {:.0f} \\\\".format(
            sign, ver, size))


for kappa,rounds, N, tau in min_parameters:
    os.system("{executable} -i {iter} {kappa} {rounds} {N} {tau} > {logfile}".format(
        executable=executable, iter=iterations, kappa=kappa/8, N=N, tau=tau, rounds=rounds, logfile=logfile))
    print("{kappa} & {N} & {tau} & ".format(kappa=kappa, N=N, tau=tau), end="")
    parse_bench(logfile)
