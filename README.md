#    HighMassLFV analysis package   #

#    Description   #

This project contains the analysis code used for the Exotics LFV search.

   - read flat Ntuples created by HighMassLFV package
   - make Background control plots
   - make W+jets and QCD background extimation
   - make all needed plots

It consists in a collection of several tools, later explained.

N.B: in the future most small tools will be merged in single tools
     depending on their purposes (i.e. All bkg estimation will form
     BkgEstimation tool)

#    Compiling: first compilation  #

This package needs a recent version of ROOT

   - login on lxplus
   - setup ATLAS software (type 'setupATLAS')
   - go to HighMassLFV_Analysis working directory 
   - setup ROOT release (type 'lsetup ROOT')
   - compile (type 'make')

#    Running   #
   - go to the working directory and set the environment type 'source config.sh')
   - then compile the package (type 'make')

#    Cascade of tools   #
   - AdjustFakeRate -> arrange tau fake rate inputs in a single file
   - makePlots.py -> call RunOnMiniTree to make starting plots
   - mergerQCDInputs.py -> merge LepFake and DoubleFake root files
   - MakeQCD -> make QCD contribution evaluation
   - AddContributions -> add W+jets and Top fit
   - MergeContributions -> make Multijet and BkgTot plots
   - SysPercentVariations -> make percent variation for each sys uncertainty
   - CreateSysBands -> create the systematic bands
   - LimitInputs -> create inputs for limits calculation

#    Top Fits    #
   - TopExtra -> arrange all top plots in a single file per channel as fit inputs
   - TopScale -> make top scale ratio w.r.t nominal case to derive sys to be applied to other distribution
