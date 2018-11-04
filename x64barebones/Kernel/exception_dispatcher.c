extern void print_all_registers();

typedef void (*func)();

static void dummy_func();
static void exception0();
static void exception6();
static void exception13();

func exception_functions[] = {exception0, dummy_func, dummy_func, dummy_func, dummy_func, dummy_func, exception6};

void exception_dispatcher(int idx){
	exception_functions[idx]();
}

void dummy_func(){ // funcion dummy que no hace nada, se deja asi hasta que se implementen las proximas excepciones
	return;
}

void exception0(){
	print_all_registers();
}

void exception6(){
	print_all_registers();
}

void exception13(){
	print_all_registers();
}
