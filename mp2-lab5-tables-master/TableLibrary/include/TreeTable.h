#ifndef Tree_H
#define Tree_H

#include <utility>
#include <sstream>
#include <iostream>
#include "TreeNode.h"
#include "tableelement.h"

using namespace std;

// Класс "дерево"
class Tree
{
	TreeNode<TableElement>* root; // Корень
	Tree* table;
	
	// Добавление в дерево
	int _add(TreeNode<TableElement>* current, const TableElement& data, int count)
	{
		// Если пуст, то создание нового узла
		if (current == NULL)
		{
			current = new TreeNode<TableElement>(data);
			return count + 1;
		}
		else if (current->data < data)
		{
			if (current->right == NULL)
			{
				current->right = new TreeNode<TableElement>(data);
				return count + 1;
			}
			else
				return _add(current->right, data, count + 1);
		}
		else
		{
			if (current->left == NULL)
			{
				current->left = new TreeNode<TableElement>(data);
				return count + 1;
			}
			else
				return _add(current->left, data, count + 1);
		}
	}

	// Поиск по дереву
	pair<TreeNode<TableElement>*, int> _find(TreeNode<TableElement>* current,
		const TableElement& key, int count)
	{
		// Если текущий пуст или нашли ключ, то возвращаем текущий
		if (current == NULL || current->data == key)
			return pair<TreeNode<TableElement>*, int>(current, count + 1);
		// Иначе переход в левое или правое поддерево
		else if (current->data < key)
			return _find(current->right, key, count + 1);
		else
			return _find(current->left, key, count + 1);
	}

	bool _existsKey(TreeNode<TableElement>* current, const TableElement& te)
	{
		if (current == NULL)
			return false;
		else if (current->data.key() == te.key())
			return true;
		else if (current->data < te)
			return _existsKey(current->right, te);
		else
			return _existsKey(current->left, te);
	}

public:
	// Конструктор по умолчанию
	Tree()
	{
		root = nullptr;
		table = nullptr;
	}

	// Конструктор с параметром
	Tree(const TableElement& data)
	{
		root = new TreeNode<TableElement>(data);
		table = new Tree;
	}

	// Добавление данных
	auto add(const TableElement& data)
	{
		// Если корень пуст, создаем его
		if (root == NULL)
		{
			root = new TreeNode<TableElement>(data);
			return 1;
		}
		else
			return _add(root, data, 0);
	}

	// Поиск по ключу
	pair<TreeNode<TableElement>*, int> find(const TableElement& key)
	{
		return _find(root, key, 0);
	}

	bool existsKey(const TableElement& te)
	{
		return _existsKey(root, te);
		
	}

	// Получение значения по ключу
	TableElement get(const std::string& key)
	{
		// Ищем элемент по ключу
		auto result = find(TableElement(key, Polynomial()));
		cout << "Таблица Дерево - операций поиска: "
			<< result.second << "." << std::endl;
		// Если элемент найден, возвращаем его значение
		if (result.first != nullptr)
			return result.first->data;
		// Иначе возвращаем пустой элемент
		else
			return TableElement();
	}
	void add(const std::string& key, const Polynomial& p)
	{
		int count = table->add(TableElement(key, p));
		cout << "Таблица Дерево - операций добавления: 1 "
			<< count << std::endl;
	}
};

#endif // !Tree_H
