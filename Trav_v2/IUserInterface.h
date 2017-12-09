#pragma once


#define UI_TYPE_NONE 0
#define UI_TYPE_BUTTON 1
#define UI_TYPE_TEXTBOX 2
#define UI_TYPE_LISTBOX 3

#define UI_RETURN_ACTION_NONE 0
#define UI_RETURN_ACTION_EXIT 1
#define UI_RETURN_ACTION_START 2
#define UI_RETURN_ACTION_CONTINUE 3
#define UI_RETURN_ACTION_NEW_GAME 4
#define UI_RETURN_ACTION_RESUME 5
#define UI_RETURN_ACTION_BACK 6
#define UI_RETURN_ACTION_SELECTED 7
#define UI_RETURN_ACTION_USER_SELECTED 8

struct UIReturn
{
	int id = UI_TYPE_NONE;
	int action = UI_RETURN_ACTION_NONE;
	void* data = nullptr;
	UIReturn() = default;
	UIReturn(const int& id, const int& action)
		:id(id), action(action)
	{}
};
struct UIPoint
{
	int x;
	int y;
	UIPoint()
		:x(0), y(0)
	{}
	UIPoint(const int& x, const int& y)
		:x(x), y(y) 
	{}
};
struct UIRect : public D2D1_RECT_F
{
	UIRect() = default;
	UIRect(float l, float t, float r, float b)
	{
		left = l; top = t; right = r; bottom = b;
	}
	bool Contains(const std::size_t& x, const std::size_t& y) const
	{
		return y >= top && y <= bottom && x >= left && x <= right;
	}
};

struct UIColor : public D2D1_COLOR_F
{
	UIColor() = default;
	UIColor(float _r, float _g, float _b, float _a)
	{
		r = _r; g = _g; b = _b; a = _a;
	}
	void Fade(float& alpha) { a = alpha; }
};
class IUserInterface
{
protected:
	int m_Type = 0;
	int m_ReturnAction = 0;
	UIRect m_frame;
	bool   m_mouseOver = false;
	bool   m_selected = false;
	bool   m_drawFrame = false;
	bool   m_showHightlight = false;
	ID2D1Bitmap* m_image = nullptr;
	static UIColor m_mouseOverColor;
	static UIColor m_frameColor;
	static UIColor m_textColor;
public:
	IUserInterface();
	IUserInterface(const int& type, const int& returnAction);
	IUserInterface(IUserInterface& other)
	{
		*this = other;
	}
	virtual ~IUserInterface();
	static void SetColors(const UIColor& frame, const UIColor& mouseOver, const UIColor & text);
	virtual void SetImage(ID2D1Bitmap* image);
	virtual bool Selected()const ;
	virtual void Selected(const bool& val);
	virtual void DrawFrame(const bool& val);
	virtual void ShowHightlight(const bool& val);
	virtual UIReturn OnMouseClick(const std::size_t& x, const std::size_t& y) ;
	virtual UIReturn OnMouseMove(const std::size_t& x, const std::size_t& y) ;
	virtual UIReturn OnKeyPress(const unsigned char& key) { return UIReturn(); };
	virtual void Draw() {};
	virtual void Update(const float& dt) {};
	virtual void SetAnchor(const UIPoint& pos) {};
};

