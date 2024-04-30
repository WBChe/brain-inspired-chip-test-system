
#include "pcie_fun.h"
#include "zcu102_sender_global.h"
#include "gdma.h"
#define SERDES_ON
#define FILES_DEBUG_PRINT
#define DOWNLOAD_DEBUG_PRINT
#define UPLOAD_DEBUG_PRINT

extern unsigned int gtp_state;
// /********** board: 1, chip_max: 9, row_max: 3, column_max: 3 **********/
// const char *chip_num_table9[1][9] = {
// 	{
// 	 "_0.bin", "_1.bin", "_2.bin", 
// 	 "_3.bin", "_4.bin", "_5.bin", 
// 	 "_6.bin", "_7.bin", "_8.bin"
// 	 }
// };
// const unsigned int chip_row_table9[1][9] = {
// 	{
// 	 1, 1, 1, 2, 2, 2, 
// 	 3, 3, 3
// 	 }
// };
// const unsigned int chip_column_table9[1][9] = {
// 	{
// 	 1, 2, 3, 1, 2, 3, 
// 	 1, 2, 3
// 	 }
// };

// /********** board: 2, chip_max: 18, row_max: 6, column_max: 3 **********/
// const char *chip_num_table18[1][18] = {
//         {
//          "_0.bin", "_1.bin", "_2.bin",
//          "_3.bin", "_4.bin", "_5.bin",
//          "_6.bin", "_7.bin", "_8.bin",
//          "_9.bin", "_10.bin", "_11.bin",
//          "_12.bin", "_13.bin", "_14.bin",
//          "_15.bin", "_16.bin", "_17.bin"
//          }
// };
// const unsigned int chip_row_table18[1][18] = {
//         {
//          1, 1, 1, 2, 2, 2,
//          3, 3, 3, 4, 4, 4,
//          5, 5, 5, 6, 6, 6
//          }
// };
// const unsigned int chip_column_table18[1][18] = {
//         {
//          1, 2, 3, 1, 2, 3,
//          1, 2, 3, 1, 2, 3,
//          1, 2, 3, 1, 2, 3
//          }
// };

// /********** board: 1, chip_max: 32, row_max: 4, column_max: 8 **********/
// const char *chip_num_table32[4][8] = {
// 	{
// 		"_0.bin", "_1.bin", "_2.bin", "_3.bin", "_4.bin", "_5.bin", "_6.bin", "_7.bin"
// 	},
// 	{
// 		"_8.bin", "_9.bin", "_10.bin", "_11.bin", "_12.bin", "_13.bin", "_14.bin", "_15.bin"
// 	},
// 	{
// 		"_16.bin", "_17.bin", "_18.bin", "_19.bin", "_20.bin", "_21.bin", "_22.bin", "_23.bin"
// 	},
// 	{
// 		"_24.bin", "_25.bin", "_26.bin", "_27.bin", "_28.bin", "_29.bin", "_30.bin", "_31.bin"
// 	}
// };
// const unsigned int chip_row_table32[4][8] = {
// 	{
// 		1, 1, 1, 1, 1, 1, 1, 1
// 	},
// 	{
// 		2, 2, 2, 2, 2, 2, 2, 2
// 	},
// 	{
// 		3, 3, 3, 3, 3, 3, 3, 3
// 	},
// 	{
// 		4, 4, 4, 4, 4, 4, 4, 4
// 	}
// };
// const unsigned int chip_column_table32[4][8] = {
// 	{
// 		1, 2, 3, 4, 5, 6, 7, 8
// 	},
// 	{
// 		1, 2, 3, 4, 5, 6, 7, 8
// 	},
// 	{
// 		1, 2, 3, 4, 5, 6, 7, 8
// 	},
// 	{
// 		1, 2, 3, 4, 5, 6, 7, 8
// 	}
// };



// /********** board: 4, chip_max: 36, row_max: 6, column_max: 6 **********/
// const char *chip_num_table36[1][36] = {
// 	{
// 	 "_0.bin", "_1.bin", "_2.bin", "_3.bin", "_4.bin", "_5.bin", 
// 	 "_6.bin", "_7.bin", "_8.bin", "_9.bin", "_10.bin", "_11.bin", 
// 	 "_12.bin", "_13.bin", "_14.bin", "_15.bin", "_16.bin", "_17.bin", 
// 	 "_18.bin", "_19.bin", "_20.bin", "_21.bin", "_22.bin", "_23.bin", 
// 	 "_24.bin", "_25.bin", "_26.bin", "_27.bin", "_28.bin", "_29.bin", 
// 	 "_30.bin", "_31.bin", "_32.bin", "_33.bin", "_34.bin", "_35.bin"
// 	 }
// };
// const unsigned int chip_row_table36[1][36] = {
// 	{
// 	 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 
// 	 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 
// 	 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6
// 	 }
// };
// const unsigned int chip_column_table36[1][36] = {
// 	{
// 	 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 
// 	 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 
// 	 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6
// 	 }
// }; 

// /********** board: 8, chip_max: 72, row_max: 6, column_max: 12 **********/
// const char *chip_num_table72[1][72] = {
// 	{
// 	 "_0.bin", "_1.bin", "_2.bin", "_3.bin", "_4.bin", "_5.bin", "_6.bin", "_7.bin", "_8.bin", "_9.bin", "_10.bin", "_11.bin", 
// 	 "_12.bin", "_13.bin", "_14.bin", "_15.bin", "_16.bin", "_17.bin", "_18.bin", "_19.bin", "_20.bin", "_21.bin", "_22.bin", "_23.bin", 
// 	 "_24.bin", "_25.bin", "_26.bin", "_27.bin", "_28.bin", "_29.bin", "_30.bin", "_31.bin", "_32.bin", "_33.bin", "_34.bin", "_35.bin", 
// 	 "_36.bin", "_37.bin", "_38.bin", "_39.bin", "_40.bin", "_41.bin", "_42.bin", "_43.bin", "_44.bin", "_45.bin", "_46.bin", "_47.bin", 
// 	 "_48.bin", "_49.bin", "_50.bin", "_51.bin", "_52.bin", "_53.bin", "_54.bin", "_55.bin", "_56.bin", "_57.bin", "_58.bin", "_59.bin", 
// 	 "_60.bin", "_61.bin", "_62.bin", "_63.bin", "_64.bin", "_65.bin", "_66.bin", "_67.bin", "_68.bin", "_69.bin", "_70.bin", "_71.bin"
// 	 }
// };
// const unsigned int chip_row_table72[1][72] = {
// 	{
// 	 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
// 	 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
// 	 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6
// 	 }
// };
// const unsigned int chip_column_table72[1][72] = {
// 	{
// 	 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 
// 	 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 
// 	 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
// 	 }
// };

