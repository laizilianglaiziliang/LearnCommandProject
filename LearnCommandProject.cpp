// LearnCommandProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include "Command.h"
#include "Receiver_Array.h"
#include "CommandMgr.h"
#include <memory>
int main()
{
	std::vector<int> vec{ 1,2,3 };
	std::shared_ptr<Receiver_Array<int>> receiver_Array(new Receiver_Array<int>(&vec));

	std::shared_ptr<AddCommand<int>> addCommand(new AddCommand<int>(receiver_Array, 3, 4));
	CommandMgr commandMgr;
	commandMgr.execute(addCommand);
	commandMgr.undo();
	commandMgr.redo();
	receiver_Array->display();

	std::shared_ptr<SeekCommand<int>> seekCommand(new SeekCommand<int>(receiver_Array, 1));
	int* val= (int*)(commandMgr.executeOther(seekCommand));
	receiver_Array->display();

	std::shared_ptr<DelCommand<int>> delCommand(new DelCommand(receiver_Array, 1));
	commandMgr.execute(delCommand);
	commandMgr.undo();
	commandMgr.redo();
	receiver_Array->display();

	std::shared_ptr<ModifyCommand<int>> modifyCommand(new ModifyCommand(receiver_Array, 2, 2));
	commandMgr.execute(modifyCommand);
	commandMgr.undo();
	commandMgr.redo();
	receiver_Array->display();

	printf("ok");
}
