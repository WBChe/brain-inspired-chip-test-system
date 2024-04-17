 #include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
//#include <AtlBase.h>
#include "pcie_fun.h"
#include "zcu102_sender_global.h"
#include "gdma.h"
#include <unistd.h>

#include <iostream>						//bin file check
#include <fstream>						//bin file check

#pragma comment(lib, "setupapi.lib")
#pragma warning(disable:4996)
typedef unsigned char BYTE;
typedef unsigned long DWORD;
BYTE   start_en;
DWORD  user_irq_ack[1],readbuf[1];
unsigned int gtp_state;

//#define OS_WIN
#pragma pack(1)

struct run_parameter {
	unsigned int parallel_num;
	unsigned int chip_num;
	unsigned int chip_sel;


	char downloadPath_DOR[100];
	char uploadPath_DOR[100];

	unsigned int row_max;
	unsigned int col_max;
	bool extern_spike;
	unsigned char  mode;
	unsigned int hw_type;
	
	unsigned int CELL_REMOTE_BASE		;
	unsigned int CELL_PROPERTY_BASE	    ;
	unsigned int CELL_ROUTE_INFO_BASE	;
										
	unsigned int CELL_TILE_ID_BASE		;
	unsigned int CELL_NDMA_STADDR_BASE	;
	unsigned int CELL_NPU_CTRL_BASE	    ;
	unsigned int CELL_SP_SIZE_BASE		;
										
	unsigned int CELL_SMT_BRAM_BASE	    ;
	unsigned int CELL_SP_BRAM_BASE		;
	unsigned int CELL_SP_CNT_BRAM_BASE	;
	unsigned int CELL_WEIGHT_BRAM_BASE	;
	unsigned int READ_WEIGHT_ADDR		;
	
	unsigned int sample_num;
	unsigned int step_count;
	unsigned int neu_num;

	char xdma_num[10];
};
#pragma pack()

//bin file check
bool Compare_Binfile(const std::string& file1, const std::string& file2) {
    std::ifstream f1(file1, std::ios::binary);
    std::ifstream f2(file2, std::ios::binary);

    if (!f1.is_open() || !f2.is_open()) {	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        std::cout << "Failed to open files." << std::endl;
        return false;
    }

    char c1, c2;
    while (f1.get(c1) && f2.get(c2)) {
        if (c1 != c2) {
            f1.close();
            f2.close();
			//data error : data bit error
			cout << "compare bin file fail                  : weight_check_" + file2 << endl;
            return false;
        }
    }
	
    // Check if both files reached end at the same time
	f1.get(c1);
	f2.get(c2);
    if (f1.eof() && f2.eof()) {
        f1.close();
        f2.close();
		cout << "compare bin file success : weight_check_" + file2 << endl;
        return true;
    }

    f1.close();
    f2.close();
	//data error : data overflow
	cout << "compare bin file fail                  : weight_check_" + file2 << endl;
    return false;
}

void print_FAIL() {
    std::cout << "FFFFFF " << "    A    " << " IIIII " << " L      \n";
    std::cout << "F      " << "   A A   " << "   I   " << " L      \n";
    std::cout << "F      " << "  A   A  " << "   I   " << " L      \n";
    std::cout << "FFFFF  " << " AAAAAAA " << "   I   " << " L      \n";
    std::cout << "F      " << " A     A " << "   I   " << " L      \n";
	std::cout << "F      " << " A     A " << "   I   " << " L      \n";
	std::cout << "F      " << " A     A " << " IIIII " << " LLLLL  \n";
	exit(EXIT_FAILURE);
}

void print_PASS() {
	std::cout << "PPPPPP   " << "    A    " << "  SSSSS  " << "  SSSSS  \n";
    std::cout << "P     P  " << "   A A   " << " S     S " << " S     S \n";
   	std::cout << "P     P  " << "  A   A  " << " S       " << "         \n";
   	std::cout << "PPPPPP   " << " AAAAAAA " << "  SSSSS  " << "  SSSSS  \n";
    std::cout << "P        " << " A     A " << "       S " << "       S \n";
    std::cout << "P        " << " A     A " << " S     S " << " S     S \n";
    std::cout << "P        " << " A     A " << "  SSSSS  " << "  SSSSS  \n";
}

