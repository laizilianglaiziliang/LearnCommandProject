// LearnCommandProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include "Command.h"
#include "Receiver_Array.h"
#include "CommandMgr.h"
#include <memory>
#include <cmath>
//class A;
//class B;
//class A
//{
//public:
//	std::shared_ptr<B> ptrb;
//	int k = 1;
//};
//class B
//{
//public:
//	std::weak_ptr<A> ptra;
//	int k = 2;
//};
//void testRef(std::shared_ptr<B>& b)
//{
//	std::shared_ptr<B> ptrB(new B());
//	std::shared_ptr<A> ptrA(new A());
//	ptrA->ptrb = ptrB;
//	ptrB->ptra = ptrA;
//	b = ptrB;
//}

struct A;
struct B;
std::weak_ptr<A> awp;
std::weak_ptr<B> bwp;
struct A
{
	std::shared_ptr<B> bptr;
	~A() { std::cout << "A is deleted!" << std::endl; }
};
struct B
{
	std::shared_ptr<A> aptr;
	~B() { std::cout << "B is deleted!" << std::endl; }
};
void testPtr()
{
	std::shared_ptr<B> bp(new B);
	{
		std::shared_ptr<A> ap(new A);		
		ap->bptr = bp;
		bp->aptr = ap;
		awp = ap;
		printf("ap.usecount = %d\n", awp.use_count());//输出ap.usecount =2
		bwp = bp;
		printf("bp.usecount = %d\n", bwp.use_count());//输出ap.usecount =2

	}
	printf("ap.usecount = %d\n", bp.use_count());//输出ap.usecount =1
	printf("ap.usecount = %d\n", awp.use_count());//输出ap.usecount =1
	printf("bp.usecount = %d\n", bwp.use_count());//输出ap.usecount =1

}
int main()
{
	wchar_t ch = '中';
	char ch1 = '中';
	std::cout << ch1 <<  std::endl;
	std::wcout << ch << std::endl;
	//testPtr();
	//std::shared_ptr<B> b;
	//testRef(b);
	//std::cout << b->ptra.lock()->k << std::endl;
	return 0;
	for (float u = 0; u < 6.18; u += 0.01)
	{
		for (float v = 0; v < 1; v += 0.01)
		{
			std::cout << u << "  " << std::acos(v) << std::endl;
		}
	}
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
	delete val;
	val = nullptr;

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
