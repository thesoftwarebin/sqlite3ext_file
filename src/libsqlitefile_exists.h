/*
    Copyright 2025 by Andrea Rossetti <andrear1979@hotmail.com>

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LIBSQLITEFILE_EXISTS_H_
#define LIBSQLITEFILE_EXISTS_H_

	#include <sqlite3ext.h>
	void libsqlitefile_exists(sqlite3_context * context, int argc, sqlite3_value ** argv);

#endif /* LIBSQLITEFILE_EXISTS_H_ */
