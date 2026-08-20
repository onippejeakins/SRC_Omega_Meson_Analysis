INPUTFILE=/Users/onippejeakins/Desktop/flattree_omega_missingn_090217.root
OUTPUTNAME=/Users/onippejeakins/Desktop/outtiff_opp.root

root -b -q 'tiff_opp.C("'${INPUTFILE}'", "'${OUTPUTNAME}'")'

