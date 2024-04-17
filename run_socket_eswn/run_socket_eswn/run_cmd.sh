#!/bin/bash
#extern_sp  mode  hw_type sample_num step_count neu_chip

sh ~/work/prog_scripts2/FPGA_prog/sender/sender_rst.sh
if [ $1 -gt 16 ]
then
	~/work/prog_scripts2/FPGA_prog/run/zcu102_sender 1 2 0 ~/work/data/ei_data_$1k_0.5_asic /home/upload/ei_$1_asic 0 0 0 0 0 0 0 0  
	~/work/prog_scripts2/FPGA_prog/run/zcu102_sender 1 2 0 ~/work/data/ei_data_$1k_0.5_asic /home/upload/ei_$1_asic 0 0 1 1 0 1 $2 0
else 
	~/work/prog_scripts2/FPGA_prog/run/zcu102_sender 1 1 0 ~/work/data/ei_data_$1k_0.5_asic /home/upload/ei_$1_asic 0 0 0 0 0 0 0 0    
	~/work/prog_scripts2/FPGA_prog/run/zcu102_sender 1 1 0 ~/work/data/ei_data_$1k_0.5_asic /home/upload/ei_$1_asic 0 0 1 1 0 1 $2 0
fi
