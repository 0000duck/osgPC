// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>



#ifdef _DEBUG
#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgUtild.lib")
#pragma comment(lib, "openThreadsd.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")
#else
#pragma comment(lib, "OpenThreads.lib")
#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgUtil.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")
#endif