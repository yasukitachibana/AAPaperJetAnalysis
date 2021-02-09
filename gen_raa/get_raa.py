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
    result[:,4] = np.nan_to_num( error_divide(dat_num[:,3],dat_num[:,4],dat_den[:,3],dat_den[:,4]) )
    
    return result
    
def get_raa(dir_pp, dir_AA):

    print('#pp dir: ', dir_pp)
    print('#AA dir: ', dir_AA)
    
    files_AA = glob.glob(os.path.join(dir_AA,'*.txt'))

    for fAA in files_AA:

        fpp = os.path.join(dir_pp,fAA.split()[-1])
        print('--pp file: ', fpp)
        print('--AA file: ', fAA)
        
        dat_pp = np.loadtxt(fpp, comments='#')
        dat_AA = np.loadtxt(fAA, comments='#')
        
        result = divide(dat_AA, dat_pp)
        
        filename = os.path.join(dir_AA,'raa_'+fAA.split()[-1])
        #np.savetxt(filename,result)


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



#import os

#import shutil
#import module_xml_out as xout
#import numpy as np
#import generate_qsub_command as qsc
#import itertools
#import submit_4_in_angle_analysis as sub4
#import set_path as spath
#
#test = 0
#
#
#def Main(argc,argvs):
#
#
#    #location = '/Users/yasukitachibana/Dropbox/Codes/SRC_OUT_IN_MGR'
#
#    location = spath.GetBuildPath()
#    #'/wsu/home/go/go54/go5410/SRC_OUT_IN/SRC_OUT_IN_MGR'
#
#    if argc < 3:
#        print('please specify event number and option')
#        exit()
#
#    n_ev = int(argvs[1])
#    print('event number input: '+str(n_ev))
#
#    option = argvs[2]
#    print('option: '+option)
#
#    option_tag = ''
#    if option == 'raw':
#        GetLiquidPart = GetLiquidPartRaw
#        option_tag = 'raw_'
#    elif option == 'iso':
#        GetLiquidPart = GetLiquidPartIso
#    else:
#        print('option error')
#        exit()
#
#
#    tagset = sub4.GetTags()
#
#    tags = tagset[0]
#    if argc >= 4:
#        print('tag is specified: '+str(int(argvs[3])))
#        tags = tagset[int(argvs[3])]
#    else:
#        #for tags in tagset:
#        tags = sub4.DecideTags(tagset)
#    print(tags)
#
#    #exit()
#
#    if len(tags)<=2:
#        print('no_hydro')
#
#
#
#
#
#    x = GetIx(location,tags)
#    n_ix = len(x[:,2])
#
#    init_infos = np.zeros((n_ev,5))
#
#    mass2 = np.zeros((n_ev,n_ix))
#    energy = np.zeros((n_ev,n_ix))
#    px = np.zeros((n_ev,n_ix))
#    py = np.zeros((n_ev,n_ix))
#    pz = np.zeros((n_ev,n_ix))
#
#    mass2_sh = np.zeros((n_ev,n_ix))
#    energy_sh= np.zeros((n_ev,n_ix))
#    px_sh = np.zeros((n_ev,n_ix))
#    py_sh = np.zeros((n_ev,n_ix))
#    pz_sh = np.zeros((n_ev,n_ix))
#
#    mass2_lq = np.zeros((n_ev,n_ix))
#    energy_lq= np.zeros((n_ev,n_ix))
#    px_lq = np.zeros((n_ev,n_ix))
#    py_lq = np.zeros((n_ev,n_ix))
#    pz_lq = np.zeros((n_ev,n_ix))
#
#    no_hydro = np.zeros(n_ev)
#
#    for i_ev in range(0,n_ev):
#
#        fluid_i = GetFluidInfo(location,tags,option,i_ev)
#
#        if fluid_i == 'false' and len(tags)>2:
#            no_hydro[i_ev] = 1
#            continue
#
#        #---------------------------------------------------------------------
#        init_i = GetInitInfo(location,tags,i_ev)
#        init_infos[i_ev,:] = init_i
#        #---------------------------------------------------------------------
#        energy_sh_i = GetShowerPart(location,tags,'energy',i_ev)
#        px_sh_i = GetShowerPart(location,tags,'px',i_ev)
#        py_sh_i = GetShowerPart(location,tags,'py',i_ev)
#        pz_sh_i = GetShowerPart(location,tags,'pz',i_ev)
#        mass2_sh_i = GetMass(energy_sh_i,px_sh_i,py_sh_i,pz_sh_i)
#
#        mass2_sh[i_ev,:] = mass2_sh_i
#        energy_sh[i_ev,:] = energy_sh_i
#        px_sh[i_ev,:] = px_sh_i
#        py_sh[i_ev,:] = py_sh_i
#        pz_sh[i_ev,:] = pz_sh_i
#        #---------------------------------------------------------------------
#        if len(tags)<=2:
#            continue
#        energy_lq_i = GetLiquidPart(location,tags,'energy',i_ev,x[:,2])
#        px_lq_i = GetLiquidPart(location,tags,'px',i_ev,x[:,2])
#        py_lq_i = GetLiquidPart(location,tags,'py',i_ev,x[:,2])
#        pz_lq_i = GetLiquidPart(location,tags,'pz',i_ev,x[:,2])
#        mass2_lq_i = GetMass(energy_lq_i,px_lq_i,py_lq_i,pz_lq_i)
#
#        mass2_lq[i_ev,:] = mass2_lq_i
#        energy_lq[i_ev,:] = energy_lq_i
#        px_lq[i_ev,:] = px_lq_i
#        py_lq[i_ev,:] = py_lq_i
#        pz_lq[i_ev,:] = pz_lq_i
#        #---------------------------------------------------------------------
#        energy_i = energy_sh_i + energy_lq_i
#        px_i = px_sh_i + px_lq_i
#        py_i = py_sh_i + py_lq_i
#        pz_i = pz_sh_i + pz_lq_i
#        mass2_i = GetMass(energy_i,px_i,py_i,pz_i)
#
#        mass2[i_ev,:] = mass2_i
#        energy[i_ev,:] = energy_i
#        px[i_ev,:] = px_i
#        py[i_ev,:] = py_i
#        pz[i_ev,:] = pz_i
#    #---------------------------------------------------------------------
#    #---------------------------------------------------------------------
#    i_hydro = np.where(no_hydro==0)
#    n_ev_true = len(no_hydro[i_hydro])
#    if n_ev_true == 0:
#        print('error!!, exit')
#        exit()
#    print('number of events with valid data: '+str(n_ev_true))
#    #---------------------------------------------------------------------
#    mass2_sh = mass2_sh[i_hydro]
#    energy_sh = energy_sh[i_hydro]
#    px_sh = px_sh[i_hydro]
#    py_sh = py_sh[i_hydro]
#    #
#    mass2_lq = mass2_lq[i_hydro]
#    energy_lq = energy_lq[i_hydro]
#    px_lq = px_lq[i_hydro]
#    py_lq = py_lq[i_hydro]
#    #
#    mass2 = mass2[i_hydro]
#    energy = energy[i_hydro]
#    px = px[i_hydro]
#    py = py[i_hydro]
#    #---------------------------------------------------------------------
#    #---------------------------------------------------------------------
#def GetOutputDerivatives(location,tags,label,x,data,n_ev_true):
#
#    delta = np.zeros( (len(data[:,0]),len(data[0,:]))      )
#    delta[:,0] = data[:,0]
#    delta[:,1:] = data[:,1:] - data[:,:-1]
#
#    avr = np.average(delta, axis = 0)
#    err = np.std(delta, axis = 0)/np.sqrt(n_ev_true)
#
#    x_width = x[:,2]-x[:,0]
#
#    avr = avr/x_width
#    err = err/x_width
#
#    result = np.zeros( ( len(avr), 5) )
#    result[:,:3] = x
#    result[:,3] = avr
#    result[:,4] = err
#
#    filename = GetOutputFileName(location,tags,'del_'+label)
#    print("save file: "+filename)
#    np.savetxt(filename,result)
#
#def GetOutput(location,tags,label,x,data,n_ev_true):
#
#    avr = np.average(data, axis = 0)
#    err = np.std(data, axis = 0)/np.sqrt(n_ev_true)
#
#    result = np.zeros( ( len(avr), 5) )
#    result[:,:3] = x
#    result[:,3] = avr
#    result[:,4] = err
#
#    filename = GetOutputFileName(location,tags,label)
#    print("save file: "+filename)
#    np.savetxt(filename,result)
#
#def GetFluidInfo(location,tags,option,i_ev):
#    if len(tags)<=2:
#        return 'true'
#    option_tag = ''
#    if option == 'raw':
#        option_tag = 'raw_'
#    filename = GetLiquidFileName(location,tags,'energy',option_tag,i_ev)
#    if os.path.exists(filename):
#        return 'true'
#    print('skip: '+filename)
#    return 'false'
#
#def GetLiquidPartRaw(location,tags,label,i_ev,x_r):
#    filename = GetLiquidFileName(location,tags,label,'raw_',i_ev)
#    dat = np.loadtxt(filename, comments='#')
#    return dat[:,3]
#
#
#def GetInitInfo(location,tags,i_ev):
#    filename = GetInitInfoFileName(location,tags,i_ev)
#    dat = np.loadtxt(filename, comments='#')
#    return dat[:,3]
#
#def GetShowerPart(location,tags,label,i_ev):
#    filename = GetShowerFileName(location,tags,label,i_ev)
#    dat = np.loadtxt(filename, comments='#')
#    return dat[:,3]
#
#def GetLiquidPartIso(location,tags,label,i_ev,x_r):
#    filename = GetLiquidFileName(location,tags,label,'',i_ev)
#    dat = np.loadtxt(filename, comments='#')
#    x_old = dat[:,2]
#    y_old = dat[:,3]
#    from scipy.interpolate import interp1d
#    f = interp1d(x_old, y_old, kind = 'cubic', fill_value="extrapolate")
##    test = np.ones((len(x_r),2))
##    test[:,0]=x_r
##    test[:,1]=f(x_r)
##    np.savetxt(label+'test.txt',test)
#    return f(x_r)
#
#
#
############################################################################################
#def GetInitInfoFileName(location,tags,i_ev):
#    dir = os.path.join(location,'Data',tags[0],tags[1])
#    filename = 'ev'+str(i_ev)+'init_momentum.txt'
#    return os.path.join(dir,filename)
#
#def GetShowerFileName(location,tags,label,i_ev):
#    dir = os.path.join(location,'Data',tags[0],tags[1])
#    filename = 'ev'+str(i_ev)+'_'+label+'_vs_theta.txt'
#    return os.path.join(dir,filename)
#
#def GetLiquidFileName(location,tags,label,option,i_ev):
#    dir = os.path.join(location,'Data',tags[0],tags[1],tags[2])
#    filename = 'ev'+str(i_ev)+'_'+option+label+'_vs_theta.txt'
#    return os.path.join(dir,filename)
#
#def GetOutputFileName(location,tags,label):
#    dir = os.path.join(location,'Data',tags[0],tags[1])
#    if len(tags)>2:
#        dir = os.path.join(dir,tags[2])
#    filename = 'avr_'+label+'_vs_theta.txt'
#    return os.path.join(dir,filename)
############################################################################################

