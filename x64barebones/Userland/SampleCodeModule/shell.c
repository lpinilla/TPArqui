#include <utilities.h>
#include <string.h>

#define EOF -1

#define RETURN_ADRESS 0xDEADC0DE

#define INVALID 0
#define PONG 1
#define TIME 2
#define SHUTDOWN 3

#define COMMANDS 3

#define MAX_LENGTH 20

typedef void (*func)();

void invalid_command();
void play_pong();
void show_time();
void shutdown();

static func execute_command[]={play_pong,show_time,shutdown};
const char * commands[] = {"pong", "time","shutdown"};

uint64_t * shell();

uint64_t * shell(void){
	int i=0;
	char command[MAX_LENGTH];
	char c;
	int flag=0;
	while(flag!=SHUTDOWN){
		c=get_char();
		put_char(c);
		if(i<MAX_LENGTH){
			command[i]=c;
		}
		if(c=='\n' && i<MAX_LENGTH){
			command[i]='\0';
			print_f(command);
			flag=command_handler(command);
			i=0;
		}
		else if(c=='\n' && i>=MAX_LENGTH){
			invalid_command();
			i=0;
		}
		else
			i++;
	}
	return (uint64_t *) RETURN_ADRESS;
}
int command_handler(char * command){
	for(int i=0; i<COMMANDS; i++){
		if(str_cmp(command, commands[i])==0){
			execute_command[i]();
			return i;
		}
	}
	invalid_command();
	return INVALID;

}
/*
	int flag = TRUE;
	char c;
	int i;
	int valid_command = FALSE;

	while(flag){
		i=0;
		while((c=get_char())!=EOF && i<MAX_LENGTH){
			command[i]=c;
			i++;
		}
		if(i>=MAX_LENGTH)
			invalid_command();
		else{
			for(int i=0; i<COMMANDS;i++){
				if(str_cmp(command,commands[i])==0){
					execute_command[i]();
					valid_command=TRUE;
				}
				if(valid_command == FALSE)
					invalid_command();
				valid_command = FALSE;
			}
		}
	}
	*/

void invalid_command(){
	print_f("Invalid command \n");
}

void shutdown(){
	print_f("Thank you, powering off \n");
}
void play_pong(){
	print_f("Aca jugamos al pong \n");
}
void show_time(){
	print_f("Aca mostramos el tiempo \n");
}
