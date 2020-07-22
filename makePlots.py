#!/usr/bin/python
import os
import sys
import subprocess
import getopt
import string

#Channels
emu_Chan   = 1
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
    m_runType   = None
    m_lfvType   = None
    m_addSyst   = None
    m_baseDir   = None
    m_ttbarCR   = None
    m_useBjet   = None
    m_revDphi   = None
    m_metCut    = None
    m_pTlep     = None
    m_rmQcdCR   = None
    m_lumi      = None
    m_blind     = None
    m_blindData = None
    m_sherpa    = None
    m_ptrw      = None
    m_debug     = None
    m_verbose   = None
    # process arguments
    for arg in args:
        if arg.find('=') > -1:
            key,value = arg.split('=',1)

            if key=="runType":
                m_runType=value

            if key=="lfvType":
                m_lfvType=value

            if key=="addSyst":
                m_addSyst=True

            if key=="baseDir":
                m_baseDir=value

            if key=="ttbarCR":
                m_ttbarCR=True

            if key=="useBjet":
                m_useBjet=True

            if key=="revDphi":
                m_revDphi=True

            if key=="metCut":
                m_metCut=True

            if key=="pTlep":
                m_pTlep=True

            if key=="rmQcdCR":
                m_rmQcdCR=True

            if key=="lumi":
                m_lumi=value

            if key=="isBlind":
                m_blind=True

            if key=="isBlindData":
                m_blindData=True

            if key=="useSherpa":
                m_sherpa=True

            if key=="doPtRw":
                m_ptrw=True

            if key=="debug":
                m_debug=True

            if key=="verbose":
                m_verbose=True

    print "-------------------------------------------------"
    if not m_lumi:
        print "lumi not set        -> using default: 36.2 fb^-1"
        m_lumi = 36.2
    if not m_runType:
        print "runType not set     -> using default: 'all' "
        m_runType = "all"
    if not m_lfvType:
        print "lfvType not set     -> using default: '0' (all channels) "
        m_lfvType = 0
    if not m_addSyst:
        print "addSyst not set     -> using default: 'False' "
        m_addSyst = False
    if not m_baseDir:
        print "baseDir not set     -> using default: 'Ntuples' "
        m_baseDir = "Ntuples"
    if not m_ttbarCR:
        print "ttbarCR not set     -> using default: 'False' "
        m_ttbarCR = False
    if not m_useBjet:
        print "useBjet not set     -> using default: 'False' "
        m_useBjet = False
    if not m_revDphi:
        print "revDphi not set     -> using default: 'False' "
        m_revDphi = False
    if not m_metCut:
        print "metCut not set      -> using default: 'False' "
        m_metCut = False
    if not m_pTlep:
        print "pTlep not set       -> using default: 'False' "
        m_pTlep = False
    if not m_rmQcdCR:
        print "rmQcdCR not set     -> using default: 'False' "
        m_rmQcdCR = False
    if not m_blind:
        print "isBlind not set     -> using default: 'False' "
        m_blind = False
    if not m_blindData:
        print "isBlindData not set -> using default: 'False' "
        m_blindData = False
    if not m_sherpa:
        print "useSherpa not set   -> using default: 'False' "
        m_sherpa = False
    if not m_ptrw:
        print "doPtRw not set      -> using default: 'False' "
        m_ptrw = False
    if not m_debug:
        print "debug is not set    -> using default: 'False' "
        m_debug = False
    if not m_verbose:
        print "verbose is not set  -> using default: 'False' "
        m_verbose = False
    print "-------------------------------------------------"
    print ""
    print "  Options set: "
    print " runType     = "+m_runType
    print " lfvType     = "+str(m_lfvType)
    print " addSyst     = "+str(m_addSyst)
    print " baseDir     = "+m_baseDir
    print " ttbarCR     = "+str(m_ttbarCR)
    print " useBjet     = "+str(m_useBjet)
    print " revDphi     = "+str(m_revDphi)
    print " metCut      = "+str(m_metCut)
    print " pTlep       = "+str(m_pTlep)
    print " rmQcdCR     = "+str(m_rmQcdCR)
    print " lumi        = "+str(m_lumi)
    print " isBlind     = "+str(m_blind)
    print " isBlindData = "+str(m_blindData)
    print " sherpa      = "+str(m_sherpa)
    print " ptrw        = "+str(m_ptrw)
    print " debug       = "+str(m_debug)
    print " verbose     = "+str(m_verbose)
    print "-------------------------------------------------"


    makeInputPlots(m_runType,   m_lfvType, m_addSyst, m_baseDir,
                   m_ttbarCR,   m_useBjet, m_revDphi, m_metCut,
                   m_pTlep,     m_rmQcdCR, m_lumi,    m_blind,
                   m_blindData, m_sherpa,  m_ptrw,    m_debug,
                   m_verbose)


