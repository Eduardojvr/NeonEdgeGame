#ifndef ITENSMANAGER_H
#define ITENSMANAGER_H

#include <vector>
#include <unordered_map>

#include "Sprite.h"

#define HOT_BAR_SIZE 3

class ItensManager
{
public:
	struct itemType
	{
		Sprite *sp;
		bool active;
		unsigned int count;
		std::string name;
		std::string description;
	};

	ItensManager();
	std::vector<itemType> GetActiveItems();
	std::vector<itemType> GetItems();
	itemType GetItem(std::string name);
	void AddItem(int id);
	bool IsActive(std::string name);
	bool IsHot(std::string name);
	void SetActive(std::string name, bool active);
	void ConsumeItem(int hotItensPos);
	void Render();
	void Update();
	std::string hotItens[HOT_BAR_SIZE];
//private:
	std::unordered_map<std::string,itemType> itens;
};

#endif // ITENSMANAGER_H