//the file is split into 8MB chunks to send;
unsigned int Files_ParallelLoadMem_Download(unsigned int *file_buffer, unsigned char gdma_index, unsigned int file_index, 
					long file_size, unsigned int gdma_addroffset, unsigned int cell_start_addr, unsigned int change_num, bool extern_spike,unsigned int hw_type, uint32_t** chip_row_table,  uint32_t ** chip_col_table, unsigned int chip_direction_sel) {
	unsigned int i;
	unsigned char *he_buffer=NULL;
	// unsigned char *buf1=NULL;
	unsigned int transfer_round;
	unsigned int aligned_file_size;  //start from 1;
	unsigned int transfer_round_limit;
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	unsigned int chip_pos;
	unsigned int word_length;
	unsigned int cmd = 0x47545057; //GTPW
	unsigned int byte_length;
	unsigned int *header_buffer;
	unsigned int merge_file_size;
	unsigned char parallel_num,data_len;
	unsigned int file_addroffset=0;
	header_buffer = (unsigned int *)malloc(5 * 6*sizeof(unsigned int));
	// he_buffer= (unsigned char *)malloc(USB_TRANSFER_LIMIT*sizeof(unsigned int));
    //load header data;
	if (file_size % 4 != 0)   //32bit address alignment tunning;
		aligned_file_size = ((file_size >> 2) + 1) << 2;
	else
		aligned_file_size = file_size;
	word_length = 3 + (aligned_file_size >> 2) - 1;
    for (parallel_num = 0; parallel_num < 6; parallel_num++){
		// chip_pos = (*((uint32_t *)chip_row_table + parallel_num) << 8) | (*((uint32_t *)chip_col_table + parallel_num));
		// cout << "row="<<*((uint32_t *)chip_row_table + parallel_num*change_num+file_index) << "  col=="<< *((uint32_t *)chip_col_table + parallel_num*change_num+file_index)<< endl;

		//choose chip direction for setting correct data header 
		switch (chip_direction_sel) { 
		case 0: 
			chip_pos = (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index));//north header
			break;
		case 1:
			chip_pos = (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index));//west header
			break;
		case 2:
			chip_pos = (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index));//south header (north header)
			break;
		case 3:
			chip_pos = (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index));//east header  (west header)
			break;
		default:
			chip_pos = (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index));//north header
			break;
		}	

		//chip_pos = (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index));//north header
		//chip_pos = (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index)); //west header
		header_buffer[0+parallel_num] = chip_pos;
		header_buffer[6+parallel_num] = word_length;   //word_length;
		header_buffer[12+parallel_num] = cmd;
		header_buffer[18+parallel_num] = cell_start_addr;

		switch (hw_type) { 
		case 0: 
			header_buffer[24+parallel_num] =  ((aligned_file_size >> 2) - 1) << 2;
			break;
		case 1:
			header_buffer[24+parallel_num] = aligned_file_size-1;
			break;
		default:
			header_buffer[24+parallel_num] =  ((aligned_file_size >> 2) - 1) << 2;
			break;
		}	

	}
	// if (!extern_spike) {
	// 	//cout << "send normal cmd mode" << endl;
	// 	h2c_transfer(0, 20*6, (unsigned char *)header_buffer);
	// }
	// else {
	// 	cout << "extern spike mode" << endl;
	// }

	h2c_transfer(gdma_addroffset, 20*6, (unsigned char *)header_buffer);
	free(header_buffer);

	//transfer file data;
	merge_file_size=aligned_file_size*6;//6 ch
	if (merge_file_size % USB_TRANSFER_LIMIT == 0)
		transfer_round_limit = merge_file_size / USB_TRANSFER_LIMIT;
	else
		transfer_round_limit = merge_file_size / USB_TRANSFER_LIMIT + 1;

	//printf("transfer_round_limit = %d\n",transfer_round_limit);
	for (transfer_round = 0; transfer_round < transfer_round_limit; transfer_round++) {
		if (transfer_round == transfer_round_limit - 1) {
			h2c_transfer(20*6+ gdma_addroffset+file_addroffset, (merge_file_size - transfer_round*USB_TRANSFER_LIMIT) , (unsigned char *)(file_buffer+(file_addroffset>>2)));
		}
		else {
			h2c_transfer(20*6+ gdma_addroffset+file_addroffset, (USB_TRANSFER_LIMIT), (unsigned char *)(file_buffer+(file_addroffset>>2)));
			file_addroffset += USB_TRANSFER_LIMIT;
		}
	}

	// c2h_transfer(0,USB_TRANSFER_LIMIT,he_buffer);
	return merge_file_size;
}