def makeInputPlots(runType,   lfvType,
                   addSyst,   baseDir,
                   ttbarCR,   useBjet,
                   revDphi,   metCut,
                   pTlep,     rmQcdCR,
                   lumi,      blind,
                   blindData, sherpa,
                   ptrw,      debug,
                   verbose):

    #Set LFV Channels
    LFVtypes = DefineLFVchannels(lfvType)

    for lfv in LFVtypes:
        
        #Set Kind of runs per channel
        RunTypes = DefineRunTypes(lfv,ttbarCR,runType)

        for rt in RunTypes:

            #Set Systematics list
            Systs = DefineSystematics(lfv,rt,addSyst,useBjet)

            for sys in Systs:

                #Get List of samples
                Samples = GetListOfSamples(lfv,rt,sys,revDphi,rmQcdCR)

                for sp in Samples:

                    print "lfvtype = "+str(lfv)+" runtype = "+rt+" syst = "+sys+" sample = "+sp
                    cmd = GetRunCommand(lfv,rt,sys,sp,baseDir,lumi,useBjet,
                                        revDphi,metCut,pTlep,rmQcdCR,blind,
                                        blindData,sherpa,ptrw,debug,verbose)
                    print cmd
                    os.system(cmd)
                    
        print ""        


def DefineLFVchannels(m_lfvType):

    lfvType = []

    if m_lfvType==0:
        lfvType.append( emu_Chan )
        lfvType.append( etau_Chan )
        lfvType.append( mutau_Chan )
    else:
        lfvType.append( int(m_lfvType) )

    return lfvType
        
    
