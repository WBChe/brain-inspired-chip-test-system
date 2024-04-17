
import os 

uploadPath=[r'/upload/ei_1000_asic', r'/upload/ei_4000_asic',  r'/upload/ei_16384_asic',  r'/upload/ei_32768_asic']
step = 1000
for tmp in uploadPath:
    for i in range(0,step+1):
                 os.makedirs(f'{tmp}/step' + str(i) + '/spike_check', exist_ok = True)
                 os.makedirs(f'{tmp}/step' + str(i) + '/weight_check', exist_ok = True)