//download files to all cell chips;
//the 4 gdma should send data in parallel;
//single file data size cannot exceed 512MB-20B since there is no slicing in gdma mem space;
//file transfer buffer array will set to 8MB;
void Files_ParallelDownload_All(char *path_prefix, unsigned int cell_start_addr, unsigned char parallel_num, unsigned int chip_num, unsigned int chip_sel, 
																	bool extern_spike, unsigned int hw_type, string ** chip_num_table, unsigned int** chip_row_table,  unsigned int ** chip_col_table, unsigned int chip_direction_sel){
	unsigned int file_index = 0;
	unsigned int aligned_file_size = 0;
	unsigned char gdma_index = 0;
	unsigned char file_overflow_flag = 0, file_unsupport_flag = 0;
	unsigned int i = 0,j=0;
	unsigned int val=0;
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	FILE *fp = NULL;
	unsigned int prefix_len = 0, postfix_len = 0;
	long file_size = 0;
	unsigned int gdma_addroffset=0;
	unsigned int send_byte_length=0;  //start from 0;
	const unsigned int change_num = chip_num / parallel_num;
	unsigned int *file_buffer=NULL;
	unsigned int *openfile_buffer=NULL;
	char *file_path = NULL;
	unsigned int func_out_val;
//copy path prefix;
	prefix_len = strlen((const char *)path_prefix);
	file_path = (char *)malloc((prefix_len + postfix_len + 100)*sizeof(char));
	file_buffer = (unsigned int *)malloc(FILE_LIMIT*sizeof(unsigned char));
	openfile_buffer = (unsigned int *)malloc(FILE_LIMIT/6*sizeof(unsigned char));
	for (i = 0; i < prefix_len; i++)
		file_path[i] = path_prefix[i];
//every gdma has 64 files to send;
	for (file_index = chip_sel; file_index < change_num; file_index++) {

		//preprocess;
		for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) { //open 4 files and check if all the 4 files can fit into gdma mem space;
			fp = NULL;
			char * tmp_char = (char *) (*((string *)chip_num_table + gdma_index * change_num+ file_index) ).data();
			postfix_len = strlen(tmp_char);
					for (i = 0; i < postfix_len + 1; i++)  //plus 1 include '\0';
						file_path[i + prefix_len] = tmp_char[i];
#ifdef PRINT_INFO
			//if (file_index == 0 && gdma_index ==0) {	
				cout << "open file: " << file_path << endl; 
			//}
#endif
			fp = fopen(file_path, "rb");
			if (fp == NULL) {
				cout << "Files_ParallelDownload_All: fopen_s failed, no such file" << endl;
				file_unsupport_flag = 1;
				break;
			}
		
			fseek(fp, 0, SEEK_END);
			file_size = ftell(fp);
			//printf("file_size=%ld",file_size);
			fseek(fp, 0, SEEK_SET);
			
			fread(openfile_buffer, sizeof(unsigned char), file_size,fp);
			for(j=0;j<file_size/4;j++){
				*(file_buffer+gdma_index+j*parallel_num)=*(openfile_buffer+j);

			}


			if (file_size == 0) {
				#ifdef PRINT_INFO
					cout << "download data file is empty" << endl;
					#endif
					file_unsupport_flag = 1;
				break;
                        }
			fclose(fp); //close current file;
		}


		//postprocess;
        
	        send_byte_length = Files_ParallelLoadMem_Download(file_buffer, gdma_index, file_index, file_size,
				       gdma_addroffset, cell_start_addr, change_num, extern_spike,hw_type, chip_row_table,  chip_col_table, chip_direction_sel); //load mem with current file;
			send_byte_length=send_byte_length+20*6;	

			gdma_addroffset+=send_byte_length;	
				

	}

		if(gdma_addroffset%16!=0||gdma_addroffset%24!=0)//send_byte_length must be divisible by 16 and 24
	{
		gdma_addroffset=gdma_addroffset/16+1;
		gdma_addroffset=gdma_addroffset<<4;
		while (gdma_addroffset%24!=0)
		{
			gdma_addroffset=gdma_addroffset+16;
		}

		
	}	

	Gdma_RegConfig(0, 0, 0, (gdma_addroffset-16), 0, 0, 0,RD_FLAG);
			while ((val&gtp_state) != gtp_state)
		{
			val=user_read(GPIO_IREG);
			//printf("val=%d\n",val); 
	
		}
		val=0;
					
	free(file_path);
	free(file_buffer);
	free(openfile_buffer);
	return;
}
void Files_Download_All(char *path_prefix, unsigned int cell_start_addr, unsigned char parallel_num, unsigned int chip_num, unsigned int chip_sel, 
																	bool extern_spike, unsigned int hw_type, string ** chip_num_table, unsigned int** chip_row_table,  unsigned int ** chip_col_table){
	unsigned int file_index = 0;
	unsigned int aligned_file_size = 0;
	unsigned char gdma_index = 0;
	unsigned char file_overflow_flag = 0, file_unsupport_flag = 0;
	unsigned int i = 0;
	unsigned int val=0;
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	FILE *fp = NULL;
	unsigned int prefix_len = 0, postfix_len = 0;
	long file_size = 0;
	unsigned int gdma_addroffset[4] = { 0, 0, 0, 0 };
	unsigned int send_byte_length[4] = { 0xcccccccc, 0xcccccccc, 0xcccccccc, 0xcccccccc };  //start from 0;
	const unsigned int change_num = chip_num / parallel_num;

	char *file_path = NULL;
	unsigned int func_out_val;
//copy path prefix;
	prefix_len = strlen((const char *)path_prefix);
	file_path = (char *)malloc((prefix_len + postfix_len + 100)*sizeof(char));
	for (i = 0; i < prefix_len; i++)
		file_path[i] = path_prefix[i];
//every gdma has 64 files to send;
	for (file_index = chip_sel; file_index < change_num; ) {

		//preprocess;
		for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) { //open 4 files and check if all the 4 files can fit into gdma mem space;
			fp = NULL;
			char * tmp_char = (char *) (*((string *)chip_num_table + gdma_index * change_num+ file_index) ).data();
			postfix_len = strlen(tmp_char);
					for (i = 0; i < postfix_len + 1; i++)  //plus 1 include '\0';
						file_path[i + prefix_len] = tmp_char[i];
#ifdef PRINT_INFO
			//if (file_index == 0 && gdma_index ==0) {	
				cout << "open file: " << file_path << endl; 
			//}
#endif
#ifdef OS_WIN
			//fopen_s(&fp, file_path, "rb");
			fp = fopen(file_path, "rb");
#else
			fp = fopen(file_path, "rb");
#endif
			if (fp == NULL) {
				cout << "Files_ParallelDownload_All: fopen_s failed, no such file" << endl;
				file_unsupport_flag = 1;
				break;
			}
		
			fseek(fp, 0, SEEK_END);
			file_size = ftell(fp);
			//file_size = 4194304;
			//printf("file_size=%ld",file_size);
			fseek(fp, 0, SEEK_SET);
			if (file_size == 0) {
				#ifdef PRINT_INFO
					cout << "download data file is empty" << endl;
					#endif
					file_unsupport_flag = 1;
				break;
                        }
	
			else if (file_size > GDMA_ADDR_LIMIT - 20) { //single file exceed upper limit;
				#ifdef PRINT_INFO
				cout << "Files_ParallelDownload_All: single file size exceed upper limit " << file_size << endl;
				#endif
				file_unsupport_flag = 1;
				break;
			}
			else if (file_size + gdma_addroffset[gdma_index] + 20 > GDMA_ADDR_LIMIT) { //file size overflow;
				#ifdef PRINT_INFO
				cout << "Files_ParallelDownload_All: file total size overflow, prepare to send out" << endl;
				#endif
				file_overflow_flag = 1;
			}
			else {  //load file to zcu102 ddr;
				aligned_file_size = Files_LoadMem_Download(fp, gdma_index, file_index, file_size,
				       gdma_addroffset[gdma_index], cell_start_addr, change_num, extern_spike,hw_type, chip_row_table,  chip_col_table); //load mem with current file;
				gdma_addroffset[gdma_index] += (aligned_file_size + 20); //file size and additional 20byte head;

			}
			fclose(fp); //close current file;
		}
		//postprocess;
		if (file_unsupport_flag == 1) {  //close exit;
			return;
		}
		else if ((file_overflow_flag == 1) || (file_index == change_num-1)) { //the rest mem space cannot hold the next file, need to transfer first;
			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) {	//32bit address alignment tunning;
				if (gdma_addroffset[gdma_index] % 4 == 0)
					send_byte_length[gdma_index] = gdma_addroffset[gdma_index] - 4; //gdma discard lower 2 bits and add 1 to upper bit;
				else {
					cout << "Files_ParallelDownload_All: gdma_addroffset not aligned" << endl;
					return;
				}
			} 

#ifdef SERDES_ON
			// printf("Files_ParallelDownload_All: Trigger gdma send_byte_length[0]=%d,send_byte_length[1]=%d,send_byte_length[2]=%d,send_byte_length[3]=%d\n",
			// 	send_byte_length[0], send_byte_length[1], send_byte_length[2], send_byte_length[3]);
			//	gdma_index = 0;
			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) {
				if (extern_spike){
					func_out_val=user_read(GPIO_OREG);
					user_write(GPIO_OREG,EXTERN_SPIKE_OUT|func_out_val);
					Gdma_RegConfig(1, gdma_base[gdma_index], 0, send_byte_length[gdma_index]-20, 0, 0, 0,RD_FLAG);
					while((val&gtp_state) != gtp_state)
					{
						val=user_read(GPIO_IREG);
				
					}
					func_out_val=user_read(GPIO_OREG);
					user_write(GPIO_OREG,~EXTERN_SPIKE_OUT&func_out_val);
				}
					
				else{
					Gdma_RegConfig(gdma_index, gdma_base[gdma_index], 0, send_byte_length[gdma_index], 0, 0, 0,RD_FLAG);
				        while ((val&gtp_state) != gtp_state)
					{
						val=user_read(GPIO_IREG);
						//printf("val=%d\n",val); 
				
					}
					
				}
					
				}
				val=0;
#else
			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) {
				printf("Files_ParallelDownload_All: send_byte_length[%d] = %d\n", gdma_index, send_byte_length[gdma_index]);
				//Gdma_DumpFile(dev_handle, path_prefix, gdma_index, 0, gdma_addroffset[gdma_index]);
			}
#endif

			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++)
				gdma_addroffset[gdma_index] = 0;
			file_overflow_flag = 0;
			if ((file_index == change_num-1) && (file_overflow_flag != 1))
				file_index++;
				}
			else
				file_index++;


	}
	//free(file_path);
	return;
}

