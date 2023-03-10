#include <stdio.h>
#include <stdbool.h>
#include "btf.h"
#include "btf_types.h"

void test_battery_info();
void test_ac_info();

int main(){
	test_battery_info();
	test_ac_info();
	return 0;
}

void test_battery_info(void){
	// check if the battery is available
	printf("checking battery...\n");
	if(!btf_battery_availabe()){
		printf("hardware battery is not found!\n");
		printf("terminating battery system check...\n");
		return;
	}

	printf("battery available...\n");
	struct BtfBatteryInfo* sys_battery_info;
	sys_battery_info = btf_battery_info_build();
	void* datum = &sys_battery_info;

	if(!sys_battery_info){
		printf("error: unable to read system property\n");
		return;
	}

	printf("battery type: %s", sys_battery_info->btf_type);
	printf("battery_capacity: %s", sys_battery_info->btf_capacity);
	printf("battery_capacity_level: %s", sys_battery_info->btf_capacity_level);
	printf("battery_manufacturer: %s", sys_battery_info->btf_manufacturer);
	printf("battery_technology: %s", sys_battery_info->btf_technology);
	printf("finished battery check...");
	printf("\nmemory address of info: %p\n", &sys_battery_info);
	printf("datum address: %p\n", datum);

	free(sys_battery_info);
	// cheking memory address
	if(datum != &sys_battery_info){
		printf("address has been reset\n");
	}
}

void test_ac_info(void){
	// check if the ac system is online
	struct BtfACInfo* btf_ac_info;
	btf_ac_info = btf_ac_info_build();
	if(!btf_ac_info){
		printf("error: unable to get ac info\n");
		return;
	}

	btf_ac_info->state == true ? printf("AC is available!\n") : printf("ac is not available!\n");
	if(!btf_ac_info->type){
		printf("ac type not available!\n");
		return;
	}

	printf("ac type: %s\n", btf_ac_info->type);

}
