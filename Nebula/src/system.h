/*
 * Copyright (C) 2025 The Layers Project
 *
 * This file is part of the Nebula application.
 *
 * Nebula is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nebula is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nebula. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>

#ifdef _WIN32
#include <windows.h>
#include <Lmcons.h>
#elif defined(__APPLE__)
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

inline std::string get_current_username()
{
#ifdef _WIN32
    WCHAR buffer[UNLEN + 1];
    DWORD buffer_len = UNLEN + 1;

    if (GetUserNameW(buffer, &buffer_len))
    {
        std::wstring wstr(buffer);
        return std::string(wstr.begin(), wstr.end());
    }
    else
    {
        return std::string("unknown");
    }

#elif defined(__APPLE__)
    // macOS and Unix-like implementation
    const char* username = getlogin(); // Try to get the username using getlogin()
    if (username)
    {
        return std::string(username);
    }
    else
    {
        // Fallback to using getpwuid() if getlogin() fails
        struct passwd* pw;
        uid_t uid = geteuid();

        if ((pw = getpwuid(uid)) != NULL)
        {
            return std::string(pw->pw_name);
        }
        else
        {
            return std::string("unknown");
        }
    }
#endif
}

#endif // !SYSTEM_H