void Data_Test(run_parameter parameter, string ** chip_num_table, unsigned int** chip_row_table,  unsigned int ** chip_col_table) {
	
	unsigned int index = 0;
	
        string download_DOR(parameter.downloadPath_DOR);
        string remote4_DOR                      = download_DOR + "/remote6_north/remote4";
        string property_DOR                     = download_DOR + "/property/property";
        string npu_on_DOR                       = download_DOR + "/npu_ctrl/npu_on";
        string tile_id_DOR                      = download_DOR + "/tile_id/tile_id";
        string ndma_staddr_DOR             	= download_DOR + "/ndma_staddr/ndma_staddr";
        string smt_DOR                          = download_DOR + "/smt/smt";
        string route_info_DOR              	= download_DOR + "/route_info/route_info";
        string weight_DOR                       = download_DOR + "/weight_socket_test/weight";	  
 		// string weight_DOR                       = download_DOR + "/inc/inc";	  
		double tmp_cnt=0;
        //set remote reg
        cout << "Download remote reg, path: " << (char*)remote4_DOR.data() << endl;
        // Files_ParallelDownload_All((char*)remote4_DOR.data(),   parameter.CELL_REMOTE_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);

		//parameter chip_direction_sel (0, 1, 2, 3) <->(north, west, south, east)
		remote_setup( parameter.CELL_REMOTE_BASE,parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);
	

		// remote_setup( parameter.CELL_REMOTE_BASE,parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        // //set npu_ctrl reg
        // cout << "Download npu_ctrl reg, path: " << (char*)npu_on_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)npu_on_DOR.data(), parameter.CELL_NPU_CTRL_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        //set tile_id reg
        // cout << "Download tile_id reg, path: " << (char*)tile_id_DOR.data() << endl;
        // Files_ParallelDownload_All((char*)tile_id_DOR.data(), parameter.CELL_TILE_ID_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        // //set ndma_staddr reg
        // cout << "Download ndma_staddr reg, path: " << (char*)ndma_staddr_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)ndma_staddr_DOR.data(), parameter.CELL_NDMA_STADDR_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        // //router bram
        // cout << "Download router bram, path: " << (char*)route_info_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)route_info_DOR.data(), parameter.CELL_ROUTE_INFO_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);

        // //smt bram
        // cout << "Download smt bram, path: " << (char*)smt_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)smt_DOR.data(), parameter.CELL_SMT_BRAM_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);

        //weight bram
        cout << "Download weight bram, path: " << (char*)weight_DOR.data() << endl;
        Files_ParallelDownload_All( (char*)weight_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE,
                                                                        parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);

		// Files_Download_All( (char*)weight_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE,
        //                                                                 parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
		string upload_DOR(parameter.uploadPath_DOR); 
        string weight_check_prefix_DOR 	        = upload_DOR + "/step" + to_string(index) + "/weight_check/weight_check";
        string smt_check_prefix_DOR 	        = upload_DOR + "/step" + to_string(index) + "/smt_check/smt_check";
        string route_check_prefix_DOR 	        = upload_DOR + "/step" + to_string(index) + "/route_check/route_check";
 
        cout << "prepare to upload test:" << endl; 
		// clock_t start, end;
		// start = clock();						
		Files_ParallelUpload_ALL( (char*)weight_check_prefix_DOR.data(),  parameter.CELL_WEIGHT_BRAM_BASE,    	64*1024 , //4*1024*1024
                                                                	parameter.parallel_num, parameter.chip_num, parameter.chip_sel, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0, 0);
		// end = clock();
		// tmp_cnt = (double)(end - start) / CLOCKS_PER_SEC;
		// cout << "upload time cost: " <<  tmp_cnt * 1000 << endl;

		//bin file check
		unsigned int i = 0;
		unsigned int error_cnt = 0;
		for (i = 0; i < 36; i++) {
			std::string bin_weight = "/home/gdiist/work/work_cwb/data/1k36chip_asic/weight_socket_test/weight_" + std::to_string(i) +".bin";
			//cout << bin_weight << endl;
    		std::string bin_weight_check = "/home/gdiist/work/work_cwb/upload/1k36chip_asic/step0/weight_check/weight_check_" + std::to_string(i) +".bin";
			//cout << bin_weight_check << endl;
			if(Compare_Binfile(bin_weight, bin_weight_check) == false){
				error_cnt = error_cnt + 1;
			}
		}
		if(error_cnt == 0) {
			cout << "chip north : " << endl;
			print_PASS();
		}
		else {
			cout << "Number of bin file errors (north) : " + std::to_string(error_cnt) << endl;
			print_FAIL();
		}
	// Files_Upload_ALL( (char*)weight_check_prefix_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE ,    	32, 
    //                                                             	parameter.parallel_num, parameter.chip_num, parameter.chip_sel, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);																
	return;
}

