#include "Instructions.h"

// int main() {
//     InstructionsClass code;

//     code.PushValue(-500);
//     code.PopAndWrite();
//     code.PushValue(1000);
//     code.PopAndWrite();

//     code.Finish();
//     code.Execute();
//     return 0;
// }

int main()
{
	InstructionsClass code;

	code.PushValue(500); // 500 to stack
	code.PopAndStore(1); // to any slot number of mData
	code.PushVariable(1); // from mData back onto stack
	code.PopAndWrite();

    code.PushValue(100); 
	code.PushValue(8);
	code.PopPopDivPush();
	code.PopAndWrite(); // should print 12

    code.PushValue(100); 
	code.PushValue(8);
	code.PopPopAddPush();
	code.PopAndWrite(); // should print 108

    code.PushValue(100); 
	code.PushValue(8);
	code.PopPopSubPush();
	code.PopAndWrite(); // should print 92

    code.PushValue(10); 
	code.PushValue(2);
	code.PopPopMulPush();
	code.PopAndWrite(); // should print 20

	code.Finish();
	code.Execute();


	return 0;
}
