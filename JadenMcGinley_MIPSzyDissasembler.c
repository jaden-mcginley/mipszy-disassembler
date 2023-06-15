#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void Display_ProgramStart()
{
	printf("-----------------------");
	printf("\n- MIPSzy DISSASEMBLER -");
	printf("\n-  BY JADEN MCGINLEY  -");
	printf("\n-----------------------");
}

void Display_ProgramEnd()
{
	printf("\n-----------------------");
	printf("\n- MIPSzy DISSASEMBLER -");
	printf("\n-      THANK YOU      -");
	printf("\n-      FOR USING      -");
	printf("\n-----------------------");
}

void Display_ProgramLineLengthError(int lineNummer)
{
	printf("\n-----------------------");
	printf("\n- MIPSzy DISSASEMBLER -");
	printf("\n-  LINE LENGTH ERROR  -");
	printf("\n- ON LINE: ");
	printf("%i", lineNummer);
	printf(" -");
	printf("\n-----------------------");
}

void Display_ProgramTranslationError(int lineNummer)
{
	printf("\n-----------------------");
	printf("\n- MIPSzy DISSASEMBLER -");
	printf("\n-  TRANSLATION ERROR  -");
	printf("\n- ON LINE: ");
	printf("%i", lineNummer);
	printf(" -");
	printf("\n-----------------------");
}

void Display_ProgramMIPSzyFileContents(FILE *file)
{
	printf("\nYour machine code was converted to the following MIPSzy program:\n\n");

	file = fopen("C:/Users/4mcgi/source/repos/JadenMcGinley_C-1/JadenMcGinley_C-1/MIPSzyCode.txt", "r");

	char c;
	c = getc(file);

	while (c != EOF)
	{
		printf("%c", c);
		c = fgetc(file);
	}

	fclose(file);
}

void Input_MachineCodeLine(char *instructions[])
{
	printf("\n\nEnter a line of machine code to be processed: ");
	fflush(stdin);
	gets(instructions);
}

int Input_PromptResponse(char *response)
{
	int continueAsking = 1;

	while (continueAsking == 1)
	{
		printf("\nWould you like to enter another line of machine code (y/n)? ");
		fflush(stdin);
		gets(response);

		if (*response == 'y' || *response == 'n')
		{
			continueAsking = 0;
		}
		else
		{
			printf("\nInput a valid response.");
		}
	}

	if (*response == 'y')
	{
		return 1;
	}
	else if (*response == 'n')
	{
		return 0;
	}

	return 0;
}

void Process_CheckInstructionLength(char *string[], int lineNumber)
{
	if (strlen(string) != 32)
	{
		Display_ProgramLineLengthError(lineNumber);
		exit();
	}
}

void Process_WriteToMachineCodeFile(FILE *file, char *string[])
{
	file = fopen("C:/Users/4mcgi/source/repos/JadenMcGinley_C-1/JadenMcGinley_C-1/MachineCode.txt", "a");
	fprintf(file, string);
	fprintf(file, "\n");
	fclose(file);
}

void Process_WriteToMIPSzyCodeFile(FILE* file, char* string[])
{
	file = fopen("C:/Users/4mcgi/source/repos/JadenMcGinley_C-1/JadenMcGinley_C-1/MIPSzyCode.txt", "a");
	fprintf(file, string);
	fprintf(file, "\n");
	fclose(file);
}

int Process_ConvertStringBinaryToDecimal(char* string)
{
	int slen = strlen(string);
	int total = 0;
	int decval = 1;

	for (int i = (slen - 1); i >= 0; i--)
	{
		if (string[i] == '1') total += decval;
		decval *= 2;
	}

	return total;
}

