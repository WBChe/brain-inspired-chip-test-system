#!/bin/bash
#extern_sp  mode  hw_type sample_num step_count neu_chip

sh ~/work/sh/load.sh
tile_num=`expr $1 / 16`
if [ $tile_num -eq 0 ]
then
        tile_num=1
fi
echo "tile_num: $tile_num"

downloadPath="${HOME}/work/data/ei_data_$1k_0.5"
uploadPath="${HOME}/work/upload/ei_$1_asic"
echo $downloadPath

for ((i=0; i<=$2; i++))
do 
	mkdir -p "${uploadPath}/step$i/spike_check"
	mkdir -p "${uploadPath}/step$i/weight_check"
done

if [ $3 -ne 2 ]
then
	./zcu102_sender 1 $tile_num 0 $downloadPath $uploadPath 4 4 0 0 0 0 0 0  
	./zcu102_sender 1 $tile_num 0 $downloadPath $uploadPath 4 4 1 1 0 1 $2 16384
elif [ $3 -eq 2 ] 
then
	./zcu102_sender 1 $tile_num 0 $downloadPath $uploadPath 4 4 0 2 0 0 0 0    
fi
