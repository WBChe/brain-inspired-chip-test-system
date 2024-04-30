
#include "zcu102_sender_global.h"

const char *gdma_dump_file[4] = { "_gdma_dump_0.bin", "_gdma_dump_1.bin", "_gdma_dump_2.bin", "_gdma_dump_3.bin" };

//Usb_Cmd[3:0] is the total length of all data blockes
//void Gdma_ParallelDownload(libusb_device_handle *dev_handle, unsigned int *usb_cmd) {
//	USB_SendCmd(dev_handle, PC_DOWNLOAD, usb_cmd);
//	USB_RecvCSW(dev_handle);	
//	return;
//}
////dd
//void Gdma_ParallelUpload(libusb_device_handle *dev_handle, unsigned int *usb_cmd) {
//	USB_SendCmd(dev_handle, PC_UPLOAD, usb_cmd);
//	USB_RecvCSW(dev_handle);
//	return;
//}

//dump gdma mem content to file for checking;
//byte_length start from 1;
//void Gdma_DumpFile(libusb_device_handle *dev_handle, char *path_prefix,
//					unsigned char gdma_index, unsigned int gdma_addroffset, unsigned int byte_length) {
//	char *file_path;
//	unsigned char *file_buffer;
//	unsigned int i = 0;
//	unsigned int prefix_len, postfix_len;
//	FILE *fp;
//	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
//	unsigned int transfer_round = 0;
//	unsigned int transfer_round_limit = 0;
//	printf("Gdma_DumpFile: start dump with byte_length=%d\n", byte_length);
//	prefix_len = strlen((const char *)path_prefix);
//	postfix_len = strlen(gdma_dump_file[gdma_index]);
//	file_path = (char *)malloc((prefix_len + postfix_len+1)*sizeof(char));
//	for (i = 0; i < prefix_len; i++)
//		file_path[i] = path_prefix[i];
//	for (i = 0; i < postfix_len+1; i++)  //plus 1 include '\0';
//		file_path[i+prefix_len] = gdma_dump_file[gdma_index][i];
//	file_buffer = (unsigned char *)malloc(USB_TRANSFER_LIMIT*sizeof(unsigned char));
////
//#ifdef OS_WIN
//	//fopen_s(&fp, file_path, "wb");
//	fp = fopen(file_path, "wb");
//#else
//	fp = fopen(file_path, "wb");
//#endif
//	if (byte_length % USB_TRANSFER_LIMIT == 0)
//		transfer_round_limit = byte_length / USB_TRANSFER_LIMIT;
//	else
//		transfer_round_limit = byte_length / USB_TRANSFER_LIMIT + 1;
//	for (transfer_round = 0; transfer_round < transfer_round_limit; transfer_round++) {
//		if (transfer_round == transfer_round_limit - 1) {
//			USB_ReadWrite(dev_handle, USB_EP1_IN, file_buffer, gdma_base[gdma_index] + gdma_addroffset, byte_length - transfer_round*USB_TRANSFER_LIMIT);
//#ifdef DEBUG_PRINT
//			printf("transfer_round = %d, transfer_length = %d\n" ,transfer_round, byte_length - transfer_round*USB_TRANSFER_LIMIT);
//#endif
//			fwrite(file_buffer, sizeof(unsigned char), byte_length - transfer_round*USB_TRANSFER_LIMIT, fp);
//			gdma_addroffset += (byte_length - transfer_round*USB_TRANSFER_LIMIT);
//		}
//		else {
//			USB_ReadWrite(dev_handle, USB_EP1_IN, file_buffer, gdma_base[gdma_index] + gdma_addroffset, USB_TRANSFER_LIMIT);
//			fwrite(file_buffer, sizeof(unsigned char), USB_TRANSFER_LIMIT, fp);
//			gdma_addroffset += USB_TRANSFER_LIMIT;
//		}
//	}
//	printf("Gdma_DumpFile: done\n");
//	fclose(fp);
//	return;
//}
