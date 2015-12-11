/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <logfile_printf.h>
#include <lv2_syscall.h>

void patch_hv_checks(){
	// peek and poke dynamically lv1 - no more toc/fw check needed ^_^
	u64 auth_check=0x16FB64; //auth_check poke-offset decr
	u64 write_eeprom=0xFEBD4; //eeprom_write_access poke-offset decr
	
	lv2_lv1_poke(0xFC4D8, 0x2f8000032F800003ULL);
	
	if(lv2_lv1_peek(auth_check)!=0x2F800000409E0050ULL){ //(1st) patch pattern - if no match, search lv1
		auth_check=0;
		for(u64 addr=0xA000; addr<0x800000ULL; addr+=4){ //search lv1
			auth_check=addr;
			if(lv2_lv1_peek(addr) == 0x4BFFFF8888010070ULL){ //static search pattern for auth_check function
				auth_check=addr+8;
				break;
			}
		}
	}
	if(auth_check && lv2_lv1_peek(auth_check)==0x2F800000409E0050ULL){
		lv2_lv1_poke(auth_check, 0x2f80000048000050ULL);
	}
	
	if(lv2_lv1_peek(write_eeprom)!=0xE81800082FA00000ULL){ //(1st) patch pattern - if no match, search lv1
		write_eeprom=0;
		for(u64 addr=0xA000; addr<0x800000ULL; addr+=4){ //search lv1
			write_eeprom=addr;
			if(lv2_lv1_peek(addr) == 0x2F8000FF419E0088ULL){ //static search pattern for eeprom_write_access function
				write_eeprom=addr+24;
				break;
			}
		}
	}
	if(write_eeprom && lv2_lv1_peek(write_eeprom)==0xE81800082FA00000ULL){
		lv2_lv1_poke(write_eeprom, 0x380000002FA00000ULL);
	}
}

#define UPDATE_MGR_PACKET_ID_READ_EPROM		0x600B

int main(int argc, char **argv){

	uint8_t value;
	// uint64_t value;
	// long long unsigned int value;
	int result;
	int i=0;
    logfile_printf_init("/dev_hdd0/EEPROM_DUMP.txt");
	logfile_printf("%s:%d: start\n", __func__, __LINE__);
 
	patch_hv_checks();
	
	
	logfile_printf("0x2F00\n");
	for(i=0x2F00;i<0x2F00+0x100;i++){
		result = lv2_ss_update_mgr_if(UPDATE_MGR_PACKET_ID_READ_EPROM, i, (uint64_t) &value, 0, 0, 0, 0);
		if (result) {
			logfile_printf("%s:%d: lv1_ss_update_mgr_if(READ_EPROM) failed (0x%08x)\n", __func__, __LINE__, result);
			//goto done;
		}
		if(i%16==0){
			logfile_printf( "\n%02x", value);
		}
		logfile_printf( "%02x", value);
		
	}
	logfile_printf("\n");
	logfile_printf("0x3000\n");
	for(i=0x3000;i<0x3000+0x100;i++){
		result = lv2_ss_update_mgr_if(UPDATE_MGR_PACKET_ID_READ_EPROM, i, (uint64_t) &value, 0, 0, 0, 0);
		if (result) {
			logfile_printf("%s:%d: lv1_ss_update_mgr_if(READ_EPROM) failed (0x%08x)\n", __func__, __LINE__, result);
			//goto done;
		}
		if(i%16==0){
			logfile_printf( "\n%02x", value);
		}
		logfile_printf( "%02x", value);
	}
	logfile_printf("\n");
	logfile_printf("0x48000\n");
	for(i=0x48000;i<0x48000+0x100;i++){
		result = lv2_ss_update_mgr_if(UPDATE_MGR_PACKET_ID_READ_EPROM, i, (uint64_t) &value, 0, 0, 0, 0);
		if (result) {
			logfile_printf("%s:%d: lv1_ss_update_mgr_if(READ_EPROM) failed (0x%08x)\n", __func__, __LINE__, result);
			//goto done;
		}
		if(i%16==0){
			logfile_printf( "\n%02x", value);
		}
		logfile_printf( "%02x", value);
	}
	logfile_printf("\n");
	logfile_printf("0x48800\n");
	for(i=0x48800;i<0x48800+0x100;i++){
		result = lv2_ss_update_mgr_if(UPDATE_MGR_PACKET_ID_READ_EPROM, i, (uint64_t) &value, 0, 0, 0, 0);
		if (result) {
			logfile_printf("%s:%d: lv1_ss_update_mgr_if(READ_EPROM) failed (0x%08x)\n", __func__, __LINE__, result);
			//goto done;
		}
		if(i%16==0){
			logfile_printf( "\n%02x", value);
		}
		logfile_printf( "%02x", value);
	}
	logfile_printf("\n");
	logfile_printf("0x48C00\n");
	for(i=0x48C00;i<0x48C00+0x100;i++){
		result = lv2_ss_update_mgr_if(UPDATE_MGR_PACKET_ID_READ_EPROM, i, (uint64_t) &value, 0, 0, 0, 0);
		if (result) {
			logfile_printf("%s:%d: lv1_ss_update_mgr_if(READ_EPROM) failed (0x%08x)\n", __func__, __LINE__, result);
			//goto done;
		}
		if(i%16==0){
			logfile_printf( "\n%02x", value);
		}
		logfile_printf( "%02x", value);
	}
	logfile_printf("\n");
	logfile_printf("0x48D00\n");
	for(i=0x48D00;i<0x48D00+0x100;i++){
		result = lv2_ss_update_mgr_if(UPDATE_MGR_PACKET_ID_READ_EPROM, i, (uint64_t) &value, 0, 0, 0, 0);
		if (result) {
			logfile_printf("%s:%d: lv1_ss_update_mgr_if(READ_EPROM) failed (0x%08x)\n", __func__, __LINE__, result);
			//goto done;
		}
		if(i%16==0){
			logfile_printf( "\n%02x", value);
		}
		logfile_printf( "%02x", value);
		
	}
	logfile_printf("\n");
	
		logfile_printf("%s:%d: end\n", __func__, __LINE__);

		lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);
		
}