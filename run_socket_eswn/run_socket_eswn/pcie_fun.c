#include "zcu102_sender_global.h"
#ifdef __cplusplus
 extern "C" {
 #endif
#include <assert.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdarg.h>
#include <syslog.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <dirent.h>

/* ltoh: little to host */
/* htol: little to host */
#if __BYTE_ORDER == __LITTLE_ENDIAN
#  define ltohl(x)       (x)
#  define ltohs(x)       (x)
#  define htoll(x)       (x)
#  define htols(x)       (x)
#elif __BYTE_ORDER == __BIG_ENDIAN
#  define ltohl(x)     __bswap_32(x)
#  define ltohs(x)     __bswap_16(x)
#  define htoll(x)     __bswap_32(x)
#  define htols(x)     __bswap_16(x)
#endif

#define MAP_SIZE (1024*1024UL)
#define MAP_MASK (MAP_SIZE - 1)
#define FPGA_DDR_START_ADDR 0x00000000
#define MAX_BYTES_PER_TRANSFER 0x800000

static void * user_base;
static int h_c2h0;
static int h_h2c0;
static int h_user;
//static int h_event0;
//static int h_event1;
//static int h_event2;
//static int h_event3;

//static unsigned int  user_irq_ack;
using namespace std;

static void *mmap_control(int device,long mapsize)
{
    void *vir_addr;
    vir_addr = mmap(0, mapsize, PROT_READ | PROT_WRITE, MAP_SHARED, device, 0);
    return vir_addr;
}

void write_device(int device,unsigned int address,unsigned int len,unsigned char *buffer)
{
    lseek(device,address,SEEK_SET);
    write(device,buffer,len);
}

void read_device(int device,unsigned int address,unsigned int len,unsigned char *buffer)
{
    lseek(device,address,SEEK_SET);
    read(device,buffer,len);
}

void c2h_transfer(unsigned int address,unsigned int size,unsigned char *buffer)
 {
    read_device(h_c2h0,address,size,buffer);
 }

void h2c_transfer(unsigned int address,unsigned int size,unsigned char *buffer)
{
    write_device(h_h2c0,address,size,buffer);
}

void user_write(unsigned int address,unsigned int val )
{
    unsigned int writeval = htoll(val);
   
   *((unsigned int *)(user_base+address)) = writeval;

}

unsigned int user_read(unsigned int address)
{
    unsigned int read_result = *((unsigned int *)(user_base+address));
   
    read_result = ltohl(read_result);
    
    return read_result;
 
}

int pcie_init( char str[])
{
    // char* user_name = (char*)"/dev/xdma1_user";
    // char* c2h0_name = (char*)"/dev/xdma1_c2h_0";
    // char* h2c0_name = (char*)"/dev/xdma1_h2c_0";

    string user_name = "/dev/xdma1_user";
    string c2h0_name = "/dev/xdma1_c2h_0";
    string h2c0_name = "/dev/xdma1_h2c_0";
    uint32_t i2=0;

    user_name=user_name.replace(5,5,str);
    c2h0_name=c2h0_name.replace(5,5,str);
    h2c0_name=h2c0_name.replace(5,5,str);
    printf("pcie_init\n"); 

    h_c2h0 = open(c2h0_name.c_str(),O_RDWR | O_NONBLOCK);
    if(h_c2h0 < 0) { printf("open c2h0 error\n"); return -1; };

    h_h2c0 = open(h2c0_name.c_str(),O_RDWR);
    if(h_h2c0 < 0) { printf("open h2c0 error\n"); return -2; };

    h_user = open(user_name.c_str(), O_RDWR | O_SYNC);
    if(h_user < 0) { printf("open user error\n"); return -3; };

    user_base = mmap_control(h_user,MAP_SIZE);
    printf("pcie_init successed\n"); 
    
    //soft rst
    i2 = 0x0000;
	user_write(HOST_FLAG, i2);
	usleep(2);
	i2 = 0x00001;
	user_write(HOST_FLAG, i2);
    usleep(2);

    return 1;
}

void pcie_deinit()
{
    //user_irq_ack = 0x00000000;
    //write_device(h_user, 0x04, 4, (unsigned char *)&user_irq_ack);//clear irq
    close(h_user);
    close(h_c2h0);
    close(h_h2c0);
}

#ifdef __cplusplus
}
#endif