//read mem data and write to files;
//1 gdma every block correspond to 1 file;
void Files_ParallelReadMem_Upload( char *path_prefix, unsigned int file_index_start, unsigned int aligned_file_size, 
																unsigned char gdma_index, uint32_t change_num, string ** chip_num_table) {
	unsigned int path_len = 0;
	unsigned int i = 0;
	char *file_path = NULL; 
	unsigned int *file_buffer;
	unsigned int *write_buffer;
	unsigned int transfer_round;
	unsigned int transfer_round_limit;
	unsigned int gdma_addroffset = 0;
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	unsigned int index = 0;
	unsigned int parallel_num=6;
	unsigned int one_ch_byte_length;
	unsigned int file_index;
	file_index=file_index_start;
	FILE *fp = NULL;
	one_ch_byte_length=aligned_file_size/6;
//copy path prefix;
	path_len = strlen((const char *)path_prefix);
	file_path = (char *)malloc((path_len + 100)*sizeof(char));
	file_buffer = (unsigned int *)malloc(aligned_file_size * sizeof(unsigned char));
	write_buffer = (unsigned int *)malloc(one_ch_byte_length * sizeof(unsigned char));
	for (i = 0; i < path_len; i++)
		file_path[i] = path_prefix[i];

		if (aligned_file_size % OneWriteFileSize == 0)
			transfer_round_limit = aligned_file_size / OneWriteFileSize;
		else
			transfer_round_limit = aligned_file_size / OneWriteFileSize + 1;
		for (transfer_round = 0; transfer_round < transfer_round_limit; transfer_round++) {
			if (transfer_round == transfer_round_limit - 1) {
				c2h_transfer(0x10000+ gdma_addroffset, (aligned_file_size- transfer_round*OneWriteFileSize) , (unsigned char *)(file_buffer+(gdma_addroffset>>2)));
				gdma_addroffset += (aligned_file_size - transfer_round*OneWriteFileSize);
			}
			else {
				c2h_transfer(0x10000 + gdma_addroffset, (OneWriteFileSize), (unsigned char *)(file_buffer+(gdma_addroffset>>2)));
				gdma_addroffset += OneWriteFileSize;
			}
		}

			// for (parallel_num = 0; parallel_num < 6; parallel_num++){
			// 	for(i=0;i<one_ch_byte_length/4;i++){
			// 		write_buffer[i]=file_buffer[i*6];	

			// 	}	

			// }
		
	// for (uint32_t file_index = file_index_start; file_index < change_num; 	file_index++) {

		for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) {

			char * tmp_char = (char *) (*((string *)chip_num_table + gdma_index * change_num+ file_index) ).data();
			// cout << strlen(tmp_char)  << endl;
			for (i = 0; i < 9; i++)
						file_path[i + path_len] = tmp_char[i];
	#ifdef PRINT_INFO
			//if (file_index == 0 && gdma_index ==0) {
				cout << "upload: " << file_path << endl; 
			//}
	#endif	
				
	#ifdef OS_WIN		
			//fopen_s(&fp, file_path, "wb+");
			fp = fopen(file_path,"ab+");
	#else
		
			fp = fopen(file_path,"wb+");
	#endif

			for(i=0;i<one_ch_byte_length/4;i++){
				write_buffer[i]=file_buffer[i*6+gdma_index];	

			}	

			if (fp == NULL)
				cout << "Files_ReadMem_Upload: fopen_s failed" << endl;
				fwrite(write_buffer, sizeof(unsigned char), one_ch_byte_length, fp);

			fclose(fp);
		}
	// }
	free(file_path);
	free(file_buffer);
	return;
}

//load mem with headers in upload;
void Files_ParallelLoadMem_Upload(unsigned int file_index, unsigned int cell_start_addr,
						  unsigned int aligned_file_size, unsigned char gdma_index, unsigned int gdma_addroffset, unsigned int change_num,unsigned int hw_type,  uint32_t** chip_row_table,  uint32_t ** chip_col_table, unsigned int chip_direction_sel) {
	
	unsigned int *header_buffer;
	unsigned int chip_pos;
	unsigned int cmd = 0x47545052;   //GTPR;
	unsigned char parallel_num,data_len;
//load header data;
	header_buffer = (unsigned int *)malloc(5 * 6*sizeof(unsigned int));

    for (parallel_num = 0; parallel_num < 6; parallel_num++){
		
		//choose chip direction for setting correct data header 
		switch (chip_direction_sel) { 
		case 0: 
			chip_pos = (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index));//north header
			break;
		case 1:
			chip_pos = (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index));//west header
			break;
		case 2:
			chip_pos = (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index));//south header (north header)
			break;
		case 3:
			chip_pos = (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index));//east header  (west header)
			break;
		default:
			chip_pos = (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index));//north header
			break;
		}	

		// chip_pos = (*((uint32_t *)chip_row_table + parallel_num) << 8) | (*((uint32_t *)chip_col_table + parallel_num));
		//chip_pos = (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index));//west header
		// chip_pos = (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index));
		header_buffer[0+parallel_num] = chip_pos;
		header_buffer[6+parallel_num] = (3 - 1);   //word_length;
		header_buffer[12+parallel_num] = cmd;
		header_buffer[18+parallel_num] = cell_start_addr;

		switch (hw_type) { 
		case 0: 
			header_buffer[24+parallel_num] =  ((aligned_file_size >> 2) - 1) << 2;
			break;
		case 1:
			header_buffer[24+parallel_num] = aligned_file_size-1;
			break;
		default:
			header_buffer[24+parallel_num] =  ((aligned_file_size >> 2) - 1) << 2;
			break;
		}	

	}
	h2c_transfer(0, 20*6, (unsigned char *)header_buffer);
	free(header_buffer);
	return;
}

