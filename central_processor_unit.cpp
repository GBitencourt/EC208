/********************************************************************************


					MAQUINA VIRTUAL DE <EC-208>


Alunos:


    Guilherme Costa
    Gustavo Marins
    Felipe Jurioli


	Este codigo implementa uma maquina virtual (interpretador) capaz de buscar,
decodificar e executar um set de instrucao.Criado para demostrar o funcionamento
de uma maquina virtual durante as aulas de EC-208.

***********************************************************************************

						Informacoes do Interpretadr

	Tamanho das instruoees: 32 bits

	Codigo das intruoees:

		ADD: 	00000001
		LOAD: 	11110011
		STORE:	11111100

	Instruoees Aritmeticas:

		- Utilizado para operacoees ADD e SUB)

             MSB                                      LSB

		(Tipo instr.) (End. Reg 1) (End. Reg 2) (End Reg Dest.)

           8 bits        8 bits        8 bits       8 bits


         - Exemplo: 0b00000001000000000000000100000010
 	 				  00000001|00000000|00000001|00000010

   	 			Realiza a soma (00000001 >> tipo da instruoeo) do registro 0
               (00000000>> end. Reg 0) com o registro 1 (00000001 >> end. Reg 1)
			   e salva o resultado em registro 2 (00000010 >> end. Reg Dest.)


    Instruoees de Controle:

     	 - Uitlizado para operaoees de LOAD e STORE

     	       MSB                        LSB

     	 (Tipo instr.) (End Reg) (End Memoria de dados)

		    4 bits       4 bits        16 bits

   	   - Exemplo: 0b11110011000000000000000000000000
   	   	   	        11110011|00000000|0000000000000000|

         	 	Realiza o LOAD (11110011 >> tipo da instruoeo) do endereco de
			memoria 0 (0000000000000000 >> end. Memoria) para o registrador 0
			(00000000 >> end. Reg )

********************************************************************************/

#include <iostream>
#include <stdlib.h>

using namespace std;


// Memoria de programa
unsigned int ProgMemory[] = {0b11110011000000000000000000000000,
							 0b11110011000000010000000000000001,
							 0b00000001000000000000000100000010,
							 0b11111100000000100000000000000010
							};
// LOAD REGISTRO0<-ENDMEMEMORIA0
// LOAD REGISTRO1<-ENDMEMEMORIA1
// ADD REGISTRO0 REGISTRO1 REGISTRO2
// STORE REGISTRO2 ENDMEMORIA2
// Memoria de dados
unsigned int DataMemory[] = { 5, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


// Registradores
unsigned int PC;
unsigned int Instr;
unsigned int InstrType;
unsigned int RegA;
unsigned int RegB;
unsigned int RegDest;
unsigned int RegAddrMemory;
unsigned int Reg[10];

// Prototipos
void decode(void);
void execute(void);

int main()
{
	unsigned char i;
	
	cout << "Valores iniciais da memoria\n";
	
	cout << DataMemory[0] << ".\n";
	cout << DataMemory[1] << ".\n";
	cout << DataMemory[2] << ".\n";
	cout << DataMemory[3] << ".\n";
	cout << DataMemory[4] << ".\n";
	cout << DataMemory[5] << ".\n";
	cout << DataMemory[6] << ".\n";
	cout << DataMemory[7] << ".\n";
	cout << DataMemory[8] << ".\n";
	cout << DataMemory[9] << ".\n";
	
	_sleep(2000);
	
	// -------------------------------------------------------------** Inicializacao dos registros **---------------------------------------------------------------- //
	
	PC = 0;
	
	for(i = 0; i < 10; i++){
		Reg[i] = 0;
	}

	cout << "Buscando instrucao\n";
	
	_sleep(1000);
	
	while(PC < 4){

		Instr = ProgMemory[PC]; // busca da instruao
		PC = PC + 1;
		decode();    // decodificacao
		execute();
	}


	cout << "Valores da memoria\n";
	cout << DataMemory[0] << ".\n";
	cout << DataMemory[1] << ".\n";
	cout << DataMemory[2] << ".\n";
	cout << DataMemory[3] << ".\n";
	cout << DataMemory[4] << ".\n";
	cout << DataMemory[5] << ".\n";
	cout << DataMemory[6] << ".\n";
	cout << DataMemory[7] << ".\n";
	cout << DataMemory[8] << ".\n";
	cout << DataMemory[9] << ".\n";

	return 0;
}


void decode(void)
{
	InstrType = Instr >> 24;

	if(InstrType == 1){
		
		/* Soma */
		if(InstrType == 1){
			cout << "Opecarao Soma \n";
		}
		
		_sleep(1000);
		
		RegA = Instr >> 16;
		RegA = RegA & 0b00000000000000000000000011111111;
		RegB = Instr >> 8;
		RegB = RegB & 0b00000000000000000000000011111111;
		RegDest = Instr & 0b00000000000000000000000011111111;
	}
	
	else if(InstrType == 243){
		
		/* Load */
		RegDest = Instr >> 16;
		RegDest = RegDest & 0b00000000000000000000000011111111;
		RegAddrMemory = Instr & 0b00000000000000001111111111111111;
	}
	
	else if(InstrType == 252){
		
		/* Store */
		RegA = Instr >> 16;
		RegA = RegA & 0b00000000000000000000000011111111;
		RegAddrMemory = Instr & 0b00000000000000001111111111111111;
	}
}

void execute(void)
{

	if(InstrType == 1){
		// Soma
		cout << "Somando registro A e B \n";
		_sleep(1000);
		Reg[RegDest] = Reg[RegA] + Reg[RegB];
	}
	
	else if(InstrType == 243){
		// Load
		cout << "Carregando registro \n";
		_sleep(1000);
		Reg[RegDest] = DataMemory[RegAddrMemory];
	}
	
	else if(InstrType == 252){
		// Store
		cout << "Guargando valor do registro na memoria \n";
		_sleep(1000);
		DataMemory[RegAddrMemory] = Reg[RegA];
	}
	
}


