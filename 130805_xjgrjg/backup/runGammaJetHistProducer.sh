#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};
#                  0        1      2        3      4        5
#void gammaJetHistProducer(sampleType collision = kHIDATA, float photonPtThr=60, float photonPtThrUp=1000000, float jetPtThr=30, int icent =1,  int genLevel=0, int qnch =0)


#root -l -b -q 'gammaJetHistProducer.C++(1, 60, 10000,30, 1, 0)'
#root -l -b -q 'gammaJetHistProducer.C+(1, 60, 10000, 30, 2, 0)'
#root -l -b -q 'gammaJetHistProducer.C+(1, 60, 10000, 30, 3, 0)'
#root -l -b -q 'gammaJetHistProducer.C+(1, 60, 10000, 30, 4, 0)'

#root -l -b -q 'gammaJetHistProducer.C+(2, 60, 10000, 30, 1, 0)'
#root -l -b -q 'gammaJetHistProducer.C+(2, 60, 10000, 30, 2, 0)'
#root -l -b -q 'gammaJetHistProducer.C+(2, 60, 10000, 30, 3, 0)'
#root -l -b -q 'gammaJetHistProducer.C+(2, 60, 10000, 30, 4, 0)'

#root -l -b -q 'gammaJetHistProducer.C+(3, 60, 10000, 30, 4, 0, 0)'
#root -l -b -q 'gammaJetHistProducer.C+(3, 60, 10000, 30, 4, 0, 10)'
#root -l -b -q 'gammaJetHistProducer.C+(3, 60, 10000, 30, 4, 0, 8)'
#root -l -b -q 'gammaJetHistProducer.C+(3, 60, 10000, 30, 4, 0, 6)'
#root -l -b -q 'gammaJetHistProducer.C+(3, 60, 10000, 30, 4, 0, 4)'
#root -l -b -q 'gammaJetHistProducer.C+(3, 60, 10000, 30, 4, 0, 2)'

# pt dependent purity
#root -l -b -q 'gammaJetHistProducer.C+(2, 50, 60, 30, 4, 0, 0)'
#root -l -b -q 'gammaJetHistProducer.C+(2, 60, 80, 30, 4, 0, 0)'
#root -l -b -q 'gammaJetHistProducer.C+(2, 80, 120, 30,4, 0, 0)'
root -l -b -q 'gammaJetHistProducer.C+(2, 80,9999, 30, 4, 0, 0)'

#PbPb data
#root -l -b -q 'gammaJetHistProducer.C+(0, 50,60, 30, 10030, 0, 0)'
#root -l -b -q 'gammaJetHistProducer.C+(0, 60,80, 30, 10030, 0, 0)'
#root -l -b -q 'gammaJetHistProducer.C+(0, 80,120, 30, 10030, 0, 0)'
root -l -b -q 'gammaJetHistProducer.C+(0, 80,9999, 30, 10030, 0, 0)'