//all chip upload certain data;
//all chip have the same start_address and byte_length (it can vary in future versions);
//byte_length can not exceed 512MB;
//byte_length only include data part;  start from 1;
void 
Files_ParallelUpload_ALL(char *path_prefix, unsigned int cell_start_addr, unsigned int byte_length, unsigned char parallel_num, 
																unsigned int chip_num, unsigned int chip_sel, unsigned int hw_type, string ** chip_num_table, uint32_t** chip_row_table,  uint32_t ** chip_col_table, bool up_flag, unsigned int chip_direction_sel) {
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	unsigned char gdma_index = 0;
	unsigned int file_index = 0;
	unsigned int file_index_start = chip_sel;
	unsigned char file_overflow_flag = 0, file_unsupport_flag = 0;
	unsigned int gdma_addroffset[4] = { 0, 0, 0, 0 };
	const unsigned int change_num = chip_num / parallel_num;
	unsigned int aligned_file_size;  //start from 1; max chip: 4*240 = 960 
	unsigned int val=0;
	unsigned int x = 0;

	unsigned int all_byte_length;

					



	for (file_index = chip_sel; file_index < change_num; file_index++) {
			
				Files_ParallelLoadMem_Upload(file_index, cell_start_addr, byte_length,
									gdma_index, gdma_addroffset[gdma_index], change_num, hw_type, chip_row_table,  chip_col_table, chip_direction_sel); //load mem with header;															
	

				// user_write(TITLE_VALID_LENGTH,byte_length/2);//one valid contain 2 byte_length

				all_byte_length=byte_length*6;

			if(all_byte_length%16!=0||all_byte_length%24!=0)//byte_length must be divisible by 16 and 24
			{
				all_byte_length=all_byte_length/16+1;
				all_byte_length=all_byte_length<<4;
				while (all_byte_length%24!=0)
				{
					all_byte_length=all_byte_length+16;
				}
	
				
			}

	
					Gdma_RegConfig(0, 
						0, 0, 144-16, //head 120, so 144
						0x10000, 0, all_byte_length-16,//44
						RD_WR_FLAG    //RD_FLAG RD_WR_FLAG
						);
					//read_interrupt(0);
				while ((val&gtp_state) != gtp_state)
					val=user_read(GPIO_IREG);
				val = 0;				
			
			Files_ParallelReadMem_Upload(path_prefix, file_index,  all_byte_length, gdma_index, change_num, chip_num_table);
	}



	// //every gdma has 64 file
	// //cout << "file_index: " ;
	// for (file_index = chip_sel; file_index < change_num; ) {
	// 	//cout << file_index  << " ";
 	// 	//preprocess;
	// 	for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) { //read 4 gdma file size;
	// 		//32bit address alignment tunning;
	// 		if (byte_length % 4 != 0) 
	// 			aligned_file_size[gdma_index][file_index] = ((byte_length >> 2) + 1) << 2;
	// 		else 
	// 			aligned_file_size[gdma_index][file_index] = byte_length;
				
	// 		//judgement of file size fitness;
	// 		if ((aligned_file_size[gdma_index][file_index] > GDMA_ADDR_LIMIT) || (aligned_file_size[gdma_index][file_index] < 20)) 
	// 			file_unsupport_flag = 1;
	// 		else if (aligned_file_size[gdma_index][file_index] + gdma_addroffset[gdma_index] > GDMA_ADDR_LIMIT) 
	// 			file_overflow_flag = 1;
	// 	}
	// 	start = clock();	
	// 	if (!file_unsupport_flag && !file_overflow_flag) { //only under this condition data will be write to 4 gdma ddr;
	
	// 		for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) {
	// 			Files_LoadMem_Upload(file_index, cell_start_addr, aligned_file_size[gdma_index][file_index],
	// 								gdma_index, gdma_addroffset[gdma_index], change_num, hw_type, chip_row_table,  chip_col_table); //load mem with header;															
	// 			#ifdef SERDES_ON		
	// 				Gdma_RegConfig(gdma_index, 
	// 					gdma_base[gdma_index] + gdma_addroffset[gdma_index], 0, (5 - 1) << 2, 
	// 					gdma_base[gdma_index] + gdma_addroffset[gdma_index], 0, aligned_file_size[gdma_index][file_index] - 4,
	// 					RD_WR_FLAG
	// 					);
	// 				//read_interrupt(0);
	// 			while ((val&gtp_state) != gtp_state)
	// 				val=user_read(GPIO_IREG);
	// 			val = 0;				
	// 			#endif  
	// 			gdma_addroffset[gdma_index] += aligned_file_size[gdma_index][file_index];
	// 		}
	// 	}
	// 	end = clock();
	// 	//cout << endl << "wait data time cost: " <<  (double)(end - start) / CLOCKS_PER_SEC *1000  << endl;
	// 	//postprocess;
	// 	if (file_unsupport_flag == 1) {  //exit;
	// 		#ifdef PRINT_INFO
	// 		cout << endl << "Files_ParallelUpload_ALL: unsupported byte_length" << endl;
	// 		#endif
	// 		return;
	// 	}
	// 	else if ( file_overflow_flag == 1 ) {   //the gdma mem space is full, or it is the last file, prepare to recv;
   	// 		#ifdef PRINT_INFO
	// 		cout  << endl << "Files overflow, parepare to upload: " << endl;
	// 		#endif
			
	// 		for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) 
	// 			Files_ReadMem_Upload(path_prefix, file_index_start,  aligned_file_size[gdma_index], gdma_index, change_num, chip_num_table);

	// 		#ifdef PRINT_INFO
	// 		cout  << "Files_ParallelUpload_All: recv complete" << endl;
	// 		#endif
	// 		//param adjust;
	// 		for (gdma_index = 0; gdma_index < parallel_num; gdma_index++)
	// 			gdma_addroffset[gdma_index] = 0;
	// 		file_index_start = file_index;
	// 		file_overflow_flag = 0;
	// 		if ( file_index == change_num-1 ) //the last file but not overflow;
	// 			file_index++;
	// 	}
	// else if ( file_index == change_num-1 &&  up_flag == 0) {   //the gdma mem space is full, or it is the last file, prepare to recv;	
	// 			#ifdef PRINT_INFO
	// 			cout  << endl  << "This gdma received all data, parepare to upload: " << endl;
	// 			#endif
	// 			start = clock();		
	// 			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) 
	// 					Files_ReadMem_Upload(path_prefix, file_index_start, aligned_file_size[gdma_index], gdma_index, change_num, chip_num_table);		
	// 		end = clock();
	// 		//cout << endl << "updata time cost: " << (double)(end - start) / CLOCKS_PER_SEC *1000  << endl;
	// 			#ifdef PRINT_INFO
	// 			cout << "Files_ParallelUpload_All: recv complete" << endl;
	// 			#endif
	// 			//param adjust;
	// 			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++)
	// 					gdma_addroffset[gdma_index] = 0;
	// 			file_index_start = file_index;
	// 			file_overflow_flag = 0;
	// 			if ((file_index == change_num-1) && (file_overflow_flag != 1)) //the last file but not overflow;
	// 					file_index++;
	// }
	// 	else
	// 		file_index++;
	// }
	return;
}

void Files_Upload_ALL(char *path_prefix, unsigned int cell_start_addr, unsigned int byte_length, unsigned char parallel_num, 
																unsigned int chip_num, unsigned int chip_sel, unsigned int hw_type, string ** chip_num_table, uint32_t** chip_row_table,  uint32_t ** chip_col_table, bool up_flag) {
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	unsigned char gdma_index = 0;
	unsigned int file_index = 0;
	unsigned int file_index_start = chip_sel;
	unsigned char file_overflow_flag = 0, file_unsupport_flag = 0;
	unsigned int gdma_addroffset[4] = { 0, 0, 0, 0 };
	const unsigned int change_num = chip_num / parallel_num;
	unsigned int aligned_file_size[4][240];  //start from 1; max chip: 4*240 = 960 
	unsigned int val=0;
	unsigned int x = 0;
	clock_t start, end;

	//every gdma has 64 file
	//cout << "file_index: " ;
	for (file_index = chip_sel; file_index < change_num; ) {
		//cout << file_index  << " ";
 		//preprocess;
		for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) { //read 4 gdma file size;
			//32bit address alignment tunning;
			if (byte_length % 4 != 0) 
				aligned_file_size[gdma_index][file_index] = ((byte_length >> 2) + 1) << 2;
			else 
				aligned_file_size[gdma_index][file_index] = byte_length;
				
			//judgement of file size fitness;
			if ((aligned_file_size[gdma_index][file_index] > GDMA_ADDR_LIMIT) || (aligned_file_size[gdma_index][file_index] < 20)) 
				file_unsupport_flag = 1;
			else if (aligned_file_size[gdma_index][file_index] + gdma_addroffset[gdma_index] > GDMA_ADDR_LIMIT) 
				file_overflow_flag = 1;
		}
		start = clock();	
		if (!file_unsupport_flag && !file_overflow_flag) { //only under this condition data will be write to 4 gdma ddr;
	
			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) {
				Files_LoadMem_Upload(file_index, cell_start_addr, aligned_file_size[gdma_index][file_index],
									gdma_index, gdma_addroffset[gdma_index], change_num, hw_type, chip_row_table,  chip_col_table); //load mem with header;															
				#ifdef SERDES_ON		
					Gdma_RegConfig(gdma_index, 
						gdma_base[gdma_index] + gdma_addroffset[gdma_index], 0, (5 - 1) << 2, 
						gdma_base[gdma_index] + gdma_addroffset[gdma_index], 0, aligned_file_size[gdma_index][file_index] - 4,
						RD_WR_FLAG
						);
					//read_interrupt(0);
				while ((val&gtp_state) != gtp_state)
					val=user_read(GPIO_IREG);
				val = 0;				
				#endif  
				gdma_addroffset[gdma_index] += aligned_file_size[gdma_index][file_index];
			}
		}
		end = clock();
		//cout << endl << "wait data time cost: " <<  (double)(end - start) / CLOCKS_PER_SEC *1000  << endl;
		//postprocess;
		if (file_unsupport_flag == 1) {  //exit;
			#ifdef PRINT_INFO
			cout << endl << "Files_ParallelUpload_ALL: unsupported byte_length" << endl;
			#endif
			return;
		}
		else if ( file_overflow_flag == 1 ) {   //the gdma mem space is full, or it is the last file, prepare to recv;
   			#ifdef PRINT_INFO
			cout  << endl << "Files overflow, parepare to upload: " << endl;
			#endif
			
			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) 
				Files_ReadMem_Upload(path_prefix, file_index_start,  aligned_file_size[gdma_index], gdma_index, change_num, chip_num_table);

			#ifdef PRINT_INFO
			cout  << "Files_ParallelUpload_All: recv complete" << endl;
			#endif
			//param adjust;
			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++)
				gdma_addroffset[gdma_index] = 0;
			file_index_start = file_index;
			file_overflow_flag = 0;
			if ( file_index == change_num-1 ) //the last file but not overflow;
				file_index++;
		}
	else if ( file_index == change_num-1 &&  up_flag == 0) {   //the gdma mem space is full, or it is the last file, prepare to recv;	
				#ifdef PRINT_INFO
				cout  << endl  << "This gdma received all data, parepare to upload: " << endl;
				#endif
				start = clock();		
				for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) 
						Files_ReadMem_Upload(path_prefix, file_index_start, aligned_file_size[gdma_index], gdma_index, change_num, chip_num_table);		
			end = clock();
			//cout << endl << "updata time cost: " << (double)(end - start) / CLOCKS_PER_SEC *1000  << endl;
				#ifdef PRINT_INFO
				cout << "Files_ParallelUpload_All: recv complete" << endl;
				#endif
				//param adjust;
				for (gdma_index = 0; gdma_index < parallel_num; gdma_index++)
						gdma_addroffset[gdma_index] = 0;
				file_index_start = file_index;
				file_overflow_flag = 0;
				if ((file_index == change_num-1) && (file_overflow_flag != 1)) //the last file but not overflow;
						file_index++;
	}
		else
			file_index++;
	}
	return;
}