void Data_Test_West(run_parameter parameter, string ** chip_num_table, unsigned int** chip_row_table,  unsigned int ** chip_col_table) {
	
	unsigned int index = 0;
	
        string download_DOR(parameter.downloadPath_DOR);
        string remote4_DOR                      = download_DOR + "/remote6_west/remote4";
        string property_DOR                     = download_DOR + "/property/property";
        string npu_on_DOR                       = download_DOR + "/npu_ctrl/npu_on";
        string tile_id_DOR                      = download_DOR + "/tile_id/tile_id";
        string ndma_staddr_DOR             	= download_DOR + "/ndma_staddr/ndma_staddr";
        string smt_DOR                          = download_DOR + "/smt/smt";
        string route_info_DOR              	= download_DOR + "/route_info/route_info";
        string weight_DOR                       = download_DOR + "/weight_socket_test/weight";	  
 		// string weight_DOR                       = download_DOR + "/inc/inc";	  
		double tmp_cnt=0;
        //set remote reg
        cout << "Download remote reg, path: " << (char*)remote4_DOR.data() << endl;
        // Files_ParallelDownload_All((char*)remote4_DOR.data(),   parameter.CELL_REMOTE_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
		remote_setup( parameter.CELL_REMOTE_BASE,parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 1);
	

		// remote_setup( parameter.CELL_REMOTE_BASE,parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        // //set npu_ctrl reg
        // cout << "Download npu_ctrl reg, path: " << (char*)npu_on_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)npu_on_DOR.data(), parameter.CELL_NPU_CTRL_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        //set tile_id reg
        // cout << "Download tile_id reg, path: " << (char*)tile_id_DOR.data() << endl;
        // Files_ParallelDownload_All((char*)tile_id_DOR.data(), parameter.CELL_TILE_ID_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        // //set ndma_staddr reg
        // cout << "Download ndma_staddr reg, path: " << (char*)ndma_staddr_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)ndma_staddr_DOR.data(), parameter.CELL_NDMA_STADDR_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        // //router bram
        // cout << "Download router bram, path: " << (char*)route_info_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)route_info_DOR.data(), parameter.CELL_ROUTE_INFO_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);

        // //smt bram
        // cout << "Download smt bram, path: " << (char*)smt_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)smt_DOR.data(), parameter.CELL_SMT_BRAM_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);

        //weight bram
        cout << "Download weight bram, path: " << (char*)weight_DOR.data() << endl;
        Files_ParallelDownload_All( (char*)weight_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE,
                                                                        parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 1);

		// Files_Download_All( (char*)weight_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE,
        //                                                                 parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
		string upload_DOR(parameter.uploadPath_DOR); 
        string weight_check_prefix_DOR 	        = upload_DOR + "/step" + to_string(index) + "/weight_check/weight_check";
        string smt_check_prefix_DOR 	        = upload_DOR + "/step" + to_string(index) + "/smt_check/smt_check";
        string route_check_prefix_DOR 	        = upload_DOR + "/step" + to_string(index) + "/route_check/route_check";
 
        cout << "prepare to upload test:" << endl; 
		// clock_t start, end;
		// start = clock();						
		Files_ParallelUpload_ALL( (char*)weight_check_prefix_DOR.data(),  parameter.CELL_WEIGHT_BRAM_BASE,    	64*1024 , //4*1024*1024
                                                                	parameter.parallel_num, parameter.chip_num, parameter.chip_sel, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0, 1);
		// end = clock();
		// tmp_cnt = (double)(end - start) / CLOCKS_PER_SEC;
		// cout << "upload time cost: " <<  tmp_cnt * 1000 << endl;

		//bin file check
		unsigned int i = 0;
		unsigned int error_cnt = 0;
		for (i = 0; i < 36; i++) {
			std::string bin_weight = "/home/gdiist/work/work_cwb/data/1k36chip_asic/weight_socket_test/weight_" + std::to_string(i) +".bin";
			//cout << bin_weight << endl;
    		std::string bin_weight_check = "/home/gdiist/work/work_cwb/upload/1k36chip_asic/step0/weight_check/weight_check_" + std::to_string(i) +".bin";
			//cout << bin_weight_check << endl;
			if(Compare_Binfile(bin_weight, bin_weight_check) == false){
				error_cnt = error_cnt + 1;
			}
		}
		if(error_cnt == 0) {
			cout << "chip west : " << endl;
			print_PASS();
		}
		else {
			cout << "Number of bin file errors (west) : " + std::to_string(error_cnt) << endl;
			print_FAIL();
		}
	
	// Files_Upload_ALL( (char*)weight_check_prefix_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE ,    	32, 
    //                                                             	parameter.parallel_num, parameter.chip_num, parameter.chip_sel, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);																
	return;
}

void Data_Test_South(run_parameter parameter, string ** chip_num_table, unsigned int** chip_row_table,  unsigned int ** chip_col_table) {
	
	unsigned int index = 0;
	
        string download_DOR(parameter.downloadPath_DOR);
        string remote4_DOR                      = download_DOR + "/remote6_west/remote4";
        string property_DOR                     = download_DOR + "/property/property";
        string npu_on_DOR                       = download_DOR + "/npu_ctrl/npu_on";
        string tile_id_DOR                      = download_DOR + "/tile_id/tile_id";
        string ndma_staddr_DOR             	= download_DOR + "/ndma_staddr/ndma_staddr";
        string smt_DOR                          = download_DOR + "/smt/smt";
        string route_info_DOR              	= download_DOR + "/route_info/route_info";
        string weight_DOR                       = download_DOR + "/weight_socket_test/weight";	  
 		// string weight_DOR                       = download_DOR + "/inc/inc";	  
		double tmp_cnt=0;
        //set remote reg
        cout << "Download remote reg, path: " << (char*)remote4_DOR.data() << endl;
        // Files_ParallelDownload_All((char*)remote4_DOR.data(),   parameter.CELL_REMOTE_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
		remote_setup( parameter.CELL_REMOTE_BASE,parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 2);
	

		// remote_setup( parameter.CELL_REMOTE_BASE,parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        // //set npu_ctrl reg
        // cout << "Download npu_ctrl reg, path: " << (char*)npu_on_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)npu_on_DOR.data(), parameter.CELL_NPU_CTRL_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        //set tile_id reg
        // cout << "Download tile_id reg, path: " << (char*)tile_id_DOR.data() << endl;
        // Files_ParallelDownload_All((char*)tile_id_DOR.data(), parameter.CELL_TILE_ID_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        // //set ndma_staddr reg
        // cout << "Download ndma_staddr reg, path: " << (char*)ndma_staddr_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)ndma_staddr_DOR.data(), parameter.CELL_NDMA_STADDR_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        // //router bram
        // cout << "Download router bram, path: " << (char*)route_info_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)route_info_DOR.data(), parameter.CELL_ROUTE_INFO_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);

        // //smt bram
        // cout << "Download smt bram, path: " << (char*)smt_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)smt_DOR.data(), parameter.CELL_SMT_BRAM_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);

        //weight bram
        cout << "Download weight bram, path: " << (char*)weight_DOR.data() << endl;
        Files_ParallelDownload_All( (char*)weight_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE,
                                                                        parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 2);

		// Files_Download_All( (char*)weight_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE,
        //                                                                 parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
		string upload_DOR(parameter.uploadPath_DOR); 
        string weight_check_prefix_DOR 	        = upload_DOR + "/step" + to_string(index) + "/weight_check/weight_check";
        string smt_check_prefix_DOR 	        = upload_DOR + "/step" + to_string(index) + "/smt_check/smt_check";
        string route_check_prefix_DOR 	        = upload_DOR + "/step" + to_string(index) + "/route_check/route_check";
 
        cout << "prepare to upload test:" << endl; 
		// clock_t start, end;
		// start = clock();						
		Files_ParallelUpload_ALL( (char*)weight_check_prefix_DOR.data(),  parameter.CELL_WEIGHT_BRAM_BASE,    	64*1024 , //4*1024*1024
                                                                	parameter.parallel_num, parameter.chip_num, parameter.chip_sel, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0, 2);
		// end = clock();
		// tmp_cnt = (double)(end - start) / CLOCKS_PER_SEC;
		// cout << "upload time cost: " <<  tmp_cnt * 1000 << endl;

		//bin file check
		unsigned int i = 0;
		unsigned int error_cnt = 0;
		for (i = 0; i < 36; i++) {
			std::string bin_weight = "/home/gdiist/work/work_cwb/data/1k36chip_asic/weight_socket_test/weight_" + std::to_string(i) +".bin";
			//cout << bin_weight << endl;
    		std::string bin_weight_check = "/home/gdiist/work/work_cwb/upload/1k36chip_asic/step0/weight_check/weight_check_" + std::to_string(i) +".bin";
			//cout << bin_weight_check << endl;
			if(Compare_Binfile(bin_weight, bin_weight_check) == false){
				error_cnt = error_cnt + 1;
			}
		}
		if(error_cnt == 0) {
			cout << "chip south : " << endl;
			print_PASS();
		}
		else {
			cout << "Number of bin file errors (south) : " + std::to_string(error_cnt) << endl;
			print_FAIL();
		}

	// Files_Upload_ALL( (char*)weight_check_prefix_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE ,    	32, 
    //                                                             	parameter.parallel_num, parameter.chip_num, parameter.chip_sel, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);																
	return;
}

