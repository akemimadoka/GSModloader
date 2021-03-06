#pragma once
#include "natType.h"
#include <Windows.h>
#include <vector>

namespace natUtil
{
	///	@brief		格式化字符串
	///	@warning	非类型安全
	///	@param[in]	str		字符串格式
	nTString FormatString(ncTStr lpStr, ...);
	nTString FormatStringv(ncTStr lpStr, const va_list vl);

	///	@brief	获得本地时间
	///	@return	包含时间信息的字符串
	inline nTString GetSysTime()
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		return FormatString(_T("%04d/%02d/%02d %02d:%02d:%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	}

	///	@brief	string转wstring
	inline std::wstring C2Wstr(std::string const& str)
	{
		return std::wstring(str.begin(), str.end());
	}
	///	@brief	wstring转string
	inline std::string W2Cstr(std::wstring const& str)
	{
		return std::string(str.begin(), str.end());
	}
	
	///	@brief	多字节转Unicode
	std::wstring MultibyteToUnicode(ncStr Str, nuInt CodePage = CP_INSTALLED);
	///	@brief	宽字符转多字节
	std::string WidecharToMultibyte(ncWStr Str, nuInt CodePage = CP_INSTALLED);

	///	@brief	获得资源字符串
	///	@param[in]	ResourceID	资源ID
	///	@param[in]	hInstance	实例句柄，默认为NULL
	nTString GetResourceString(DWORD ResourceID, HINSTANCE hInstance = NULL);

	///	@brief	获得资源数据
	///	@param[in]	ResourceID	资源ID
	///	@param[in]	lpType		资源类型
	///	@param[in]	hInstance	实例句柄，默认为NULL
	std::vector<nByte> GetResourceData(DWORD ResourceID, ncTStr lpType, HINSTANCE hInstance = NULL);

	///	@brief	字符串分割函数
	///	@param[in]	str			要分割的字符串
	///	@param[in]	pattern		分割字符
	///	@param[out]	container	存储结果的容器，应实现emplace_back，接受参数为 字符串, 字符起始位置, 字符串长度
	template <typename Char_T, typename Container>
	void split(std::basic_string<Char_T> const& str, std::basic_string<Char_T> const& pattern, Container& container)
	{
		typedef typename std::basic_string<Char_T>::size_type pos_t;
		const auto size = str.size();

		pos_t pos = 0;

		for (pos_t i = 0u; i < size; ++i)
		{
			auto currentchar = str[i];
			for (auto c : pattern)
			{
				if (currentchar == c)
				{
					container.emplace_back(str, pos, i - pos);

					pos = i + 1;
					break;
				}
			}
		}

		if (pos != size)
		{
			container.emplace_back(str, pos, size - pos);
		}
	}
}