#define NO_ARG_LEN 2 
#include "btf_types.h"

// argument types
#define BTF_ARGUMENT_LONG  2
#define BTF_ARGUMENT_SHORT 1
#define BTF_ARGUMENT_NONE  0

// a structure for parsing arguments
typedef struct Argument{
	btf_str arg_name;
	i8 arg_type;
	btf_str* arg_list;
	Argument* next;
}Argument;

boolean btf_argument_short(btf_str);
boolean btf_argument_long(btf_str);

void btf_parse_args();
void btf_print_version();
void btf_print_help();
void btf_no_argument();
void btf_show_info();

