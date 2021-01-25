import os
import argparse
import subprocess


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="")
    parser.add_argument('-p', '--problem', help="problem ID")
    parser.add_argument('-t', '--type', help="type of code")
    args=parser.parse_args()

    path = os.path.join('/data', '%04d'%(int(args.problem)))
    program = os.path.join(path, 'program')
    Compile = subprocess.Popen('./'+args.type+'.sh ' + program, shell=True, cwd='/compile', stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    try:
        Compile.wait(20)
    except subprocess.TimeoutExpired:
        Compile.terminate()
        print(' '.join(['CompileTimeout', '0', '0']))
        exit()
        
    if Compile.returncode:
        result = ['CompileError', '0', '0']
    else:
        result = subprocess.run(['python3', 'judge.py', '-ai', 'program'], encoding='utf-8', cwd=path, stdout=subprocess.PIPE, stderr=subprocess.PIPE).stdout.split()
    print(' '.join(result))
