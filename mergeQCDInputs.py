#!/usr/bin/python
import os
import sys
import subprocess
import getopt
import string

#Channels
etau_Chan  = 2
mutau_Chan = 3

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
    m_addSyst  = None
    m_ttbarCR  = None
    m_revDphi  = None
    m_useBjet  = None
    m_Blind    = None
    m_isSherpa = None
    # process arguments
    for arg in args:
        if arg.find('=') > -1:
            key,value = arg.split('=',1)

            if key=="lfvType":
                m_lfvType=value

            if key=="addSyst":
                m_addSyst=True

            if key=="ttbarCR":
                m_ttbarCR=True

            if key=="useBjet":
                m_useBjet=True

            if key=="isBlind":
                m_Blind=True

            if key=="isRevDphi":
                m_revDphi=True

            if key=="useSherpa":
                m_isSherpa=True

    print "-------------------------------------------------"
    if not m_lfvType:
        print "lfvType not set   -> exiting (options: 2,3) "
        exit(0)
    if not m_addSyst:
        print "addSyst not set   -> using default: 'False' "
        m_addSyst = False
    if not m_ttbarCR:
        print "ttbarCR not set   -> using default: 'False' "
        m_ttbarCR = False
    if not m_useBjet:
        print "useBjet not set   -> using default: 'False' "
        m_useBjet = False
    if not m_Blind:
        print "isBlind not set   -> using default: 'False' "
        m_Blind = False
    if not m_revDphi:
        print "isRevDphi not set -> using default: 'False' "
        m_revDphi = False
    if not m_isSherpa:
        print "useSherpa noy set -> using default: 'Fakse' "
        m_isSherpa = False
    print "-------------------------------------------------"
    print ""
    print "  Options set: "
    print " lfvType     = "+str(m_lfvType)
    print " addSyst     = "+str(m_addSyst)
    print " ttbarCR     = "+str(m_ttbarCR)
    print " useBjet     = "+str(m_useBjet)
    print " isBlind     = "+str(m_Blind)
    print " isRevDphi   = "+str(m_revDphi)
    print " useSherpa   = "+str(m_isSherpa)
    print "-------------------------------------------------"


    mergeQCDInputs(m_lfvType,m_addSyst,m_ttbarCR,m_useBjet,
                   m_Blind,m_revDphi,m_isSherpa)


def mergeQCDInputs(lfvType,
                   addSyst,
                   ttbarCR,
                   useBjet,
                   blind,
                   revDphi,
                   useSherpa):

    
    #Set LFV Channels
    LFVtype = int(lfvType)

    #Set Directories where merge
    Dirs = SetDirectories(useBjet,ttbarCR,revDphi,useSherpa)
    
    for dir in Dirs:

        #Set Systematics list
        Systs = DefineSystematics(LFVtype,addSyst,useBjet,ttbarCR)

        for sys in Systs:

            #CreateCommand
            print "Merging QCD files for lfvType = "+str(LFVtype)+" dir = "+dir+" syst = "+sys
            cmd = GetRunCommand(LFVtype,dir,sys,blind)
            print cmd
            os.system(cmd)
            print " "


def SetDirectories(m_useBjet,m_ttbarCR,m_revDphi,m_useSherpa):

    dirs = []

    dirPrefix=""
    if m_useBjet:
        dirPrefix = "Bjet/"
    else:
        dirPrefix = "NoBjet/"

    if m_ttbarCR:
        dirPrefix += "ttbarCR"
        if m_useSherpa:
            dirPrefix += "_Sherpa"
        dirPrefix += "/"

    if m_revDphi:
        dirPrefix += "revDphi/"
        
    dirs.append( dirPrefix+"QcdReg3/" )
    dirs.append( dirPrefix+"QcdReg1_SS/" )
    if not m_ttbarCR and not m_revDphi:
        dirs.append( dirPrefix+"QcdReg3_SS/" )
        dirs.append( dirPrefix+"QcdReg3_OS/" )
        dirs.append( dirPrefix+"QcdReg1_OS/" )    
        
    return dirs


