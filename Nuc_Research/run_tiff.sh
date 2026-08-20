INPUTFILE=/Users/onippejeakins/Desktop/flattree_omega_missingn.root
OUTPUTNAME=/Users/onippejeakins/Desktop/outtiff.root

root -b -q 'tiff.C("'${INPUTFILE}'", "'${OUTPUTNAME}'")'

