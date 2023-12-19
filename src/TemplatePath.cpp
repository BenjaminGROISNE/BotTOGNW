#include "TemplatePath.h"


Tnode::Tnode(std::string id) {
	this->id = id;
	clear();
}
Tnode::Tnode(Tnode* tn) {
	setPrevious(tn->previous);
	setNext(tn->next);
}
void Tnode::addPrevious(Tnode* tn) {
	previous.push_back(tn);
}
void Tnode::addNext(Tnode* tn) {
	next.push_back(tn);
}
void Tnode::setPrevious(std::vector<Tnode*> tprevious) {
	previous = tprevious;
}
void Tnode::setNext(std::vector<Tnode*> tnext) {
	next = tnext;
}
void Tnode::clearPrevious() {
	previous.clear();
}
void Tnode::clearNext() {
	previous.clear();
}
void Tnode::clear() {
	clearPrevious();
	clearNext();
}
void Tnode::setId(std::string id) {
	this->id = id;
}
std::string Tnode::getId() const {
	return id;
}
std::vector<Tnode*> Tnode::getPrevious() {
	return previous;
}
std::vector<Tnode*> Tnode::getNext() {
	return next;
}

TemplatePath::TemplatePath()
{
	path.clear();
}

TemplatePath::TemplatePath(Tnode* tn)
{
	path.push_back(tn);
}

void TemplatePath::clearPath()
{
	path.clear();
}

void TemplatePath::insertNode(Tnode* tn)
{
	path.push_back(tn);
}

Tnode* TemplatePath::findNode(std::string id)
{
	auto temp = std::find_if(path.begin(), path.end(),[id](const Tnode* node) { return node->getId() == id; });
	if (temp != path.end()) {
		return *temp;
	}
	return nullptr;
}

std::string TemplatePath::findTemplate(Tnode* te)
{
	auto temp=std::find(path.begin(), path.end(), te);
	if (temp != path.end()) {
		return te->getId();
	}
	return std::string();
}

