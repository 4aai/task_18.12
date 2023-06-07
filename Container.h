#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class User {
	std::string _name;
	std::string _login;
	std::string _pass;

public:
	User(std::string name, std::string login, std::string pass) :_name(name), _login(login), _pass(pass) {}
	User() = default;
	void printUser() const
	{
		std::cout << std::setw(10) << _name;
		std::cout << std::setw(10) << _login;
		std::cout << std::setw(10) << _pass; 
		std::cout << std::endl;
	}
	friend std::fstream& operator >>(std::fstream& is, User& obj);
	friend std::ostream& operator <<(std::ostream& os, const User& obj);
	
};

std::fstream& operator >>(std::fstream& is, User& obj)
{
	is >> obj._name;
	is >> obj._login;
	is >> obj._pass;
	return is;
}
std::ostream& operator <<(std::ostream& os, const User& obj)
{
	os << obj._name;
	os << ' ';
	os << obj._login;
	os << ' ';
	os << obj._pass;
	return os;
}


class Message {

	std::string _sender;
	std::string _receiver;
	std::string _text;


public:
	Message(const std::string& sender, const std::string& receiver, const std::string& text) :
		_sender{ sender }, _receiver{ receiver }, _text{ text } {}
	Message() = default;
	friend std::fstream& operator >>(std::fstream& is, Message& obj);
	friend std::ostream& operator <<(std::ostream& os, const Message& obj);
	void printMessage() const
	{
		std::cout << std::setw(10) << _sender;
		std::cout << std::setw(10) << _receiver;
		std::cout << std::setw(27) << _text;
		std::cout << std::endl;
	}
};

std::fstream& operator >>(std::fstream& is, Message& obj)
{
	is >> obj._sender;
	is >> obj._receiver;
	is >> obj._text;
	return is;
}
std::ostream& operator <<(std::ostream& os, const Message& obj)
{
	os << obj._sender;
	os << ' ';
	os << obj._receiver;
	os << ' ';
	os << obj._text;
	return os;
}


class Container
{

public:
	Container() {}
	~Container() {}

	void addMessasage(Message message)
	{
		_messages.emplace_back(message);
	}
	void addUser(User user)
	{
		_users.emplace_back(user);
	}

	void saveStateToFiles() const
	{
		// users
		if (!_users.empty())
		{
			std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::out);
			if (!user_file)
				user_file = std::fstream("users.txt", std::ios::in | std::ios::out | std::ios::trunc);
			
			fs::permissions("users.txt",
				fs::perms::group_write | 
				fs::perms::others_all,
				fs::perm_options::remove);

			if (user_file) {
				for (auto& user : _users)
				{
					user_file << user << std::endl;
				}
			}
			else
			{
				std::cout << "Could not open file users.txt !\n";
			}
		}

		// messages
		if (!_messages.empty())
		{
			std::fstream message_file = std::fstream("messages.txt", std::ios::in | std::ios::out);
			if (!message_file)
				message_file = std::fstream("messages.txt", std::ios::in | std::ios::out | std::ios::trunc);

			fs::permissions("messages.txt",
				fs::perms::group_write |
				fs::perms::others_all,
				fs::perm_options::remove);

			if (message_file) {
				for (auto& message : _messages)
				{
					message_file << message << std::endl;
				}
			}
			else
			{
				std::cout << "Could not open file messages.txt !\n";
			}
		}
	}

	void loadStateFromFiles()
	{
		// users
		std::fstream user_file = std::fstream("users.txt", std::ios::in | std::ios::out);
		if (user_file) {
			_users.clear();
			while (!user_file.eof())
			{
				User tmp;
				user_file >> tmp;
				addUser(tmp);
			}
		}
		else
		{
			std::cout << "Could not open file users.txt !\n";
		}

		// messages
		std::fstream message_file = std::fstream("messages.txt", std::ios::in | std::ios::out);
		if (message_file) {
			_messages.clear();
			while (!message_file.eof())
			{
				Message tmp;
				message_file >> tmp;
				addMessasage(tmp);
			}
		}
		else
		{
			std::cout << "Could not open file messages.txt !\n";
		}
	}

	void printState() const
	{
		// users
		if (!_users.empty())
		{
			std::cout << std::setw(10) << "name";
			std::cout << std::setw(10) << "login";
			std::cout << std::setw(10) << "pass";
			std::cout << std::endl;
			std::cout << "------------------------------------------" << std::endl;
			for (auto& user : _users)
			{
				user.printUser();
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "users is empty!\n";
		}
		
		// messages
		if (!_messages.empty())
		{
			std::cout << std::setw(10) << "sender";
			std::cout << std::setw(10) << "receiver";
			std::cout << std::setw(10) << "text";
			std::cout << std::endl;
			std::cout << "------------------------------------------" << std::endl;
			for (auto& message : _messages)
			{
				message.printMessage();
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "messages is empty!\n";
		}
	}

private:
	std::vector<Message> _messages;
	std::vector<User> _users;
};

