![语言](https://img.shields.io/badge/语言-verilog-FF1010.svg) ![仿真](https://img.shields.io/badge/部署-vivado-green.svg) ![部署](https://img.shields.io/badge/语言-C++-blue.svg) ![部署](https://img.shields.io/badge/部署-vscode-9A90FD.svg) 

<span id="en">brain-inspired chip test system for gdiist</span>
===========================

（1）硬件部分

* 1 * 米联客K7开发板
* 4 * fpga光口子板
* 1 * socket测试板
* 1 * 12v电源线 
* 4 * 光纤线

<div align=center>
<img width="500" alt="image" src="imgs/socket.jpg">
</div>

<div align=center>
<img width="500" alt="image" src="imgs/hw.jpg">
</div>

（2）软件部分

* Ubuntu 20.04
* xdma驱动文件
* sh文件
* 上位机程序文件：work_cwb/run_socket_eswn/
* 下载数据weight文件路径：work_cwb/data/1k36chip_asic/weight_socket_test/（最大不超过64K）
* 上传数据weight_check文件路径：work_cwb/upload/1k36chip_asic/step0/

PS：确认上位机程序的launch.json中的下载和上传路径设置正确
