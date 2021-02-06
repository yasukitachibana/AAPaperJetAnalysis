import os
import sys
import pathlib
import re
import numpy as np



def generate(args):

    xml, input, output = manage_path(args.xml, args.input, args.output)
    Mkdirs(output)

    command_head = 'python slurm_sub.py --p {} --time {} --mem {} --n {} --o {} --e {} --c {}'
    command_head = command_head.format(args.p, args.time, args.mem, args.n, args.o, args.e, args.c)

    print('Exe:', command_head)
    #os.system(command)
    print("#################\n")
    print("\n")
    
    
    
def manage_path(xml, input, output):
    cwd = os.getcwd()
    xml = os.path.join(cwd,xml)
    input = os.path.join(cwd,input)
    output = os.path.join(cwd,output)
    return xml, input, output

def Mkdirs(path):
    if not os.path.isdir(path):
        print('creating "'+path+'" directory')
        os.makedirs(path)
    
    
def main():

    import argparse

    parser = argparse.ArgumentParser()
    
    
    parser.add_argument("--p", type=str, default="primary")
    parser.add_argument("--time", type=str, default="720:00:00")
    parser.add_argument("--mem", type=str, default="16G")
    
    parser.add_argument("--e", type=str, default="/dev/null")
    parser.add_argument("--o", type=str, default="/dev/null")

    parser.add_argument("--root", type=str, default="ON")
    parser.add_argument("--d", type=str, default="../build")

    parser.add_argument("--n", type=str, default="jet_analysis")

    parser.add_argument("--c", type=str, default="./Main")

    parser.add_argument("--xml", type=str, default="")
    parser.add_argument("--input", type=str, default="")
    parser.add_argument("--output", type=str, default="")
    
    args = parser.parse_args()

    generate(args)




if __name__ == '__main__':
    main()
