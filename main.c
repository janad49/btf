#include <stdio.h>
#include <stdlib.h>
#include "btf.h"
#include "btf_types.h"
#include "main.h"

// prints the version 
void btf_print_version(){
	printf("%s\n", BTF_HELP);
}

// prints the help manual
void btf_print_help(){
	printf("%s\n", BTF_HELP);
}

i32 myArgc;
btf_str* myArgv;

// argument operation
btf_str btf_short_arg_opt;
btf_str btf_long_arg_opt;
boolean btf_arg_short_opt; // enabled if short argument is provided (-i)
boolean btf_arg_long_opt; // enabled if long argument is provided (--info)

void btf_parse_args(){

}

void btf_show_info(){
	if(myArgc < NO_ARG_LEN){
		// shows every available info 
		// about the device hardware
		return;
	}

}
int kain(int argc, char* argv[]){
	myArgc = argc;
	myArgv = argv;
	btf_parse_args();
	btf_show_info();
}

