/*
 * The MIT License (MIT)

 Copyright (c) 2023 Naol Dereje

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
#include <stdlib.h>
#include <stdio.h>
#include "btf_types.h"

#ifndef BTF
#define BTF
#define BTF_VERSION "0.1"
#define BTF_HELP ""\
	"--info | -i : shows informations available about the hardware battery"\
	"--version | -v : prints the version of btf"\
	"--help | -h : shows this help message" 

#define BTF_SYS_READ "r"
/*
 * System battery informations are stored here
 */
#define BTF_BATTERY_PATH "/sys/class/power_supply/BAT0"
#define BTF_BATTERY_CAPACITY "/sys/class/power_supply/BAT0/capacity"
#define BTF_BATTERY_CAPACITY_LEVEL "/sys/class/power_supply/BAT0/capacity_level" 
#define BTF_BATTERY_MANUFACTURER "/sys/class/power_supply/BAT0/manufacturer"
#define BTF_BATTERY_SERIAL "/sys/class/power_supply/BAT0/serial_number"
#define BTF_BATTERY_TECHNOLOGY "/sys/class/power_supply/BAT0/technology"
#define BTF_BATTERY_TYPE "/sys/class/power_supply/BAT0/type"

/*
 * when the system is on AC power_supply
 * boolean flag is stored in here 
*/
#define BTF_AC_PATH "/sys/class/power_supply/AC"
#define BTF_AC_STATE "/sys/class/power_supply/AC/online"
#define BTF_AC_TYPE "/sys/class/power_supply/AC/type"
#define BTF_AC_ON  "1" 


/*
 * BTF argument configurations
 */
#ifndef BTF_ARGS
#define BTF_ARGS
#define BTF_ARGS_SHORT_INFO "-i"
#define BTF_ARGS_SHORT_VERSION "-v"
#define BTF_ARGS_SHORT_HELP "-h"

#define BTF_ARGS_LONG_INFO "--info"
#define BTF_ARGS_LONG_VERSION "--version"
#define BTF_ARGS_LONG_HELP "--help"
#endif

#endif

// BtfBattery structure to hold
// different properties of the battery
struct BtfBatteryInfo{
	btf_str btf_capacity;
	btf_str btf_capacity_level;
	btf_str btf_manufacturer;
	btf_str btf_serial_number;
	btf_str btf_technology;
	btf_str btf_type;
};

// BtfBattery AC structure info
struct BtfACInfo{
	boolean state;
	btf_str type;
};


boolean btf_ac_info_state(void);
btf_str btf_ac_info_type(void);

// btf battery functions
boolean btf_battery_availabe(void); // checks if a battery is available
btf_str btf_battery_info_capacity(void); // checks battery capacity
btf_str btf_battery_info_capacity_level(void); // checks battery capacity level
btf_str btf_battery_info_manufacturer(void); // reads battery manufacturer
btf_str btf_battery_info_serial(void); // reads battery info serial
btf_str btf_battery_info_technology(void); // reads battery technology
										
// oooh this one! i have no idea what is a type.
btf_str btf_battery_info_type(void); // reads battery type

size_t btf_sys_file_length(FILE*);
btf_str btf_sys_file_read_buffer(FILE*, size_t);

// battery information builder
struct BtfBatteryInfo* btf_battery_info_build();

// a builder for ac component 
struct BtfACInfo* btf_ac_info_build();

