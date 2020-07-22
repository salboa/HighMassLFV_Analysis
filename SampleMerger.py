#!/usr/bin/python
import os
import sys
import subprocess
import getopt
import string
import argparse
from Backgrounds import *
from Signals import *


parser = argparse.ArgumentParser()
parser.add_argument("--inputDir" , type=str           , default=""   ,
                    help="input directory [Needed value]"                )
parser.add_argument("--outputDir", type=str           , default=""   ,
                    help="output directory [Needed value]"               )
parser.add_argument("--type"     , type=str           , default="Bkg",
                    help="possibile values: Bkg, Wjets, ttV, ttSys, Sig" )
parser.add_argument("--debug"    , action='store_true', default=False,
                    help="enabling debug mode"                           )
args = parser.parse_args()


def main():

    InMCDir  = "Ntuples/"+args.inputDir
    OutMCDir = "Ntuples/"+args.outputDir

    if not os.path.exists(OutMCDir):
        print "directory '"+OutMCDir+"' not present!!! Creating ..."
        os.makedirs(OutMCDir)

    Samples = None
    if args.type=="Bkg" :
        Samples = Backgrounds
    elif args.type=="Wjets":
        Samples = Wjets
    elif args.type=="ttV":
        Samples = ttV
    elif args.type=="ttSys":
        Samples = ttbar_Sys
    elif args.type=="Sig":
        Samples = Signals

    if args.debug:
        print "  <SampleMerger>:  InputDir = "+InMCDir+" , OutputDir = "+OutMCDir
        print "                   type = "+args.type


    #strating the merging
    for sam in Samples:
    
        print "  <SampleMerger>: Merging sample "+sam[0]+" (ChanNum = "+sam[1]+")"
    
        FilesPath = InMCDir+"/"+"user.salvucci*MC_DSID*"+sam[1]+"*/*"
        OutName   = sam[0]+".root"
        cmd = "hadd -f "+OutMCDir+"/"+OutName+" "+FilesPath
    
        if args.debug:
            print cmd
            
        os.system(cmd)
    
        print ""
        print ""


if __name__ == "__main__":
    main()
