#include <utilities.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define EOF -1

#define RETURN_ADRESS 0xDEADC0DE

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


uint64_t * shell();

uint64_t * shell(void){
<<<<<<< HEAD
	put_char('h');
	put_char('o');
	put_char('l');
	put_char('a');	

	while(1){
		put_char('g');
	}
	return;
=======
	char c;
	int flag=TRUE;
	while(flag){
		c=get_char();
		if(c!=EOF)
			put_char(c);
	}


	/*
	const char * commands = {"pong", "time","shutdown"};
	char command[MAX_LENGTH];
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
	return (uint64_t *) RETURN_ADRESS;
}

void invalid_command(){
	print_f("Invalid command \n");
}

void shutdown(){
	print_f("Thank you, powering off");
}
void play_pong(){
	print_f("Aca jugamos al pong");
}
void show_time(){
	print_f("Aca mostramos el tiempo");
>>>>>>> 526d47a5772574140a7180bc72fd61c69fb15f26
}
