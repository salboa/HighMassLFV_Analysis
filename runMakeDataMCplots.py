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
    m_lfvType   = None
    m_useBjet   = None
    m_isBlind   = None
    m_splitQCD  = None
    m_useSignal = None
    m_addStat   = None
    # process arguments
    for arg in args:
        if arg.find('=') > -1:
            key,value = arg.split('=',1)

            if key=="lfvType":
                m_lfvType=value

            if key=="useBjet":
                m_useBjet=True

            if key=="isBlind":
                m_isBlind=True

            if key=="splitQCD":
                m_splitQCD=True

            if key=="useSignal":
                m_useSignal=True

            if key=="addStat":
                m_addStat=True

    print "-------------------------------------------------"
    if not m_lfvType:
        print "lfvType not set    -> exiting (options: 1, 2, 3 ) "
        exit(0)
    if not m_useBjet:
        print "useBjet not set    -> using default: 'False' "
        m_useBjet = False
    if not m_isBlind:
        print "isBlind not set    -> using default: 'False' "
        m_isBlind = False
    if not m_splitQCD:
        print "splitQCD not set   -> using default: 'False'"
        m_splitQCD = False
    if not m_useSignal:
        print "useSignal not set  -> using default: 'False'"
        m_useSignal = False
    if not m_addStat:
        print "addStat not set    -> using default: 'False'"
        m_addStat = False
    if m_splitQCD and m_lfvType==1:
        print "splitQCD enabled but running on emu channel: switching off!"
        m_splitQCD = False
    print "-------------------------------------------------"
    print ""
    print "  Options set: "
    print " lfvType   = "+str(m_lfvType)
    print " useBjet   = "+str(m_useBjet)
    print " isBlind   = "+str(m_isBlind)
    print " splitQCD  = "+str(m_splitQCD)
    print " useSignal = "+str(m_useSignal)
    print " addStat   = "+str(m_addStat)
    print "-------------------------------------------------"
    print ""
    
    makeDataMCplots(m_lfvType,m_useBjet,m_isBlind,m_splitQCD,
                    m_useSignal,m_addStat)


def makeDataMCplots(lfvType, useBjet, isBlind, splitQCD, useSignal, addStat):


    Htype = DefineComponents(lfvType)

    for hist in Htype:

        RunCommand(hist,lfvType,useBjet,isBlind,splitQCD,useSignal,addStat)


def DefineComponents(lfvType):

    comp = []

    comp.append( "mllCorr"    )
    comp.append( "mllCorr_MC" )
    comp.append( "ptllCorr"   )
    comp.append( "etall"      )
    comp.append( "phill"      )
    comp.append( "met"        )
    comp.append( "njet"       )
    if int(lfvType)!=2:
        comp.append( "mu_pt"  )
        comp.append( "mu_eta" )
        comp.append( "mu_phi" )
    if int(lfvType)!=3:
        comp.append( "el_pt"  )
        comp.append( "el_eta" )
        comp.append( "el_phi" )
    if int(lfvType)!=1:
        comp.append( "ta_pt"  )
        comp.append( "ta_eta" )
        comp.append( "ta_phi" )

    return comp


def RunCommand(hist, lfvType, useBjet, isBlind, splitQCD, useSignal, addStat):

    cmd = "./MakeDataMCplots --useSysBand --lfvType "+lfvType+" "

    if isBlind and hist=="mllCorr":
        useSignal=False

    if addStat:
        cmd += "--addStatInBand "
        
    if hist!="mllCorr_MC":
        cmd += "--useData "

    if hist=="mllCorr_MC":
        cmd += "--Htype mllCorr "
    else:
        cmd += "--Htype "+hist+" "

    if useBjet:
        cmd += "--useBjet "

    if isBlind and hist!="mllCorr_MC":
        cmd += "--isBlind "

    if splitQCD:
        cmd += "--showQCD "

    if useSignal:
        cmd += "--useSignal "
    
    print cmd
    os.system(cmd)


def ShowDoc():
    print ""
    print "Script to run MakeDataMCplots to make Data/MC plots in one shot!"
    print "  Usage : ./runMakeDataMCplots.py [Options]!"
    print "          Options:  "
    print "                   lfvType   = [1, 2, 3]    : value needed "
    print "                   useBjet   = [True/False] : default is False "
    print "                   isBlind   = [True/False] : default is False "
    print "                   splitQCD  = [True/False] : default is False "
    print "                   useSignal = [True/False] : default is False "
    print "                   addStat   = [True/False] : defualt is False "
        
if __name__ == "__main__":
    main()