void Process_TranslateToMIPSzy(char *instruction1, char *address1, char *address2, char *address3, char *instruction2, int lineNumber, FILE* file)
{
	char *machineCodeTranslation_Zero = "00000";
	char *machineCodeTranslation_Register0 = "01000";
	char *machineCodeTranslation_Register1 = "01001";
	char *machineCodeTranslation_Register2 = "01010";
	char *machineCodeTranslation_Register3 = "01011";
	char *machineCodeTranslation_Register4 = "01100";
	char *machineCodeTranslation_Register5 = "01101";
	char *machineCodeTranslation_Register6 = "01110";

	char *machineCodeTranslation_LoadRegisterInstruction1 = "100011";

	char *machineCodeTranslation_SaveRegisterInstruction1 = "101011";

	char *machineCodeTranslation_AddiRegisterInstruction1 = "001000";

	char *machineCodeTranslation_AddRegisterInstruction1 = "000000";
	char *machineCodeTranslation_AddRegisterInstruction2 = "00000100000";

	char *machineCodeTranslation_SubRegisterInstruction1 = "000000";
	char *machineCodeTranslation_SubRegisterInstruction2 = "00000100010";

	char *machineCodeTranslation_MulRegisterInstruction1 = "000000";
	char *machineCodeTranslation_MulRegisterInstruction2 = "00000011000";

	char *machineCodeTranslation_SltRegisterInstruction1 = "000000";
	char *machineCodeTranslation_SltRegisterInstruction2 = "00000101010";

	const char* machineCodeString_Zero = "$zero";
	const char* machineCodeString_Register0 = "$t0";
	const char* machineCodeString_Register1 = "$t1";
	const char* machineCodeString_Register2 = "$t2";
	const char* machineCodeString_Register3 = "$t3";
	const char* machineCodeString_Register4 = "$t4";
	const char* machineCodeString_Register5 = "$t5";
	const char* machineCodeString_Register6 = "$t6";

	const char* machineCodeString_Load = "lw";
	const char* machineCodeString_Save = "sw";

	const char* machineCodeString_Add = "add";
	const char* machineCodeString_Addi = "addi";
	const char* machineCodeString_Sub = "sub";
	const char* machineCodeString_Mul = "mul";
	const char* machineCodeString_Slt = "slt";

	const char *machineCodeString_Space = " ";

	const char mipsCodeString[100] = "";
	const char addressInstructionCombo[100] = "";

	if (!strcmp(instruction1, machineCodeTranslation_LoadRegisterInstruction1))
		//Check for Load Instruction
	{
		if (!strcmp(address1, machineCodeTranslation_Zero) || !strcmp(address2, machineCodeTranslation_Zero))
		{
			//No translation
			Display_ProgramTranslationError(lineNumber);

			exit();
		}

		strcat(mipsCodeString, machineCodeString_Load);
		strcat(mipsCodeString, machineCodeString_Space);

		if (!strcmp(address2, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}

		strcat(mipsCodeString, ", ");

		strcat(addressInstructionCombo, address3);
		strcat(addressInstructionCombo, instruction2);

		char decimalNumber[100] = "";

		sprintf(decimalNumber, "%d", Process_ConvertStringBinaryToDecimal(addressInstructionCombo));
		strcat(mipsCodeString, decimalNumber);

		strcat(mipsCodeString, "(");

		if (!strcmp(address1, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}
		else if (!strcmp(address1, machineCodeTranslation_Zero))
		{
			strcat(mipsCodeString, machineCodeString_Zero);
		}

		strcat(mipsCodeString, ")");

		Process_WriteToMIPSzyCodeFile(file, mipsCodeString);
	}
	else if (!strcmp(instruction1, machineCodeTranslation_SaveRegisterInstruction1))
		//Check for Save Instruction
	{
		if (!strcmp(address1, machineCodeTranslation_Zero) || !strcmp(address2, machineCodeTranslation_Zero))
		{
			//No translation
			Display_ProgramTranslationError(lineNumber);

			exit();
		}

		strcat(mipsCodeString, machineCodeString_Save);
		strcat(mipsCodeString, machineCodeString_Space);

		if (!strcmp(address2, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}

		strcat(mipsCodeString, ", ");

		strcat(addressInstructionCombo, address3);
		strcat(addressInstructionCombo, instruction2);

		char decimalNumber[100] = "";

		sprintf(decimalNumber, "%d", Process_ConvertStringBinaryToDecimal(addressInstructionCombo));
		strcat(mipsCodeString, decimalNumber);

		strcat(mipsCodeString, "(");

		if (!strcmp(address1, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}
		else if (!strcmp(address1, machineCodeTranslation_Zero))
		{
			strcat(mipsCodeString, machineCodeString_Zero);
		}

		strcat(mipsCodeString, ")");

		Process_WriteToMIPSzyCodeFile(file, mipsCodeString);
	}
	else if (!strcmp(instruction1, machineCodeTranslation_AddRegisterInstruction1)
		&& !strcmp(instruction2, machineCodeTranslation_AddRegisterInstruction2))
		//Check for Add Instruction
	{
		if (!strcmp(address3, machineCodeTranslation_Zero))
		{
			//No translation
			Display_ProgramTranslationError(lineNumber);

			exit();
		}

		if (!strcmp(address1, machineCodeTranslation_Zero) && !strcmp(address2, machineCodeTranslation_Zero))
		{
			//No translation
			Display_ProgramTranslationError(lineNumber);

			exit();
		}

		strcat(mipsCodeString, machineCodeString_Add);
		strcat(mipsCodeString, machineCodeString_Space);

		if (!strcmp(address3, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}

		strcat(mipsCodeString, ", ");

		if (!strcmp(address1, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}
		else if (!strcmp(address1, machineCodeTranslation_Zero))
		{
			strcat(mipsCodeString, machineCodeString_Zero);
		}

		strcat(mipsCodeString, ", ");

		if (!strcmp(address2, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}
		else if (!strcmp(address2, machineCodeTranslation_Zero))
		{
			strcat(mipsCodeString, machineCodeString_Zero);
		}

		Process_WriteToMIPSzyCodeFile(file, mipsCodeString);
	}
	else if (!strcmp(instruction1, machineCodeTranslation_SubRegisterInstruction1)
		&& !strcmp(instruction2, machineCodeTranslation_SubRegisterInstruction2))
		//Check for Sub Instruction
	{
		if (!strcmp(address3, machineCodeTranslation_Zero))
		{
			//No translation
			Display_ProgramTranslationError(lineNumber);

			exit();
		}

		if (!strcmp(address1, machineCodeTranslation_Zero) && !strcmp(address2, machineCodeTranslation_Zero))
		{
			//No translation
			Display_ProgramTranslationError(lineNumber);

			exit();
		}

		strcat(mipsCodeString, machineCodeString_Sub);
		strcat(mipsCodeString, machineCodeString_Space);

		if (!strcmp(address3, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}

		strcat(mipsCodeString, ", ");

		if (!strcmp(address1, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}
		else if (!strcmp(address1, machineCodeTranslation_Zero))
		{
			strcat(mipsCodeString, machineCodeString_Zero);
		}

		strcat(mipsCodeString, ", ");

		if (!strcmp(address2, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}
		else if (!strcmp(address2, machineCodeTranslation_Zero))
		{
			strcat(mipsCodeString, machineCodeString_Zero);
		}

		Process_WriteToMIPSzyCodeFile(file, mipsCodeString);
	}
	else if (!strcmp(instruction1, machineCodeTranslation_MulRegisterInstruction1)
		&& !strcmp(instruction2, machineCodeTranslation_MulRegisterInstruction2))
	{
		if (!strcmp(address3, machineCodeTranslation_Zero))
		{
			//No translation
			Display_ProgramTranslationError(lineNumber);

			exit();
		}

		if (!strcmp(address1, machineCodeTranslation_Zero) && !strcmp(address2, machineCodeTranslation_Zero))
		{
			//No translation
			Display_ProgramTranslationError(lineNumber);

			exit();
		}

		strcat(mipsCodeString, machineCodeString_Mul);
		strcat(mipsCodeString, machineCodeString_Space);

		if (!strcmp(address3, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}

		strcat(mipsCodeString, ", ");

		if (!strcmp(address1, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}
		else if (!strcmp(address1, machineCodeTranslation_Zero))
		{
			strcat(mipsCodeString, machineCodeString_Zero);
		}

		strcat(mipsCodeString, ", ");

		if (!strcmp(address2, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}
		else if (!strcmp(address2, machineCodeTranslation_Zero))
		{
			strcat(mipsCodeString, machineCodeString_Zero);
		}

		Process_WriteToMIPSzyCodeFile(file, mipsCodeString);
	}
	else if (!strcmp(instruction1, machineCodeTranslation_SltRegisterInstruction1)
		&& !strcmp(instruction2, machineCodeTranslation_SltRegisterInstruction2))
	{
		if (!strcmp(address3, machineCodeTranslation_Zero))
		{
			//No translation
			Display_ProgramTranslationError(lineNumber);

			exit();
		}

		if (!strcmp(address1, machineCodeTranslation_Zero) && !strcmp(address2, machineCodeTranslation_Zero))
		{
			//No translation
			Display_ProgramTranslationError(lineNumber);

			exit();
		}

		strcat(mipsCodeString, machineCodeString_Slt);
		strcat(mipsCodeString, machineCodeString_Space);

		if (!strcmp(address3, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address3, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}

		strcat(mipsCodeString, ", ");

		if (!strcmp(address1, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}
		else if (!strcmp(address1, machineCodeTranslation_Zero))
		{
			strcat(mipsCodeString, machineCodeString_Zero);
		}

		strcat(mipsCodeString, ", ");

		if (!strcmp(address2, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}
		else if (!strcmp(address2, machineCodeTranslation_Zero))
		{
			strcat(mipsCodeString, machineCodeString_Zero);
		}

		Process_WriteToMIPSzyCodeFile(file, mipsCodeString);
	}
	else if (!strcmp(instruction1, machineCodeTranslation_AddiRegisterInstruction1))
	{
		if (!strcmp(address1, machineCodeTranslation_Zero) && !strcmp(address2, machineCodeTranslation_Zero))
		{
			//No translation
			Display_ProgramTranslationError(lineNumber);

			exit();
		}

		strcat(mipsCodeString, machineCodeString_Addi);
		strcat(mipsCodeString, machineCodeString_Space);

		if (!strcmp(address2, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address2, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}

		strcat(mipsCodeString, ", ");

		if (!strcmp(address1, machineCodeTranslation_Register0))
		{
			strcat(mipsCodeString, machineCodeString_Register0);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register1))
		{
			strcat(mipsCodeString, machineCodeString_Register1);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register2))
		{
			strcat(mipsCodeString, machineCodeString_Register2);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register3))
		{
			strcat(mipsCodeString, machineCodeString_Register3);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register4))
		{
			strcat(mipsCodeString, machineCodeString_Register4);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register5))
		{
			strcat(mipsCodeString, machineCodeString_Register5);
		}
		else if (!strcmp(address1, machineCodeTranslation_Register6))
		{
			strcat(mipsCodeString, machineCodeString_Register6);
		}
		else if (!strcmp(address1, machineCodeTranslation_Zero))
		{
			strcat(mipsCodeString, machineCodeString_Zero);
		}

		strcat(mipsCodeString, ", ");

		strcat(addressInstructionCombo, address3);
		strcat(addressInstructionCombo, instruction2);

		char decimalNumber[100] = "";

		sprintf(decimalNumber, "%d", Process_ConvertStringBinaryToDecimal(addressInstructionCombo));
		strcat(mipsCodeString, decimalNumber);

		Process_WriteToMIPSzyCodeFile(file, mipsCodeString);
	}
	else //No translation
	{
		Display_ProgramTranslationError(lineNumber);

		exit();
	}
}

int Process_CheckCurrentLineNumber(FILE *file)
{
	char c;
	int characters = 0;

	file = fopen("C:/Users/4mcgi/source/repos/JadenMcGinley_C-1/JadenMcGinley_C-1/MachineCode.txt", "r");
	
	for (c = getc(file); c != EOF; c = getc(file))
	{
		// Increment count for this character
		characters++;
	}

	fclose(file);
	
	if (characters != 0 && characters != NULL)
	{
		return characters;
	}

	return 0;
}

void Process_SliceString(const char *string, char *result, size_t start, size_t end)
{
	strncpy(result, string + start, end - start);
}

void Process_PopulateSlicedStrings(char *machineCodeLine, char *instruction1, char *address1, char *address2, char *address3, char *instruction2)
{
	Process_SliceString(machineCodeLine, instruction1, 0, 6);
	Process_SliceString(machineCodeLine, address1, 6, 11);
	Process_SliceString(machineCodeLine, address2, 11, 16);
	Process_SliceString(machineCodeLine, address3, 16, 21);
	Process_SliceString(machineCodeLine, instruction2, 21, 33);
}

int main()
{
	FILE *machineCodeFile;
	FILE *mipsCodeFile;

	machineCodeFile = fopen("C:/Users/4mcgi/source/repos/JadenMcGinley_C-1/JadenMcGinley_C-1/MachineCode.txt", "w");
	fclose(machineCodeFile);

	mipsCodeFile = fopen("C:/Users/4mcgi/source/repos/JadenMcGinley_C-1/JadenMcGinley_C-1/MIPSzyCode.txt", "w");
	fclose(mipsCodeFile);

	int currentLineNumber = 0;
	int continueVariable = 1;
	
	char *user_MachineCodeInstructions[32];

	char *user_MachineCodeSlice_Instruction1 = "######";
	char* user_MachineCodeSlice_Address1[5] = { '#', '#', '#', '#', '#' };
	char* user_MachineCodeSlice_Address2[5] = { '#', '#', '#', '#', '#' };
	char* user_MachineCodeSlice_Address3[5] = { '#', '#', '#', '#', '#' };
	char *user_MachineCodeSlice_Instruction2[11]; // I don't know why this one has to be different...

	char *user_PromptResponse = ' ';

	Display_ProgramStart();

	while (continueVariable == 1)
	{
		currentLineNumber = (Process_CheckCurrentLineNumber(&machineCodeFile) / 32) + 1;

		Input_MachineCodeLine(&user_MachineCodeInstructions);
		Process_CheckInstructionLength(&user_MachineCodeInstructions, currentLineNumber);

		Process_PopulateSlicedStrings(&user_MachineCodeInstructions, &user_MachineCodeSlice_Instruction1, &user_MachineCodeSlice_Address1, 
			&user_MachineCodeSlice_Address2, &user_MachineCodeSlice_Address3, &user_MachineCodeSlice_Instruction2);

		Process_WriteToMachineCodeFile(&machineCodeFile, &user_MachineCodeInstructions);

		Process_TranslateToMIPSzy(&user_MachineCodeSlice_Instruction1, &user_MachineCodeSlice_Address1,
			&user_MachineCodeSlice_Address2, &user_MachineCodeSlice_Address3, &user_MachineCodeSlice_Instruction2, currentLineNumber, &mipsCodeFile);

		continueVariable = Input_PromptResponse(&user_PromptResponse);
	}

	Display_ProgramMIPSzyFileContents(&mipsCodeFile);

	Display_ProgramEnd();

	return 0;
}