void Data_Test_East(run_parameter parameter, string ** chip_num_table, unsigned int** chip_row_table,  unsigned int ** chip_col_table) {
	
	unsigned int index = 0;
	
        string download_DOR(parameter.downloadPath_DOR);
        string remote4_DOR                      = download_DOR + "/remote6_west/remote4";
        string property_DOR                     = download_DOR + "/property/property";
        string npu_on_DOR                       = download_DOR + "/npu_ctrl/npu_on";
        string tile_id_DOR                      = download_DOR + "/tile_id/tile_id";
        string ndma_staddr_DOR             	= download_DOR + "/ndma_staddr/ndma_staddr";
        string smt_DOR                          = download_DOR + "/smt/smt";
        string route_info_DOR              	= download_DOR + "/route_info/route_info";
        string weight_DOR                       = download_DOR + "/weight_socket_test/weight";	  
 		// string weight_DOR                       = download_DOR + "/inc/inc";	  
		double tmp_cnt=0;
        //set remote reg
        cout << "Download remote reg, path: " << (char*)remote4_DOR.data() << endl;
        // Files_ParallelDownload_All((char*)remote4_DOR.data(),   parameter.CELL_REMOTE_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
		remote_setup( parameter.CELL_REMOTE_BASE,parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 3);
	

		// remote_setup( parameter.CELL_REMOTE_BASE,parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        // //set npu_ctrl reg
        // cout << "Download npu_ctrl reg, path: " << (char*)npu_on_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)npu_on_DOR.data(), parameter.CELL_NPU_CTRL_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        //set tile_id reg
        // cout << "Download tile_id reg, path: " << (char*)tile_id_DOR.data() << endl;
        // Files_ParallelDownload_All((char*)tile_id_DOR.data(), parameter.CELL_TILE_ID_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        // //set ndma_staddr reg
        // cout << "Download ndma_staddr reg, path: " << (char*)ndma_staddr_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)ndma_staddr_DOR.data(), parameter.CELL_NDMA_STADDR_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
        // //router bram
        // cout << "Download router bram, path: " << (char*)route_info_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)route_info_DOR.data(), parameter.CELL_ROUTE_INFO_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);

        // //smt bram
        // cout << "Download smt bram, path: " << (char*)smt_DOR.data() << endl;
        // Files_ParallelDownload_All( (char*)smt_DOR.data(), parameter.CELL_SMT_BRAM_BASE,
        //                                                         parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);

        //weight bram
        cout << "Download weight bram, path: " << (char*)weight_DOR.data() << endl;
        Files_ParallelDownload_All( (char*)weight_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE,
                                                                        parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 3);

		// Files_Download_All( (char*)weight_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE,
        //                                                                 parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);
		string upload_DOR(parameter.uploadPath_DOR); 
        string weight_check_prefix_DOR 	        = upload_DOR + "/step" + to_string(index) + "/weight_check/weight_check";
        string smt_check_prefix_DOR 	        = upload_DOR + "/step" + to_string(index) + "/smt_check/smt_check";
        string route_check_prefix_DOR 	        = upload_DOR + "/step" + to_string(index) + "/route_check/route_check";
 
        cout << "prepare to upload test:" << endl; 
		// clock_t start, end;
		// start = clock();						
		Files_ParallelUpload_ALL( (char*)weight_check_prefix_DOR.data(),  parameter.CELL_WEIGHT_BRAM_BASE,    	64*1024 , //4*1024*1024
                                                                	parameter.parallel_num, parameter.chip_num, parameter.chip_sel, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0, 3);
		// end = clock();
		// tmp_cnt = (double)(end - start) / CLOCKS_PER_SEC;
		// cout << "upload time cost: " <<  tmp_cnt * 1000 << endl;
		
		//bin file check
		unsigned int i = 0;
		unsigned int error_cnt = 0;
		for (i = 0; i < 36; i++) {
			std::string bin_weight = "/home/gdiist/work/work_cwb/data/1k36chip_asic/weight_socket_test/weight_" + std::to_string(i) +".bin";
			//cout << bin_weight << endl;
    		std::string bin_weight_check = "/home/gdiist/work/work_cwb/upload/1k36chip_asic/step0/weight_check/weight_check_" + std::to_string(i) +".bin";
			//cout << bin_weight_check << endl;
			if(Compare_Binfile(bin_weight, bin_weight_check) == false){
				error_cnt = error_cnt + 1;
			}
		}
		if(error_cnt == 0) {
			cout << "chip east : " << endl;
			print_PASS();
		}
		else {
			cout << "Number of bin file errors (east) : " + std::to_string(error_cnt) << endl;
			print_FAIL();
		}
	
	// Files_Upload_ALL( (char*)weight_check_prefix_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE ,    	32, 
    //                                                             	parameter.parallel_num, parameter.chip_num, parameter.chip_sel, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);																
	return;
}