def DefineSystematics(m_lfvType,m_addSyst,m_useBjet,m_ttbarCR):

    systs = []

    systs.append("Nominal")

    if m_addSyst:

        if m_lfvType==mutau_Chan:
            systs.append( "MuReco_StatUp"    )
            systs.append( "MuReco_StatDown"  )
            systs.append( "MuReco_SysUp"     )
            systs.append( "MuReco_SysDown"   )
            systs.append( "MuIso_StatUp"     )
            systs.append( "MuIso_StatDown"   )
            systs.append( "MuIso_SysUp"      )
            systs.append( "MuIso_SysDown"    )
            systs.append( "MuTrg_StatUp"     )
            systs.append( "MuTrg_StatDown"   )
            systs.append( "MuTrg_SysUp"      )
            systs.append( "MuTrg_SysDown"    )
            systs.append( "MuTTVA_StatUp"    )
            systs.append( "MuTTVA_StatDown"  )
            systs.append( "MuTTVA_SysUp"     )
            systs.append( "MuTTVA_SysDown"   )
            systs.append( "MuSmeID_SysUp"    )
            systs.append( "MuSmeID_SysDown"  )
            systs.append( "MuSmeMS_SysUp"    )
            systs.append( "MuSmeMS_SysDown"  )
            systs.append( "MuScale_SysUp"    )
            systs.append( "MuScale_SysDown"  )
            systs.append( "MuSagRho_SysUp"   )
            systs.append( "MuSagRho_SysDown" )
            systs.append( "MuSagRes_SysUp"   )
            systs.append( "MuSagRes_SysDown" )
            
        if m_lfvType==etau_Chan:
            systs.append( "ElReco_SysUp"    )
            systs.append( "ElReco_SysDown"  )
            systs.append( "ElID_SysUp"      )
            systs.append( "ElID_SysDown"    )
            systs.append( "ElIso_SysUp"     )
            systs.append( "ElIso_SysDown"   )
            systs.append( "ElTrg_SysUp"     )
            systs.append( "ElTrg_SysDown"   )
            systs.append( "ElSme_SysUp"     )
            systs.append( "ElSme_SysDown"   )
            systs.append( "ElScale_SysUp"   )
            systs.append( "ElScale_SysDown" )
                
        if m_lfvType==etau_Chan or m_lfvType==mutau_Chan:
            systs.append( "TaReco_SysUp"       )
            systs.append( "TaReco_SysDown"     )
            systs.append( "TaRecoHpt_SysUp"    )
            systs.append( "TaRecoHpt_SysDown"  )
            systs.append( "TaEleOlr_SysUp"     )
            systs.append( "TaEleOlr_SysDown"   )
            systs.append( "TaJetID_SysUp"      )
            systs.append( "TaJetID_SysDown"    )
            systs.append( "TaJetIDHpt_SysUp"   )
            systs.append( "TaJetIDHpt_SysDown" )
            systs.append( "TaSme_SysUp"        )
            systs.append( "TaSme_SysDown"      )
            systs.append( "TaSmeDet_SysUp"     )
            systs.append( "TaSmeDet_SysDown"   )
            systs.append( "TaSmeMod_SysUp"     )
            systs.append( "TaSmeMod_SysDown"   )
            
        systs.append( "JtJvtSF_SysUp"    )
        systs.append( "JtJvtSF_SysDown"  )
        systs.append( "JtSme_SysUp"      )
        systs.append( "JtUncNP1_SysUp"   )
        systs.append( "JtUncNP1_SysDown" )
        systs.append( "JtUncNP2_SysUp"   )
        systs.append( "JtUncNP2_SysDown" )
        systs.append( "JtUncNP3_SysUp"   )
        systs.append( "JtUncNP3_SysDown" )
        systs.append( "JtUncETA_SysUp"   )
        systs.append( "JtUncETA_SysDown" )
        systs.append( "MetResPara"       )
        systs.append( "MetResPer"        )
        systs.append( "MetScl_SysUp"     )
        systs.append( "MetScl_SysDown"   )
        systs.append( "PU_SysUp"         )
        systs.append( "PU_SysDown"       )
            
        if m_useBjet:
            systs.append( "BtagSF_Beff_SysUp"      )
            systs.append( "BtagSF_Beff_SysDown"    )
            systs.append( "BtagSF_Ceff_SysUp"      )
            systs.append( "BtagSF_Ceff_SysDown"    )
            systs.append( "BtagSF_Leff_SysUp"      )
            systs.append( "BtagSF_Leff_SysDown"    )
            systs.append( "BtagSF_ExtCeff_SysUp"   )
            systs.append( "BtagSF_ExtCeff_SysDown" )
            systs.append( "BtagSF_ExtEff_SysUp"    )
            systs.append( "BtagSF_ExtEff_SysDown"  )

    return systs


def GetRunCommand(m_lfvType,m_dir,m_sysVar,m_blind):

    lfvName = ""
    if m_lfvType==etau_Chan:
        lfvName = "etau"
    elif m_lfvType==mutau_Chan:
        lfvName = "mutau"

    FileName = "Plots_"+m_sysVar+"_"+lfvName
    if(m_blind):
        FileName += "_Blind"
        
    FileName += ".root"
    
    cmd  = "hadd -f "+m_dir+FileName+" "+m_dir+"LepFake/"+FileName+" "+m_dir+"DoubFake/"+FileName
    
    return cmd

        
def ShowDoc():
    print ""
    print "Script to run MakeInput code!"
    print "  Usage : ./RunMakeInput.py [Options]!"
    print "          Options:  "
    print "              lfvType   = 2,3          : value needed. Options: 2,3 "
    print "              addSyst   = [True/False] : default is False "
    print "              ttbarCR   = [True/False] : default is False "
    print "              useBjet   = [True/False] : default is False "
    print "              isBlind   = [True/False] : default is False "
    print "              isRevDphi = [True/False] : default is False "
    print "              useSherpa = [True/False] : default is False "
    
if __name__ == "__main__":
    main()