def DefineRunTypes(m_lfvType,m_ttbarCR,m_runType):

    runType = []

    if m_runType=="all":

        runType.append("Main")
        
        
        if m_lfvType==emu_Chan and m_ttbarCR: #to be removed ?
            runType.append("ttbarCR")         #to be removed ?
        
        if m_lfvType==etau_Chan or m_lfvType==mutau_Chan:
            #W+jets specific estimation
            runType.append( "WjetCR"            ) #renable
            runType.append( "WjetCR_SS"         ) #renable
            runType.append( "WjetCR_OS"         ) #renable
            runType.append( "WjetSR"            ) #renable
            runType.append( "WjetSR_SS"         ) #renable
            runType.append( "WjetSR_OS"         ) #renable
            runType.append( "WjetNoTauId"       ) #renable
                    
            #Qcd specific estimation
            runType.append( "QcdReg3_LepFake"     ) #renable
            runType.append( "QcdReg3_DoubFake"    ) #renable
            runType.append( "QcdReg3_SS_LepFake"  ) #renable
            runType.append( "QcdReg3_SS_DoubFake" ) #renable
            runType.append( "QcdReg3_OS_LepFake"  ) #renable
            runType.append( "QcdReg3_OS_DoubFake" ) #renable
            runType.append( "QcdReg1_SS_LepFake"  ) #renable
            runType.append( "QcdReg1_SS_DoubFake" ) #renable
            runType.append( "QcdReg1_OS_LepFake"  ) #renable
            runType.append( "QcdReg1_OS_DoubFake" ) #renable
            runType.append( "QcdReg2_SS"          ) #renable
            runType.append( "QcdReg2_OS"          ) #renable
        
            if m_ttbarCR:
                runType.append( "ttbarCR"                     )   #to be removed ?
                runType.append( "ttbarCR_WjetNoTauId"         )   #to be removed ?
                runType.append( "ttbarCR_WjetCR"              )   #to be removed ?
                runType.append( "ttbarCR_WjetCR_SS"           )   #to be removed ?
                runType.append( "ttbarCR_WjetSR"              )   #to be removed ?
                runType.append( "ttbarCR_WjetSR_SS"           )   #to be removed ?
                runType.append( "ttbarCR_QcdReg3_LepFake"     )   #to be removed ?
                runType.append( "ttbarCR_QcdReg3_DoubFake"    )   #to be removed ?
                runType.append( "ttbarCR_QcdReg1_SS_LepFake"  )   #to be removed ?
                runType.append( "ttbarCR_QcdReg1_SS_DoubFake" )   #to be removed ?
                runType.append( "ttbarCR_QcdReg2_SS"          )   #to be removed ?

    elif m_runType=="ttbarCR":

        runType.append("ttbarCR")
            
        if m_lfvType==etau_Chan or m_lfvType==mutau_Chan:
            #W+jets specific estimation
            runType.append( "ttbarCR_WjetNoTauId"         )
            runType.append( "ttbarCR_WjetCR"              )
            runType.append( "ttbarCR_WjetCR_SS"           )
            runType.append( "ttbarCR_WjetSR"              )
            runType.append( "ttbarCR_WjetSR_SS"           )
            
            #Qcd specific estimation            
            runType.append( "ttbarCR_QcdReg3_LepFake"     )
            runType.append( "ttbarCR_QcdReg3_DoubFake"    )
            runType.append( "ttbarCR_QcdReg1_SS_LepFake"  )
            runType.append( "ttbarCR_QcdReg1_SS_DoubFake" )
            runType.append( "ttbarCR_QcdReg2_SS"          )

    elif m_runType=="revDphi":

        runType.append("revDphi")
                
        if m_lfvType==etau_Chan or m_lfvType==mutau_Chan:
            #W+jets specific estimation
            runType.append( "revDphi_WjetNoTauId"       )
            runType.append( "revDphi_WjetCR"            )
            runType.append( "revDphi_WjetCR_SS"         )
            runType.append( "revDphi_WjetSR"            )
            runType.append( "revDphi_WjetSR_SS"         )
                                                
            #Qcd specific estimation
            runType.append( "revDphi_QcdReg3_LepFake"     )
            runType.append( "revDphi_QcdReg3_DoubFake"    )
            runType.append( "revDphi_QcdReg1_SS_LepFake"  )
            runType.append( "revDphi_QcdReg1_SS_DoubFake" )
            runType.append( "revDphi_QcdReg2_SS"          )
                    
    else:
        runType.append( m_runType )
    
    return runType


def DefineSystematics(m_lfvType,m_runType,m_addSyst,m_useBjet):

    systs = []

    systs.append( "Nominal" )

    #swict off systematics for Signals
    #if m_runType.find("Signal")!=-1:
    #m_addSyst=False

    if m_runType=="WjetNoTauId":
        if not m_addSyst:
            systs.append( "TauFake_StatUp"      )
            systs.append( "TauFake_StatDown"    )
            systs.append( "TauFake_BDT_SysUp"   )
            systs.append( "TauFake_BDT_SysDown" )
            systs.append( "TauFake_CR_Sys"      ) 
            systs.append( "TauFake_NoBDT"       )
            systs.append( "TauFake_Comp_SysUp"   )
            systs.append( "TauFake_Comp_SysDown" )

    if m_addSyst:

        if m_lfvType==emu_Chan or m_lfvType==mutau_Chan:
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
            
        if m_lfvType==emu_Chan or m_lfvType==etau_Chan:
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
    
        if m_runType=="Main" or m_runType=="revDphi" or m_runType=="ttbarCR":
            systs.append( "TopFit_Sys"       )
                        
        if m_runType.find("WjetNoTauId")!=-1 or m_runType=="Main" or m_runType=="revDphi" or m_runType=="ttbarCR":
        
            if m_lfvType==etau_Chan or m_lfvType==mutau_Chan:
                systs.append( "TauFake_StatUp"      )
                systs.append( "TauFake_StatDown"    )
                systs.append( "TauFake_BDT_SysUp"   )
                systs.append( "TauFake_BDT_SysDown" )
                systs.append( "TauFake_CR_Sys"      )
                systs.append( "TauFake_NoBDT"       )
                systs.append( "TauFake_Comp_SysUp"   )
                systs.append( "TauFake_Comp_SysDown" )

        if m_runType=="Main":
        
            systs.append( "PtRw_Sys" )

            if m_lfvType==etau_Chan or m_lfvType==mutau_Chan:
                systs.append( "Multijet_kMJ_Stat" )
                if m_lfvType==etau_Chan:
                    systs.append( "Multijet_kMJ_Sys" )
        
        if m_runType=="TopExtra" or m_runType=="Main" or m_runType=="revDphi" or m_runType=="ttbarCR":
            systs.append( "TopScale_SysUp"   )
            systs.append( "TopScale_SysDown" )
            systs.append( "PDF_Sys"          )
                
    return systs


