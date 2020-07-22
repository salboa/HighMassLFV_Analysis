#!/usr/bin/python
import os
import sys
import subprocess
import getopt
import string
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--process"   , type=str,            default="Background" ,
                    help="Define process to run: default is 'Background'" )
parser.add_argument("--useBjet"   , action='store_true', default=False        ,
                    help="Enable b-jet veto: default is 'False'"          )
parser.add_argument("--useSmooth" , action='store_true', default=False        ,
                    help="Enable smoothed qcd mll: default is 'False'"    )
parser.add_argument("--sigShapes" , action='store_true', default=False        ,
                    help="Save signal shapes: default is 'False'"         )
parser.add_argument("--lfvType"   , type=int           , default=-1           ,
                    help="Choose lfv channel: options are '1,2,3'"        )
parser.add_argument("--debug"     , action='store_true', default=False        ,
                    help="enabling debug mode"                            )
args = parser.parse_args()


def main():

    if args.lfvType<0:
        print "<runLimitInputs>: lfvType not defined!!! Exiting ... "
        exit(0)

    if args.debug:
        print "<runLimitInputs>:  lfvType   = "+str(args.lfvType)
        print "                   useBjet   = "+str(args.useBjet)
        print "                   process   = "+args.process
        print "                   useSmooth = "+str(args.useSmooth)
        print "                   sigShapes = "+str(args.sigShapes)


    cmd = "./LimitInputs --lfvType "+str(args.lfvType)
    if args.useBjet:
        cmd += " --useBjet "
    
    os.system( cmd )
    if args.lfvType==1:
        os.system( cmd+" --useSmooth" )
        
    if args.sigShapes:
        signals = GetSignals()
        cmd += " --sigShapes"
        for sig in signals:
            os.system( cmd+" --sigShapes --process "+sig )
            
        
def GetSignals():

    signals = []

    signals.append( "Zprime0500" )
    signals.append( "Zprime0600" )
    signals.append( "Zprime0700" )
    signals.append( "Zprime0800" )
    signals.append( "Zprime0900" )
    signals.append( "Zprime1000" )
    signals.append( "Zprime1100" )
    signals.append( "Zprime1200" )
    signals.append( "Zprime1300" )
    signals.append( "Zprime1400" )
    signals.append( "Zprime1500" )
    signals.append( "Zprime1600" )
    signals.append( "Zprime1700" )
    signals.append( "Zprime1800" )
    signals.append( "Zprime1900" )
    signals.append( "Zprime2000" )
    signals.append( "Zprime2200" )
    signals.append( "Zprime2400" )
    signals.append( "Zprime2600" )
    signals.append( "Zprime2800" )
    signals.append( "Zprime3000" )
    signals.append( "Zprime3500" )
    signals.append( "Zprime4000" )
    signals.append( "Zprime4500" )
    signals.append( "Zprime5000" )
    signals.append( "QBH1000_n1" )
    signals.append( "QBH1500_n1" )
    signals.append( "QBH2000_n1" )
    signals.append( "QBH2500_n1" )
    signals.append( "QBH3000_n1" )
    signals.append( "QBH3000_n6" )
    signals.append( "QBH3500_n1" )
    signals.append( "QBH3500_n6" )
    signals.append( "QBH4000_n1" )
    signals.append( "QBH4000_n6" )
    signals.append( "QBH4500_n1" )
    signals.append( "QBH4500_n6" )
    signals.append( "QBH5000_n1" )
    signals.append( "QBH5000_n6" )
    signals.append( "QBH5500_n1" )
    signals.append( "QBH5500_n6" )
    signals.append( "QBH6000_n1" )
    signals.append( "QBH6000_n6" )
    signals.append( "QBH6500_n6" )
    signals.append( "QBH7000_n6" )
    signals.append( "QBH7500_n6" )
    signals.append( "QBH8000_n6" )
    signals.append( "SVT0500"    )
    signals.append( "SVT0600"    )
    signals.append( "SVT0700"    )
    signals.append( "SVT0800"    )
    signals.append( "SVT0900"    )
    signals.append( "SVT1000"    )
    signals.append( "SVT1100"    )
    signals.append( "SVT1200"    )
    signals.append( "SVT1300"    )
    signals.append( "SVT1400"    )
    signals.append( "SVT1500"    )
    signals.append( "SVT1600"    )
    signals.append( "SVT1700"    )
    signals.append( "SVT1800"    )
    signals.append( "SVT1900"    )
    signals.append( "SVT2000"    )
    signals.append( "SVT2200"    )
    signals.append( "SVT2400"    )
    signals.append( "SVT2600"    )
    signals.append( "SVT2800"    )
    signals.append( "SVT3000"    )
    signals.append( "SVT3500"    )
    signals.append( "SVT4000"    )
    signals.append( "SVT4500"    )
    signals.append( "SVT5000"    )
    
    return signals

if __name__ == "__main__":
    main()