//read mem data and write to files;
//1 gdma every block correspond to 1 file;
void Files_ReadALL_Upload( char *path_prefix,  uint32_t upload_size, 
																unsigned char gdma_index) {
	unsigned int path_len = 0;
	unsigned int i = 0;
	char *file_path = NULL; 
	unsigned char *file_buffer;
	unsigned int transfer_round;
	unsigned int transfer_round_limit;
	unsigned int gdma_addroffset = 0;
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	unsigned int index = 0;
	FILE *fp = NULL;
	char  tmp_char []= ".bin";

//copy path prefix;
	path_len = strlen((const char *)path_prefix);
	file_path = (char *)malloc((path_len + 100)*sizeof(char));
	file_buffer = (unsigned char *)malloc(OneWriteFileSize * sizeof(unsigned char));
	for (i = 0; i < path_len; i++)
		file_path[i] = path_prefix[i];
	for (i = 0; i < 5; i++)
				file_path[i + path_len] = tmp_char[i];
#ifdef PRINT_INFO
	//if (file_index == 0 && gdma_index ==0) {
		cout << "upload: " << file_path << endl; 
	//}
#endif	
		
#ifdef OS_WIN		
	//fopen_s(&fp, file_path, "wb+");
	fp = fopen(file_path,"ab+");
#else

	fp = fopen(file_path,"wb+");
#endif
	if (fp == NULL)
		cout << "Files_ReadMem_Upload: fopen_s failed" << endl;
	if (upload_size % OneWriteFileSize == 0)
		transfer_round_limit =upload_size / OneWriteFileSize;
	else
		transfer_round_limit =upload_size / OneWriteFileSize + 1;
	for (transfer_round = 0; transfer_round < transfer_round_limit; transfer_round++) {
		if (transfer_round == transfer_round_limit - 1) {
			/* USB_ReadWrite(dev_handle, USB_EP1_IN, file_buffer, gdma_base[gdma_index] + gdma_addroffset, 
							aligned_file_size[file_index] - transfer_round*OneWriteFileSize); */
			c2h_transfer(gdma_base[gdma_index] + gdma_addroffset, (upload_size - transfer_round*OneWriteFileSize) , (unsigned char *)file_buffer);

			fwrite(file_buffer, sizeof(unsigned char), upload_size - transfer_round*OneWriteFileSize, fp);
			gdma_addroffset += (upload_size - transfer_round*OneWriteFileSize);
		}
		else {
			//USB_ReadWrite(dev_handle, USB_EP1_IN, file_buffer, gdma_base[gdma_index] + gdma_addroffset, OneWriteFileSize);
			c2h_transfer(gdma_base[gdma_index] + gdma_addroffset, (OneWriteFileSize), (unsigned char *)file_buffer);
			fwrite(file_buffer, sizeof(unsigned char), OneWriteFileSize, fp);
			gdma_addroffset += OneWriteFileSize;
		}
	}
	fclose(fp);
	free(file_path);
	free(file_buffer);
	return;
}



void remote_setup(unsigned int cell_start_addr, unsigned char parallel_num, unsigned int chip_num, unsigned int chip_sel, 
																	bool extern_spike, unsigned int hw_type, string ** chip_num_table, unsigned int** chip_row_table,  unsigned int ** chip_col_table, unsigned int chip_direction_sel){
	unsigned int file_index = 0;
	unsigned int aligned_file_size = 0;
	unsigned char gdma_index = 0;
	unsigned char file_overflow_flag = 0, file_unsupport_flag = 0;
	unsigned int i = 0;
	unsigned int val=0;
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	unsigned int prefix_len = 0, postfix_len = 0;
	long file_size = 0;
	unsigned int gdma_addroffset[4] = { 0, 0, 0, 0 };
	unsigned int send_byte_length[4] = { 0xcccccccc, 0xcccccccc, 0xcccccccc, 0xcccccccc };  //start from 0;
	const unsigned int change_num = chip_num / parallel_num;
	file_size = 8;//8 byte remote
	for (file_index = chip_sel; file_index < change_num; file_index++) {

	aligned_file_size = LoadRemote_Download(0,1, gdma_index, file_index, file_size,
		gdma_addroffset[gdma_index], cell_start_addr, change_num, extern_spike,hw_type, chip_row_table,  chip_col_table, chip_direction_sel); //load mem with current file;

	gdma_addroffset[gdma_index] += (aligned_file_size + 20); //file size and additional 28byte remote;
	Gdma_RegConfig(gdma_index, gdma_base[gdma_index], 0, 192-16, 0, 0, 0,RD_FLAG);//44
			while ((val&gtp_state) != gtp_state)
		{
			val=user_read(GPIO_IREG);
			//printf("val=%d\n",val); 
	
		}
	}
	return;
}