void Data_Init(run_parameter parameter, string ** chip_num_table, unsigned int** chip_row_table,  unsigned int ** chip_col_table) {
	 	unsigned int i;
	string download_DOR(parameter.downloadPath_DOR);
	string remote4_DOR		        = download_DOR + "/remote4/remote4";
	string property_DOR		        = download_DOR + "/property/property";
	string npu_on_DOR		        = download_DOR + "/npu_ctrl/npu_on";
	string tile_id_DOR		        = download_DOR + "/tile_id/tile_id";
	string ndma_staddr_DOR		    = download_DOR + "/ndma_staddr/ndma_staddr";
	string smt_DOR		        	= download_DOR + "/smt/smt";
	string route_info_DOR		    = download_DOR + "/route_info/route_info";
	string weight_DOR		        = download_DOR + "/weight/weight";
	//init reg
	if (parameter.hw_type==0) {
		//set remote reg
		cout << "Download remote reg, path: " << (char*)remote4_DOR.data() << endl;
		// Files_ParallelDownload_All((char*)remote4_DOR.data(),	parameter.CELL_REMOTE_BASE, 
		// 							parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);			
		remote_setup( parameter.CELL_REMOTE_BASE,parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);


		//set npu_ctrl reg
		cout << "Download npu_ctrl reg, path: " << (char*)npu_on_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)npu_on_DOR.data(), parameter.CELL_NPU_CTRL_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);		
		//set tile_id reg
		cout << "Download tile_id reg, path: " << (char*)tile_id_DOR.data() << endl;
		Files_ParallelDownload_All((char*)tile_id_DOR.data(), parameter.CELL_TILE_ID_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);		    
		//set ndma_staddr reg
		cout << "Download ndma_staddr reg, path: " << (char*)ndma_staddr_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)ndma_staddr_DOR.data(), parameter.CELL_NDMA_STADDR_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);	    
		//router bram
		cout << "Download router bram, path: " << (char*)route_info_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)route_info_DOR.data(), parameter.CELL_ROUTE_INFO_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);
		
		//smt bram
		cout << "Download smt bram, path: " << (char*)smt_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)smt_DOR.data(), parameter.CELL_SMT_BRAM_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);
		
		//weight bram
		cout << "Download weight bram, path: " << (char*)weight_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)weight_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);
	}
	else if (parameter.hw_type==1) {
		//set remote reg
		cout << "Download remote reg, path: " << (char*)remote4_DOR.data() << endl;
		// Files_ParallelDownload_All( (char*)remote4_DOR.data(),	parameter.CELL_REMOTE_BASE, 
		// 							parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);			
		remote_setup( parameter.CELL_REMOTE_BASE,parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);


		//set property reg
		cout << "Download property reg, path: " << (char*)property_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)property_DOR.data(), parameter.CELL_PROPERTY_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);		
									
		//router bram
		cout << "Download router bram, path: " << (char*)route_info_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)route_info_DOR.data(), parameter.CELL_ROUTE_INFO_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);
		
		//smt bram
		cout << "Download smt bram, path: " << (char*)smt_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)smt_DOR.data(), parameter.CELL_SMT_BRAM_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);
		
		//weight bram
		cout << "Download weight bram, path: " << (char*)weight_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)weight_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);		
	}
		return;
	
}
void Data_Upload(uint32_t step, run_parameter parameter, string ** chip_num_table, uint32_t** chip_row_table,  uint32_t ** chip_col_table) {

	string upload_DOR(parameter.uploadPath_DOR);	
	string all_prefix_DOR		= upload_DOR + "/step" + to_string(step) + "/all_check";
	string sp_check_prefix_DOR		= upload_DOR + "/step" + to_string(step) + "/spike_check/spike_check";
	string weight_check_prefix_DOR	= upload_DOR + "/step" + to_string(step) + "/weight_check/weight_check";
	
	bool up_flag = 0;
    // cout << "up_flag: " << up_flag << endl;
	Files_ParallelUpload_ALL( (char*)sp_check_prefix_DOR.data(), parameter.CELL_SP_BRAM_BASE,		parameter.neu_num * 4, 
								parameter.parallel_num, parameter.chip_num, parameter.chip_sel, parameter.hw_type, chip_num_table,  chip_row_table,  chip_col_table, up_flag, 0);
	Files_ParallelUpload_ALL( (char*)weight_check_prefix_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE + 0x10000 * parameter.chip_num,	parameter.neu_num * 32, 
	 							parameter.parallel_num, parameter.chip_num, parameter.chip_sel, parameter.hw_type, chip_num_table, chip_row_table,   chip_col_table, up_flag, 0);

	if (step == parameter.step_count && up_flag ) {

			#ifdef PRINT_INFO
			cout  << endl << "step count over, prepare to upload data: " << endl;
			#endif
			Files_ReadALL_Upload((char*)all_prefix_DOR.data(), parameter.neu_num * 4 *parameter.step_count * parameter.chip_num, 0);
			#ifdef PRINT_INFO
			cout << "Files_ParallelUpload_All: recv complete" << endl;
			#endif
	}
	return;
}

