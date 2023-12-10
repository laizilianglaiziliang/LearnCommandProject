#pragma once
#include "Receiver_Array.h"
#include<optional>
#include <memory>
class Command
{
public:		
	int m_iPos;
	bool m_bCanRevert;
public:
	Command(int _pos) : m_iPos(_pos), m_bCanRevert(true)
	{
	}
	virtual ~Command(){}
	virtual bool  execute() = 0;
	virtual void* executeOther()
	{
		return nullptr;
	}
	virtual bool  undo() = 0;
	virtual bool  redo() = 0;
};
template <class T>
class AddCommand:public Command
{
private:
	std::shared_ptr<Receiver_Array<T>> m_Receiver_Array;
	T m_Val;
public:
	AddCommand() {}
	AddCommand(std::shared_ptr<Receiver_Array<T>> _receiver_Array, int _pos,const T& _val) :Command( _pos), m_Receiver_Array(_receiver_Array), m_Val(_val)
	{		
	}
	virtual ~AddCommand() 
	{
		//if (m_Receiver_Array)
		//{
		//	m_Receiver_Array->destory();
		//	m_Receiver_Array = nullptr;
		//}
	}
	bool execute() override
	{
		try
		{
			if (this->m_Receiver_Array->add(this->m_iPos, m_Val))
			{
				printf("  Add Success.");
				return true;
			}
			printf("  Add Fail.");
			return false;
		}
		catch(...)
		{
			printf("  Add Fail.");
			return false;
		}
		return true; 
	}
	virtual bool undo() override
	{
		try
		{
			if (this->m_Receiver_Array->del(this->m_iPos))
			{
				printf("  Undo Success.");
				return true;
			}
		}
		catch (...)
		{
		}
		printf("  Undo Fail.");
		return false;
	}
	virtual bool redo() override
	{
		if (execute())
		{
			printf("  Redo Success.");
			return true;
		}
		printf("  Redo Fail.");
		return false;
	}
};
template <class T>
class DelCommand :public Command
{
private:
	std::shared_ptr<Receiver_Array<T>>  m_Receiver_Array;
	T m_Val;
public:
	DelCommand() {}
	DelCommand(std::shared_ptr<Receiver_Array<T>>  _receiver_Array, int _pos) :Command(_pos), m_Receiver_Array(_receiver_Array)
	{
	}
	virtual ~DelCommand()
	{
		//if (m_Receiver_Array)
		//{
		//	m_Receiver_Array->destory();
		//	m_Receiver_Array = nullptr;
		//}
	}
	bool execute() override
	{
		try
		{
			std::optional<T> val = m_Receiver_Array->seek(m_iPos);
			if (val!=std::nullopt && this->m_Receiver_Array->del(this->m_iPos))
			{
				printf("  Del Success.");
				m_Val = val.value();
				return true;
			}
			printf("  Del Fail.");
			return false;
		}
		catch (...)
		{
			printf("  Del Fail.");
			return false;
		}
		return true;
	}
	virtual bool undo() override
	{
		try
		{
			if (this->m_Receiver_Array->add(this->m_iPos, m_Val))
			{
				printf("  Undo Success.");
				return true;
			}
		}
		catch (...)
		{
		}
		printf("  Undo Fail.");
		return false;
	}
	virtual bool redo() override
	{
		if (execute())
		{
			printf("  Redo Success.");
			return true;
		}
		printf("  Redo Fail.");
		return false;
	}
};
template <class T>
class ModifyCommand :public Command
{
private:
	std::shared_ptr<Receiver_Array<T>>  m_Receiver_Array;
	T m_Val;
public:
	ModifyCommand() {}
	ModifyCommand(std::shared_ptr<Receiver_Array<T>>  _receiver_Array, int _pos,const T& _val) :Command(_pos), m_Receiver_Array(_receiver_Array), m_Val(_val)
	{
	}
	virtual ~ModifyCommand()
	{
		//if (m_Receiver_Array)
		//{
		//	m_Receiver_Array->destory();
		//	m_Receiver_Array = nullptr;
		//}
	}
	bool execute() override
	{
		try
		{
			std::optional<T> val = this->m_Receiver_Array->seek(m_iPos);//判断m_iPos是合法的
			if (val != std::nullopt && this->m_Receiver_Array->modify(this->m_iPos, m_Val))
			{
				printf("  Modify Success.");
				m_Val = val.has_value();//用于undo redo
				return true;
			}			
			printf("  Modify Fail.");
			return false;
		}
		catch (...)
		{
			printf("  Modify Fail.");
			return false;
		}
		return true;
	}
	virtual bool undo() override
	{
		try
		{
			if (execute())
			{
				printf("  Undo Success.");
				return true;
			}
		}
		catch (...)
		{
		}
		printf("  Undo Fail.");
		return false;
	}
	virtual bool redo() override
	{
		if (execute())
		{
			printf("  Redo Success.");
			return true;
		}
		printf("  Redo Fail.");
		return false;
	}
};
template <class T>
class SeekCommand :public Command
{
private:
	std::shared_ptr<Receiver_Array<T>>  m_Receiver_Array;
public:
	SeekCommand():m_bCanRevert(false) {}
	SeekCommand(std::shared_ptr<Receiver_Array<T>>  _receiver_Array, int _pos) :Command(_pos), m_Receiver_Array(_receiver_Array)
	{
		m_bCanRevert = false;
		//, m_bCanRevert(false)
	}
	virtual ~SeekCommand()
	{
		//if (m_Receiver_Array)
		//{
		//	m_Receiver_Array->destory();
		//	m_Receiver_Array = nullptr;
		//}
	}
	bool execute() override
	{
		return true;
	}
	virtual void* executeOther() override
	{
		try
		{
			std::optional<T> val = m_Receiver_Array->seek(m_iPos);
			if (val == std::nullopt)
			{
				printf("  Seek Fail.");
				return nullptr;
			}
			printf("  Seek Success.");
			T* ret = new T();
			*ret = val.value();
			return ret;
		}
		catch (...)
		{
		}
		printf("  Seek Fail.");
		return nullptr;
	}
	virtual bool undo() override
	{
		printf("  Undo Fail.");
		return false;
	}
	virtual bool redo() override
	{
		printf("  Redo Fail.");
		return false;
	}
};