
#ifndef PCIE_FUNC_H
#define PCIE_FUNC_H
#ifdef __cplusplus
 extern "C" {
 #endif
 	

void h2c_transfer(unsigned int address,unsigned int size,unsigned char *buffer);
void c2h_transfer(unsigned int address,unsigned int size,unsigned char *buffer);


void user_write(unsigned int address,unsigned int val );
unsigned int user_read(unsigned int address);


void pcie_deinit();
int pcie_init( char str[]);
#ifdef __cplusplus
}
#endif
#endif