void Sim_Process( run_parameter parameter, int rev_num,unsigned int stop_pkg, string **chip_num_table, unsigned int** chip_row_table,  unsigned int ** chip_col_table) {

	unsigned int step_limit = 1;
	clock_t start, end;
	double time = 0;
	double sim_TimeCnt = 0, up_TimeCnt = 0, tmp_cnt = 0;
	unsigned int func_out_val=0;
	unsigned int sim_end_cnt=0;
	bool CTRL_MODE = 1;  // 1:sync_start ;  0: unicast ctrl
	string download_DOR(parameter.downloadPath_DOR);	
	string npu_start_DOR		    = download_DOR + "/npu_ctrl/npu_after";
	string npu_stop_DOR		        = download_DOR + "/npu_ctrl/npu_all0";
	string npu_spike_DOR		        = download_DOR + "/npu_ctrl/npu_spike";
	string spike_in_DOR = download_DOR + "/spike_bin/sample" + to_string(parameter.sample_num) + "/spike";

    sim_end_cnt=(rev_num+1)<<1;
	unsigned int pkg_done=0;
	if ( !CTRL_MODE )  {
			sysc_set(1, 0);
			usleep(3000);
	}

	cout << '\n' << "Sim Step Loop : " << parameter.step_count << " ......" << endl;
	for (int step_i = 1; step_i < parameter.step_count + 1; step_i++) {
		cout << "\nstep--" << step_i << endl;

		if (parameter.extern_spike) {
			if (step_i == 1) {
				Files_ParallelDownload_All( (char*)npu_spike_DOR.data(), parameter.CELL_NPU_CTRL_BASE, 
						parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);		//set sim start
				usleep(1000);
				spike_in_DOR = spike_in_DOR + to_string(step_i);		
				Files_Download_All((char*)spike_in_DOR.data(), parameter.CELL_NPU_CTRL_BASE,
                                                        1, 1, 0, 1, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table); 
				usleep(1000);
			}
		}
    
		// if (step_i == 1) {
		// Files_ParallelDownload_All( (char*)npu_spike_DOR.data(), parameter.CELL_NPU_CTRL_BASE, 
		// 		parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table);		//set sim start
		// usleep(1000);
	
		// }

		//sim_end_pkg_data stream bypass
		stop_pkg = 1<<16;
		user_write(TITLE_VALID_LENGTH, sim_end_cnt);//write sim_pkg_length
		func_out_val=user_read(GPIO_OREG);			   
		user_write(GPIO_OREG,stop_pkg|func_out_val);   //pull up stop_pkg_flag


		if (CTRL_MODE) {
			if (step_i != 1) {
				Files_ParallelDownload_All( (char*)npu_spike_DOR.data(), parameter.CELL_NPU_CTRL_BASE, 
							parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);		//set sim start
				usleep(1000);
			}
			cout << "sync sim start:" << endl;
			sysc_set(0, 0);
			usleep(1000);
			sysc_set(1, 0);
		}
		else {
			cout << "unicast sim start:" << endl;
			Files_ParallelDownload_All( (char*)npu_start_DOR.data(), parameter.CELL_NPU_CTRL_BASE, 
							parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type, chip_num_table, chip_row_table, chip_col_table, 0);	
		}
		
		cout << "prepare to receive pkg  ..." << endl;
		start = clock();						
		while ((pkg_done&0x4)!= 0x4)                 //wait pkg done 
	{
		pkg_done=user_read(GPIO_IREG);

	}
		user_write(GPIO_OREG,~stop_pkg&func_out_val); //pull down stop_pkg_flag
		pkg_done=0;
		
		end = clock();
		tmp_cnt = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "sim time cost:    " <<  tmp_cnt * 1000 << endl;
        sim_TimeCnt += tmp_cnt;

		// func_out_val=user_read(GPIO_OREG);
		// user_write(GPIO_OREG, (~stop_pkg)&func_out_val);
		// usleep(1000);

 		Files_ParallelDownload_All((char*)npu_stop_DOR.data(), parameter.CELL_NPU_CTRL_BASE,
							parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type,chip_num_table, chip_row_table, chip_col_table, 0);		//set sim stop
		usleep(1000);



		cout << "prepare to upload ..." << endl ;
		start = clock();						
		Data_Upload(step_i, parameter, chip_num_table, chip_row_table, chip_col_table);
		end = clock();
		tmp_cnt = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "upload time cost: " <<  tmp_cnt * 1000 << endl;
		up_TimeCnt += tmp_cnt;

		// usleep(100000);
	}
	cout << "total time step: " << parameter.step_count << ", averaged sim cost: "; 
	cout << setprecision(6) << double(sim_TimeCnt / parameter.step_count * 1000) <<  "ms, averaged upload cost: ";
	cout << setprecision(6) << double(up_TimeCnt / parameter.step_count * 1000) <<  "ms, total time cost: ";
	cout << setprecision(6) << sim_TimeCnt + up_TimeCnt << "s" << endl;
	return;
}

