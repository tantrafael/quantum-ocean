#include "Window.h"


Window::Window()
{}

Window::Window( HINSTANCE hInst, HWND hWnd, int cols, int rows )
{
	m_hInst  = hInst;
	m_hWnd   = hWnd;
	m_cols   = cols;
	m_rows   = rows;
	m_width  = 1.0f;
	m_height = rows * m_width / m_cols;
}

Window::~Window()
{}

HINSTANCE Window::hInst()  { return m_hInst;  }
HWND	  Window::hWnd()   { return m_hWnd;   }
int		  Window::cols()   { return m_cols;   }
int		  Window::rows()   { return m_rows;   }
float	  Window::width()  { return m_width;  }
float	  Window::height() { return m_height; }
