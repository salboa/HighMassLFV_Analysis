#!/usr/bin/python
import os
import sys
import subprocess
import getopt
import string

def main():
    # parse command line options
    try:
        opts, args = getopt.getopt(sys.argv[1:], "h", ["help"])
    except getopt.error, msg:
        print msg
        print "for help use --help"
        sys.exit(2)
    # process options
    for o, a in opts:
        if o in ("-h", "--help"):
            ShowDoc()
            sys.exit(0)

    #Assign None to all variable
    m_lfvType  = None
    m_useBjet  = None
    m_perVar   = None
    m_bands    = None
    m_useBlind = None
    # process arguments
    for arg in args:
        if arg.find('=') > -1:
            key,value = arg.split('=',1)

            if key=="lfvType":
                m_lfvType=value

            if key=="useBjet":
                m_useBjet=True

            if key=="onlyPerVar":
                m_perVar=True

            if key=="onlyBands":
                m_bands=True

            if key=="useBlind":
                m_useBlind=True

    print "-------------------------------------------------"
    if not m_lfvType:
        print "lfvType not set    -> exiting (options: 1, 2, 3 ) "
        exit(0)
    if not m_useBjet:
        print "useBjet not set    -> using default: 'False' "
        m_useBjet = False
    if not m_perVar:
        print "onlyPerVar not set -> using default: 'False' "
        m_perVar = False
    if not m_bands:
        print "onlyBands not set  -> using default: 'False' "
        m_bands = False
    if not m_useBlind:
        print "useBlind not set   -> using default: 'False' "
        m_useBlind = False
    print "-------------------------------------------------"
    print ""
    print "  Options set: "
    print " lfvType    = "+str(m_lfvType)
    print " useBjet    = "+str(m_useBjet)
    print " onlyPerVar = "+str(m_perVar)
    print " onlyBands  = "+str(m_bands)
    print " useBlind   = "+str(m_useBlind)
    print "-------------------------------------------------"
    print ""
    if not m_perVar and not m_bands:
        print "both onlyPerVar and onlyBands not set -> doing Both!!"
        m_perVar=True
        m_bands=True
    print  "-------------------------------------------------"
    
    makePerVarBands(m_lfvType,m_useBjet,m_perVar,m_bands,m_useBlind)


def makePerVarBands(lfvType, useBjet, perVar, bands, blind):

    if perVar:
        makePercentVariation(lfvType, useBjet, blind)
    if bands:
        makeBands(lfvType, useBjet, blind)
        

def makePercentVariation(lfvType, useBjet, blind):


    Htype = DefineComponents(True)

    for hist in Htype:

        RunCommand(hist,lfvType,useBjet,True,blind)


def makeBands(lfvType, useBjet, blind):

    Htype = DefineComponents(False)

    for hist in Htype:
        RunCommand(hist,lfvType,useBjet,False,blind)


def DefineComponents(isPerVar):

    comp = []

    if isPerVar:
        comp.append( "BkgTot"   )
    else:
        comp.append( "BkgSM"   )
        
    comp.append( "Top"      )
    comp.append( "DY"       )
    comp.append( "DiBoson"  )
    comp.append( "Multijet" )

    return comp


def RunCommand(hist,lfvType,useBjet,isPerVar,blind):

    prefs = []

    if isPerVar:
        prefs.append( "./SysPercentVariations" )
        if blind:
            prefs.append( "./SysPercentVariations --isBlind" )
    else:
        prefs.append( "./CreateSysBands" )
        if blind:
            prefs.append( "./CreateSysBands --isBlind" )
        
    for p in prefs:

        #cmd += p+" --Htype "+hist+" --lfvType "+lfvType
        cmd = p
        if isPerVar:
            cmd += " --Htype "+hist
        else:
            cmd += " --process "+hist

        cmd += " --lfvType "+lfvType
            
        if(useBjet):
            cmd += " --useBjet"
        
        print cmd
        os.system(cmd)


def ShowDoc():
    print ""
    print "Script to run SysPercentVariations and CreateSysBands in one shot!"
    print "  Usage : ./runPercVarsBands.py [Options]!"
    print "          Options:  "
    print "                   lfvType    = [1, 2, 3]    : value needed     "
    print "                   useBjet    = [True/False] : default is False "
    print "                   onlyPerVar = [True/False] : default is False "
    print "                   onlyBands  = [True/False] : default is False "
    print "                   useBlind   = [True/False] : default is False "
    
if __name__ == "__main__":
    main()
