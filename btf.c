/*
 * The MIT License (MIT)

Copyright (c) 2023 Author

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include "btf.h"
#include "btf_types.h"

/*
 * checks if the hardware battery is not available 
 * in other terms if the battery is plugged or not
 */
boolean btf_ac_info_state(){
	FILE* btf_ac_info_state_file;
	btf_ac_info_state_file = btf_file_open(BTF_AC_STATE, BTF_SYS_READ);
	size_t buffer_size = btf_sys_file_length(btf_ac_info_state_file);
	btf_str state = btf_sys_file_read_buffer(btf_ac_info_state_file, buffer_size);
	if(strcmp(state, BTF_AC_ON))return true;

	return false;
}

/* reads the ac information */
btf_str btf_ac_info_type(){
	FILE* btf_ac_info_type_file;
	btf_ac_info_type_file = btf_file_open(BTF_AC_TYPE, BTF_SYS_READ);
	size_t buffer_size = btf_sys_file_length(btf_ac_info_type_file);
	return btf_sys_file_read_buffer(btf_ac_info_type_file, buffer_size);
}

/* checks if the hardware battery is plugged in */
boolean btf_battery_availabe(){
	DIR* btf_battery_system;
	btf_battery_system = opendir(BTF_BATTERY_PATH);
	if(btf_battery_system){
		closedir(btf_battery_system);
		return true;
	}

	return false;
}

/* reads the battery capacity */
btf_str btf_battery_info_capacity(){
	FILE* btf_battery_info_capacity_file;
	btf_battery_info_capacity_file = btf_file_open(BTF_BATTERY_CAPACITY, BTF_SYS_READ);
	size_t buffer_size = btf_sys_file_length(btf_battery_info_capacity_file);
	return btf_sys_file_read_buffer(btf_battery_info_capacity_file, buffer_size);
}

/* reads the battery capacity level */
btf_str btf_battery_info_capacity_level(){
	FILE* btf_battery_info_capacity_level_file;
	btf_battery_info_capacity_level_file = btf_file_open(BTF_BATTERY_CAPACITY_LEVEL, BTF_SYS_READ);
	size_t buffer_size = btf_sys_file_length(btf_battery_info_capacity_level_file);
	return btf_sys_file_read_buffer(btf_battery_info_capacity_level_file, buffer_size);
}

/* reads the battery manufacturer */
btf_str btf_battery_info_manufacturer(){
	FILE* btf_battery_info_manufacturer_file;
	btf_battery_info_manufacturer_file = btf_file_open(BTF_BATTERY_MANUFACTURER, BTF_SYS_READ);
	size_t buffer_size = btf_sys_file_length(btf_battery_info_manufacturer_file);
	return btf_sys_file_read_buffer(btf_battery_info_manufacturer_file, buffer_size);
}

/* reads the serial number of the battery */
btf_str btf_battery_info_serial(){
	FILE* btf_battery_info_serial_file;
	btf_battery_info_serial_file = btf_file_open(BTF_BATTERY_SERIAL, BTF_SYS_READ);
	size_t buffer_size = btf_sys_file_length(btf_battery_info_serial_file);
	return btf_sys_file_read_buffer(btf_battery_info_serial_file, buffer_size);
}

/* reads what technology is the battery is using */
btf_str btf_battery_info_technology(){
	FILE* btf_battery_info_technology_file;
	btf_battery_info_technology_file = btf_file_open(BTF_BATTERY_TECHNOLOGY, BTF_SYS_READ);
	size_t buffer_size = btf_sys_file_length(btf_battery_info_technology_file);
	return btf_sys_file_read_buffer(btf_battery_info_technology_file, buffer_size);
}

btf_str btf_battery_info_type(){
	FILE* btf_battery_info_type_file;
	btf_battery_info_type_file = btf_file_open(BTF_BATTERY_TYPE, BTF_SYS_READ);
	size_t buffer_size = btf_sys_file_length(btf_battery_info_type_file);
	return btf_sys_file_read_buffer(btf_battery_info_type_file, buffer_size);
}


size_t btf_sys_file_length(FILE* sys_file){
	size_t buffer_size = 0;
	if(!sys_file)return 0;
	while((fgetc(sys_file)) != EOF){
		buffer_size++;
	}
	return buffer_size;
}

btf_str btf_sys_file_read_buffer(FILE* sys_file, size_t buffer_size){
	// check if file is open
	if(!sys_file){
		printf("error: unable to read system property\n");
		return NULL;
	}

	rewind(sys_file);
	btf_str buffer;
	buffer = (btf_str)malloc(sizeof(btf_chr) * buffer_size);

	if(!buffer)return NULL;
	// read the buffer 	
	int stream;
	size_t stream_length = 0;
	while((stream = fgetc(sys_file)) != EOF){
		*(buffer + stream_length++) = stream;
	}

	if(ferror(sys_file)){
		printf("error: reading file interrupted!\n");
		return NULL;
	}

	if(!feof(sys_file)){
		printf("error: reading file not done!\n");
		return NULL;
	}

	fclose(sys_file);
	return buffer;
}

struct BtfBatteryInfo* btf_battery_info_build(){
	struct BtfBatteryInfo* battery_info;
	battery_info = (struct BtfBatteryInfo*)malloc(sizeof(struct BtfBatteryInfo));
	if(!battery_info)return NULL;

	battery_info->btf_type = btf_battery_info_type();
	battery_info->btf_capacity = btf_battery_info_capacity();
	battery_info->btf_capacity_level = btf_battery_info_capacity_level();
	battery_info->btf_technology = btf_battery_info_technology();
	battery_info->btf_manufacturer = btf_battery_info_manufacturer();
	battery_info->btf_serial_number = btf_battery_info_serial();
	return battery_info;
}

struct BtfACInfo* btf_ac_info_build(){
	struct BtfACInfo* btf_ac_info;
	btf_ac_info = (struct BtfACInfo*)malloc(sizeof(struct BtfACInfo));
	if(!btf_ac_info)return NULL;
	btf_ac_info->type = btf_ac_info_type();
	btf_ac_info->state = btf_ac_info_state();
	return btf_ac_info;
}

