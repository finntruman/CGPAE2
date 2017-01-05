//#include "Menu.h"
//#include "TextManager.h"
//
//Menu::Menu(GameManager &manager, SDL_Renderer &renderer, TextManager &textManager, std::vector<std::string> options, std::string font)
//	:p_manager(&manager), p_renderer(&renderer), p_textManager(&textManager), m_font(font), c_menuOptions(options), m_menuPosition(0)
//{
//	for (int i = 0; i < options.size(); i++)
//	{
//		p_textManager->CreateText(320, 100 + p_textManager->FontHeight(m_font) * i, c_menuOptions[i], m_font);
//	}
//}
//
//Menu::~Menu()
//{
//	if (p_renderer) p_renderer = nullptr;
//	if (p_manager) p_manager = nullptr;
//}
//
//void Menu::Update()
//{
//}