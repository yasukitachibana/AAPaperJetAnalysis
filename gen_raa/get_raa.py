import sys
import glob
import os
import numpy as np


def error_divide(val_num, err_num, val_den, err_den):
    a = err_num/val_den
    b = err_den*val_num/val_den/val_den
    return np.sqrt(a*a+b*b)

def divide(dat_num, dat_den):

    result = np.zeros( ( len(dat_num[:,0]), 5) )
    result[:,0:3] = dat_num[:,0:3]
    result[:,3] = np.nan_to_num( dat_num[:,3]/dat_den[:,3] , nan=0 )
    result[:,4] = np.nan_to_num( error_divide(dat_num[:,3],dat_num[:,4],dat_den[:,3],dat_den[:,4]), nan=0  )
    
    return result
    
def file_excluded(filename):

    a = filename.startswith('raa')
    b = filename.startswith('CMake')
    c = filename.startswith('hist')
    d = filename.startswith('count')
    e = filename.startswith('sideband')
    
    if a or b or c or d or e:
        return True
    else:
        return False
    
    
def get_raa(dir_pp, dir_AA):

    print('#pp dir: ', dir_pp)
    print('#AA dir: ', dir_AA)
    search = os.path.join(dir_AA,'*.txt') 

    files_AA = glob.glob(search)
   
    for fAA in files_AA:
    
        filename = os.path.basename(fAA)

        if file_excluded(filename):
            continue

        fpp = os.path.join(dir_pp,filename)
        print('#\n--pp file: ', fpp)
        print('--AA file: ', fAA)
        
        dat_pp = np.loadtxt(fpp, comments='#')
        dat_AA = np.loadtxt(fAA, comments='#')
        
        result = divide(dat_AA, dat_pp)
        #print(result)
        
        file_path = os.path.join( os.path.dirname(fAA) ,'raa_'+filename)
        print('->generating raa file: ', file_path)
        np.savetxt(file_path,result)


def main():

    import argparse
    parser = argparse.ArgumentParser()
    
    parser.add_argument("--pp", type=str, default="No Input For pp")
    parser.add_argument("--AA", type=str, default="No Input For AA")
    args = parser.parse_args()

    args_error_exit( args )
    dir_pp = args.pp
    dir_AA = args.AA

    get_raa(dir_pp, dir_AA)
    

def args_error( arg, ppAA ):
    if arg == "No Input For {}".format(ppAA):
        print(arg, ' Specify Input Directory for {} with --{}'.format(ppAA,ppAA) )
        return False
    return True

def args_error_exit( args ):
    pp = args_error( args.pp, 'pp' )
    aa = args_error( args.AA, 'AA' )
    if not pp or not aa:
        print('Exit.')
        exit()

if __name__ == '__main__':
    main()
