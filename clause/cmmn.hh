/*~
 * Copyright (C) 2013, 2014, 2015 George Makrydakis <george@irrequietus.eu>
 *
 * This file is part of 'clause', a highly generic C++ meta-programming library,
 * subject to the terms and conditions of the Mozilla Public License v 2.0. If
 * a copy of the MPLv2 license text was not distributed with this file, you can
 * obtain it at: http://mozilla.org/MPL/2.0/.
 *
 * The 'clause' library is an experimental library in active development with
 * a source code repository at: https://github.com/irrequietus/clause.git and
 * issue tracker at https://github.com/irrequietus/clause/issues.
 *
 */

#ifndef _CLAUSE_CMNEXPR_HH_
#define _CLAUSE_CMNEXPR_HH_

namespace clause {
/*~
 * @desc Expanding a type to its member "iterator" type identifier.
 * @tprm T: type parameter type containing 'iterator' member type identifier.
 */
template<typename T>
using of_iterator = typename T::iterator;

} /* clause */

#endif /* _CLAUSE_CMNEXPR_HH_ */
