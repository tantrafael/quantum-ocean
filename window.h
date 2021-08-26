#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <windows.h>


class Window
{
	public:
		Window();
		Window( HINSTANCE hInst, HWND hWnd, int cols, int rows );
		~Window();

		HINSTANCE hInst();
		HWND	  hWnd();
		int		  cols();
		int		  rows();
		float	  width();
		float	  height();

	protected:
		HINSTANCE m_hInst;
		HWND	  m_hWnd;
		int		  m_cols;
		int		  m_rows;
		float	  m_width;
		float	  m_height;
};


#endif