unsigned int LoadRemote_Download(unsigned int remote_x, unsigned int remote_y,unsigned char gdma_index, unsigned int file_index, 
					long file_size, unsigned int gdma_addroffset, unsigned int cell_start_addr, unsigned int change_num, bool extern_spike,unsigned int hw_type, uint32_t** chip_row_table,  uint32_t ** chip_col_table, unsigned int chip_direction_sel) {
	unsigned int i;
	unsigned char *file_buffer=NULL;
	unsigned int transfer_round;
	unsigned int aligned_file_size;  //start from 1;
	unsigned int transfer_round_limit;
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	unsigned int chip_pos;
	unsigned int word_length;
	unsigned int cmd = 0x47545057; //GTPW
	unsigned int byte_length;
	unsigned int parallel_num;
	if (file_size % 4 != 0)   //32bit address alignment tunning;
		aligned_file_size = ((file_size >> 2) + 1) << 2;
	else
		aligned_file_size = file_size;
	file_buffer = (unsigned char *)malloc(USB_TRANSFER_LIMIT*sizeof(unsigned char));

	word_length = 3 + (aligned_file_size >> 2) - 1;

		byte_length = ((aligned_file_size >> 2) - 1) << 2;
	//byte_length = aligned_file_size - 1;
	switch (hw_type) {
	case 0:
		byte_length = ((aligned_file_size >> 2) - 1) << 2;  
		break;
	case 1:
		byte_length = aligned_file_size-1;	
		break;
	default:
		byte_length = ((aligned_file_size >> 2) - 1) << 2;  
                break;
	}

	 for (parallel_num = 0; parallel_num < 6; parallel_num++){
		

		//choose chip direction for setting correct data header 
		switch (chip_direction_sel) { 
		case 0: 
			chip_pos = (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index));//north header
			break;
		case 1:
			chip_pos = (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index));//west header
			break;
		case 2:
			chip_pos = (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index));//south header (north header)
			break;
		case 3:
			chip_pos = (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index));//east header  (west header)
			break;
		default:
			chip_pos = (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index));//north header
			break;
		}	

		// chip_pos = (*((uint32_t *)chip_row_table + parallel_num) << 8) | (*((uint32_t *)chip_col_table + parallel_num));
		// chip_pos = (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index));
		// chip_pos = (*((uint32_t *)chip_col_table + parallel_num*change_num+file_index) << 8) | (*((uint32_t *)chip_row_table + parallel_num*change_num+file_index));//north 
		*(unsigned int *)(file_buffer + 4*parallel_num) = chip_pos;
	
		*(unsigned int *)(file_buffer + 4*6+4*parallel_num) = word_length;
		*(unsigned int *)(file_buffer + 4*12+4*parallel_num) = cmd;
		*(unsigned int *)(file_buffer + 4*18+4*parallel_num) = cell_start_addr;
		*(unsigned int *)(file_buffer + 4*24+4*parallel_num) = byte_length;
		switch (chip_direction_sel) { 
			case 0: 
				*(unsigned int *)(file_buffer + 4*30+4*parallel_num) = 0;
				*(unsigned int *)(file_buffer + 4*36+4*parallel_num) = 1+parallel_num;
				break;

			case 1: 
				*(unsigned int *)(file_buffer + 4*30+4*parallel_num) = 1+parallel_num;               //y
				*(unsigned int *)(file_buffer + 4*36+4*parallel_num) = 0;  //x
				break;

			case 2: 
				*(unsigned int *)(file_buffer + 4*30+4*parallel_num) = 7;
				*(unsigned int *)(file_buffer + 4*36+4*parallel_num) = 1+parallel_num;
				break;

			case 3: 
				*(unsigned int *)(file_buffer + 4*30+4*parallel_num) = 1+parallel_num;               //y
				*(unsigned int *)(file_buffer + 4*36+4*parallel_num) = 7;  //x
				break;

			default:
				*(unsigned int *)(file_buffer + 4*30+4*parallel_num) = 0;               //y
				*(unsigned int *)(file_buffer + 4*36+4*parallel_num) = 1+parallel_num;  //x
				break;
		}
	}

// 	chip_pos = (*((uint32_t *)chip_row_table + gdma_index * change_num+ file_index) << 8) | (*((uint32_t *)chip_col_table + gdma_index * change_num+ file_index));
// //transfer header;
// 	*(unsigned int *)file_buffer = chip_pos;
// 	*(unsigned int *)(file_buffer + 4) = chip_pos;
// 	*(unsigned int *)(file_buffer + 8) = chip_pos;
// 	*(unsigned int *)(file_buffer + 12) = chip_pos;
// 	*(unsigned int *)(file_buffer + 16) = chip_pos;
// 	*(unsigned int *)(file_buffer + 20) = chip_pos;
// 	word_length = 3 + (aligned_file_size >> 2) - 1;
// 	*(unsigned int *)(file_buffer + 24) = word_length;
// 	*(unsigned int *)(file_buffer + 28) = word_length;
// 	*(unsigned int *)(file_buffer + 32) = word_length;
// 	*(unsigned int *)(file_buffer + 36) = word_length;
// 	*(unsigned int *)(file_buffer + 40) = word_length;
// 	*(unsigned int *)(file_buffer + 44) = word_length;
// 	*(unsigned int *)(file_buffer + 48) = cmd;
// 	*(unsigned int *)(file_buffer + 52) = cmd;
// 	*(unsigned int *)(file_buffer + 56) = cmd;
// 	*(unsigned int *)(file_buffer + 60) = cmd;
// 	*(unsigned int *)(file_buffer + 64) = cmd;
// 	*(unsigned int *)(file_buffer + 68) = cmd;
// 	*(unsigned int *)(file_buffer + 72) = cell_start_addr;
// 	*(unsigned int *)(file_buffer + 76) = cell_start_addr;
// 	*(unsigned int *)(file_buffer + 80) = cell_start_addr;
// 	*(unsigned int *)(file_buffer + 84) = cell_start_addr;
// 	*(unsigned int *)(file_buffer + 88) = cell_start_addr;
// 	*(unsigned int *)(file_buffer + 92) = cell_start_addr;
	

// 	*(unsigned int *)(file_buffer + 96) = byte_length;
// 	*(unsigned int *)(file_buffer + 100) = byte_length;
// 	*(unsigned int *)(file_buffer + 104) = byte_length;
// 	*(unsigned int *)(file_buffer + 108) = byte_length;
// 	*(unsigned int *)(file_buffer + 112) = byte_length;
// 	*(unsigned int *)(file_buffer + 116) = byte_length;
// 	*(unsigned int *)(file_buffer + 120) = remote_x;
// 	*(unsigned int *)(file_buffer + 124) = remote_x;
// 	*(unsigned int *)(file_buffer + 128) = remote_x;
// 	*(unsigned int *)(file_buffer + 132) = remote_x;
// 	*(unsigned int *)(file_buffer + 136) = remote_x;
// 	*(unsigned int *)(file_buffer + 140) = remote_x;

// 	*(unsigned int *)(file_buffer + 144) = remote_y;
// 	*(unsigned int *)(file_buffer + 148) = remote_y;
// 	*(unsigned int *)(file_buffer + 152) = remote_y;
// 	*(unsigned int *)(file_buffer + 156) = remote_y;
// 	*(unsigned int *)(file_buffer + 160) = remote_y;
// 	*(unsigned int *)(file_buffer + 164) = remote_y;



	
	h2c_transfer(0, 168, (unsigned char *)file_buffer);
		// h2c_transfer(0, 168, (unsigned char *)file_buffer);
	gdma_addroffset += 28;		
	

	return 168;
}