//void mem_rw_test () {
//	// 获取Python程序中一个列表对象的内存地址
//   	 PyObject* pyList = PyList_New(3);
//   	 PyList_SetItem(pyList, 0, PyLong_FromLong(1));
//   	 PyList_SetItem(pyList, 1, PyLong_FromLong(2));
//   	 PyList_SetItem(pyList, 2, PyLong_FromLong(3));
//   	 void* addr = (void*)pyList;
//
//   	 // 使用libffi库访问Python程序中的内存地址，并获取其中的数据
//   	 ffi_cif cif;
//   	 ffi_type* argTypes[] = {&ffi_type_pointer};
//   	 void* argValues[] = {&addr};
//   	 long value;
//   	 ffi_type* returnType = &ffi_type_slong;
//   	 ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1, returnType, argTypes);
//   	 void* funcAddr = dlopen("libpython3.7m.so", RTLD_LAZY);
//   	 ffi_call(&cif, FFI_FN(dlsym(funcAddr, "PyLong_AsLong")), &value, argValues);
//   	 std::cout << "Value at address " << addr << " is " << value << std::endl;
//   	 dlclose(funcAddr);
//
//   	 // 释放Python对象
//   	 Py_DECREF(pyList);
//
//   	 return;
//}
void init_tab(run_parameter parameter, string **chip_num_table, unsigned int**chip_row_table,  unsigned int **chip_col_table) {

	uint32_t para_max = parameter.parallel_num;
	uint32_t row_max = parameter.row_max;
	uint32_t col_max = parameter.col_max;
	uint32_t tmp_length = int(col_max*row_max/para_max);
	uint32_t file_index=0, row_index=0;
	uint32_t tmp_id = 0;

	for (int gdma_loop = 0; gdma_loop < para_max; gdma_loop++) {
			file_index =  col_max * gdma_loop;
			row_index = gdma_loop+1;
			for (int row=0;  row<int(row_max/para_max); row++) {
				for (int col=0;  col<col_max; col++) {
					*((string *)chip_num_table + gdma_loop * tmp_length+ tmp_id) =  '_' + to_string(file_index)  + ".bin";
					// cout << *((string *)chip_num_table + gdma_loop * tmp_length+ tmp_id).length();
					*((uint32_t *)chip_row_table + gdma_loop * tmp_length+ tmp_id) =  row_index;
					*((uint32_t *)chip_col_table + gdma_loop * tmp_length+ tmp_id) =  col+1;

					tmp_id++;
					file_index ++;
				}
				row_index = row_index + para_max;
				file_index = file_index + (para_max-1)*col_max;	
			}
			tmp_id = 0;
	}
	 #ifdef DEBUG_PRINT
			for (int i = 0; i<para_max; i++)  {
				for (int j = 0; j<tmp_length; j++) {	
					cout << *((string *)chip_num_table + i * tmp_length+ j)<< '\t';
				}
				cout << endl;
			}
			cout << endl;

			for (int i = 0; i<para_max; i++)  {
				for (int j = 0; j<tmp_length; j++) {	
					cout << *((uint32_t *)chip_row_table + i * tmp_length+ j) << '\t';
				}
				cout << endl;
			}
			cout << endl;
			for (int i = 0; i<para_max; i++)  {
				for (int j = 0; j<tmp_length; j++) {	
					cout << *((uint32_t *)chip_col_table + i * tmp_length+ j) << '\t';
				}
				cout << endl;
			}
		 #endif
}