def GetListOfSamples(m_lfvType,m_runType,m_sys,m_revDphi,m_rmQcdCR):

    samples = []

    samples.append( "data" )
                    
    if m_runType=="Main" or m_runType=="revDphi":
        samples.append( "DY"      )
        samples.append( "DiBoson" )
        samples.append( "Top"     )
        samples.append( "ttV"     )
    
    if m_runType=="ttbarCR":
        samples.append( "DY"      )
        samples.append( "DiBoson" )
        samples.append( "Top"     )
        
    if m_runType.find("WjetNoTauId")!=-1 or m_runType.find("WjetSR")!=-1 or m_runType.find("WjetsMC")!=-1:
        samples.append( "Wjets" )
            
    if m_runType.find("WjetCR")!=-1 or m_runType.find("Qcd")!=-1:
        samples.append( "DY"      )
        samples.append( "DiBoson" )
        samples.append( "Top"     )
        samples.append( "Wjets"   )
        #if m_rmQcdCR:
        #    samples.append( "Zprime1000" )
        #    samples.append( "QBH1000_n1" )
        #    samples.append( "SVT1100"    )

    if m_runType=="TopExtra":
        samples.append( "Top" )

    if m_runType.find("Signal")!=-1:
        samples.append( "Zprime0500" )
        samples.append( "Zprime0600" )
        samples.append( "Zprime0700" )
        samples.append( "Zprime0800" )
        samples.append( "Zprime0900" )
        samples.append( "Zprime1000" )
        samples.append( "Zprime1100" )
        samples.append( "Zprime1200" )
        samples.append( "Zprime1300" )
        samples.append( "Zprime1400" )
        samples.append( "Zprime1500" )
        samples.append( "Zprime1600" )
        samples.append( "Zprime1700" )
        samples.append( "Zprime1800" )
        samples.append( "Zprime1900" )
        samples.append( "Zprime2000" )
        samples.append( "Zprime2200" )
        samples.append( "Zprime2400" )
        samples.append( "Zprime2600" )
        samples.append( "Zprime2800" )
        samples.append( "Zprime3000" )
        samples.append( "Zprime3500" )
        samples.append( "Zprime4000" )
        samples.append( "Zprime4500" )
        samples.append( "Zprime5000" )
        samples.append( "QBH1000_n1" )
        samples.append( "QBH1500_n1" )
        samples.append( "QBH2000_n1" )
        samples.append( "QBH2500_n1" )
        samples.append( "QBH3000_n1" )
        samples.append( "QBH3000_n6" )
        samples.append( "QBH3500_n1" )
        samples.append( "QBH3500_n6" )
        samples.append( "QBH4000_n1" )
        samples.append( "QBH4000_n6" )
        samples.append( "QBH4500_n1" )
        samples.append( "QBH4500_n6" )
        samples.append( "QBH5000_n1" )
        samples.append( "QBH5000_n6" )
        samples.append( "QBH5500_n1" )
        samples.append( "QBH5500_n6" )
        samples.append( "QBH6000_n1" )
        samples.append( "QBH6000_n6" )
        samples.append( "QBH6500_n6" )
        samples.append( "QBH7000_n6" )
        samples.append( "QBH7500_n6" )
        samples.append( "QBH8000_n6" )
        samples.append( "SVT0500"    )
        samples.append( "SVT0600"    )
        samples.append( "SVT0700"    )
        samples.append( "SVT0800"    )
        samples.append( "SVT0900"    )
        samples.append( "SVT1000"    )
        samples.append( "SVT1100"    )
        samples.append( "SVT1200"    )
        samples.append( "SVT1300"    )
        samples.append( "SVT1400"    )
        samples.append( "SVT1500"    )
        samples.append( "SVT1600"    )
        samples.append( "SVT1700"    )
        samples.append( "SVT1800"    )
        samples.append( "SVT1900"    )
        samples.append( "SVT2000"    )
        samples.append( "SVT2200"    )
        samples.append( "SVT2400"    )
        samples.append( "SVT2600"    )
        samples.append( "SVT2800"    )
        samples.append( "SVT3000"    )
        samples.append( "SVT3500"    )
        samples.append( "SVT4000"    )
        samples.append( "SVT4500"    )
        samples.append( "SVT5000"    )

    return samples
    

