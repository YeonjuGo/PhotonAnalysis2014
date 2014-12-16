#yeonju_highPtPhotonSkimmerV3(TString inputFile_="./files/merged.root", int ptHatLowerCut=30, int ptHatUpperCut=50, float photonPtCut=50)
#

root -l -b -q 'yeonju_highPtPhotonSkimmerV3.C+("./files/merged.root", 30, 50)'
root -l -b -q 'yeonju_highPtPhotonSkimmerV3.C+("./files/merged.root", 50, 80)'
root -l -b -q 'yeonju_highPtPhotonSkimmerV3.C+("./files/merged.root", 80, 120)'
root -l -b -q 'yeonju_highPtPhotonSkimmerV3.C+("./files/merged.root", 120, 9999)'
#root -l -b -q 'yeonju_highPtPhotonSkimmerV3.C+("./files/merged.root", 0, 30, 50)'
