#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};
#                  0        1      2        3      4        5
#void gammaJetHistProducer(sampleType collision = kHIDATA, float photonPtThr=60, float photonPtThrUp=1000000, float jetPtThr=30, int icent =1)


#pp data and PbPb data 
root -l -b -q 'one_systErrCal.C+(2, 7)'
root -l -b -q 'one_systErrCal.C+(0, 10030)'
root -l -b -q 'one_systErrCal.C+(0, 13099)'


