#pragma once
#include <stack>
#include <memory>
class Command;
class CommandMgr
{
private:
	std::stack<std::shared_ptr<Command>> m_stkUndo;//undoջ
	std::stack<std::shared_ptr<Command>> m_stkRedo;//redoջ
public:
	CommandMgr();
	~CommandMgr();
	void execute(std::shared_ptr<Command> command) noexcept;
	void* executeOther(std::shared_ptr<Command> command)noexcept;
	void undo() noexcept;
	void redo() noexcept;
};

