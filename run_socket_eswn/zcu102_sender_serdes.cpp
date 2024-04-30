
#include "zcu102_sender_global.h"

//initialize data path;
const char property_path_prefix[] = "../../../InitData/bin_data_003/property";
const char route_path_prefix[] = "../../../InitData/bin_data_003/route_info";
const char weight_path_prefix[] = "../../../InitData/bin_data_003/weight";
//simulation data path;

/*
//initialization of data;
void Serdes_Initialize(libusb_device_handle *dev_handle) {
//property initialize;
	Files_ParallelDownload_All(dev_handle, (char*)property_path_prefix, CELL_PROPERTY_BASE);
//route info initialize;
	Files_ParallelDownload_All(dev_handle, (char*)route_path_prefix, CELL_ROUTE_INFO_BASE);
//weight initialize;
	Files_ParallelDownload_All(dev_handle, (char*)weight_path_prefix, CELL_WEIGHT_BASE);

	return;
}
*/

//
//void Serdes_Init(libusb_device_handle *dev_handle, unsigned int parallel_num, unsigned int chip_num) {
//	unsigned int usb_cmd[4] = {0xcccccccc, 0xcccccccc, 0xcccccccc, 0xcccccccc};
//	usb_cmd[0] = parallel_num;
//	usb_cmd[1] = chip_num;
//	USB_SendCmd(dev_handle, PC_SET_CHIP, usb_cmd);  //trigger gdma to send data;
//	USB_RecvCSW(dev_handle);  //wait for step sim done;
//	printf("Serdes_Init End, parallel_num = %d, chip_num = %d\r\n", parallel_num, chip_num);
//}


//void Serdes_StepSim(libusb_device_handle *dev_handle,unsigned int step) {
//	unsigned int usb_cmd[4] = {0xcccccccc, 0xcccccccc, 0xcccccccc, 0xcccccccc};
//	usb_cmd[0] = step;
//	//printf("Step Start steps=%d\r\n",step);
//	//printf("trigger gdma to send data\r\n");
//	USB_SendCmd(dev_handle, PC_STEPSIM, usb_cmd);  //trigger gdma to send data;
//	cout << "wait for step sim done" << endl;
//	USB_RecvCSW(dev_handle);  //wait for step sim done;
//	cout << "Sim step End" << endl;
//}