def GetRunCommand(m_lfvType,m_runType,m_sysVar,m_sample,m_baseDir,
                  m_lumi,m_useBjet,m_revDphi,m_metCut,m_pTlep,m_rmQcdCR,
                  m_blind,m_blindData,m_sherpa,m_ptrw,m_debug,m_verbose):

    cmd  = "./RunOnMiniTree --Sample "+m_sample+" --BaseDir "+m_baseDir
    cmd += " --SysVar "+m_sysVar+" --RunType "+m_runType
    cmd += " --Lumi "+str(m_lumi)+" --LFVtype "+str(m_lfvType)

    if m_useBjet:
        cmd += " --UseBjet"

    if m_blind:
        cmd += " --Blind"

    if m_blindData:
        cmd += " --BlindData"

    if m_runType.find("ttbarCR")!=-1:
        cmd += " --ttbarCR"

    if m_runType.find("revDphi")!=-1:
        cmd += " --DphiRev --metCut"
        
    if m_runType.find("WjetNoTauId")!=-1:
        cmd += " --TauFake --NoTauID"

    if m_runType.find("WjetCR")!=-1:
        cmd += " --WjetCR"

    if m_runType.find("SS")!=-1:
        cmd += " --SSpair"

    if m_runType.find("OS")!=-1:
        cmd += " --OSpair"

    if m_runType.find("LepFake")!=-1:
        cmd += " --AntiIso"

    if m_runType.find("DoubFake")!=-1:
        cmd += " --AntiIso --NoTauID"
        
    if not m_rmQcdCR:
        if m_runType.find("Reg1")!=-1 or m_runType.find("Reg2")!=-1:
            cmd += " --QcdCR"

    if m_revDphi:
        cmd += " --DphiRev"

    if m_metCut:
        cmd += " --metCut"

    if m_pTlep:
        cmd += " --pTlep"

    if m_sherpa:
        cmd += " --useTopSherpa"

    if m_ptrw:
        cmd += " --doPtRw"

    if m_debug:
        cmd += " --debug"

    if m_verbose:
        cmd += " --verbose"

    return cmd

        
def ShowDoc():
    print ""
    print "Script to run MakeInput code!"
    print "  Usage : ./RunMakeInput.py [Options]!"
    print "          Options:  "
    print "                   runType     = all          : default is 'all' "
    print "                   lfvType     = 1            : default is 0     "
    print "                   addSyst     = [True/False] : default is False "
    print "                   ttbarCR     = [True/False] : default is False "
    print "                   useBjet     = [True/False] : default is False "
    print "                   revDphi     = [True/False] : default is False "
    print "                   metCut      = [True/False] : default is False "
    print "                   pTlep       = [True/False] : default is False "
    print "                   rmQcdCR     = [True/False] : default is False "
    print "                   lumi        = 36.2         : default is 36.2  "
    print "                   isBlind     = [True/False] : default is False "
    print "                   isBlindData = [True/False] : default is False "
    print "                   useSherpa   = [True/False] : default is False "
    print "                   doPtRw      = [True/False] : default is False "
    print "                   debug       = [True/False] : default is False "
    print "                   verbose     = [True/False] : default is False "

    
if __name__ == "__main__":
    main()
