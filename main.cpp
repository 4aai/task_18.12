#include <fstream>
#include <iostream>
#include <vector>
#include "Container.h"

int main() {

	// test container
	Container box;

	box.addUser(User("name",  "login",  "passwd"));
	box.addUser(User("name1", "login1", "passwd"));
	box.addUser(User("name2", "login2", "passwd"));
	box.addUser(User("name3", "login3", "passwd"));
	box.addUser(User("name4", "login4", "passwd"));

	box.addMessasage(Message("login1", "login4", "message_without_spaces"));
	box.addMessasage(Message("login4", "login1", "message_without_spaces1"));
	box.addMessasage(Message("login3", "login4", "message_without_spaces2"));
	box.addMessasage(Message("login1", "login",  "message_without_spaces3"));
	box.addMessasage(Message("login",  "login2", "message_without_spaces4"));

	box.loadStateFromFiles();
	box.printState();
	box.saveStateToFiles();

}