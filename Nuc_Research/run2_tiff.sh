for CONFIG in 090_para 090_perp 45135_para 45135_perp
do

	INPUTFILE=/Users/onippejeakins/Desktop/run_configs/flattree_omega_missingn_${CONFIG}.root
	OUTPUTNAME=/Users/onippejeakins/Desktop/run_configs/output/output_${CONFIG}.root

	root -b -q 'tiff.C("'${INPUTFILE}'", "'${OUTPUTNAME}'")'

done
echo 'finished with all 4 configs'
