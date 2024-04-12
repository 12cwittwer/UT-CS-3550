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

	code.Finish();
	code.Execute();
	return 0;
}