int main(int argc, char* argv[])
{

	//unsigned int buf1[1024];
	//unsigned int buf2[1024] = {4,3,5,7,8,9};
	unsigned int i = 0;
	unsigned int val=0;
	unsigned int error_cnt = 0;

   	unsigned int  i2, t, stop_pkg = 1;
	struct run_parameter parameter;
	unsigned int step_limit = 1, step_count = 250;
	

	cout << "Input arguments count: " << argc << endl;

	//load_parameter(parameter, argv);
	if (!(argc == 15)) {
		cout << "Input arguments error!" << endl;
		return -1;
	}
	else {
		parameter.parallel_num = atoi(argv[1]);
		parameter.chip_num = atoi(argv[2]);
		parameter.chip_sel = atoi(argv[3]);
		strcpy( parameter.downloadPath_DOR      	 , argv[4] );  
		strcpy( parameter.uploadPath_DOR            	 , argv[5] ); 
		parameter.row_max = atoi(argv[6]);
		parameter.col_max = atoi(argv[7]);
		parameter.extern_spike = atoi(argv[8]);
		parameter.mode = atoi(argv[9]);
		parameter.hw_type = atoi(argv[10]);
		parameter.sample_num = atoi(argv[11]);
		parameter.step_count = atoi(argv[12]);
		parameter.neu_num = atoi(argv[13]);
		strcpy( parameter.xdma_num    , argv[14] );  
	
	}



	if (parameter.hw_type==0) {  //asic 1k
		parameter.CELL_REMOTE_BASE		= 0x00000000  ;
		parameter.CELL_PROPERTY_BASE		= 0xC0000000  ;
		parameter.CELL_ROUTE_INFO_BASE	= 0x00008000  ;

		parameter.CELL_TILE_ID_BASE		= 0x04040000  ;
		parameter.CELL_NDMA_STADDR_BASE	= 0x04040004  ;
		parameter.CELL_NPU_CTRL_BASE		= 0x04040008  ;
		parameter.CELL_SP_SIZE_BASE		= 0x04040034  ;

		parameter.CELL_SMT_BRAM_BASE		= 0x04000000  ;
		parameter.CELL_SP_BRAM_BASE		= 0x05000000  ;
		parameter.CELL_SP_CNT_BRAM_BASE	= 0x05010000  ;
		parameter.CELL_WEIGHT_BRAM_BASE	= 0x06000000  ;

	}
	else if (parameter.hw_type==1) {
		parameter.CELL_REMOTE_BASE		= 0xC0000000  ;
		parameter.CELL_PROPERTY_BASE		= 0xC0011000  ;
		parameter.CELL_ROUTE_INFO_BASE	= 0xC0008000  ;
		parameter.CELL_NPU_CTRL_BASE		= 0xC0011008  ;
		parameter.CELL_SMT_BRAM_BASE		= 0xC0010000  ;
		parameter.CELL_SP_BRAM_BASE		= 0xC0020000  ;
		parameter.CELL_SP_CNT_BRAM_BASE	= 0x05010000  ;
		parameter.CELL_WEIGHT_BRAM_BASE	= 0x00000000  ;
	}   
	uint32_t chip_max = parameter.row_max * parameter.col_max;
	if ( chip_max < parameter.chip_num ) {
		cout << "row or col error! " << "now chip_max: " << chip_max;
	       	cout << " total chip need: " << parameter.chip_num << endl;
		return -1;
	}

	string 		chip_num_table[parameter.parallel_num][int(chip_max/parameter.parallel_num)]; 
	uint32_t	chip_row_table[parameter.parallel_num][int(chip_max/parameter.parallel_num)]; 
	uint32_t 	chip_col_table[parameter.parallel_num][int(chip_max/parameter.parallel_num)]; 

	cout << "init tab:"<< endl;
	init_tab(parameter, (string **) chip_num_table, (uint32_t **) chip_row_table, (uint32_t **) chip_col_table);
	pcie_init(parameter.xdma_num); 


        for(i=0;i<parameter.parallel_num;i++){
        	stop_pkg = stop_pkg <<1;
        	//printf("stop_pkg=%x\n",stop_pkg);
        }
	stop_pkg =(stop_pkg-1)<<8;

	printf("Serdes_Init End, parallel_num = %d, chip_num = %d, mode = %d, stop_pkg = %x,hw_type = %d, neu_num = %d\r\n", parameter.parallel_num, parameter.chip_num, parameter.mode, stop_pkg,parameter.hw_type, parameter.neu_num);
	int16_t rev_num = parameter.chip_num / (parameter.parallel_num ) - 1;
	if (rev_num < 0) 
		rev_num = 0;
	printf("every gdma channel: %d\r\n", rev_num);
	printf("*************System Init Complete*************\r\n");

	switch (parameter.parallel_num)
	{
	case 1:
		gtp_state = 0x0003;
		break;
	case 2:
		gtp_state = 0x000f;
		break;
	case 3:
		gtp_state = 0x003f;
		break;
	case 4:
		gtp_state = 0x00ff;
		break;
	default:
		gtp_state = 0x0003;
		break;
	}
	printf("gtp_state= %d\n",gtp_state);


		die_power_enable(0);
		gtp_speed_set();
		usleep(10000);
 		RouterSetup(parameter.row_max, parameter.col_max);

	if (parameter.mode == 0) {

		while ((val&gtp_state) != gtp_state) {
			val = user_read(GPIO_IREG);
			printf("val=%d\n",val);
		}

		//direction select: low 4 bit (N 00000001-S 00000010-W 000100-E 00001000)
    	user_write(DIRECTION_SEL, 0x00000000);
   	 	usleep(2);
		//north test
    	user_write(DIRECTION_SEL, 0x00000001);//north    
    	usleep(10000);
		Data_Test(parameter, (string **) chip_num_table, (uint32_t **) chip_row_table, (uint32_t **) chip_col_table);
		//west test
		user_write(DIRECTION_SEL, 0x00000100);//west    
    	usleep(10000);
		Data_Test_West(parameter, (string **) chip_num_table, (uint32_t **) chip_row_table, (uint32_t **) chip_col_table);
		//south test
		user_write(DIRECTION_SEL, 0x00000010);//south   
    	usleep(10000);
		Data_Test_South(parameter, (string **) chip_num_table, (uint32_t **) chip_row_table, (uint32_t **) chip_col_table);
		//east test
		user_write(DIRECTION_SEL, 0x00001000);//east    
    	usleep(10000);
		Data_Test_East(parameter, (string **) chip_num_table, (uint32_t **) chip_row_table, (uint32_t **) chip_col_table);

		cout << '\n' << "Chip north/west/south/east : Test Complete" << endl;
		cout << "        A    " << " L       " << " L       \n";
    	cout << "       A A   " << " L       " << " L       \n";
    	cout << "      A   A  " << " L       " << " L       \n";
    	cout << "     AAAAAAA " << " L       " << " L       \n";
    	cout << "     A     A " << " L       " << " L       \n";
		cout << "     A     A " << " L       " << " L       \n";
		cout << "     A     A " << " LLLLLLL " << " LLLLLLL \n";
		print_PASS();

        // cout << '\n' << "Data_Test: Complete" << endl;
		// Data_Init(parameter, (string **) chip_num_table, (uint32_t **) chip_row_table, (uint32_t **) chip_col_table);	
		// Sim_Process( parameter,rev_num,stop_pkg, (string **) chip_num_table, (uint32_t **) chip_row_table, (uint32_t **) chip_col_table);
		// cout << "Data_Init: Complete\r\n" << endl;
	}	
	else if (parameter.mode == 1) {
		Data_Init(parameter, (string **) chip_num_table, (uint32_t **) chip_row_table, (uint32_t **) chip_col_table);	
	//	Data_Upload(0, parameter);
	//	usleep(100000);
		Sim_Process( parameter,rev_num,stop_pkg, (string **) chip_num_table, (uint32_t **) chip_row_table, (uint32_t **) chip_col_table);
	}
	else {
		RouterSetup(parameter.row_max, parameter.col_max);
                while (val != gtp_state) {
                	val = user_read(GPIO_IREG);
               		printf("val=%d\n",val);
                }
		Data_Test(parameter, (string **) chip_num_table, (uint32_t **) chip_row_table, (uint32_t **) chip_col_table);
             	cout << '\n' << "Data_Test: Complete" << endl;
	}

}

