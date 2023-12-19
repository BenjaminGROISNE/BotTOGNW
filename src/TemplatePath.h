#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include "fopencv.h"

enum poswipe { samex, samey, rightx, leftx, upy, downy };
enum pos { N, S, W, E, NW, NE, SW, SE };
enum state { disconnect, block, wait };
enum Orders { noOrd, K, M, B, T };
enum day { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
enum Action { Click, Swipe };

struct RebootException : public std::exception {};
struct EndMacroException : public std::exception {};

struct Digit {
	int dig;
	Coords Cnb;
	Digit() {
		dig = 0;
		Cnb.x = Cnb.y = 0;
	}
};

struct Unit {
	std::string nameunit;
	Orders Ord;
	Unit() {
		nameunit.clear();
		Ord = Orders::noOrd;
	}
	Unit(std::string name, Orders ord) {
		nameunit = name;
		Ord = ord;
	}
};

struct Number {
	Unit U;
	long double nb;
	bool integer, decimal;
	bool T, B, M, K;
	std::vector<Digit> digits;
	int dotposition;
	Number() {
		nb = dotposition = 0;
		T = B = M = K = integer = decimal = false;
		digits.clear();
	}
};

struct CustomNumber {
	Number number;
	int pos;
	CustomNumber() {
		number.digits.clear();
		pos = 0;
	}
};

struct Popup: Template {
	state action;
	Popup() :Template() {
		action = state::wait;
	}
	Popup(Template T) : Template(T) {
		action = state::wait;
	}
	Popup(std::string pop):Template(pop) {
		action = state::wait;
	}
	Popup(std::string pop, state c):Template(pop) {
		action = c;
	}
	Popup(std::string pop, state c, typeMat t):Template(pop,t) {
		action = c;
	}
};

struct Tnode {

	Tnode(std::string id = "");
	Tnode(Tnode* tn);
	void addPrevious(Tnode* tn);
	void addNext(Tnode* tn);
	void setPrevious(std::vector<Tnode*> tprevious);
	void setNext(std::vector<Tnode*> tnext);
	void clearPrevious();
	void clearNext();
	void clear();
	void setId(std::string id);
	std::string getId()const;
	std::vector<Tnode*> getPrevious();
	std::vector<Tnode*> getNext();
	private:
		std::vector<Tnode*> previous;
		std::vector<Tnode*> next;
		std::string id;
};


class TemplatePath {
public:
	TemplatePath();
	TemplatePath(Tnode* tn);
	std::vector<Tnode*> path;
	void clearPath();
	void insertNode(Tnode* tn);
	Tnode* findNode(std::string te);
	std::string findTemplate(Tnode*tn);
};