//the file is split into 8MB chunks to send;
unsigned int Files_LoadMem_Download(FILE *fp, unsigned char gdma_index, unsigned int file_index, 
					long file_size, unsigned int gdma_addroffset, unsigned int cell_start_addr, unsigned int change_num, bool extern_spike,unsigned int hw_type, uint32_t** chip_row_table,  uint32_t ** chip_col_table) {
	unsigned int i;
	unsigned char *file_buffer=NULL;
	// unsigned char *buf1=NULL;
	unsigned int transfer_round;
	unsigned int aligned_file_size;  //start from 1;
	unsigned int transfer_round_limit;
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	unsigned int chip_pos;
	unsigned int word_length;
	unsigned int cmd = 0x47545057; //GTPW
	unsigned int byte_length;
	

	
	if (file_size % 4 != 0)   //32bit address alignment tunning;
		aligned_file_size = ((file_size >> 2) + 1) << 2;
	else
		aligned_file_size = file_size;
	file_buffer = (unsigned char *)malloc(USB_TRANSFER_LIMIT*sizeof(unsigned char));
	// buf1 = (unsigned char *)malloc(USB_TRANSFER_LIMIT*sizeof(unsigned char));
	chip_pos = (*((uint32_t *)chip_row_table + gdma_index * change_num+ file_index) << 8) | (*((uint32_t *)chip_col_table + gdma_index * change_num+ file_index));
//transfer header;
	*(unsigned int *)file_buffer = chip_pos;
	word_length = 3 + (aligned_file_size >> 2) - 1;
	*(unsigned int *)(file_buffer + 4) = word_length;
	*(unsigned int *)(file_buffer + 8) = cmd;
	*(unsigned int *)(file_buffer + 12) = cell_start_addr;
	byte_length = ((aligned_file_size >> 2) - 1) << 2;
	//byte_length = aligned_file_size - 1;
	switch (hw_type) {
	case 0:
		byte_length = ((aligned_file_size >> 2) - 1) << 2;  
		break;
	case 1:
		byte_length = aligned_file_size-1;	
		break;
	default:
		byte_length = ((aligned_file_size >> 2) - 1) << 2;  
                break;
	}
	*(unsigned int *)(file_buffer + 16) = byte_length;

	if (!extern_spike) {
		//printf("chip_pos = %d\r\n", chip_pos);
		//printf("gdma_index = %d\r\n", gdma_index);
		//cout << "send normal cmd mode" << endl;
	//	USB_ReadWrite(dev_handle, USB_EP1_OUT, file_buffer, gdma_base[gdma_index] + gdma_addroffset, 20);
	

//		h2c_transfer(0, 1024 * 4, (unsigned char *)buf1);
		h2c_transfer(gdma_base[gdma_index] + gdma_addroffset, 20, (unsigned char *)file_buffer);
		//c2h_transfer(gdma_base[gdma_index] + gdma_addroffset, 20 , (unsigned char *)buf1);
		gdma_addroffset += 20;		
	}
	else {
		cout << "extern spike mode" << endl;
	}
//transfer file data;
	if (aligned_file_size % USB_TRANSFER_LIMIT == 0)
		transfer_round_limit = aligned_file_size / USB_TRANSFER_LIMIT;
	else
		transfer_round_limit = aligned_file_size / USB_TRANSFER_LIMIT + 1;

	//printf("transfer_round_limit = %d\n",transfer_round_limit);
	for (transfer_round = 0; transfer_round < transfer_round_limit; transfer_round++) {
		if (transfer_round == transfer_round_limit - 1) {
			fread(file_buffer, sizeof(unsigned char), file_size - transfer_round*USB_TRANSFER_LIMIT,fp);
			for (i = 0; i < aligned_file_size - file_size; i++)
				file_buffer[i + file_size - transfer_round*USB_TRANSFER_LIMIT] = 0; //add 0 to remaining bytes;
			//USB_ReadWrite(dev_handle, USB_EP1_OUT, file_buffer, gdma_base[gdma_index] + gdma_addroffset, aligned_file_size - transfer_round*USB_TRANSFER_LIMIT);
			h2c_transfer(gdma_base[gdma_index] + gdma_addroffset, (aligned_file_size - transfer_round*USB_TRANSFER_LIMIT) , (unsigned char *)file_buffer);
		}
		else {
			fread(file_buffer, sizeof(unsigned char), USB_TRANSFER_LIMIT, fp);
			//USB_ReadWrite(dev_handle, USB_EP1_OUT, file_buffer, gdma_base[gdma_index] + gdma_addroffset, USB_TRANSFER_LIMIT);
			h2c_transfer(gdma_base[gdma_index] + gdma_addroffset, (USB_TRANSFER_LIMIT), (unsigned char *)file_buffer);
			gdma_addroffset += USB_TRANSFER_LIMIT;
		}
	}

//	c2h_transfer(0, (2048)* 4, (unsigned char *)buf1);

	free(file_buffer);
	// free(buf1);
	return aligned_file_size;
}



//load mem with headers in upload;
void Files_LoadMem_Upload(unsigned int file_index, unsigned int cell_start_addr,
						  unsigned int aligned_file_size, unsigned char gdma_index, unsigned int gdma_addroffset, unsigned int change_num,unsigned int hw_type,  uint32_t** chip_row_table,  uint32_t ** chip_col_table) {
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	unsigned int *header_buffer;
	unsigned int chip_pos;
	unsigned int cmd = 0x47545052;   //GTPR;

//load header data;
	header_buffer = (unsigned int *)malloc(5 * sizeof(unsigned int));
	chip_pos = (*((uint32_t *)chip_row_table + gdma_index * change_num+ file_index) << 8) | (*((uint32_t *)chip_col_table + gdma_index * change_num+ file_index));
	header_buffer[0] = chip_pos;
	header_buffer[1] = (3 - 1);   //word_length;
	header_buffer[2] = cmd;
	header_buffer[3] = cell_start_addr;
	//header_buffer[4] =  ((aligned_file_size >> 2) - 1) << 2;
	switch (hw_type) { 
	case 0: 
		header_buffer[4] =  ((aligned_file_size >> 2) - 1) << 2;
		break;
	case 1:
		header_buffer[4] = aligned_file_size-1;
		break;
	default:
                header_buffer[4] =  ((aligned_file_size >> 2) - 1) << 2;
                break;
	}	
	//USB_ReadWrite(dev_handle, USB_EP1_OUT, (unsigned char *)header_buffer, gdma_base[gdma_index] + gdma_addroffset, 20);
	h2c_transfer(gdma_base[gdma_index] + gdma_addroffset, 20, (unsigned char *)header_buffer);
	//cout << "Load read cmd header into DDR" << endl;
	free(header_buffer);
	return;
}


void Files_ReadMem_Upload( char *path_prefix, unsigned int file_index_start, unsigned int *aligned_file_size, 
																unsigned char gdma_index, uint32_t change_num, string ** chip_num_table) {
	unsigned int path_len = 0;
	unsigned int i = 0;
	char *file_path = NULL; 
	unsigned char *file_buffer;
	unsigned int transfer_round;
	unsigned int transfer_round_limit;
	unsigned int gdma_addroffset = 0;
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	unsigned int index = 0;
	FILE *fp = NULL;

//copy path prefix;
	path_len = strlen((const char *)path_prefix);
	file_path = (char *)malloc((path_len + 100)*sizeof(char));
	file_buffer = (unsigned char *)malloc(OneWriteFileSize * sizeof(unsigned char));
	for (i = 0; i < path_len; i++)
		file_path[i] = path_prefix[i];
	for (uint32_t file_index = file_index_start; file_index < change_num; 	file_index++) {
		char * tmp_char = (char *) (*((string *)chip_num_table + gdma_index * change_num+ file_index) ).data();
		// cout << strlen(tmp_char)  << endl;
		for (i = 0; i < 9; i++)
					file_path[i + path_len] = tmp_char[i];
#ifdef PRINT_INFO
		//if (file_index == 0 && gdma_index ==0) {
			cout << "upload: " << file_path << endl; 
		//}
#endif	
			
#ifdef OS_WIN		
		//fopen_s(&fp, file_path, "wb+");
		fp = fopen(file_path,"ab+");
#else
	
		fp = fopen(file_path,"wb+");
#endif
		if (fp == NULL)
			cout << "Files_ReadMem_Upload: fopen_s failed" << endl;
		if (aligned_file_size[file_index] % OneWriteFileSize == 0)
			transfer_round_limit = aligned_file_size[file_index] / OneWriteFileSize;
		else
			transfer_round_limit = aligned_file_size[file_index] / OneWriteFileSize + 1;
		for (transfer_round = 0; transfer_round < transfer_round_limit; transfer_round++) {
			if (transfer_round == transfer_round_limit - 1) {
				c2h_transfer(gdma_base[gdma_index] + gdma_addroffset, (aligned_file_size[file_index] - transfer_round*OneWriteFileSize) , (unsigned char *)file_buffer);
				fwrite(file_buffer, sizeof(unsigned char), aligned_file_size[file_index] - transfer_round*OneWriteFileSize, fp);
				gdma_addroffset += (aligned_file_size[file_index] - transfer_round*OneWriteFileSize);
			}
			else {
				c2h_transfer(gdma_base[gdma_index] + gdma_addroffset, (OneWriteFileSize), (unsigned char *)file_buffer);
				fwrite(file_buffer, sizeof(unsigned char), OneWriteFileSize, fp);
				gdma_addroffset += OneWriteFileSize;
			}
		}
		fclose(fp);
	}
	free(file_path);
	free(file_buffer);
	return;
}
