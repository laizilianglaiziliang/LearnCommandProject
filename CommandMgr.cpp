#include "CommandMgr.h"
#include "Command.h"
CommandMgr::CommandMgr()
{
}
CommandMgr::~CommandMgr()
{
	while (!m_stkRedo.empty())
	{
		m_stkRedo.pop();
	}
	while (!m_stkUndo.empty())
	{		
		m_stkUndo.pop();
	}
}
void CommandMgr::execute(std::shared_ptr<Command> command) noexcept
{
	if (command->execute())
	{
		printf("  Command Execute Success\n\n");
		if (command->m_bCanRevert)
		{
			m_stkUndo.push(command);
		}
	}
	else
	{
		printf("  Command Execute Fail\n\n");
	}
}

void* CommandMgr::executeOther(std::shared_ptr<Command> command) noexcept
{
	void* val = command->executeOther();
	if (val)
	{
		printf("  Command Execute Success\n\n");
		if (command->m_bCanRevert)
		{
			m_stkUndo.push(command);
		}
		return val;
	}
	else
	{
		printf("  Command Execute Fail\n\n");
	}
	return nullptr;
}

void CommandMgr::undo() noexcept
{
	if (m_stkUndo.empty())
	{
		return;
	}
	std::shared_ptr<Command> command = m_stkUndo.top();
	if (command && command->m_bCanRevert && command->undo())
	{		
		m_stkUndo.pop();
		m_stkRedo.push(command);
		printf("  Command Undo Success\n\n");
	}
	else
	{
		printf("  Command Undo Fail\n\n");
	}
}

void CommandMgr::redo() noexcept
{
	if (m_stkRedo.empty())
	{
		return;
	}
	std::shared_ptr<Command> command = m_stkRedo.top();
	if (command && command->m_bCanRevert && command->redo())
	{
		m_stkUndo.push(command);
		printf("  Command Redo Success\n\n");
	}
	else
	{
		printf("  Command Redo Fail\n\n");
	}
}
