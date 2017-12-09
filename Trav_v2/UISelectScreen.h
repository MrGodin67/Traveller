#pragma once
#include "IUserInterface.h"
#include "Table.h"
#include "TextureLoader.h"
#include "UI.h"
class UISelectUser :
	public IUserInterface
{
protected:
	const int m_cellSize = 16;
	Table<UIPoint> m_grid;
	std::vector<std::unique_ptr<IUserInterface>> m_items;
	UITextBox* m_selectedTextBox = nullptr;
public:
	UISelectUser();
	UISelectUser(const int& posX, const int& posY, const int& width, const int& height);
	virtual ~UISelectUser();

	// Inherited via IUserInterface
	virtual UIReturn OnMouseClick(const std::size_t & x, const std::size_t & y) override;
	virtual UIReturn OnKeyPress(const unsigned char & key) override;
	virtual void Draw() override;
	virtual void Update(const float & dt) override;
	virtual IUserInterface& AddItem(IUserInterface* item, const int& row, const int& col);

	// Inherited via IUserInterface
	virtual UIReturn OnMouseMove(const std::size_t & x, const std::size_t & y) override;
};

